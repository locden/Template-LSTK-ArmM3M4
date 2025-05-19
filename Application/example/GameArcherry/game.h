#ifndef EXAMPLE_GAME_GAME_H_
#define EXAMPLE_GAME_GAME_H_


#include "task.h"
#include "timer.h"
#include "app_main.h"
#include "observer.h"
#include "lcd_16x2.h"

enum GameSignals
{
	TIME_TICK_SIG = USER_SIG,
	BLINK_TIMEOUT_SIG,
	BUTTON_UP_PRESSED,
	BUTTON_UP_RELEASE,
	BUTTON_DOWN_PRESSED,
	BUTTON_DOWN_RELEASE,
	BUTTON_MODE_PRESSED,
	BUTTON_MODE_RELEASE,

	ARCHERY_PLAYING_SIG,
	ARCHERY_IMG_SIG,
	BORDER_IMG_SIG,
	ARROW_IMG_SIG,
	DETROYED_METEOROID_SIG,
	BANG_IMG_SIG,
	SCORE_SIG,


	MAX_SIG,
};

#define GAME_ARCHERY_X 			0U
#define GAME_ARCHERY_Y			0U


enum GameBitmapIds
{
	ARCHERY_BMP,
	ARROW_BMP,
	METEOROID_BMP,
	BORDER_BMP,
	EXPLOSION_BMP

};


typedef struct
{
	LTK_Evt_t super;

	uint8_t x;
	uint8_t y;
	uint8_t bmp;
} ObjectImageEvt;

typedef struct
{
	LTK_Evt_t super;

	uint8_t x;
	uint8_t y;
} ObjectPostEvt;

typedef struct {
// protected:
	LTK_Evt_t super;

// public:
    uint16_t score;
} ScoreEvt;


extern obs_sub_t sysTickSubject;


extern LTK_Task_t * const AO_arrow;
extern LTK_Task_t * const AO_archery;
extern LTK_Task_t * const AO_border;
extern LTK_Task_t * const AO_bang;
extern LTK_Task_t * const AO_meteoroid;
extern LTK_Task_t * const AO_screen;

extern void Archery_instance(void);
extern void Arrow_instance(void);
extern void Bang_instance(void);
extern void Border_instance(void);
extern void Meteoroid_instance(void);
extern void Screen_instance(void);


#endif /* EXAMPLE_GAME_GAME_H_ */
