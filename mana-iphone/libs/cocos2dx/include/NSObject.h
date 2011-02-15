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

#ifndef __COCOA_NSOBJECT_H__
#define __COCOA_NSOBJECT_H__

#include "ccxCommon.h"


namespace   cocos2d {
class NSZone;
class NSObject;
class NSString;

class CCX_DLL CCCopying
{
public:
	virtual NSObject* copyWithZone(NSZone* pZone);
};

class CCX_DLL NSObject : public CCCopying
{
protected:
	// object id
    unsigned int		m_uID;
	// count of refrence
	unsigned int		m_uRefrence;
	// is the object autoreleased
	bool		m_bManaged;		
public:
	NSObject(void);
	virtual ~NSObject(void);
    
	virtual void release(void);
	virtual void retain(void);
	NSObject* autorelease(void);
	NSObject* copy(void);
	bool isSingleRefrence(void);
	unsigned int retainCount(void);
	bool isEqual(const NSObject* pObject);

	friend class NSAutoreleasePool;
};
}//namespace   cocos2d 

#endif // __COCOA_NSOBJECT_H__
