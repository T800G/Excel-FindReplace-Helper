#ifndef _HELPERS_9EF22F0D_46AB_423F_BA5A_D1BD482453D1_
#define _HELPERS_9EF22F0D_46AB_423F_BA5A_D1BD482453D1_

//
//   FUNCTION: AutoWrap(int, VARIANT*, IDispatch*, LPOLESTR, int,...)
//   PURPOSE: Automation helper function. It simplifies most of the low-level 
//      details involved with using IDispatch directly. Feel free to use it 
//      in your own implementations. One caveat is that if you pass multiple 
//      parameters, they need to be passed in reverse-order.
//   PARAMETERS:
//      * autoType - Could be one of these values: DISPATCH_PROPERTYGET, 
//      DISPATCH_PROPERTYPUT, DISPATCH_PROPERTYPUTREF, DISPATCH_METHOD.
//      * pvResult - Holds the return value in a VARIANT.
//      * pDisp - The IDispatch interface.
//      * ptName - The property/method name exposed by the interface.
//      * cArgs - The count of the arguments.
//   RETURN VALUE: An HRESULT value indicating whether the function succeeds or not.
//   EXAMPLE: 
//      AutoWrap(DISPATCH_METHOD, NULL, pDisp, L"call", 2, parm[1], parm[0]);
//
HRESULT AutoWrap(WORD autoType, VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName, int cArgs...)
{
	// Begin variable-argument list
	va_list marker;
	va_start(marker, cArgs);

	if (!pDisp) return E_INVALIDARG;

	// Variables used
	DISPPARAMS dp = { NULL, NULL, 0, 0 };
	DISPID dispidNamed = DISPID_PROPERTYPUT;
	DISPID dispID;
	HRESULT hr;

	// Get DISPID for name passed
	hr = pDisp->GetIDsOfNames(IID_NULL, &ptName, 1, /*LOCALE_USER_DEFAULT*/ LOCALE_SYSTEM_DEFAULT, &dispID);
	if (FAILED(hr))
	{
//#ifdef _DEBUG
		OutputDebugString(_T("AutoWrap::IDispatch->GetIDsOfNames failed\n"));
		_com_error err(hr);
		OutputDebugString(err.ErrorMessage()); OutputDebugString(_T("\n"));
//#endif//_DEBUG
		return hr;
	}

	// Allocate memory for arguments
	VARIANT *pArgs = new VARIANT[cArgs + 1];
	// Extract arguments...
	for(int i=0; i < cArgs; i++)
	{
		pArgs[i] = va_arg(marker, VARIANT);
	}

	// Build DISPPARAMS
	dp.cArgs = cArgs;
	dp.rgvarg = pArgs;

	// Handle special-case for property-puts
	if (autoType & DISPATCH_PROPERTYPUT)
	{
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
	}

	// Make the call
	hr = pDisp->Invoke(dispID, IID_NULL, /*LOCALE_USER_DEFAULT*/ LOCALE_SYSTEM_DEFAULT, autoType, &dp, pvResult, NULL, NULL);
	if FAILED(hr) 
	{
//#ifdef _DEBUG
		OutputDebugString(_T("AutoWrap::IDispatch->Invoke failed\n"));
		_com_error err(hr);
		OutputDebugString(err.ErrorMessage()); OutputDebugString(_T("\n"));
//#endif//_DEBUG
		return hr;
	}

	// End variable-argument section
	va_end(marker);
	delete[] pArgs;
return hr;
}

//////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

#ifndef __ATLMISC_H__  //helper classes from WTL

// forward declarations
class CSize;
class CPoint;
class CRect;

///////////////////////////////////////////////////////////////////////////////
// CSize - Wrapper for Windows SIZE structure.

class CSize : public SIZE
{
public:
// Constructors
	CSize()
	{
		cx = 0;
		cy = 0;
	}

	CSize(int initCX, int initCY)
	{
		cx = initCX;
		cy = initCY;
	}

	CSize(SIZE initSize)
	{
		*(SIZE*)this = initSize;
	}

	CSize(POINT initPt)
	{
		*(POINT*)this = initPt;
	}

	CSize(DWORD dwSize)
	{
		cx = (short)LOWORD(dwSize);
		cy = (short)HIWORD(dwSize);
	}

// Operations
	BOOL operator ==(SIZE size) const
	{
		return (cx == size.cx && cy == size.cy);
	}

	BOOL operator !=(SIZE size) const
	{
		return (cx != size.cx || cy != size.cy);
	}

	void operator +=(SIZE size)
	{
		cx += size.cx;
		cy += size.cy;
	}

	void operator -=(SIZE size)
	{
		cx -= size.cx;
		cy -= size.cy;
	}

	void SetSize(int CX, int CY)
	{
		cx = CX;
		cy = CY;
	}

// Operators returning CSize values
	CSize operator +(SIZE size) const
	{
		return CSize(cx + size.cx, cy + size.cy);
	}

	CSize operator -(SIZE size) const
	{
		return CSize(cx - size.cx, cy - size.cy);
	}

	CSize operator -() const
	{
		return CSize(-cx, -cy);
	}

// Operators returning CPoint values
	CPoint operator +(POINT point) const;
	CPoint operator -(POINT point) const;

// Operators returning CRect values
	CRect operator +(const RECT* lpRect) const;
	CRect operator -(const RECT* lpRect) const;
};


///////////////////////////////////////////////////////////////////////////////
// CPoint - Wrapper for Windows POINT structure.

class CPoint : public POINT
{
public:
// Constructors
	CPoint()
	{
		x = 0;
		y = 0;
	}

	CPoint(int initX, int initY)
	{
		x = initX;
		y = initY;
	}

	CPoint(POINT initPt)
	{
		*(POINT*)this = initPt;
	}

	CPoint(SIZE initSize)
	{
		*(SIZE*)this = initSize;
	}

	CPoint(DWORD dwPoint)
	{
		x = (short)LOWORD(dwPoint);
		y = (short)HIWORD(dwPoint);
	}

// Operations
	void Offset(int xOffset, int yOffset)
	{
		x += xOffset;
		y += yOffset;
	}

	void Offset(POINT point)
	{
		x += point.x;
		y += point.y;
	}

	void Offset(SIZE size)
	{
		x += size.cx;
		y += size.cy;
	}

	BOOL operator ==(POINT point) const
	{
		return (x == point.x && y == point.y);
	}

	BOOL operator !=(POINT point) const
	{
		return (x != point.x || y != point.y);
	}

	void operator +=(SIZE size)
	{
		x += size.cx;
		y += size.cy;
	}

	void operator -=(SIZE size)
	{
		x -= size.cx;
		y -= size.cy;
	}

	void operator +=(POINT point)
	{
		x += point.x;
		y += point.y;
	}

	void operator -=(POINT point)
	{
		x -= point.x;
		y -= point.y;
	}

	void SetPoint(int X, int Y)
	{
		x = X;
		y = Y;
	}

// Operators returning CPoint values
	CPoint operator +(SIZE size) const
	{
		return CPoint(x + size.cx, y + size.cy);
	}

	CPoint operator -(SIZE size) const
	{
		return CPoint(x - size.cx, y - size.cy);
	}

	CPoint operator -() const
	{
		return CPoint(-x, -y);
	}

	CPoint operator +(POINT point) const
	{
		return CPoint(x + point.x, y + point.y);
	}

// Operators returning CSize values
	CSize operator -(POINT point) const
	{
		return CSize(x - point.x, y - point.y);
	}

// Operators returning CRect values
	CRect operator +(const RECT* lpRect) const;
	CRect operator -(const RECT* lpRect) const;
};


///////////////////////////////////////////////////////////////////////////////
// CRect - Wrapper for Windows RECT structure.

class CRect : public RECT
{
public:
// Constructors
	CRect()
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}

	CRect(int l, int t, int r, int b)
	{
		left = l;
		top = t;
		right = r;
		bottom = b;
	}

	CRect(const RECT& srcRect)
	{
		::CopyRect(this, &srcRect);
	}

	CRect(LPCRECT lpSrcRect)
	{
		::CopyRect(this, lpSrcRect);
	}

	CRect(POINT point, SIZE size)
	{
		right = (left = point.x) + size.cx;
		bottom = (top = point.y) + size.cy;
	}

	CRect(POINT topLeft, POINT bottomRight)
	{
		left = topLeft.x;
		top = topLeft.y;
		right = bottomRight.x;
		bottom = bottomRight.y;
	}

// Attributes (in addition to RECT members)
	int Width() const
	{
		return right - left;
	}

	int Height() const
	{
		return bottom - top;
	}

	CSize Size() const
	{
		return CSize(right - left, bottom - top);
	}

	CPoint& TopLeft()
	{
		return *((CPoint*)this);
	}

	CPoint& BottomRight()
	{
		return *((CPoint*)this + 1);
	}

	const CPoint& TopLeft() const
	{
		return *((CPoint*)this);
	}

	const CPoint& BottomRight() const
	{
		return *((CPoint*)this + 1);
	}

	CPoint CenterPoint() const
	{
		return CPoint((left + right) / 2, (top + bottom) / 2);
	}

	// convert between CRect and LPRECT/LPCRECT (no need for &)
	operator LPRECT()
	{
		return this;
	}

	operator LPPOINT() { return (LPPOINT)this; }

	operator LPCRECT() const
	{
		return this;
	}

	BOOL IsRectEmpty() const
	{
		return ::IsRectEmpty(this);
	}

	BOOL IsRectNull() const
	{
		return (left == 0 && right == 0 && top == 0 && bottom == 0);
	}

	BOOL PtInRect(POINT point) const
	{
		return ::PtInRect(this, point);
	}

// Operations
	void SetRect(int x1, int y1, int x2, int y2)
	{
		::SetRect(this, x1, y1, x2, y2);
	}

	void SetRect(POINT topLeft, POINT bottomRight)
	{
		::SetRect(this, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
	}

	void SetRectEmpty()
	{
		::SetRectEmpty(this);
	}

	void CopyRect(LPCRECT lpSrcRect)
	{
		::CopyRect(this, lpSrcRect);
	}

	BOOL EqualRect(LPCRECT lpRect) const
	{
		return ::EqualRect(this, lpRect);
	}

	void InflateRect(int x, int y)
	{
		::InflateRect(this, x, y);
	}

	void InflateRect(SIZE size)
	{
		::InflateRect(this, size.cx, size.cy);
	}

	void InflateRect(LPCRECT lpRect)
	{
		left -= lpRect->left;
		top -= lpRect->top;
		right += lpRect->right;
		bottom += lpRect->bottom;
	}

	void InflateRect(int l, int t, int r, int b)
	{
		left -= l;
		top -= t;
		right += r;
		bottom += b;
	}

	void DeflateRect(int x, int y)
	{
		::InflateRect(this, -x, -y);
	}

	void DeflateRect(SIZE size)
	{
		::InflateRect(this, -size.cx, -size.cy);
	}

	void DeflateRect(LPCRECT lpRect)
	{
		left += lpRect->left;
		top += lpRect->top;
		right -= lpRect->right;
		bottom -= lpRect->bottom;
	}

	void DeflateRect(int l, int t, int r, int b)
	{
		left += l;
		top += t;
		right -= r;
		bottom -= b;
	}

	void OffsetRect(int x, int y)
	{
		::OffsetRect(this, x, y);
	}
	void OffsetRect(SIZE size)
	{
		::OffsetRect(this, size.cx, size.cy);
	}

	void OffsetRect(POINT point)
	{
		::OffsetRect(this, point.x, point.y);
	}

	void NormalizeRect()
	{
		int nTemp;
		if (left > right)
		{
			nTemp = left;
			left = right;
			right = nTemp;
		}
		if (top > bottom)
		{
			nTemp = top;
			top = bottom;
			bottom = nTemp;
		}
	}

	// absolute position of rectangle
	void MoveToY(int y)
	{
		bottom = Height() + y;
		top = y;
	}

	void MoveToX(int x)
	{
		right = Width() + x;
		left = x;
	}

	void MoveToXY(int x, int y)
	{
		MoveToX(x);
		MoveToY(y);
	}

	void MoveToXY(POINT pt)
	{
		MoveToX(pt.x);
		MoveToY(pt.y);
	}

	// operations that fill '*this' with result
	BOOL IntersectRect(LPCRECT lpRect1, LPCRECT lpRect2)
	{
		return ::IntersectRect(this, lpRect1, lpRect2);
	}

	BOOL UnionRect(LPCRECT lpRect1, LPCRECT lpRect2)
	{
		return ::UnionRect(this, lpRect1, lpRect2);
	}

	BOOL SubtractRect(LPCRECT lpRectSrc1, LPCRECT lpRectSrc2)
	{
		return ::SubtractRect(this, lpRectSrc1, lpRectSrc2);
	}

// Additional Operations
	void operator =(const RECT& srcRect)
	{
		::CopyRect(this, &srcRect);
	}

	BOOL operator ==(const RECT& rect) const
	{
		return ::EqualRect(this, &rect);
	}

	BOOL operator !=(const RECT& rect) const
	{
		return !::EqualRect(this, &rect);
	}

	void operator +=(POINT point)
	{
		::OffsetRect(this, point.x, point.y);
	}

	void operator +=(SIZE size)
	{
		::OffsetRect(this, size.cx, size.cy);
	}

	void operator +=(LPCRECT lpRect)
	{
		InflateRect(lpRect);
	}

	void operator -=(POINT point)
	{
		::OffsetRect(this, -point.x, -point.y);
	}

	void operator -=(SIZE size)
	{
		::OffsetRect(this, -size.cx, -size.cy);
	}

	void operator -=(LPCRECT lpRect)
	{
		DeflateRect(lpRect);
	}

	void operator &=(const RECT& rect)
	{
		::IntersectRect(this, this, &rect);
	}

	void operator |=(const RECT& rect)
	{
		::UnionRect(this, this, &rect);
	}

// Operators returning CRect values
	CRect operator +(POINT pt) const
	{
		CRect rect(*this);
		::OffsetRect(&rect, pt.x, pt.y);
		return rect;
	}

	CRect operator -(POINT pt) const
	{
		CRect rect(*this);
		::OffsetRect(&rect, -pt.x, -pt.y);
		return rect;
	}

	CRect operator +(LPCRECT lpRect) const
	{
		CRect rect(this);
		rect.InflateRect(lpRect);
		return rect;
	}

	CRect operator +(SIZE size) const
	{
		CRect rect(*this);
		::OffsetRect(&rect, size.cx, size.cy);
		return rect;
	}

	CRect operator -(SIZE size) const
	{
		CRect rect(*this);
		::OffsetRect(&rect, -size.cx, -size.cy);
		return rect;
	}

	CRect operator -(LPCRECT lpRect) const
	{
		CRect rect(this);
		rect.DeflateRect(lpRect);
		return rect;
	}

	CRect operator &(const RECT& rect2) const
	{
		CRect rect;
		::IntersectRect(&rect, this, &rect2);
		return rect;
	}

	CRect operator |(const RECT& rect2) const
	{
		CRect rect;
		::UnionRect(&rect, this, &rect2);
		return rect;
	}

	CRect MulDiv(int nMultiplier, int nDivisor) const
	{
		return CRect(
			::MulDiv(left, nMultiplier, nDivisor),
			::MulDiv(top, nMultiplier, nDivisor),
			::MulDiv(right, nMultiplier, nDivisor),
			::MulDiv(bottom, nMultiplier, nDivisor));
	}
};


// CSize implementation

inline CPoint CSize::operator +(POINT point) const
{ return CPoint(cx + point.x, cy + point.y); }

inline CPoint CSize::operator -(POINT point) const
{ return CPoint(cx - point.x, cy - point.y); }

inline CRect CSize::operator +(const RECT* lpRect) const
{ return CRect(lpRect) + *this; }

inline CRect CSize::operator -(const RECT* lpRect) const
{ return CRect(lpRect) - *this; }


// CPoint implementation

inline CRect CPoint::operator +(const RECT* lpRect) const
{ return CRect(lpRect) + *this; }

inline CRect CPoint::operator -(const RECT* lpRect) const
{ return CRect(lpRect) - *this; }


#endif


//////////////////////////////////////////////////////////////////////////////

BOOL CenterWindow(HWND hWnd, HWND hWndCenter = NULL)
{
	_ASSERTE(::IsWindow(hWnd));

	// determine owner window to center against
	DWORD dwStyle = (DWORD)GetWindowLong(hWnd, GWL_STYLE);
	//DWORD dwExStyle = (DWORD)GetWindowLong(hWnd, GWL_EXSTYLE);
	if(hWndCenter == NULL)
	{
		if(dwStyle & WS_CHILD)
			hWndCenter = ::GetParent(hWnd);
		else
			hWndCenter = ::GetWindow(hWnd, GW_OWNER);
	}

	// get coordinates of the window relative to its parent
	RECT rcDlg;
	::GetWindowRect(hWnd, &rcDlg);
	RECT rcArea;
	RECT rcCenter;
	HWND hWndParent;
	if(!(dwStyle & WS_CHILD))
	{
		// don't center against invisible or minimized windows
		if(hWndCenter != NULL)
		{
			DWORD dwStyleCenter = ::GetWindowLong(hWndCenter, GWL_STYLE);
			if(!(dwStyleCenter & WS_VISIBLE) || (dwStyleCenter & WS_MINIMIZE))
				hWndCenter = NULL;
		}

		// center within screen coordinates
		::SystemParametersInfo(SPI_GETWORKAREA, NULL, &rcArea, NULL);
		if(hWndCenter == NULL)
			rcCenter = rcArea;
		else
			::GetWindowRect(hWndCenter, &rcCenter);
	}
	else
	{
		// center within parent client coordinates
		hWndParent = ::GetParent(hWnd);
		_ASSERTE(::IsWindow(hWndParent));
		::GetClientRect(hWndParent, &rcArea);
		_ASSERTE(::IsWindow(hWndCenter));
		::GetClientRect(hWndCenter, &rcCenter);
		::MapWindowPoints(hWndCenter, hWndParent, (POINT*)&rcCenter, 2);
	}

	int DlgWidth = rcDlg.right - rcDlg.left;
	int DlgHeight = rcDlg.bottom - rcDlg.top;

	// find dialog's upper left based on rcCenter
	int xLeft = (rcCenter.left + rcCenter.right) / 2 - DlgWidth / 2;
	int yTop = (rcCenter.top + rcCenter.bottom) / 2 - DlgHeight / 2;

	// if the dialog is outside the screen, move it inside
	if(xLeft < rcArea.left)
		xLeft = rcArea.left;
	else if(xLeft + DlgWidth > rcArea.right)
		xLeft = rcArea.right - DlgWidth;

	if(yTop < rcArea.top)
		yTop = rcArea.top;
	else if(yTop + DlgHeight > rcArea.bottom)
		yTop = rcArea.bottom - DlgHeight;

	// map screen coordinates to child coordinates
	return ::SetWindowPos(hWnd, NULL, xLeft, yTop, -1, -1, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

///////////////////////////////////////////////////////////////////////////////

BOOL CenterRectToWindow(LPRECT pRect, HWND hWndCenter)
{
	if ((pRect==NULL) || (hWndCenter==NULL)) return FALSE;

	// don't center against invisible or minimized windows
	DWORD dwStyleCenter = ::GetWindowLong(hWndCenter, GWL_STYLE);
	if(!(dwStyleCenter & WS_VISIBLE) || (dwStyleCenter & WS_MINIMIZE)) return FALSE;
	
	CRect rcCenter;
	if (!GetWindowRect(hWndCenter, &rcCenter)) return FALSE;
	DBGTRACE("rcCenter=(x%d,y%d,w%d,h%d)\n",rcCenter.left,rcCenter.top,rcCenter.Width(),rcCenter.Height());

	LONG rcWidth = pRect->right - pRect->left;
	LONG rcHeight = pRect->bottom - pRect->top;

	// find dialog's upper left based on rcCenter
	LONG xLeft = (rcCenter.left + rcCenter.right) / 2 - rcWidth / 2;
	LONG yTop = (rcCenter.top + rcCenter.bottom) / 2 - rcHeight / 2;
	DBGTRACE("xLeft=%d,  yTop=%d\n", xLeft, yTop);

	// if the dialog is outside the monitor, move it inside
	HMONITOR hMonitor = MonitorFromRect(&rcCenter, MONITOR_DEFAULTTONEAREST);
	_ASSERTE(hMonitor!=NULL);
	if (hMonitor==NULL) return FALSE;
	MONITORINFO mi;
	mi.cbSize = sizeof(MONITORINFO);
	if (!GetMonitorInfo(hMonitor, &mi)) return FALSE;
	DBGTRACE("mi.rcWork=(%d,%d,%d,%d)\n", mi.rcWork.left, mi.rcWork.top, mi.rcWork.right, mi.rcWork.bottom);
	if(xLeft < mi.rcWork.left)
		xLeft = mi.rcWork.left;
	else if(xLeft + rcWidth > mi.rcWork.right)
		xLeft = mi.rcWork.right - rcWidth;
	if(yTop < mi.rcWork.top)
		yTop = mi.rcWork.top;
	else if(yTop + rcHeight > mi.rcWork.bottom)
		yTop = mi.rcWork.bottom - rcHeight;
	
	pRect->left = xLeft;
	pRect->top = yTop;
	pRect->right = xLeft + rcWidth;
	pRect->bottom = yTop + rcHeight;

	DBGTRACE("pRect=(%d,%d,%d,%d)\n", pRect->left, pRect->top, pRect->right, pRect->bottom);

return TRUE;
}



#endif//_HELPERS_9EF22F0D_46AB_423F_BA5A_D1BD482453D1_
