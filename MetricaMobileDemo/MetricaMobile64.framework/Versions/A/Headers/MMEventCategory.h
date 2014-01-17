//
//  MMEventCategory.h
//  MetricaMobilFramework
//
//  Created by Marcos Ortega on 10/09/13.
//  Copyright (c) 2013 logicoim@gmail.com. All rights reserved.
//

#ifndef MetricaMobile_MMEventCategory_h
#define MetricaMobile_MMEventCategory_h

//----------------------------------------------------------------------
//-- Esta es la interfaz publica para el registro de Eventos en MetricaMobile.
//-- Para uso del desarrollador, por ejemplo:
//--
//-- MMEventCategory* myCat = [MetricaMobile getEventCategoryByName:@"in_app_purchase"];
//-- [myCat registerEvent:@"MySong.mp3" withIncrement:1 andAcumulate:0.99f];
//--
//----------------------------------------------------------------------

@interface MMEventCategory : NSObject {
	//
}

//Event's API
+ (MMEventCategory*)getEventCategoryByName:(NSString*)name;

-(void) init:(void*)ref ref2:(unsigned int)ref2;
-(void) registerEvent:(NSString*)name withIncrement:(unsigned int)increment;
-(void) registerEvent:(NSString*)name withIncrement:(unsigned int)increment andAcumulate:(float)acumulate;

@end

#endif
