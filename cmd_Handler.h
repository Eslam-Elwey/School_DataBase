#ifndef CMD_HANDLER_H
#define CMD_HANDLER_H


/****************** INCLUDES ************************/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>   
#include "STD_Types.h"

/**********_Normal_Colors_Define_***********/
#define TEXT_Sky	    3U
#define TEXT_Red	    4U
#define TEXT_DPurple	5U 
#define TEXT_DYellow	6U
#define TEXT_DWhite	    7U
#define TEXT_Gray	    8U
#define TEXT_Blue	    9U
#define TEXT_Green	    10U
#define TEXT_Cyan	    11U
#define TEXT_Pink	    12U
#define TEXT_LPurple	13U
#define TEXT_LYellow	14U
#define TEXT_LWhite	    15U

/*************** FUNCTION_PROTOTYPE ***************/
void cmdSetConsoleColour(u8 au8Color);
void cmdResetConsoleColour(void);
void cmdGoToXY(u8 au8Xposition, u8 au8Yposition);
void cmdClearScreen(void);
void cmdShowConsoleCursor(u8 au8ShowFlag);
void cmdDelay(u32 DelayValue);

#endif /* CMD_HANDLER_H */