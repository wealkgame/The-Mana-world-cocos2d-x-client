//
//  mana_iphoneAppDelegate.h
//  mana-iphone
//
//  Created by 赵 鹏 on 11-2-15.
//  Copyright wealk 2011. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "cocos2d.h"

@class RootViewController;

@interface mana_iphoneAppDelegate : NSObject <UIApplicationDelegate> {
        UIWindow                              *window;
        RootViewController             *viewController;
        cocos2d::CCXEGLView     *view;
}

@property (nonatomic, retain) UIWindow *window;

@end
