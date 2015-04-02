/*****************************************************************************
 * Copyright (c) 2014 Ted John
 * OpenRCT2, an open source clone of Roller Coaster Tycoon 2.
 *
 * This file is part of OpenRCT2.
 *
 * OpenRCT2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/

#include "../addresses.h"
#include "../drawing/drawing.h"
#include "../game.h"
#include "../interface/viewport.h"
#include "../interface/widget.h"
#include "../interface/window.h"
#include "../localisation/localisation.h"
#include "../ride/track.h"

/* move to ride.c */
void sub_6B2FA9(rct_windownumber number)
{
	rct_window* w;

	w = window_find_by_number(WC_RIDE, number);
	if (w != NULL && w->page == 1)
		window_close(w);
}

enum {
	WIDX_BACKGROUND,
	WIDX_TITLE,
	WIDX_CLOSE,
	WIDX_DIRECTION_GROUPBOX,
	WIDX_SLOPE_GROUPBOX,
	WIDX_BANKING_GROUPBOX,
	WIDX_LEFT_CURVE_VERY_SMALL,
	WIDX_LEFT_CURVE_SMALL,
	WIDX_LEFT_CURVE,
	WIDX_STRAIGHT,
	WIDX_RIGHT_CURVE,
	WIDX_RIGHT_CURVE_SMALL,
	WIDX_RIGHT_CURVE_VERY_SMALL,
	WIDX_SPECIAL_TRACK_DROPDOWN,
	WIDX_SLOPE_DOWN_STEEP,
	WIDX_SLOPE_DOWN,
	WIDX_LEVEL,
	WIDX_SLOPE_UP,
	WIDX_SLOPE_UP_STEEP,
	WIDX_CHAIN_LIFT,
	WIDX_BANK_LEFT,
	WIDX_BANK_STRAIGHT,
	WIDX_BANK_RIGHT,
	WIDX_CONSTRUCT,
	WIDX_DEMOLISH,
	WIDX_LEFT_CURVE_LARGE,
	WIDX_PREVIOUS_SECTION,
	WIDX_NEXT_SECTION,
	WIDX_ENTRANCE_EXIT_GROUPBOX,
	WIDX_ENTRANCE,
	WIDX_EXIT,
	WIDX_RIGHT_CURVE_LARGE,
	WIDX_ROTATE,
	WIDX_U_TRACK,
	WIDX_O_TRACK,
	WIDX_SEAT_ROTATION_GROUPBOX,
	WIDX_SEAT_ROTATION_ANGLE_SPINNER,
	WIDX_SEAT_ROTATION_ANGLE_SPINNER_UP,
	WIDX_SEAT_ROTATION_ANGLE_SPINNER_DOWN,

	WIDX_MAZE_MODE_GROUPBOX = 3,
	WIDX_MAZE_BUILD_MODE = 6,
	WIDX_MAZE_MOVE_MODE,
	WIDX_MAZE_FILL_MODE,
	WIDX_MAZE_DIRECTION_GROUPBOX = 23,
	WIDX_MAZE_DIRECTION_NW,
	WIDX_MAZE_DIRECTION_NE,
	WIDX_MAZE_DIRECTION_SW,
	WIDX_MAZE_DIRECTION_SE,
};

#pragma region Widgets

static rct_widget window_ride_construction_widgets[] = {
	{ WWT_FRAME,			0,	0,		165,	0,		393,	0xFFFFFFFF,							STR_NONE												},
	{ WWT_CAPTION,			0,	1,		164,	1,		14,		896,								STR_WINDOW_TITLE_TIP									},
	{ WWT_CLOSEBOX,			0,	153,	163,	2,		13,		STR_CLOSE_X,						STR_CLOSE_WINDOW_TIP									},
	{ WWT_GROUPBOX,			0,	3,		162,	17,		73,		STR_RIDE_CONSTRUCTION_DIRECTION,	STR_NONE												},
	{ WWT_GROUPBOX,			0,	3,		162,	76,		116,	STR_RIDE_CONSTRUCTION_SLOPE,		STR_NONE												},
	{ WWT_GROUPBOX,			0,	3,		162,	120,	160,	STR_RIDE_CONSTRUCTION_ROLL_BANKING,	STR_NONE												},
	{ WWT_FLATBTN,			1,	6,		27,		29,		52,		0x1414,								STR_RIDE_CONSTRUCTION_LEFT_CURVE_VERY_SMALL_TIP			},
	{ WWT_FLATBTN,			1,	6,		27,		29,		52,		0x1414,								STR_RIDE_CONSTRUCTION_LEFT_CURVE_SMALL_TIP				},
	{ WWT_FLATBTN,			1,	28,		49,		29,		52,		0x1412,								STR_RIDE_CONSTRUCTION_LEFT_CURVE_TIP					},
	{ WWT_FLATBTN,			1,	72,		93,		29,		52,		0x1411,								STR_RIDE_CONSTRUCTION_STRAIGHT_TIP						},
	{ WWT_FLATBTN,			1,	116,	137,	29,		52,		0x1413,								STR_RIDE_CONSTRUCTION_RIGHT_CURVE_TIP					},
	{ WWT_FLATBTN,			1,	138,	159,	29,		52,		0x1415,								STR_RIDE_CONSTRUCTION_RIGHT_CURVE_SMALL_TIP				},
	{ WWT_FLATBTN,			1,	138,	159,	29,		52,		0x1415,								STR_RIDE_CONSTRUCTION_RIGHT_CURVE_VERY_SMALL_TIP		},
	{ WWT_DROPDOWN_BUTTON,	1,	17,		148,	55,		68,		1384,								STR_RIDE_CONSTRUCTION_OTHER_TRACK_CONFIGURATIONS_TIP	},
	{ WWT_FLATBTN,			1,	23,		46,		88,		111,	0x1418,								STR_RIDE_CONSTRUCTION_STEEP_SLOPE_DOWN_TIP				},
	{ WWT_FLATBTN,			1,	47,		70,		88,		111,	0x1419,								STR_RIDE_CONSTRUCTION_SLOPE_DOWN_TIP					},
	{ WWT_FLATBTN,			1,	71,		94,		88,		111,	0x141A,								STR_RIDE_CONSTRUCTION_LEVEL_TIP							},
	{ WWT_FLATBTN,			1,	95,		118,	88,		111,	0x141B,								STR_RIDE_CONSTRUCTION_SLOPE_UP_TIP						},
	{ WWT_FLATBTN,			1,	119,	142,	88,		111,	0x141C,								STR_RIDE_CONSTRUCTION_STEEP_SLOPE_UP_TIP				},
	{ WWT_FLATBTN,			1,	134,	157,	88,		111,	0x142B,								STR_RIDE_CONSTRUCTION_CHAIN_LIFT_TIP					},
	{ WWT_FLATBTN,			1,	47,		70,		132,	155,	0x1421,								STR_RIDE_CONSTRUCTION_ROLL_FOR_LEFT_CURVE_TIP			},
	{ WWT_FLATBTN,			1,	71,		94,		132,	155,	0x1422,								STR_RIDE_CONSTRUCTION_NO_ROLL_TIP						},
	{ WWT_FLATBTN,			1,	95,		118,	132,	155,	0x1423,								STR_RIDE_CONSTRUCTION_ROLL_FOR_RIGHT_CURVE_TIP			},
	{ WWT_IMGBTN,			1,	3,		162,	164,	333,	0xFFFFFFFF,							STR_RIDE_CONSTRUCTION_CONSTRUCT_SELECTED_SECTION_TIP	},
	{ WWT_FLATBTN,			1,	60,		105,	338,	361,	0x142A,								STR_RIDE_CONSTRUCTION_REMOVE_HIGHLIGHTED_SECTION_TIP	},
	{ WWT_FLATBTN,			1,	50,		71,		29,		52,		0x1416,								STR_RIDE_CONSTRUCTION_LEFT_CURVE_LARGE_TIP				},
	{ WWT_FLATBTN,			1,	20,		43,		338,	361,	0x1428,								STR_RIDE_CONSTRUCTION_MOVE_TO_PREVIOUS_SECTION_TIP		},
	{ WWT_FLATBTN,			1,	122,	145,	338,	361,	0x1429,								STR_RIDE_CONSTRUCTION_MOVE_TO_NEXT_SECTION_TIP			},
	{ WWT_GROUPBOX,			0,	3,		162,	362,	389,	0xFFFFFFFF,							STR_NONE												},
	{ WWT_DROPDOWN_BUTTON,	1,	9,		78,		372,	383,	STR_RIDE_CONSTRUCTION_ENTRANCE,		STR_RIDE_CONSTRUCTION_ENTRANCE_TIP						},
	{ WWT_DROPDOWN_BUTTON,	1,	87,		156,	372,	383,	STR_RIDE_CONSTRUCTION_EXIT,			STR_RIDE_CONSTRUCTION_EXIT_TIP							},
	{ WWT_FLATBTN,			1,	94,		115,	29,		52,		0x1417,								STR_RIDE_CONSTRUCTION_RIGHT_CURVE_LARGE_TIP				},
	{ WWT_FLATBTN,			1,	72,		95,		338,	361,	0x1431,								STR_ROTATE_90_TIP										},
	{ WWT_FLATBTN,			1,	19,		42,		132,	155,	0x1424,								STR_RIDE_CONSTRUCTION_U_SHAPED_OPEN_TRACK_TIP			},
	{ WWT_FLATBTN,			1,	123,	146,	132,	155,	0x1425,								STR_RIDE_CONSTRUCTION_O_SHAPED_ENCLOSED_TRACK_TIP		},
	{ WWT_GROUPBOX,			0,	96,		162,	120,	160,	STR_RIDE_CONSTRUCTION_SEAT_ROT,		STR_NONE												},
	{ WWT_SPINNER,			1,	101,	158,	138,	149,	0,									STR_RIDE_CONSTRUCTION_SELECT_SEAT_ROTATION_ANGLE_TIP	},
	{ WWT_DROPDOWN_BUTTON,	1,	147,	157,	139,	143,	STR_NUMERIC_UP,						STR_RIDE_CONSTRUCTION_SELECT_SEAT_ROTATION_ANGLE_TIP	},
	{ WWT_DROPDOWN_BUTTON,	1,	147,	157,	144,	148,	STR_NUMERIC_DOWN,					STR_RIDE_CONSTRUCTION_SELECT_SEAT_ROTATION_ANGLE_TIP	},
	{ WIDGETS_END }
};

static rct_widget window_ride_construction_maze_widgets[] = {
	{ WWT_FRAME,			0,	0,		165,	0,		199,	0xFFFFFFFF,							STR_NONE												},
	{ WWT_CAPTION,			0,	1,		164,	1,		14,		896,								STR_WINDOW_TITLE_TIP									},
	{ WWT_CLOSEBOX,			0,	153,	163,	2,		13,		STR_CLOSE_X,						STR_CLOSE_WINDOW_TIP									},
	{ WWT_GROUPBOX,			0,	3,		162,	17,		71,		STR_RIDE_CONSTRUCTION_MODE,			STR_NONE												},
	{ WWT_EMPTY,			0,	0,		0,		0,		0,		0xFFFFFFFF,							STR_NONE												},
	{ WWT_EMPTY,			0,	0,		0,		0,		0,		0xFFFFFFFF,							STR_NONE												},
	{ WWT_FLATBTN,			1,	35,		66,		29,		60,		0x15C8,								STR_RIDE_CONSTRUCTION_BUILD_MODE						},
	{ WWT_FLATBTN,			1,	67,		98,		29,		60,		0x15C9,								STR_RIDE_CONSTRUCTION_MOVE_MODE							},
	{ WWT_FLATBTN,			1,	99,		130,	29,		60,		0x15CA,								STR_RIDE_CONSTRUCTION_FILL_IN_MODE						},
	{ WWT_EMPTY,			0,	0,		0,		0,		0,		0xFFFFFFFF,							STR_NONE												},
	{ WWT_EMPTY,			0,	0,		0,		0,		0,		0xFFFFFFFF,							STR_NONE												},
	{ WWT_EMPTY,			0,	0,		0,		0,		0,		0xFFFFFFFF,							STR_NONE												},
	{ WWT_EMPTY,			0,	0,		0,		0,		0,		0xFFFFFFFF,							STR_NONE												},
	{ WWT_EMPTY,			0,	0,		0,		0,		0,		0xFFFFFFFF,							STR_NONE												},
	{ WWT_EMPTY,			0,	0,		0,		0,		0,		0xFFFFFFFF,							STR_NONE												},
	{ WWT_EMPTY,			0,	0,		0,		0,		0,		0xFFFFFFFF,							STR_NONE												},
	{ WWT_EMPTY,			0,	0,		0,		0,		0,		0xFFFFFFFF,							STR_NONE												},
	{ WWT_EMPTY,			0,	0,		0,		0,		0,		0xFFFFFFFF,							STR_NONE												},
	{ WWT_EMPTY,			0,	0,		0,		0,		0,		0xFFFFFFFF,							STR_NONE												},
	{ WWT_EMPTY,			0,	0,		0,		0,		0,		0xFFFFFFFF,							STR_NONE												},
	{ WWT_EMPTY,			0,	0,		0,		0,		0,		0xFFFFFFFF,							STR_NONE												},
	{ WWT_EMPTY,			0,	0,		0,		0,		0,		0xFFFFFFFF,							STR_NONE												},
	{ WWT_EMPTY,			0,	0,		0,		0,		0,		0xFFFFFFFF,							STR_NONE												},
	{ WWT_GROUPBOX,			0,	3,		162,	80,		166,	STR_RIDE_CONSTRUCTION_BUILD,		STR_NONE												},
	{ WWT_FLATBTN,			1,	83,		127,	96,		124,	0x1603,								STR_RIDE_CONSTRUCTION_BUILD_MAZE_IN_THIS_DIRECTION_TIP	},
	{ WWT_FLATBTN,			1,	83,		127,	125,	153,	0x1604,								STR_RIDE_CONSTRUCTION_BUILD_MAZE_IN_THIS_DIRECTION_TIP	},
	{ WWT_FLATBTN,			1,	38,		82,		125,	153,	0x1605,								STR_RIDE_CONSTRUCTION_BUILD_MAZE_IN_THIS_DIRECTION_TIP	},
	{ WWT_FLATBTN,			1,	38,		82,		96,		124,	0x1606,								STR_RIDE_CONSTRUCTION_BUILD_MAZE_IN_THIS_DIRECTION_TIP	},
	{ WWT_GROUPBOX,			0,	3,		162,	168,	195,	0xFFFFFFFF,							STR_NONE												},
	{ WWT_DROPDOWN_BUTTON,	1,	9,		78,		178,	189,	STR_RIDE_CONSTRUCTION_ENTRANCE,		STR_RIDE_CONSTRUCTION_ENTRANCE_TIP						},
	{ WWT_DROPDOWN_BUTTON,	1,	87,		156,	178,	189,	STR_RIDE_CONSTRUCTION_EXIT,			STR_RIDE_CONSTRUCTION_EXIT_TIP							},
	{ WWT_EMPTY,			0,	0,		0,		0,		0,		0xFFFFFFFF,							STR_NONE												},
	{ WWT_EMPTY,			0,	0,		0,		0,		0,		0xFFFFFFFF,							STR_NONE												},
	{ WIDGETS_END }
};

#pragma endregion

static void window_ride_construction_emptysub() {}

static void window_ride_construction_close();
static void window_ride_construction_mouseup();
static void window_ride_construction_invalidate();
static void window_ride_construction_paint();

static void window_ride_construction_maze_close();
static void window_ride_construction_maze_invalidate();
static void window_ride_construction_maze_paint();

// 0x993F6C
static void* window_ride_construction_maze_events[] = {
	window_ride_construction_maze_close,
	(void*)0x006CD461,
	(void*)0x006CD623,
	(void*)0x006CD48C,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	(void*)0x006CD767,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	(void*)0x006CD63E,
	(void*)0x006CD65D,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	window_ride_construction_maze_invalidate,
	window_ride_construction_maze_paint,
	window_ride_construction_emptysub
};

//0x993EEC
static void* window_ride_construction_events[] = {
	window_ride_construction_close,
	window_ride_construction_mouseup,
	(void*)0x006C7934,
	(void*)0x006C6E6A,
	(void*)0x006C78CD,
	window_ride_construction_emptysub,
	(void*)0x006C8374,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	(void*)0x006C8229,
	(void*)0x006C8248,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	window_ride_construction_emptysub,
	window_ride_construction_invalidate,
	window_ride_construction_paint,
	window_ride_construction_emptysub
};

static void window_ride_construction_mouseup_demolish(rct_window* w);

/**
 *
 * rct2: 0x006CB481
 */
rct_window *window_ride_construction_open()
{
	int rideIndex = RCT2_GLOBAL(0x00F440A7, uint8);
	sub_6B2FA9(rideIndex);

	rct_window *w;
	rct_ride* ride = GET_RIDE(rideIndex);
	if (ride->type == RIDE_TYPE_MAZE) {
		w = window_create(0, 29, 166, 200, (uint32*)window_ride_construction_maze_events, WC_RIDE_CONSTRUCTION, WF_9);

		w->widgets = window_ride_construction_maze_widgets;
		w->enabled_widgets = 0x6F0001C4;

		window_init_scroll_widgets(w);

		w->colours[0] = 24;
		w->colours[1] = 24;
		w->colours[2] = 24;

		w->number = rideIndex;

		window_push_others_right(w);
		show_gridlines();
		return w;
	}

	w = window_create(0, 29, 166, 394, (uint32*)window_ride_construction_events, WC_RIDE_CONSTRUCTION, WF_9);

	w->widgets = window_ride_construction_widgets;
	w->enabled_widgets = 0x67EFFFFFC4;

	window_init_scroll_widgets(w);

	w->colours[0] = 24;
	w->colours[1] = 24;
	w->colours[2] = 24;

	w->number = rideIndex;

	window_push_others_right(w);
	show_gridlines();

	RCT2_GLOBAL(0x00F44070, uint32) = 0x80000000;
	RCT2_GLOBAL(0x00F440CD, uint8) = 8;
	RCT2_GLOBAL(0x00F440CE, uint8) = 18;
	RCT2_GLOBAL(0x00F440CF, uint8) = 4;

	if (ride->type == RIDE_TYPE_REVERSE_FREEFALL_COASTER)
		RCT2_GLOBAL(0x00F440CE, uint8) = 30;

	if (ride->type == RIDE_TYPE_AIR_POWERED_VERTICAL_COASTER)
		RCT2_GLOBAL(0x00F440CE, uint8) = 30;

	RCT2_GLOBAL(0x00F440A0, uint16) = RCT2_ADDRESS(0x0097CC68, uint8)[ride->type * 2] | 0x100;
	RCT2_GLOBAL(0x00F440B2, uint8) = 0;
	RCT2_GLOBAL(0x00F440B3, uint8) = 0;
	RCT2_GLOBAL(0x00F440B4, uint8) = 0;
	RCT2_GLOBAL(0x00F440B5, uint8) = 0;

	if (RCT2_ADDRESS(0x0097D4F2, uint16)[ride->type * 4] & 0x8000)
		RCT2_GLOBAL(0x00F440B5, uint8) |= 2;

	RCT2_GLOBAL(0x00F440B6, uint8) = 0;
	RCT2_GLOBAL(0x00F440B7, uint8) = 0;

	RCT2_GLOBAL(RCT2_ADDRESS_TRACK_PREVIEW_ROTATION, uint8) = 0;
	RCT2_GLOBAL(0x00F440A6, uint8) = 4;
	RCT2_GLOBAL(0x00F440B0, uint8) = 0;
	RCT2_GLOBAL(0x00F440B1, uint8) = 0;
	RCT2_GLOBAL(0x00F44159, uint8) = 0;
	RCT2_GLOBAL(0x00F4415C, uint8) = 0;
	return w;
}

/**
 *
 * rct2: 0x006C845D
 */
static void window_ride_construction_close()
{
	rct_window *w;
	rct_xy_element mapElement;

	window_get_register(w);

	sub_6C9627();
	viewport_set_visibility(0);

	map_invalidate_map_selection_tiles();
	RCT2_GLOBAL(0x009DE58A, uint16) &= 0xFFFD;

	hide_gridlines();

	uint8 rideIndex = RCT2_GLOBAL(0x00F440A7, uint8);
	if (sub_6CAF80(rideIndex, &mapElement)) {
		window_ride_main_open(rideIndex);
	} else {
		int eax = RCT2_GLOBAL(RCT2_ADDRESS_GAME_PAUSED, uint8);

		RCT2_GLOBAL(RCT2_ADDRESS_GAME_PAUSED, uint8) = 0;
		game_do_command(0, 9, 0, rideIndex, GAME_COMMAND_7, 0, 0);

		RCT2_GLOBAL(RCT2_ADDRESS_GAME_PAUSED, uint8) = eax;
	}
}

/**
 *
 * rct2: 0x006CD811
 */
static void window_ride_construction_maze_close()
{
	rct_window *w;

	window_get_register(w);

	sub_6C9627();
	viewport_set_visibility(0);

	map_invalidate_map_selection_tiles();
	RCT2_GLOBAL(0x009DE58A, uint16) &= 0xFFFD;

	hide_gridlines();

	uint8 rideIndex = RCT2_GLOBAL(0x00F440A7, uint8);
	rct_ride* ride = GET_RIDE(rideIndex);
	if (ride->overall_view == 0xFFFF) {
		int savedPausedState = RCT2_GLOBAL(RCT2_ADDRESS_GAME_PAUSED, uint8);
		RCT2_GLOBAL(RCT2_ADDRESS_GAME_PAUSED, uint8) = 0;
		game_do_command(0, 9, 0, rideIndex, GAME_COMMAND_7, 0, 0);
		RCT2_GLOBAL(RCT2_ADDRESS_GAME_PAUSED, uint8) = savedPausedState;
	} else {
		window_ride_main_open(rideIndex);
	}
}

/**
 *
 * rct2: 0x006C6E14
 */
static void window_ride_construction_mouseup()
{
	short widgetIndex;
	rct_window *w;

	window_widget_get_registers(w, widgetIndex);

	RCT2_CALLPROC_X(0x006C6A77, 0, 0, 0, 0, 0, 0, 0);

	switch (widgetIndex){
	case WIDX_CLOSE:
		window_close(w);
		break;
	case 27:
		RCT2_CALLPROC_X(0x006C9296, 0, 0, 0, widgetIndex, (int)w, 0, 0);
		break;
	case 26:
		RCT2_CALLPROC_X(0x006C93B8, 0, 0, 0, widgetIndex, (int)w, 0, 0);
		break;
	case 23:
		RCT2_CALLPROC_X(0x006C9F72, 0, 0, 0, widgetIndex, (int)w, 0, 0);
		break;
	case WIDX_DEMOLISH:
		window_ride_construction_mouseup_demolish(w);
		break;
	case 32:
		RCT2_CALLPROC_X(0x006C78AA, 0, 0, 0, widgetIndex, (int)w, 0, 0);
		break;
	case 29:
		RCT2_CALLPROC_X(0x006C7802, 0, 0, 0, widgetIndex, (int)w, 0, 0);
		break;
	case 30:
		RCT2_CALLPROC_X(0x006C7866, 0, 0, 0, widgetIndex, (int)w, 0, 0);
		break;
	}
}

/**
 *
 * rct2: 0x006C9BA5
 */
static void window_ride_construction_mouseup_demolish(rct_window* w)
{
	RCT2_CALLPROC_X(0x006C9BA5, 0, 0, 0, 0, (int)w, 0, 0);
	return;

	RCT2_GLOBAL(0x00F44070, uint32) = 0x80000000;
	sub_6C9627();

	RCT2_GLOBAL(0x00F440B8, uint8) = 3;
	if (RCT2_GLOBAL(0x00F440A6, uint8) == 1) {
		//6C9C4F
	}

	if (RCT2_GLOBAL(0x00F440A6, uint8) != 2) {
		//6c9cc4
		int eax = RCT2_GLOBAL(0x00F440A8, uint16),
			ebx = RCT2_GLOBAL(0x00F440AF, uint8) || (RCT2_GLOBAL(RCT2_ADDRESS_TRACK_PREVIEW_ROTATION, uint8) << 8),
			ecx = RCT2_GLOBAL(0x00F440AA, uint16),
			edx = RCT2_GLOBAL(0x00F440AC, uint16);

		sub_6C683D(&eax, &ecx, edx, RCT2_GLOBAL(RCT2_ADDRESS_TRACK_PREVIEW_ROTATION, uint8), RCT2_GLOBAL(0xF440AF, uint8) & 0x3FF, 0, 0, 0);
	}

	int ride_id = RCT2_GLOBAL(0x00F440A7, uint8);
	RCT2_GLOBAL(0x00F441D2, uint8) = ride_id;
	//6c9BFE
}

/**
 *
 * rct2: 0x006CD435
 */
static void window_ride_construction_maze_invalidate()
{
	int rideIndex = RCT2_GLOBAL(0x00F440A7, uint8);
	rct_ride *ride = GET_RIDE(rideIndex);

	// Set window title arguments
	RCT2_GLOBAL(0x013CE956, uint16_t) = ride->name;
	RCT2_GLOBAL(0x013CE958, uint32_t) = ride->name_arguments;
}

/**
 *
 * rct2: 0x006C6AD5
 */
static void window_ride_construction_invalidate()
{
	rct_window *w;
	rct_ride *ride;
	rct_string_id stringId;
	int rideIndex, previousTrackPieceSlope;

	window_get_register(w);

	rideIndex = RCT2_GLOBAL(0x00F440A7, uint8);
	ride = GET_RIDE(rideIndex);

	previousTrackPieceSlope = RCT2_GLOBAL(0x00F440A0, uint16);
	stringId = STR_RIDE_CONSTRUCTION_SPECIAL;
	if (previousTrackPieceSlope >= 256) {
		stringId = RCT2_ADDRESS(0x00999492, rct_string_id)[previousTrackPieceSlope - 256];
		if (stringId == STR_RAPIDS && ride->type == RIDE_TYPE_CAR_RIDE)
			stringId = STR_LOG_BUMPS;
	}
	RCT2_GLOBAL(0x013CE952, uint16) = stringId;

	if (RCT2_GLOBAL(0x00F440D3, uint8) == 1)
		RCT2_GLOBAL(0x013CE952 + 2, uint16) = ((RCT2_GLOBAL(0x00F440CD, uint8) * 9) >> 2) & 0xFFFF;

	window_ride_construction_widgets[WIDX_SEAT_ROTATION_ANGLE_SPINNER].image =
		STR_RIDE_CONSTRUCTION_SEAT_ROTATION_ANGLE_NEG_180 + RCT2_GLOBAL(0x00F440CF, uint8);

	if (RCT2_GLOBAL(0x00F440D3, uint8) == 2)
		RCT2_GLOBAL(0x013CE952 + 2, uint16) = ((RCT2_GLOBAL(0x00F440CE, uint8) * 9) >> 2) & 0xFFFF;

	// Set window title arguments
	RCT2_GLOBAL(0x013CE952 + 4, uint16) = ride->name;
	RCT2_GLOBAL(0x013CE952 + 6, uint32) = ride->name_arguments;
}

/**
 *
 * rct2: 0x006C6B86
 */
static void window_ride_construction_paint()
{
	rct_window *w;
	rct_drawpixelinfo *dpi;
	rct_widget *widget;

	window_paint_get_registers(w, dpi);

	window_draw_widgets(w, dpi);
	
	widget = &window_ride_construction_widgets[WIDX_CONSTRUCT];
	if (widget->type == WWT_EMPTY)
		return;

	uint32_t eax = 0, esi = (uint32_t)w, ebp = 0;//nothing
	uint32_t ebx = 0, ecx = 0, edx = 0, edi = (uint32_t)dpi;//returns
	if (RCT2_CALLFUNC_X(0x006CA2DF, &eax, &ebx, &ecx, &edx, &esi, &edi, &ebp) & 0x100)
		return;

	RCT2_GLOBAL(0x00F44133, uint8_t) = edx & 0xFF;
	RCT2_GLOBAL(0x00F44134, uint8_t) = (ebx >> 8) & 0xFF;
	RCT2_GLOBAL(0x00F44135, uint8_t) = (edx >> 8) & 0xFF;
	edx >>= 16;
	RCT2_GLOBAL(0x00F44136, int16_t) = edx;
	rct_ride* ride = GET_RIDE(RCT2_GLOBAL(0x00F44133, uint8));
	RCT2_GLOBAL(0x00F44064, uint32_t) = RCT2_GLOBAL(RCT2_ADDRESS_RIDE_FLAGS + ride->type * 8, uint32_t);

	short width = widget->right - widget->left - 1;
	short height = widget->bottom - widget->top - 1;
	rct_drawpixelinfo* clip_dpi = clip_drawpixelinfo(
		dpi,
		w->x + widget->left + 1,
		width,
		w->y + widget->top + 1,
		height
	);
	if (clip_dpi != NULL) {
		rct_preview_track *trackBlock;
		ecx = RCT2_GLOBAL(0x00F44135, uint8_t);
		if (RCT2_GLOBAL(0x00F44064, uint32_t) & 0x80000)
			trackBlock = RCT2_ADDRESS(0x00994A38, rct_preview_track*)[ecx];//RCT2_GLOBAL(0x994A38 + ecx * 4, rct_preview_track*);
		else
			trackBlock = RCT2_ADDRESS(0x00994638, rct_preview_track*)[ecx];//RCT2_GLOBAL(0x994638 + ecx * 4, rct_preview_track*);

		while ((trackBlock + 1)->var_00 != 0xFF)
			trackBlock++;

		short x = trackBlock->x;
		short z = trackBlock->z;
		short y = trackBlock->y;
		if (trackBlock->var_09 & 2) {
			x = 0;
			y = 0;
		}

		short tmp;
		switch (RCT2_GLOBAL(0x00F44134, uint8_t) & 3) {
		case 1:
			tmp = x;
			x = y;
			y = -tmp;
			break;
		case 2:
			x = -x;
			y = -y;
			break;
		case 3:
			tmp = x;
			x = -y;
			y = tmp;
			break;
		case 0:
			break;
		}
		//this is actually case 0, but the other cases all jump to it
		x /= 2;
		y /= 2;
		x += 4112;
		y += 4112;
		z += 1024;
		ebx = RCT2_GLOBAL(0x00F44135, uint8_t);
		short bx;
		if (RCT2_GLOBAL(0x00F44064, uint32_t) & 0x80000)
			bx = RCT2_GLOBAL(0x009984A2 + ebx * 8, uint8_t);
		else
			bx = RCT2_GLOBAL(0x00997CA2 + ebx * 8, uint8_t);
		z -= bx;
		int start_x = x;
		switch (RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_ROTATION, uint32_t)) {
		case 0:
			x = y - x;
			y = (y + start_x) / 2 - z;
			break;
		case 1:
			x = -x - y;
			y = (y - start_x) / 2 - z;
			break;
		case 2:
			x -= y;
			y = (-y - start_x) / 2 - z;
			break;
		case 3:
			x += y;
			y = (-y + start_x) / 2 - z;
			break;
		}
		clip_dpi->x += x - width / 2;
		clip_dpi->y += y - height / 2 - 16;
		RCT2_GLOBAL(0x140E9A8, rct_drawpixelinfo*) = clip_dpi;
		uint32_t d = RCT2_GLOBAL(0xF44136, int16_t) << 16;
		d |= RCT2_GLOBAL(0x00F44133, uint8_t);
		d |= RCT2_GLOBAL(0x00F44135, uint8_t) << 8;
		RCT2_CALLPROC_X(0x006CBCE2, 0x1000, (((uint16_t)bx) & 0xFF) | (RCT2_GLOBAL(0xF44134, uint8_t) << 8), 0x1000, d, width, 0x400, height);
		rct2_free(clip_dpi);
	}

	short string_x = (widget->left + widget->right) / 2 + w->x;
	short string_y = widget->bottom + w->y - 23;
	if (RCT2_GLOBAL(0x00F440A6, uint8_t) != 4)
		gfx_draw_string_centred(dpi, 1407, string_x, string_y, 0, w);

	string_y += 11;
	if (RCT2_GLOBAL(0x00F44070, uint32_t) != 0x80000000 && !(RCT2_GLOBAL(RCT2_ADDRESS_PARK_FLAGS, uint32_t) & 0x800))
		gfx_draw_string_centred(dpi, 1408, string_x, string_y, 0, (void*)0x00F44070);
}

/**
 *
 * rct2: 0x006CD45B
 */
static void window_ride_construction_maze_paint()
{
	rct_window *w;
	rct_drawpixelinfo *dpi;

	window_paint_get_registers(w, dpi);
	
	window_draw_widgets(w, dpi);
}