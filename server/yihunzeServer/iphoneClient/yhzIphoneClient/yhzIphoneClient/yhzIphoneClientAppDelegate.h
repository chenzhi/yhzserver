//
//  yhzIphoneClientAppDelegate.h
//  yhzIphoneClient
//
//  Created by thcz on 11-9-29.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class yhzIphoneClientViewController;

@interface yhzIphoneClientAppDelegate : NSObject <UIApplicationDelegate> {

}

@property (nonatomic, retain) IBOutlet UIWindow *window;

@property (nonatomic, retain) IBOutlet yhzIphoneClientViewController *viewController;

@end
