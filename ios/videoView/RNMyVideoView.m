//
//  RNMyVideoView.m
//  RNMyLibrary
//
//  Created by developer on 2020/3/26.
//  Copyright © 2020 Facebook. All rights reserved.
//

#import "RNMyVideoView.h"

@implementation RNMyVideoView

+ (instancetype)sharedView {
    static RNMyVideoView *instance;
    //static id instance;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        
        BOOL isMainThread = [NSThread isMainThread];
        if (isMainThread) {
          instance = [[self alloc] init];
        } else {
            dispatch_sync(dispatch_get_main_queue(), ^{
               instance = [[self alloc] init];
            });
        }
    });
    return instance;
}


#pragma mark - willMoveToSuperview
-(void) willMoveToSuperview:(UIView *)newSuperview {
  [super willMoveToSuperview:newSuperview];
}

@end
