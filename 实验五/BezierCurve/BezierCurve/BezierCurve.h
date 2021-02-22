
// BezierCurve.h : main header file for the BezierCurve application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CBezierCurveApp:
// See BezierCurve.cpp for the implementation of this class
//

class CBezierCurveApp : public CWinApp
{
public:
	CBezierCurveApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBezierCurveApp theApp;
