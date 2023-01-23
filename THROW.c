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

void Render_Ball(int x, int y, int clear){
    if(clear==0){
        Bdisp_DrawLineVRAM(x-1,y+2,x+1,y+2);
        Bdisp_DrawLineVRAM(x-2,y+1,x+2,y+1);
        Bdisp_DrawLineVRAM(x-2,y,x+2,y);
        Bdisp_DrawLineVRAM(x-2,y-1,x+2,y-1);
        Bdisp_DrawLineVRAM(x-1,y-2,x+1,y-2);
    }else if(clear==1){
        Bdisp_ClearLineVRAM(x-1,y+2,x+1,y+2);
        Bdisp_ClearLineVRAM(x-2,y+1,x+2,y+1);
        Bdisp_ClearLineVRAM(x-2,y,x+2,y);
        Bdisp_ClearLineVRAM(x-2,y-1,x+2,y-1);
        Bdisp_ClearLineVRAM(x-1,y-2,x+1,y-2);
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
    unsigned char seconds[2]={0x22,0};

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
        sh = (pow(startvelocity, 2)*pow((sin(rad)), 2)/(2*gravitationalforce));
        th = ((startvelocity*sin(rad))/gravitationalforce);

        Print_Float(86,16, sw, 0);
        PrintXY(117,16, (unsigned char*)"m        ",0);
        Print_Float(86,26, sh, 0);
        PrintXY(117,26, (unsigned char*)"m        ",0);
        Print_Float(86,36, th, 0);
        PrintXY(117,36, (unsigned char*)"         ",0);
        PrintXY(117,36, seconds,0);
    }

    Bdisp_PutDisp_DD();
}

Render_GRAPH(int x, int y, int xmax, int ymax, double sw, double sh, int angle, float gravitationalforce, float startvelocity, int ball){
    double xstep;
    int iteration = 0;
    float ypoint;
    float rad;
    float yscale;
    rad = (angle/180.0)*3.141592;

    Bdisp_DrawLineVRAM(x,y,x,y+50);
    Bdisp_DrawLineVRAM(x-2,y+48,x+120,y+48);

    Bdisp_PutDisp_DD();

    xstep = 1.00/(120.00/xmax);
    yscale = (50/ymax);
    if(yscale<0){
        yscale = 1;
    }


    while(iteration<121){
        // x = xstep*iteration
        ypoint = tan(rad)*(xstep*iteration)-(gravitationalforce/(2*pow(startvelocity,2)*cos(rad)*cos(rad)))*pow((xstep*iteration),2);
        // Print_Float(90,30,xstep,1);
        // Print_Float(90,36,yscale,1);

        if(ball==0){
            Bdisp_SetPoint_VRAM(iteration+5, ypoint*-1*yscale+48 ,1);
        }else if(ball==1){
            Bdisp_DrawLineVRAM(x,y,x,y+50);
            Bdisp_DrawLineVRAM(x-2,y+48,x+120,y+48);
            Render_Ball(iteration+5, ypoint*-1*yscale+48,0);
            Bdisp_PutDisp_DD();
            Render_Ball(iteration+5, ypoint*-1*yscale+48,1);
            Sleep(20);
        }

        if(ypoint<(-2)){
                break;
        }
        
        iteration = iteration + 1;
    }

    //(0|0) = x|y+48
    // Render_Ball(x,y+48);
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
    int helpy = -28;
    int type = 0;

    float rad;

    int angle;
    float startvelocity;
    float gravitationalforce;

    double sw = 0.0;
    double sh = 0.0;
    double th = 0.0;

    Bdisp_AllClr_DDVRAM(); 
    

    angle = 45;
    startvelocity = 5;
    gravitationalforce = 9.81;
    Render_Main(angle, startvelocity, gravitationalforce, type);
    varselected = Render_Indacator(varselected);

    while(1){
	    GetKey(&key);

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
                    startvelocity = 5.0;
                    gravitationalforce = 9.81;
                    break;
                }else if(key==KEY_CTRL_F6){
                    break;
                }
            }
        } 

        if(key==KEY_CTRL_F4){
            rad = (angle/180.0)*3.141592;
            sw = ((pow(startvelocity, 2)*sin(2*rad))/gravitationalforce);
            sh = (pow(startvelocity, 2)*pow((sin(rad)), 2)/(2*gravitationalforce));
            th = ((startvelocity*sin(rad))/gravitationalforce);

            Bdisp_AllClr_DDVRAM();
            Render_F_Button(1,58, "EXIT");
            Render_F_Button(110,58, "PLAY");
            Render_GRAPH(3, 5, sw+5, sh+2, sw , sh, angle, gravitationalforce, startvelocity,0);

            while(1){
                GetKey(&key);

                Render_F_Button(1,58, "EXIT");
                Render_F_Button(110,58, "PLAY");

                Render_GRAPH(3, 5, sw+5, sh+2, sw , sh, angle, gravitationalforce, startvelocity,0);
                
                if(key==KEY_CTRL_F6){
                    //(0|0) = x|y+48
                    Render_GRAPH(3, 5, sw+5, sh+2, sw , sh, angle, gravitationalforce, startvelocity,1);
                }

                if(key==KEY_CTRL_F1){
                    Render_Main(angle, startvelocity, gravitationalforce, type);   
                    varselected = Render_Indacator(varselected);
                    break;
                }
            }
        }

        if(key==KEY_CTRL_F5){

            Bdisp_AllClr_DDVRAM();
            PrintXY(55,7,(unsigned char*)"Press EXE", 0);
            PrintXY(55,15,(unsigned char*)"to continue", 0);
            //Print Page
            Bdisp_DrawLineVRAM(5,5,45,5);
            Bdisp_DrawLineVRAM(5,50,45,50);
            Bdisp_DrawLineVRAM(5,5,5,50);
            Bdisp_DrawLineVRAM(45,5,45,50);
            PrintXY(7,7,(unsigned char*)"HELP", 0);
            //display lines
            Bdisp_DrawLineVRAM(7,18,40,18);
            Bdisp_DrawLineVRAM(7,22,36,22);
            Bdisp_DrawLineVRAM(7,26,37,26);

            Bdisp_DrawLineVRAM(7,33,40,33);
            Bdisp_DrawLineVRAM(7,37,38,37);
            Bdisp_DrawLineVRAM(7,41,34,41);

            Render_F_Button(1,58, "EXIT");
            Render_F_Button(23,58, "EXE ");

            while(1){
                GetKey(&key);

                Bdisp_AllClr_DDVRAM();
                Render_F_Button(1,58, "EXIT");

                if(key==KEY_CTRL_F1){
                    Render_Main(angle, startvelocity, gravitationalforce, type);   
                    varselected = Render_Indacator(varselected);
                    break;
                }

                if(key==KEY_CTRL_DOWN){
                    helpy = helpy +12;
                }

                if(key==KEY_CTRL_UP){
                    helpy = helpy -12;
                }

                if(key==KEY_CTRL_F5){
                    helpy = -28;
                }

                if(key==KEY_CTRL_F6){
                    helpy = 152;
                }

                PrintMini(2,-16-helpy,(unsigned char*)"(c) 2023 Felix Wittwer",MINI_OVER);
			    PrintMini(2,-10-helpy,(unsigned char*)"Version 1.0",MINI_OVER);

                PrintXY(2,2-helpy,(unsigned char*)"How to use HELP", 0);
                PrintMini(2,16-helpy,(unsigned char*)"Use arrows UP and DOWN to",MINI_OVER);
                PrintMini(2,22-helpy,(unsigned char*)"scroll up and down.",MINI_OVER);

                PrintXY(2,36-helpy,(unsigned char*)"Main", 0);
                PrintMini(2,50-helpy,(unsigned char*)"Use arrows UP and DOWN to",MINI_OVER);
                PrintMini(2,56-helpy,(unsigned char*)"control the cursor on the left.",MINI_OVER);

                PrintMini(2,68-helpy,(unsigned char*)"Use arrows LEFT and RIGHT",MINI_OVER);
                PrintMini(2,74-helpy,(unsigned char*)"to change the value on the",MINI_OVER);
                PrintMini(2,80-helpy,(unsigned char*)"right side of the cursor.",MINI_OVER);

                PrintMini(2,92-helpy,(unsigned char*)"[DEL] F2",MINI_OVER);
                PrintMini(2,98-helpy,(unsigned char*)"Sets all values to their",MINI_OVER);
                PrintMini(2,104-helpy,(unsigned char*)"standard value.",MINI_OVER);

                PrintMini(2,116-helpy,(unsigned char*)"[CALC] F3",MINI_OVER);
                PrintMini(2,122-helpy,(unsigned char*)"calculates sw , sh , th",MINI_OVER);
                PrintMini(2,128-helpy,(unsigned char*)"sw = thrown distance",MINI_OVER);
                PrintMini(2,134-helpy,(unsigned char*)"sh = max height during throw",MINI_OVER);
                PrintMini(2,140-helpy,(unsigned char*)"th = time to reach max height",MINI_OVER);

                PrintMini(2,152-helpy,(unsigned char*)"[SIM] F4",MINI_OVER);
                PrintMini(2,158-helpy,(unsigned char*)"draws a graph with the",MINI_OVER);
                PrintMini(2,164-helpy,(unsigned char*)"calculated values.",MINI_OVER);

                PrintMini(2,176-helpy,(unsigned char*)"[HELP] F5",MINI_OVER);
                PrintMini(2,182-helpy,(unsigned char*)"You probably found out the",MINI_OVER);
                PrintMini(2,188-helpy,(unsigned char*)"function of this key at this",MINI_OVER);
                PrintMini(2,194-helpy,(unsigned char*)"point.",MINI_OVER);

                Render_F_Button(1,58, "EXIT");
                Render_F_Button(88,58, "TOP ");
                Render_F_Button(110,58, "BTM ");
            }
        }        

        if(key==KEY_CTRL_DOWN){
            varselected = varselected+1;
        }else if(key==KEY_CTRL_UP){
            varselected = varselected-1;
        }

        if(varselected==1){
            if(key==KEY_CTRL_RIGHT){
                angle = angle+1;
            }else if(key==KEY_CTRL_LEFT){
                angle = angle-1;
            }   
        }

        if(varselected==2){
            if(key==KEY_CTRL_RIGHT){
                startvelocity = startvelocity+0.2;
            }else if(key==KEY_CTRL_LEFT){
                startvelocity = startvelocity-0.2;
            }   
        }

        if(varselected==3){
            if(key==KEY_CTRL_RIGHT){
                gravitationalforce = gravitationalforce+0.01;
            }else if(key==KEY_CTRL_LEFT){
                gravitationalforce = gravitationalforce-0.01;
            }   
        }

        if(key==KEY_CTRL_F3){
            type = 1;
        }else{
            type = 0;
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

