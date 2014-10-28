#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"

#include "SwTimer.h"

extern boolean bTickFlag;

uint16_t u16SwTimerCnt[SW_TIMER_NUM];

void swTimerUpdate (void) {
	uint16_t	i;
	
	if (bTickFlag) {
		for (i = 0; i < SW_TIMER_NUM; i++) {
			if (u16SwTimerCnt[i] != 0)
				u16SwTimerCnt[i] --;
		}
		bTickFlag = 0;
	}
}

void swTimerClearAll (void) {
	uint16_t i;
	
	for (i = 0; i < SW_TIMER_NUM; i++)
		u16SwTimerCnt[i] = 0;
}

void swTimerClear (eSwTimer t) {
	u16SwTimerCnt[t] = 0;
}

void swTimerSet (eSwTimer timer, uint16_t time) {
	u16SwTimerCnt[timer] = time;
}

boolean swTimerIsTimeout (eSwTimer timer) {
	if (u16SwTimerCnt[timer] == 0)
		return true;
	else
		return false;
}
