//
//  MetricaMobile.m
//
//  Created by Irving  Medina on 29/06/12.
//  Copyright (c) 2012 logicoim@gmail.com. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface MetricaMobile : NSObject {
	double unsentSessionLength;
	NSTimer *timer;
	double lastTime;
	BOOL isSuspended;
}

+ (MetricaMobile *)sharedInstance;

- (void)start:(NSString *)appKey withHost:(NSString *)appHost;


@end
