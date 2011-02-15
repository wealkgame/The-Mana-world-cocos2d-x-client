/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __CCX_EGLVIEW_WIN32_H__
#define __CCX_EGLVIEW_WIN32_H__

#include <Windows.h>

#include "CCXCocos2dDefine.h"
#include "CGGeometry.h"

namespace   cocos2d {
class NSSet;
class CCTouch;
class EGLTouchDelegate;

class CCXEGL;

class CCX_DLL CCXEGLView
{
public:

    CCXEGLView();
    virtual ~CCXEGLView();

	CGRect  getFrame();
    CGSize  getSize();
    bool    isOpenGLReady();
    void    release();
    void    setTouchDelegate(EGLTouchDelegate * pDelegate);
    void    swapBuffers();
    bool    canSetContentScaleFactor();
    void    setContentScaleFactor(float contentScaleFactor);

	virtual bool Create(LPCTSTR pTitle, int w, int h);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	HWND    getHWnd();
	int setDeviceOrientation(int eOritation);

private:

    bool                m_bCaptured;
	bool				m_bOrientationReverted;
	bool				m_bOrientationInitVertical;
    NSSet *             m_pSet;
    CCTouch *           m_pTouch;
    EGLTouchDelegate *  m_pDelegate;

    CCXEGL *            m_pEGL;

	HWND				m_hWnd;

	int					m_eInitOrientation;
};

}   // end of namespace   cocos2d

#endif	// end of __CCX_EGLVIEW_WIN32_H__
