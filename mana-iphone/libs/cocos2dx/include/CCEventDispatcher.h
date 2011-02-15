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

#ifndef __CCEVENT_DISPATCHER_H__
#define __CCEVENT_DISPATCHER_H__

#include "CCXCocos2dDefine.h"
#include "CCMouseEventDelegate.h"
#include "CCKeyboardEventDelegate.h"
#include "ccConfig.h"
#include "selector_protocol.h"

namespace   cocos2d {

struct _listEntry;

/** CCEventDispatcher

This is object is responsible for dispatching the events:
- Mouse events
- Keyboard events
- Touch events

Only available on Mac
*/
class CCEventDispatcher : public NSObject
{
public:
    static CCEventDispatcher* sharedDispatcher();
    bool init(void);

    /** Adds a mouse delegate to the dispatcher's list.
    Delegates with a lower priority value will be called before higher priority values.
    All the events will be propgated to all the delegates, unless the one delegate returns YES.

    IMPORTANT: The delegate will be retained.
    */
    void addMouseDelegate(CCMouseEventDelegate* pDelegate, int priority);

    /** removes a mouse delegate */
    void removeMouseDelegate(CCMouseEventDelegate* pDelegate);

    /** Removes all mouse delegates, releasing all the delegates */
    void removeAllMouseDelegates();

    /** Adds a Keyboard delegate to the dispatcher's list.
    Delegates with a lower priority value will be called before higher priority values.
    All the events will be propgated to all the delegates, unless the one delegate returns YES.

    IMPORTANT: The delegate will be retained.
    */
    void addKeyboardDelegate(CCKeyboardEventDelegate* pDelegate, int priority);

    /** removes a mouse delegate */
    void removeKeyboardDelegate(CCKeyboardEventDelegate* pDelegate);

    /** Removes all mouse delegates, releasing all the delegates */
    void removeAllKeyboardDelegates();

    /** Mouse events */
    // left
    void mouseDown(NSEvent *pEvent);
    void mouseMoved(NSEvent *pEvent);
    void mouseDragged(NSEvent *pEvent);
    void mouseUp(NSEvent *pEvent);

    // right
    void rightMouseDown(NSEvent *pEvent);
    void rightMouseDragged(NSEvent *pEvent);
    void rightMouseUp(NSEvent *pEvent);

    // other
    void otherMouseDown(NSEvent *pEvent);
    void otherMouseDragged(NSEvent *pEvent);
    void otherMouseUp(NSEvent *pEvent);

    // scroll Wheel
    void scrollWheel(NSEvent *pEvent);

    // Mouse enter / exit
    void mouseExited(NSEvent *pEvent);
    void mouseEntered(NSEvent *pEvent);

    /** keyboard events */
    void keyDown(NSEvent *pEvent);
    void keyUp(NSEvent *pEvent);
    void flagsChanged(NSEvent *pEvent);

    void touchesBeganWithEvent(NSEvent *pEvent);
    void touchesMovedWithEvent(NSEvent *pEvent);
    void touchesEndedWithEvent(NSEvent *pEvent);
    void touchesCancelledWithEvent(NSEvent *pEvent);

#if CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD
    void dispatchQueuedEvents();
    void queueEvent(NSEvent* pEvent, SEL_EventHandler selector);
#endif

    CCX_PROPERTY(bool, m_bDispatchEvents, IsDispatchEvents)

protected:
    void addDelegate(NSObject* pHandle, int priority, _listEntry** pList);
    void removeAllDelegatesFromList(_listEntry** pList);

protected:
    struct _listEntry* m_pKeyboardDelegates;
    struct _listEntry* m_pMouseDelegates;
};

} //namespace   cocos2d 

#endif // __CCEVENT_DISPATCHER_H__
