//
//  MetricaMobile.h
//  MetricaMobile
//
//  Created by MetricaMobile.
//  Copyright (c) 2013 MetricaMobile. All rights reserved.
//

#ifndef MetricaMobile_h
#define MetricaMobile_h

#import "MMEventCategory.h"

//----------------------------------------------------------------------
//-- Esta es la interfaz publica de MetricaMobile.
//-- Todos los metodos que el desarrollador puede
//-- invocar estan concentrados en esta clase.
//----------------------------------------------------------------------
@interface MetricaMobile : NSObject {
	//Empty
}

//General API
+ (void)start:(NSString *)appKey;

//CustomEvents API
+ (MMEventCategory*)getEventCategoryByName:(NSString*)name;

//Debugging API
+ (NSString*) getLastRunCrashSymbols;
@end

#endif
