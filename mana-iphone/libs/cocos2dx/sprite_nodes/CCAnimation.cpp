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
#include "CCAnimation.h"
#include "CCTextureCache.h"
#include "CCTexture2D.h"
#include "ccMacros.h"
#include "CCSpriteFrame.h"

namespace cocos2d
{
	// implementation of CCAnimation

	CCAnimation* CCAnimation::animation()
	{
		CCAnimation *pAnimation = new CCAnimation();
		pAnimation->init();
		pAnimation->autorelease();

		return pAnimation;
	} 

	bool CCAnimation::init()
	{
		return initWithFrames(NULL, 0);
	}

	CCAnimation* CCAnimation::animationWithFrames(NSArray<CCSpriteFrame*> *frames)
	{
		CCAnimation *pAnimation = new CCAnimation();
		pAnimation->initWithFrames(frames);
		pAnimation->autorelease();

		return pAnimation;
	}

	CCAnimation* CCAnimation::animationWithFrames(NSArray<CCSpriteFrame*> *frames, float delay)
	{
		CCAnimation *pAnimation = new CCAnimation();
		pAnimation->initWithFrames(frames, delay);
		pAnimation->autorelease();

		return pAnimation;
	}

	CCAnimation* CCAnimation::animationWithName(const char *pszName)
	{
		CCAnimation *pAnimation = new CCAnimation();
		pAnimation->initWithName(pszName);
		pAnimation->autorelease();

		return pAnimation;
	}

	CCAnimation* CCAnimation::animationWithName(const char *pszName, NSMutableArray<CCSpriteFrame*> *pFrames)
	{
		CCAnimation *pAnimation = new CCAnimation();
		pAnimation->initWithName(pszName, pFrames);
		pAnimation->autorelease();

		return pAnimation;
	}

	CCAnimation* CCAnimation::animationWithName(const char *pszName, float fDelay, NSMutableArray<CCSpriteFrame*> *pFrames)
	{
		CCAnimation *pAnimation = new CCAnimation();
		pAnimation->initWithName(pszName, fDelay, pFrames);
		pAnimation->autorelease();

		return pAnimation;
	}

	CCAnimation* CCAnimation::animationWithName(const char *pszName, float fDelay)
	{
		CCAnimation *pAnimation = new CCAnimation();
		pAnimation->initWithName(pszName, fDelay);
		pAnimation->autorelease();

		return pAnimation;
	}

	bool CCAnimation::initWithFrames(NSArray<CCSpriteFrame*> *pFrames, float delay)
	{
        m_fDelay = delay;
		m_pobFrames = NSMutableArray<CCSpriteFrame*>::arrayWithArray(pFrames);

		return true;
	}

	bool CCAnimation::initWithFrames(NSArray<CCSpriteFrame*> *pFrames)
	{
        return initWithFrames(pFrames, 0);
	}

	bool CCAnimation::initWithName(const char *pszName)
	{
		return initWithName(pszName, 0, NULL);
	}

	bool CCAnimation::initWithName(const char *pszName, float fDelay)
	{
		return initWithName(pszName, fDelay, NULL);
	}

	bool CCAnimation::initWithName(const char *pszName, NSMutableArray<CCSpriteFrame*> *pFrames)
	{
		return initWithName(pszName, 0, pFrames);
	}

	bool CCAnimation::initWithName(const char *pszName, float fDelay, NSMutableArray<CCSpriteFrame*> *pFrames)
	{
		m_fDelay = fDelay;
		m_nameStr = pszName;
		m_pobFrames = NSMutableArray<CCSpriteFrame*>::arrayWithArray(pFrames);

		return true;
	}

	CCAnimation::~CCAnimation(void)
	{
		CCLOGINFO("cocos2d, deallocing %p", this);
		// [name_ release];
		m_nameStr.clear();
		CCX_SAFE_RELEASE(m_pobFrames);
	}

	void CCAnimation::addFrame(CCSpriteFrame *pFrame)
	{
		m_pobFrames->addObject(pFrame);
	}

	void CCAnimation::addFrameWithFileName(const char *pszFileName)
	{
		CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(pszFileName);
		CGRect rect = CGRectZero;
		rect.size = pTexture->getContentSize();
		CCSpriteFrame *pFrame = CCSpriteFrame::frameWithTexture(pTexture, rect);
		m_pobFrames->addObject(pFrame);
	}

	void CCAnimation::addFrameWithTexture(CCTexture2D *pobTexture, CGRect rect)
	{
		CCSpriteFrame *pFrame = CCSpriteFrame::frameWithTexture(pobTexture, rect);
		m_pobFrames->addObject(pFrame);
	}
}