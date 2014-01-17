//
//  MMEventCategoryC.h
//  MetricaMobilFramework
//
//  Created by Marcos Ortega on 23/09/13.
//  Copyright (c) 2013 logicoim@gmail.com. All rights reserved.
//

#ifndef MetricaMobilFramework_MMEventCategoryC_h
#define MetricaMobilFramework_MMEventCategoryC_h

#ifdef __cplusplus
extern "C" {
#endif

struct MMEventCategoryC {
	void* _a;
	unsigned int _b;
} MMEventCategoryC;

struct MMEventCategoryC	MMGetEventCategoryByName(const char* catNameUTF8);
void 					MMRegisterEvent(struct MMEventCategoryC* obj, const char* eventNameUTF8, unsigned int countIncrement);
void					MMRegisterEventWithAcumulate(struct MMEventCategoryC* obj, const char* eventNameUTF8, unsigned int countIncrement, float acumulateIncrement);
void					MMInitEventsEngine(void* a);

#ifdef __cplusplus
}
#endif

#endif
