/*****************************************************************/
/*                                                               */
/*   CASIO fx-9860G SDK Library                                  */
/*                                                               */
/*   File name : [ProjectName].c                                 */
/*                                                               */
/*   Copyright (c) 2006 CASIO COMPUTER CO., LTD.                 */
/*                                                               */
/*****************************************************************/
#include "fxlib.h"

void IL_Print_Float(int x, int y, int f){
    unsigned char buffer[9];
    sprintf(buffer, "%f", f);
    PrintXY(x,y,buffer,0);
}

void Render_Arrows(int x, int y){
    unsigned char up[3]={0xE6,0x9C,0};
    unsigned char down[3]={0xE6,0x9D,0};

    PrintXY(x, y-6, up, 0);
    PrintXY(x, y+8, down, 0);
}

void Render_F_Button(int x, int y, unsigned char *str){
    Bdisp_DrawLineVRAM(x, y-1, x+17, y-1);
    Bdisp_DrawLineVRAM(x-1, y-1, x-1, y+5);
    Bdisp_DrawLineVRAM(x+17, y-1, x+17, y+5);
    Bdisp_DrawLineVRAM(x+16, y-1, x+16, y+5);
    PrintMini(x,y, str, MINI_REV);

    Bdisp_ClearLineVRAM(x+17, y+4, x+15, y+6);
    Bdisp_ClearLineVRAM(x+17, y+5, x+16, y+6);
    Bdisp_SetPoint_VRAM(x+17, y+6, 0);
}

void Initialize(){
    unsigned char alpha[3]={0xE6,0x40,0};
    unsigned char zero[3]={0xE5,0xD0,0};

    Bdisp_AllClr_DDVRAM();

    PrintMini(2,2, (unsigned char*)"Throw simulation",MINI_OVER);
    Render_F_Button(2,58, "EXIT");
    Render_F_Button(24,58, "DEL ");
    Render_F_Button(46,58, "CALC");
    Render_F_Button(68,58, "SIM ");

    PrintXY(5,16, alpha, 0);
    PrintXY(17,17, (unsigned char*)"=",0);
    
    PrintXY(10,27, zero, 0);
    PrintXY(5,26, (unsigned char*)"v",0);
    PrintXY(17,27, (unsigned char*)"=",0);

    PrintXY(5,37, (unsigned char*)"g",0);
    PrintXY(17,37, (unsigned char*)"=",0);


    Bdisp_PutDisp_DD();
}


//****************************************************************************
//  AddIn_main (Sample program main function)
//
//  param   :   isAppli   : 1 = This application is launched by MAIN MENU.
//                        : 0 = This application is launched by a strip in eACT application.
//
//              OptionNum : Strip number (0~3)
//                         (This parameter is only used when isAppli parameter is 0.)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int AddIn_main(int isAppli, unsigned short OptionNum)
{
    unsigned int key;

    int varselected = 1;

    unsigned int angle;
    unsigned int startvelocity;
    float gravitationalforce;

    Bdisp_AllClr_DDVRAM();
    Initialize();

    angle = 0;
    startvelocity = 0;
    gravitationalforce = 9.81;

    while(1){
	    GetKey(&key);
        Initialize();

        if(key==KEY_CTRL_F2){
            PopUpWin(4);
            PrintXY(12,8, (unsigned char*)"Delete All?",0);
            PrintXY(30,24, (unsigned char*)"Yes:[F1]",0);
            PrintXY(30,32, (unsigned char*)"No :[F6]",0);
            if(key==KEY_CTRL_F1){
                break;
            }else if(key==KEY_CTRL_F6){
                angle = 0;
                startvelocity = 0;
                gravitationalforce = 9.81;
                break;
            }
        }

        // Render_Arrows(24, 16);


    }

    return 1;
}




//****************************************************************************
//**************                                              ****************
//**************                 Notice!                      ****************
//**************                                              ****************
//**************  Please do not change the following source.  ****************
//**************                                              ****************
//****************************************************************************


#pragma section _BR_Size
unsigned long BR_Size;
#pragma section


#pragma section _TOP

//****************************************************************************
//  InitializeSystem
//
//  param   :   isAppli   : 1 = Application / 0 = eActivity
//              OptionNum : Option Number (only eActivity)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section

