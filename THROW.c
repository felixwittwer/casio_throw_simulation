/*************************************************************/
/** throwing calculation and simulation                     **/
/**                                                         **/
/** @author Felix Wittwer                                   **/
/**                                                         **/
/** @file THROW.c                                           **/
/**                                                         **/
/** @date 01-15-2023                                        **/
/*************************************************************/
#include <stdio.h>
#include <math.h>
#include <mathf.h>
#include "fxlib.h"

void Print_Float(int x, int y, float f, int mini){
    unsigned char buffer[9];
    sprintf(buffer, "%lf", f);
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

int Render_Indacator(int varselected){
    unsigned char indicator[3]={0xE6,0x91,0};

    if(varselected==1){
        // Render_Indacator(3,16);
        PrintXY(3, 16, indicator, 0);
    }else if(varselected==2){
        // Render_Indacator(3,26)
        PrintXY(3, 26, indicator, 0);
    }else if(varselected==3){
        // Render_Indacator(3,37);
        PrintXY(3, 37, indicator, 0);
    }else if(varselected>3){
        varselected = 1;
        // Render_Indacator(3,16);
        PrintXY(3, 16, indicator, 0);
    }else if(varselected<1){
        varselected = 3;
        // Render_Indacator(3,37);
        PrintXY(3, 37, indicator, 0);
    }
    return varselected;
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

void Render_Main(int angle, float startvelocity, float gravitationalforce, int type){
    unsigned char alpha[3]={0xE6,0x40,0};
    unsigned char zero[3]={0xE5,0xD0,0};
    unsigned char degree[2]={0x8C,0};

    double sw = 0.0;
    double sh = 0.0;
    double th = 0.0;

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

    Print_Int(31, 16, angle, 0);
    PrintXY(50,16, degree, 0);
    Print_Float(31, 26, startvelocity, 0);
    PrintXY(56,26, (unsigned char*)"        ",0);
    Print_Float(31, 37, gravitationalforce, 0);
    PrintXY(56,37, (unsigned char*)"        ",0);

    PrintMini(72,18, (unsigned char*)"w",MINI_OVER);
    PrintXY(65,16, (unsigned char*)"s",0);
    PrintXY(78,17, (unsigned char*)"=",0);

    PrintMini(72,28, (unsigned char*)"h",MINI_OVER);
    PrintXY(65,26, (unsigned char*)"s",0);
    PrintXY(78,27, (unsigned char*)"=",0);

    PrintMini(72,38, (unsigned char*)"h",MINI_OVER);
    PrintXY(65,36, (unsigned char*)"t",0);
    PrintXY(78,37, (unsigned char*)"=",0);

    PrintXY(86,16, (unsigned char*)"        ",0);
    PrintXY(86,26, (unsigned char*)"        ",0);
    PrintXY(86,36, (unsigned char*)"        ",0);

    if(type==1){
        float rad;
        rad = (angle/180.0)*3.141592;
        sw = ((pow(startvelocity, 2)*sin(2*rad))/gravitationalforce);
        // correct math.h sin behaviour when alpha = 45
        if(angle==45){
            sw = (pow(startvelocity, 2)/gravitationalforce);
        }
        Print_Float(86,16, sw, 0);
        PrintXY(117,16, (unsigned char*)"m        ",0);
        Print_Float(86,26, sh, 0);
        PrintXY(117,26, (unsigned char*)"        ",0);
        Print_Float(86,36, th, 0);
        PrintXY(117,36, (unsigned char*)"        ",0);
    }

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
    int type = 0;

    int angle;
    float startvelocity;
    float gravitationalforce;

    Bdisp_AllClr_DDVRAM(); 
    

    angle = 45;
    startvelocity = 5;
    gravitationalforce = 9.81;
    Render_Main(angle, startvelocity, gravitationalforce, type);
    varselected = Render_Indacator(varselected);

    while(1){
	    GetKey(&key);
        Render_Main(angle, startvelocity, gravitationalforce, type);

        if(key==KEY_CTRL_F3){
            type = 1;
        }else{
            type = 0;
        }

        if(key==KEY_CTRL_F2){
            PopUpWin(4);
            PrintXY(12,8, (unsigned char*)"Delete All?",0);
            PrintXY(30,24, (unsigned char*)"Yes:[F1]",0);
            PrintXY(30,32, (unsigned char*)"No :[F6]",0);
            while(1){
                GetKey(&key);
                if(key==KEY_CTRL_F1){
                    varselected = 1;
                    angle = 45;
                    startvelocity = 0.0;
                    gravitationalforce = 9.81;
                    break;
                }else if(key==KEY_CTRL_F6){
                    break;
                }
            }
        }

        Render_Main(angle, startvelocity, gravitationalforce, type);
        varselected = Render_Indacator(varselected);      

        if(key==KEY_CTRL_DOWN){
            varselected = varselected+1;
        }else if(key==KEY_CTRL_UP){
            varselected = varselected-1;
        }
        varselected = Render_Indacator(varselected);

        if(varselected==1){
            if(key==KEY_CTRL_RIGHT){
                angle = angle+1;
            }else if(key==KEY_CTRL_LEFT){
                angle = angle-1;
            }   
        }

        if(varselected==2){
            if(key==KEY_CTRL_RIGHT){
                startvelocity = startvelocity+0.1;
            }else if(key==KEY_CTRL_LEFT){
                startvelocity = startvelocity-0.1;
            }   
        }

        if(varselected==3){
            if(key==KEY_CTRL_RIGHT){
                gravitationalforce = gravitationalforce+0.01;
            }else if(key==KEY_CTRL_LEFT){
                gravitationalforce = gravitationalforce-0.01;
            }   
        }

        Render_Main(angle, startvelocity, gravitationalforce, type);   
        varselected = Render_Indacator(varselected);
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

