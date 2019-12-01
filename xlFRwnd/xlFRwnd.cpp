#include "stdafx.h"
#include "debugtrace.h"
#include "helpers.h"
#include "multimon.h"
#include "events.h"

//#ifdef _DEBUG
//#define DBGTRACE(x) OutputDebugString(_T(x))
//#define DBGTRACEW(x) OutputDebugStringW(x)
//#else
//#define DBGTRACE(x)
//#define DBGTRACEW(x)
//#endif


extern "C" IMAGE_DOS_HEADER __ImageBase;

HWINEVENTHOOK g_hWinEventHook;

IDispatch* g_pApplication; //LONG g_AppID;//Excel=0, Word=1
HWND g_hFRWnd;
HWND g_hwXLMain;
CRect g_frDlgRect;

#define SWP_XLFRDLG_FLAGS (SWP_DRAWFRAME | SWP_FRAMECHANGED | SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define APPWNDCLASSNAME  _T("bosa_sdm_XL9")

//https://docs.microsoft.com/en-us/windows/win32/winauto/event-constants
const DWORD g_arrWinEvents[] = {
	EVENT_OBJECT_CREATE
	//,EVENT_OBJECT_DESTROY,
	,EVENT_OBJECT_SHOW
	,EVENT_OBJECT_HIDE
	//,EVENT_OBJECT_REORDER
	//,EVENT_SYSTEM_FOREGROUND
	//,EVENT_OBJECT_LOCATIONCHANGE
	//,EVENT_OBJECT_STATECHANGE
};

//https://solarianprogrammer.com/2016/11/28/cpp-passing-c-style-array-with-size-information-to-function/
template <class T, size_t N> T GetArrayMin(const T (&arr)[N])
{
	T m = arr[0];
	size_t i;
	for (i = 1; i < N; i++)
	{
		if (arr[i] < m) m = arr[i];
	}
return m;
};
template <class T, size_t N> T GetArrayMax(const T (&arr)[N])
{
	T m = arr[0];
	size_t i;
	for (i = 1; i < N; i++)
	{
		if (arr[i] > m) m = arr[i];
	}
return m;
};

BOOL IsAppWindowClass(HWND hw)
{
	TCHAR strBuf[256];
	return ((GetClassName(hw, strBuf, 256) == (_countof(APPWNDCLASSNAME)-1) ) && (lstrcmp(strBuf, APPWNDCLASSNAME) == 0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CALLBACK WinEventProcCallback(HWINEVENTHOOK hook, DWORD dwEvent, HWND hwnd,
								   LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime)
{
	UNREFERENCED_PARAMETER(hook);
	UNREFERENCED_PARAMETER(idChild);
	UNREFERENCED_PARAMETER(dwEventThread);
	UNREFERENCED_PARAMETER(dwmsEventTime);

	HWND hwFR, hwST1, hwST2;
	CRect rc, rcClient;
	VARIANT vtHwnd;
	VariantInit(&vtHwnd);

	if (idObject == OBJID_WINDOW)
	{
		switch (dwEvent)
		{
			case EVENT_OBJECT_SHOW: //earliest event that won't change our custom size/position
			if (IsAppWindowClass(hwnd) &&
				(FindWindowEx(hwnd, NULL, L"EDTBX", NULL) &&
				( ((hwFR = FindWindowEx(hwnd, NULL, L"XLTFRCLASS", NULL)) != NULL) && 
				FindWindowEx(hwFR, NULL, L"SysListView32", NULL)) &&
				( ((hwST1 = FindWindowEx(hwnd, NULL, L"XLTFSTATCLASS", NULL)) != NULL) && 
				((hwST2 = FindWindowEx(hwST1, NULL, L"msctls_statusbar32", NULL)) != NULL) ) ))
				{
					DBGTRACE("EVENT_OBJECT_SHOW <bosa_sdm_XL9> g_hFRWnd=0x%x\n", g_hFRWnd);
					if (!IsWindowVisible(hwnd)) return;
					if (!GetWindowRect(hwnd, g_frDlgRect)) return;
					if FAILED(AutoWrap(DISPATCH_PROPERTYGET, &vtHwnd, g_pApplication, L"Hwnd", 0)) return;
					g_hwXLMain = (HWND)vtHwnd.lVal;
					g_hFRWnd = hwnd;
					
					if (CenterRectToWindow(g_frDlgRect, g_hwXLMain))
					{
						g_frDlgRect.bottom += (LONG)(g_frDlgRect.Height()*0.618);//golden ratio
						SetWindowPos(g_hFRWnd, NULL, g_frDlgRect.left, g_frDlgRect.top, g_frDlgRect.Width(), g_frDlgRect.Height(), SWP_XLFRDLG_FLAGS);

						if (GetClientRect(g_hFRWnd, rcClient) && GetWindowRect(hwST2, &rc))
						{
							rc.top = rcClient.Height() - rc.Height();
							rc.bottom = rcClient.Height();
							rc.left = 0;
							rc.right = rcClient.Width();

							SetWindowPos(hwST1, NULL, rc.left, rc.top, rc.Width(), rc.Height(), SWP_XLFRDLG_FLAGS);
							SetWindowPos(hwST2, NULL, rc.left, rc.top, rc.Width(), rc.Height(), SWP_XLFRDLG_FLAGS);
						}

					}

				}

			break;
			case EVENT_OBJECT_HIDE: //dialog is destroyed when closed (not just hidden)
				if (g_hFRWnd != hwnd) return;
				g_hFRWnd = NULL;
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
STDAPI Connect(IDispatch *pApplication)
{
	if (pApplication==NULL) return E_INVALIDARG;
	HRESULT hr=S_OK;

	_ASSERTE(g_pApplication == NULL);
	_ASSERTE(g_hFRWnd == NULL);

	if (g_pApplication == NULL)
	{
		g_pApplication = pApplication;
		g_pApplication->AddRef();
#ifdef _DEBUG
		{UINT pctinfo;
		DBGTRACE("GetTypeInfoCount=%d\n",g_pApplication->GetTypeInfoCount(&pctinfo));}
#endif
		DBGTRACE("xlFRwnd::Connect\n");
	}
	else hr = ERROR_ALREADY_ASSIGNED;

	if SUCCEEDED(hr)
	{
		if (g_hWinEventHook == NULL)
		{
			g_hWinEventHook = SetWinEventHook(GetArrayMin(g_arrWinEvents),GetArrayMax(g_arrWinEvents), (HINSTANCE)&__ImageBase,
												WinEventProcCallback, GetCurrentProcessId(), 0, WINEVENT_INCONTEXT);
			DBGTRACE("xlFRwnd::SetWinEventHook\n");
		}
		else {hr = ERROR_ALREADY_EXISTS; DBGTRACE("ERROR_ALREADY_EXISTS\n");}

	}
return hr;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
STDAPI Disconnect()
{
	_ASSERTE(g_hWinEventHook);
	_ASSERTE(g_pApplication);

	if (g_hWinEventHook)
	{
		UnhookWinEvent(g_hWinEventHook);
		g_hWinEventHook = NULL;
		g_hFRWnd = NULL;
		DBGTRACE("xlFRwnd::UnhookWinEvent\n");
	}

	if (g_pApplication)
	{
		g_pApplication->Release();
		g_pApplication = NULL;
		DBGTRACE("xlFRwnd::Disconnect\n");
	}
return S_OK;
}