#ifndef _MULTIMON_67D8181A_3E50_4D18_B406_34D6DB6113DE_
#define _MULTIMON_67D8181A_3E50_4D18_B406_34D6DB6113DE_

#define MONITOR_CENTER     0x0001        // center rect to monitor 
#define MONITOR_CLIP     0x0000        // clip rect to monitor 
#define MONITOR_WORKAREA 0x0002        // use monitor work area 
#define MONITOR_AREA     0x0000        // use monitor entire area 

// 
//  ClipOrCenterRectToMonitor 
// 
//  The most common problem apps have when running on a 
//  multimonitor system is that they "clip" or "pin" windows 
//  based on the SM_CXSCREEN and SM_CYSCREEN system metrics. 
//  Because of app compatibility reasons these system metrics 
//  return the size of the primary monitor. 
// 
//  This shows how you use the multi-monitor functions 
//  to do the same thing. 
// 
BOOL ClipOrCenterRectToMonitor(LPRECT prc, UINT flags)
{
    HMONITOR hMonitor;
    MONITORINFO mi;
    RECT        rc;
    int         w = prc->right  - prc->left;
    int         h = prc->bottom - prc->top;

    // 
    // get the nearest monitor from the passed rect. 
    // 
    hMonitor = MonitorFromRect(prc, MONITOR_DEFAULTTONEAREST);
	if (hMonitor==NULL) return FALSE;
    // 
    // get the work area or entire monitor rect. 
    // 
    mi.cbSize = sizeof(mi);
    if (!GetMonitorInfo(hMonitor, &mi)) return FALSE;

    if (flags & MONITOR_WORKAREA)
        rc = mi.rcWork;
    else
        rc = mi.rcMonitor;

    // 
    // center or clip the passed rect to the monitor rect 
    // 
    if (flags & MONITOR_CENTER)
    {
        prc->left   = rc.left + (rc.right  - rc.left - w) / 2;
        prc->top    = rc.top  + (rc.bottom - rc.top  - h) / 2;
        prc->right  = prc->left + w;
        prc->bottom = prc->top  + h;
    }
    else
    {
        prc->left   = max(rc.left, min(rc.right-w,  prc->left));
        prc->top    = max(rc.top,  min(rc.bottom-h, prc->top));
        prc->right  = prc->left + w;
        prc->bottom = prc->top  + h;
    }
return TRUE;
}

BOOL ClipOrCenterWindowToMonitor(HWND hwnd, UINT flags)
{
    RECT rc;
    if (!GetWindowRect(hwnd, &rc)) return FALSE;
    if (!ClipOrCenterRectToMonitor(&rc, flags))	return FALSE;
	return SetWindowPos(hwnd, NULL, rc.left, rc.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

#endif//_MULTIMON_67D8181A_3E50_4D18_B406_34D6DB6113DE_
