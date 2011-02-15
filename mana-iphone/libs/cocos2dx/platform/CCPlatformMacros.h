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
#ifndef __CC_PLATFORM_MACROS_H__
#define __CC_PLATFORM_MACROS_H__

/**
 * define some platform specific macros
 */
#include "config_platform.h"

#ifdef CCX_PLATFORM_MOBILE
    #define MacGLView					void
    #define NSWindow					        void
#elif defined(CCX_PLATFORM_PC)
    #include "platform/MacGLView.h"
#endif

/** @def CC_ENABLE_CACHE_TEXTTURE_DATA
Enable it if you want to cache the texture data.
Basically,it's only enabled in android

It's new in cocos2d-x since v0.99.5
*/
#ifdef CCX_PLATFORM_ANDROID
    #define CC_ENABLE_CACHE_TEXTTURE_DATA       1
#else
    #define CC_ENABLE_CACHE_TEXTTURE_DATA       0
#endif

#endif // __CC_PLATFORM_MACROS_H__
