/*************************************************************/
/** throwing calculation and simulation                     **/
/**                                                         **/
/** @author Felix Wittwer                                   **/
/**                                                         **/
/** @file THROW.c                                           **/
/**                                                         **/
/** @date 01-14-2023                                        **/
/*************************************************************/
#include <stdio.h>
#include <math.h>
#include "fxlib.h"

void Print_Float(int x, int y, float f, int mini){
    unsigned char buffer[9];
    sprintf(buffer, "%f", f);
    if(mini==0){
        PrintXY(x,y,buffer,0);
    }else if(mini==1){
        PrintMini(x,y,buffer, MINI_OVER);
    }
}

void Print_Int(int x, int y, int i, int mini){
    unsigned char buffer[9];
    sprintf(buffer, "%d", i);
    if(mini==0){
        PrintXY(x,y,buffer,0);
    }else if(mini==1){
        PrintMini(x,y,buffer, MINI_OVER);
    }
}

void Render_Indacator(int x, int y){
    unsigned char up[3]={0xE6,0x91,0};
    PrintXY(x, y, up, 0);
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

void Render_Main(){
    unsigned char alpha[3]={0xE6,0x40,0};
    unsigned char zero[3]={0xE5,0xD0,0};

    Bdisp_AllClr_DDVRAM();

    PrintMini(2,2, (unsigned char*)"Throw simulation",MINI_OVER);
    Render_F_Button(1,58, "EXIT");
    Render_F_Button(23,58, "DEL ");
    Render_F_Button(45,58, "CALC");
    Render_F_Button(67,58, "SIM ");
    Render_F_Button(89,58, "HELP");

    PrintXY(11,16, alpha, 0);
    PrintXY(23,17, (unsigned char*)"=",0);
    
    PrintXY(16,27, zero, 0);
    PrintXY(11,26, (unsigned char*)"v",0);
    PrintXY(23,27, (unsigned char*)"=",0);

    PrintXY(11,37, (unsigned char*)"g",0);
    PrintXY(23,37, (unsigned char*)"=",0);

    Bdisp_PutDisp_DD();
}

void Render_Var(angle, startvelocity, gravitationalforce){
    Print_Float(31, 37, gravitationalforce, 0);
    Print_Int(31, 16, angle, 0);
    Print_Int(31, 26, startvelocity, 0);
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
    Render_Main();
    Render_Indacator(3,16);

    angle = 0;
    startvelocity = 0;
    gravitationalforce = 9.81;

    while(1){
	    GetKey(&key);
        Render_Main();
        Render_Var(angle, startvelocity, gravitationalforce);

        if(key==KEY_CTRL_DOWN){
            varselected = varselected+1;
        }else if(key==KEY_CTRL_UP){
            varselected = varselected-1;
        }

        if(varselected==1){
            Render_Indacator(3,16);
        }else if(varselected==2){
            Render_Indacator(3,26);
        }else if(varselected==3){
            Render_Indacator(3,37);
        }else if(varselected <1||varselected>3){
            varselected = 1;
            Render_Indacator(3,16);
        }

        if(key==KEY_CTRL_RIGHT&&varselected==1){
            angle = angle+1;
        }else if(key==KEY_CTRL_RIGHT&&varselected==2){
            startvelocity = startvelocity+1;
        }
        Render_Var(angle, startvelocity, gravitationalforce);


        if(key==KEY_CTRL_F2){
            PopUpWin(4);
            PrintXY(12,8, (unsigned char*)"Delete All?",0);
            PrintXY(30,24, (unsigned char*)"Yes:[F1]",0);
            PrintXY(30,32, (unsigned char*)"No :[F6]",0);
            while(1){
                GetKey(&key);
                if(key==KEY_CTRL_F1){
                    break;
                }else if(key==KEY_CTRL_F6){
                    angle = 0;
                    startvelocity = 0;
                    gravitationalforce = 9.81;
                    varselected = 1;
                    break;
                }
            }
            Render_Main();    
        }
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
//  Render_MainSystem
//
//  param   :   isAppli   : 1 = Application / 0 = eActivity
//              OptionNum : Option Number (only eActivity)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int Render_MainSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section

