#ifndef SW_TIMER_H
#define SW_TIMER_H

#define TIME_PERIOD_TICK			1							// Tick 25ms
#define TIME_PERIOD_100MS			(4 * TIME_PERIOD_TICK)
#define TIME_PERIOD_1S				(10 * TIME_PERIOD_100MS)

#define TIME_PERIOD_PRE_CALIBRATION		(9 * TIME_PERIOD_1S)
#define TIME_PERIOD_CALIBRATION			(1 * TIME_PERIOD_1S)

#define TIME_PERIOD_SPEED_PATTERN_1		(5 * TIME_PERIOD_100MS)
#define TIME_PERIOD_SPEED_PATTERN_2		(4 * TIME_PERIOD_100MS)
#define TIME_PERIOD_SPEED_PATTERN_3		(3 * TIME_PERIOD_100MS)
#define TIME_PERIOD_SPEED_PATTERN_4		(2 * TIME_PERIOD_100MS)
#define TIME_PERIOD_SPEED_PATTERN_5		(1 * TIME_PERIOD_100MS)

#define TIME_PERIOD_HALT_PATTERN		(1 * TIME_PERIOD_100MS)

#define TIME_PERIOD_LED_CALIBRATION_PATTERN		(2 * TIME_PERIOD_TICK)
#define TIME_PERIOD_LED_TEST_PATTERN	(5 * TIME_PERIOD_100MS)

typedef enum {
	SW_TIMER_LED_BLINK = 0,
	SW_TIMER_STATE_DURATION,
	SW_TIMER_DELAY,
	SW_TIMER_NUM
} eSwTimer;

void swTimerUpdate (void);
void swTimerClearAll (void);
void swTimerClear (eSwTimer t);
void swTimerSet (eSwTimer timer, uint16_t time);
boolean swTimerIsTimeout (eSwTimer timer);

#endif
