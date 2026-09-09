// Copyright 2026 Beanie "Code/Tech" - All Rights Reserved
#define UNICODE
#define _UNICODE
#define Short_Wall 36
#define WallNum 15
#define bulletNum 15
#include <windows.h>
#include <mmsystem.h>

//keep in mind I forgot about this project in May then came back to it in late august. So if some stuff is inconsistant that's why
// Especially since I kind of forgot my programming conventions for this File.


// Game States 0-4 are being used as of 2026-09-02

//Bg/Tiles data

// REMEMBER 255 is BLACK 0 TRANS 
//Functions use this global space
//SPRITE CHARS
unsigned char SnowIceTile[64] = {
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    7, 4, 4, 7, 7, 4, 4, 4,
    6, 7, 6, 6, 7, 4, 6, 7,
    7, 6, 7, 6, 6, 4, 7, 6,
    7, 7, 7, 7, 6, 6, 7, 7,
    7, 7, 7, 6, 7, 7, 7, 7,
};
unsigned char SnowCoveredDirt[64] = {
    7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7,
    255, 255, 7, 7, 255, 255, 7, 7,
    8, 8, 255, 255, 8, 8, 255, 255,
    9, 9, 8, 8, 9, 9, 8, 8,
    9, 8, 9, 9, 9, 9, 8, 9,
    9, 8, 9, 8, 8, 9, 8, 9,
    8, 9, 9, 9, 8, 9, 9, 8,
};
unsigned char IceWallLower[64] = {
    7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7,
    6, 7, 6, 7, 7, 6, 6, 6,
    7, 6, 7, 6, 6, 6, 7, 6,
    4, 7, 7, 6, 7, 6, 4, 4,
    4, 4, 4, 7, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
};
unsigned char IceWallUpper[64] = {
    0, 4, 4, 4, 4, 0, 0, 0,
    4, 4, 4, 4, 4, 4, 4, 0,
    4, 4, 6, 4, 6, 4, 4, 4,
    4, 6, 7, 6, 7, 6, 4, 4,
    6, 7, 7, 7, 7, 6, 6, 4,
    7, 7, 7, 7, 6, 7, 7, 6,
    7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7,
};
unsigned char DirtUpper[64] = {
    9, 9, 9, 8, 9, 9, 9, 9,
    8, 8, 9, 8, 8, 8, 8, 9,
    8, 9, 9, 8, 8, 9, 9, 8,
    9, 9, 8, 8, 9, 255, 8, 8,
    8, 8, 8, 8, 255, 10, 9, 8,
    8, 8, 255, 9, 255, 10, 255, 8,
    8, 255, 8, 255, 10, 10, 10, 255,
    255, 8, 10, 8, 10, 10, 10, 10,
};
unsigned char DirtLower[64] = {
    10, 10, 10, 8, 10, 10, 8, 10,
    10, 10, 8, 8, 8, 8, 10, 8,
    8, 8, 8, 8, 10, 10, 8, 8,
    10, 8, 8, 10, 10, 8, 8, 8,
    10, 8, 10, 8, 10, 8, 10, 8,
    10, 8, 10, 10, 8, 10, 10, 8,
    10, 8, 10, 8, 10, 8, 10, 8,
    8, 10, 8, 8, 8, 10, 8, 10,
};
// < 0 = Black
 
//Sprite Data
unsigned char Efox[256] = {
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 12, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 12, 255, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   255, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   4, 4, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0,
   0, 0, 0, 4, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0,
   0, 0, 0, 0, 4, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
   0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 12, 0, 0, 4,
   0, 0, 0, 0, 0, 13, 0, 13, 0, 0, 14, 0, 14, 0, 0, 0,
   0, 0, 0, 0, 0, 13, 0, 13, 0, 0, 14, 0, 14, 0, 0, 0,
};
unsigned char pengI[144] = {0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 2, 2, 2, 2, 0, 0,
                  0, 0, 2, 2, 2, 2, 2, 2, 0,
                  0, 0, 2, 2, 255, 2, 2, 2, 0,
                  0, 0, 2, 2, 2, 2, 3, 3, 3,
                  0, 0, 2, 2, 2, 2, 2, 2, 0,
                  0, 2, 2, 2, 4, 4, 2, 2, 0,
                  2, 2, 2, 4, 4, 4, 4, 2, 2,
                  2, 2, 2, 4, 4, 4, 4, 2, 2,
                  2, 2, 4, 4, 4, 4, 4, 2, 2,
                  2, 2, 4, 4, 4, 4, 4, 2, 0,
                  0, 2, 2, 4, 4, 4, 4, 2, 0,
                  0, 0, 2, 4, 4, 4, 2, 0, 0,
                  0, 0, 3, 3, 0, 5, 5, 0, 0};
unsigned char pengJump[144] = {
                  0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 2, 2, 2, 2, 0, 0,
                  0, 0, 2, 2, 2, 2, 2, 2, 0,
                  0, 0, 2, 2, 255, 2, 2, 2, 0,
                  0, 0, 2, 2, 2, 2, 3, 3, 3,
                  0, 0, 2, 2, 2, 2, 2, 2, 0,
                  0, 2, 2, 2, 4, 4, 2, 2, 0,
                  2, 2, 2, 4, 4, 4, 4, 2, 2,
                  2, 2, 2, 4, 4, 4, 4, 2, 2,
                  2, 2, 4, 4, 4, 4, 4, 2, 2,
                  2, 2, 4, 4, 4, 4, 4, 2, 0,
                  0, 2, 2, 4, 4, 4, 4, 2, 0,
                  0, 0, 3, 4, 4, 5, 2, 0, 0,
                  0, 0, 3, 0, 0, 5, 0, 0, 0
};
unsigned char pengW1[144] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 2, 2, 2, 2, 0, 0,
    0, 0, 2, 2, 2, 2, 2, 2, 0,
    0, 0, 2, 2, 255, 2, 2, 2, 0,
    0, 0, 2, 2, 2, 2, 3, 3, 3,
    0, 0, 2, 2, 2, 2, 2, 2, 0,
    0, 2, 2, 4, 4, 4, 2, 2, 0,
    2, 2, 4, 4, 4, 4, 2, 2, 2,
    2, 2, 4, 4, 4, 4, 4, 2, 2,
    2, 2, 4, 4, 4, 4, 4, 2, 2,
    2, 2, 4, 4, 4, 4, 4, 2, 0,
    0, 2, 4, 4, 4, 4, 2, 0, 0,
    0, 0, 3, 3, 0, 5, 0, 0, 0,
};
unsigned char pengW2[144] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 2, 2, 2, 2, 0, 0,
    0, 0, 2, 2, 2, 2, 2, 2, 0,
    0, 0, 2, 2, 255, 2, 2, 2, 0,
    0, 0, 2, 2, 2, 2, 3, 3, 3,
    0, 0, 2, 2, 2, 2, 2, 2, 0,
    0, 2, 2, 2, 2, 2, 2, 2, 0,
    2, 2, 2, 4, 4, 4, 2, 2, 2,
    2, 2, 4, 4, 4, 4, 2, 2, 2,
    2, 2, 4, 4, 4, 4, 4, 2, 2,
    2, 2, 4, 4, 4, 4, 4, 2, 0,
    2, 2, 4, 4, 4, 4, 4, 2, 0,
    0, 2, 4, 4, 4, 4, 2, 0, 0,
    0, 0, 3, 3, 5, 0, 0, 0, 0,
};
unsigned char pengW3[144] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 2, 2, 2, 2, 0, 0,
    0, 0, 2, 2, 2, 2, 2, 2, 0,
    0, 0, 2, 2, 255, 2, 2, 2, 0,
    0, 0, 2, 2, 2, 2, 3, 3, 3,
    0, 0, 2, 2, 2, 2, 2, 2, 0,
    0, 2, 2, 2, 4, 4, 2, 2, 0,
    2, 2, 2, 4, 4, 4, 4, 2, 2,
    2, 2, 2, 4, 4, 4, 4, 2, 2,
    2, 2, 4, 4, 4, 4, 4, 2, 2,
    0, 2, 4, 4, 4, 4, 4, 2, 0,
    0, 2, 4, 4, 4, 4, 4, 2, 0,
    0, 2, 2, 4, 4, 4, 4, 2, 0,
    0, 0, 2, 4, 4, 4, 2, 5, 5,
    0, 0, 0, 3, 3, 0, 0, 0, 0,
};
unsigned char pengW4[144] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 2, 2, 2, 2, 0, 0,
    0, 0, 2, 2, 2, 2, 2, 2, 0,
    0, 0, 2, 2, 255, 2, 2, 2, 0,
    0, 0, 2, 2, 2, 2, 3, 3, 3,
    0, 0, 2, 2, 2, 2, 2, 2, 0,
    0, 2, 2, 2, 4, 4, 2, 2, 0,
    2, 2, 2, 4, 4, 4, 4, 2, 2,
    2, 2, 2, 4, 4, 4, 4, 2, 2,
    2, 2, 4, 4, 4, 4, 4, 2, 2,
    2, 2, 4, 4, 4, 4, 4, 2, 0,
    0, 2, 2, 4, 4, 4, 4, 2, 0,
    0, 0, 2, 4, 4, 4, 2, 0, 0,
    0, 0, 3, 3, 0, 0, 5, 5, 0,
};
unsigned char pengW5[144] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 2, 2, 2, 2, 0, 0,
    0, 0, 2, 2, 2, 2, 2, 2, 0,
    0, 0, 2, 2, 255, 2, 2, 2, 0,
    0, 0, 2, 2, 2, 2, 3, 3, 3,
    0, 0, 2, 2, 2, 2, 2, 2, 0,
    0, 2, 2, 4, 4, 4, 2, 2, 0,
    2, 2, 4, 4, 4, 4, 2, 2, 2,
    2, 2, 4, 4, 4, 4, 4, 2, 2,
    2, 2, 4, 4, 4, 4, 4, 2, 2,
    2, 2, 4, 4, 4, 4, 4, 2, 0,
    0, 3, 4, 4, 4, 4, 2, 0, 0,
    0, 3, 0, 0, 0, 0, 5, 5, 0,
};
unsigned char pengW6[144] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 2, 2, 2, 2, 0, 0,
    0, 0, 2, 2, 2, 2, 2, 2, 0,
    0, 0, 2, 2, 255, 2, 2, 2, 0,
    0, 0, 2, 2, 2, 2, 3, 3, 3,
    0, 0, 2, 2, 2, 2, 2, 2, 0,
    0, 2, 2, 2, 2, 2, 2, 2, 0,
    2, 2, 2, 4, 4, 4, 2, 2, 2,
    2, 2, 4, 4, 4, 4, 2, 2, 2,
    2, 2, 4, 4, 4, 4, 4, 2, 2,
    2, 2, 4, 4, 4, 4, 4, 2, 0,
    2, 2, 4, 4, 4, 4, 4, 2, 0,
    0, 3, 3, 4, 4, 4, 2, 0, 0,
    0, 0, 0, 0, 0, 5, 5, 0, 0,
};
unsigned char pengW7[144] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 2, 2, 2, 2, 0, 0,
    0, 0, 2, 2, 2, 2, 2, 2, 0,
    0, 0, 2, 2, 255, 2, 2, 2, 0,
    0, 0, 2, 2, 2, 2, 3, 3, 3,
    0, 0, 2, 2, 2, 2, 2, 2, 0,
    0, 2, 2, 2, 4, 4, 2, 2, 0,
    2, 2, 2, 4, 4, 4, 4, 2, 2,
    2, 2, 2, 4, 4, 4, 4, 2, 2,
    2, 2, 4, 4, 4, 4, 4, 2, 2,
    0, 2, 4, 4, 4, 4, 4, 2, 0,
    0, 2, 4, 4, 4, 4, 4, 2, 0,
    0, 2, 2, 4, 4, 4, 4, 2, 0,
    0, 0, 2, 3, 3, 4, 2, 0, 0,
    0, 0, 0, 0, 0, 5, 5, 0, 0,
};
 
unsigned char* pengWalkCycle[] = {pengI, pengW1, pengW2, pengW3, pengW4, pengW5, pengW6, pengW7, pengJump};
unsigned char pengWCInd = 0;
int pengLength = sizeof(pengWalkCycle) / sizeof(pengWalkCycle[0]);
unsigned int penganim_timer = 0;
 
unsigned char Arrow[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 4, 0, 0, 0,
    0, 0, 0, 0, 4, 4, 0, 0,
    0, 4, 4, 4, 4, 4, 4, 0,
    0, 4, 4, 4, 4, 4, 4, 0,
    0, 0, 0, 0, 4, 4, 0, 0,
    0, 0, 0, 0, 4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
 
//Font
unsigned char letterA[64] = {
                   0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 4, 4, 4, 4, 0, 0,
                   0, 4, 4, 4, 4, 4, 4, 0,
                   0, 4, 4, 0, 0, 4, 4, 0,
                   0, 4, 4, 4, 4, 4, 4, 0,
                   0, 4, 4, 0, 0, 4, 4, 0,
                   0, 4, 4, 0, 0, 4, 4, 0,
                   0, 0, 0, 0, 0, 0, 0, 0,};
unsigned char letterB[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 4, 0, 0,
    0, 0, 4, 4, 0, 0, 4, 0,
    0, 0, 4, 4, 4, 4, 0, 0,
    0, 0, 4, 4, 0, 0, 4, 0,
    0, 0, 4, 4, 0, 0, 4, 0,
    0, 0, 4, 4, 4, 4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char letterC[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 4, 0, 0,
    0, 4, 4, 0, 0, 0, 4, 0,
    0, 4, 4, 0, 0, 0, 0, 0,
    0, 4, 4, 0, 0, 0, 0, 0,
    0, 4, 4, 0, 0, 0, 4, 0,
    0, 0, 4, 4, 4, 4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char letterD[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 4, 4, 4, 4, 4, 0, 0,
    0, 4, 4, 0, 0, 4, 4, 0,
    0, 4, 4, 0, 0, 4, 4, 0,
    0, 4, 4, 0, 0, 4, 4, 0,
    0, 4, 4, 0, 0, 4, 4, 0,
    0, 4, 4, 4, 4, 4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char letterE[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 4, 0, 0,
    0, 0, 4, 4, 4, 4, 0, 0,
    0, 0, 4, 4, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 4, 0, 0,
    0, 0, 4, 4, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char letterF[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 4, 0, 0,
    0, 0, 4, 4, 4, 4, 0, 0,
    0, 0, 4, 4, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 4, 0, 0,
    0, 0, 4, 4, 0, 0, 0, 0,
    0, 0, 4, 4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char letterG[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 4, 0, 0,
    0, 4, 4, 0, 0, 0, 4, 0,
    0, 4, 4, 0, 0, 0, 0, 0,
    0, 4, 4, 0, 0, 4, 4, 0,
    0, 4, 4, 0, 0, 0, 4, 0,
    0, 0, 4, 4, 4, 4, 4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char letterH[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 4, 4, 0, 0, 4, 4, 0,
    0, 4, 4, 0, 0, 4, 4, 0,
    0, 4, 4, 4, 4, 4, 4, 0,
    0, 4, 4, 4, 4, 4, 4, 0,
    0, 4, 4, 0, 0, 4, 4, 0,
    0, 4, 4, 0, 0, 4, 4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char letterI[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 4, 0, 0,
    0, 0, 0, 4, 4, 0, 0, 0,
    0, 0, 0, 4, 4, 0, 0, 0,
    0, 0, 0, 4, 4, 0, 0, 0,
    0, 0, 0, 4, 4, 0, 0, 0,
    0, 0, 4, 4, 4, 4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char letterJ[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 4, 4, 4, 0,
    0, 0, 0, 0, 0, 4, 4, 0,
    0, 0, 0, 0, 0, 4, 4, 0,
    0, 0, 4, 0, 0, 4, 4, 0,
    0, 0, 4, 4, 4, 4, 4, 0,
    0, 0, 0, 4, 4, 4, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char letterK[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 4, 4, 0, 0, 4, 4, 0,
    0, 4, 4, 0, 4, 4, 0, 0,
    0, 4, 4, 4, 4, 0, 0, 0,
    0, 4, 4, 0, 4, 4, 0, 0,
    0, 4, 4, 0, 0, 4, 4, 0,
    0, 4, 4, 0, 0, 4, 4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char letterL[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 4, 4, 0, 0, 0, 0, 0,
    0, 4, 4, 0, 0, 0, 0, 0,
    0, 4, 4, 0, 0, 0, 0, 0,
    0, 4, 4, 0, 0, 0, 0, 0, 
    0, 4, 4, 0, 0, 0, 0, 0,
    0, 4, 4, 4, 4, 4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char letterM[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 4, 4, 0, 4, 0, 0,
    0, 4, 4, 4, 0, 4, 4, 0,
    0, 4, 4, 0, 4, 0, 4, 0,
    0, 4, 4, 0, 4, 0, 4, 0,
    0, 4, 4, 0, 0, 0, 4, 0,
    0, 4, 4, 0, 0, 0, 4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char letterN[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 4, 4, 4, 0, 0, 4, 0,
    0, 4, 4, 4, 0, 0, 4, 0,
    0, 4, 4, 0, 4, 0, 4, 0,
    0, 4, 4, 0, 4, 0, 4, 0,
    0, 4, 4, 0, 0, 4, 4, 0,
    0, 4, 4, 0, 0, 4, 4, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 
};
// O is special as to save space we resuse as 0
unsigned char letterO[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 4, 0, 0,
    0, 4, 4, 0, 0, 4, 4, 0,
    0, 4, 4, 0, 0, 4, 4, 0,
    0, 4, 4, 0, 0, 4, 4, 0,
    0, 4, 4, 0, 0, 4, 4, 0,
    0, 0, 4, 4, 4, 4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char letterP[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 4, 4, 4, 4, 4, 0, 0,
    0, 4, 4, 0, 0, 4, 4, 0,
    0, 4, 4, 0, 0, 4, 4, 0,
    0, 4, 4, 4, 4, 4, 0, 0,
    0, 4, 4, 0, 0, 0, 0, 0,
    0, 4, 4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char letterQ[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 0, 0, 0,
    0, 4, 4, 0, 0, 4, 0, 0,
    0, 4, 4, 0, 0, 4, 0, 0,
    0, 4, 4, 0, 0, 4, 0, 0,
    0, 4, 4, 0, 4, 4, 0, 0,
    0, 0, 4, 4, 4, 4, 4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char letterR[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 4, 4, 4, 4, 4, 0, 0,
    0, 4, 4, 0, 0, 4, 4, 0,
    0, 4, 4, 4, 4, 4, 0, 0,
    0, 4, 4, 4, 4, 0, 0, 0,
    0, 4, 4, 0, 4, 4, 0, 0,
    0, 4, 4, 0, 0, 4, 4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char letterS[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 0, 0, 0,
    0, 4, 4, 0, 0, 4, 0, 0,
    0, 0, 4, 4, 0, 0, 0, 0,
    0, 0, 0, 0, 4, 0, 0, 0,
    0, 4, 0, 0, 4, 4, 0, 0,
    0, 0, 4, 4, 4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char letterS2[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 4, 4, 4, 4, 4, 4, 0,
    0, 4, 4, 0, 0, 0, 0, 0,
    0, 4, 4, 4, 4, 4, 4, 0,
    0, 0, 0, 0, 0, 4, 4, 0,
    0, 0, 0, 0, 0, 4, 4, 0,
    0, 4, 4, 4, 4, 4, 4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char letterT[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 4, 4, 4, 4, 4, 4, 0,
    0, 4, 4, 4, 4, 4, 4, 0,
    0, 0, 0, 4, 4, 0, 0, 0,
    0, 0, 0, 4, 4, 0, 0, 0, 
    0, 0, 0, 4, 4, 0, 0, 0,
    0, 0, 0, 4, 4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char letterU[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 4, 4, 0, 0, 4, 4, 0,
    0, 4, 4, 0, 0, 4, 4, 0,
    0, 4, 4, 0, 0, 4, 4, 0,
    0, 4, 4, 0, 0, 4, 4, 0,
    0, 4, 4, 0, 0, 4, 4, 0,
    0, 0, 4, 4, 4, 4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char letterV[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 4, 4, 0, 0, 0, 4, 0,
    0, 4, 4, 0, 0, 0, 4, 0,
    0, 4, 4, 0, 0, 0, 4, 0,
    0, 4, 4, 0, 0, 0, 4, 0,
    0, 0, 4, 4, 0, 4, 0, 0,
    0, 0, 0, 4, 4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char letterW[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 4 ,4, 0, 0, 0, 4, 0,
    0, 4, 4, 0, 0, 0, 4, 0,
    0, 4, 4, 0, 4, 0, 4, 0,
    0, 4, 4, 0, 4, 0, 4, 0,
    0, 4, 4, 4, 0, 4, 4, 0,
    0, 0, 4, 4, 0, 4, 0, 0,
};
unsigned char letterX[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 4 ,4, 0, 0, 4, 0, 0,
    0, 4, 4, 0, 0, 4, 0, 0,
    0, 0, 4, 4, 4, 0, 0, 0,
    0, 0, 4, 4, 4, 0, 0, 0,
    0, 4, 4, 0, 0, 4, 0, 0,
    0, 4, 4, 0, 0, 4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char letterY[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 4, 4, 0, 0, 4, 0, 0,
    0, 4, 4, 0, 0, 4, 0, 0,
    0, 0, 4, 4, 4, 0, 0, 0,
    0, 0, 0, 4, 4, 0, 0, 0,
    0, 0, 0, 4, 4, 0, 0, 0,
    0, 0, 0, 4, 4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char letterZ[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 4, 4, 4, 4, 4, 4, 0,
    0, 0, 0, 0, 4, 4, 0, 0,
    0, 0, 0, 4, 4, 0, 0, 0,
    0, 0, 4, 4, 0, 0, 0, 0,
    0, 4, 4, 4, 4, 4, 4, 0,
    0, 4, 4, 4, 4, 4, 4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char number1[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 4, 4, 0, 0, 0,
    0, 0, 4, 4, 4, 0, 0, 0,
    0, 0, 0, 4, 4, 0, 0, 0,
    0, 0, 0, 4, 4, 0, 0, 0,
    0, 0, 0, 4, 4, 0, 0, 0,
    0, 0, 4, 4, 4, 4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char number2[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 4, 4, 0, 0, 0,
    0, 0, 4, 0, 0, 4, 0, 0,
    0, 0, 0, 0, 4, 0, 0, 0,
    0, 0, 4, 4, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 4, 0, 0,
    0, 0, 4, 4, 4, 4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char number3[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 4, 4, 0, 0, 0,
    0, 0, 4, 0, 4, 4, 0, 0,
    0, 0, 0, 0, 4, 0, 0, 0,
    0, 0, 0, 0, 4, 4, 0, 0,
    0, 0, 4, 0, 4, 4, 0, 0,
    0, 0, 0, 4, 4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char number4[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 4, 0, 0, 4, 4, 0, 0,
    0, 4, 0, 0, 4, 4, 0, 0,
    0, 4, 0, 0, 4, 4, 0, 0,
    0, 0, 4, 4, 4, 4, 0, 0,
    0, 0, 0, 0, 4, 4, 0, 0,
    0, 0, 0, 0, 4, 4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char number5[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 4, 0, 0,
    0, 0, 4, 4, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 0, 0, 0,
    0, 0, 0, 0, 0, 4, 0, 0,
    0, 0, 0, 0, 0, 4, 0, 0,
    0, 0, 4, 4, 4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
 
};
unsigned char number6[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 4, 4, 0, 0, 0,
    0, 0, 4, 4, 0, 4, 0, 0,
    0, 0, 4, 4, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 0, 0, 0,
    0, 0, 4, 4, 0, 4, 0, 0,
    0, 0, 0, 4, 4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char number7[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 4, 4, 4, 4, 4, 4, 0,
    0, 0, 0, 0, 0, 4, 4, 0,
    0, 0, 0, 0, 4, 4, 0, 0,
    0, 0, 0, 4, 4, 0, 0, 0,
    0, 0, 4, 4, 0, 0, 0, 0,
    0, 4, 4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char number8[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 4, 4, 0, 0, 0,
    0, 0, 4, 0, 4, 4, 0, 0,
    0, 0, 0, 4, 4, 0, 0, 0,
    0, 0, 4, 0, 4, 4, 0, 0,
    0, 0, 4, 0, 4, 4, 0, 0,
    0, 0, 0, 4, 4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char number9[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 4, 0, 0,
    0, 4, 4, 0, 4, 4, 0, 0,
    0, 0, 4, 4, 4, 4, 0, 0,
    0, 0, 0, 0, 4, 4, 0, 0,
    0, 0, 0, 0, 4, 4, 0, 0,
    0, 0, 0, 0, 4, 4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char numberper[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 4, 4, 0, 0, 0,
    0, 0, 0, 4, 4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char SelectBox[64] = {
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 0, 0, 0, 0, 0, 0, 4,
    4, 0, 0, 0, 0, 0, 0, 4,
    4, 0, 0, 0, 0, 0, 0, 4,
    4, 0, 0, 0, 0, 0, 0, 4,
    4, 0, 0, 0, 0, 0, 0, 4,
    4, 0, 0, 0, 0, 0, 0, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
};

unsigned char Bullet[64] = {
    255, 255, 255, 0, 0, 0, 0, 0,
    255, 255, 255, 255, 0, 0, 0, 0,
    255, 255, 255, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

unsigned char Dash[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 4, 4, 4, 4, 4, 4, 0,
    0, 4, 4, 4, 4, 4, 4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char CopyRight[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 4, 4, 4, 4, 0, 0,
    0, 4, 0, 4, 4, 0, 4, 0,
    0, 4, 0, 4, 0, 0, 4, 0,
    0, 4, 0, 4, 0, 0, 4, 0,
    0, 4, 0, 4, 4, 0, 4, 0,
    0, 0, 4, 4, 4, 4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
//End of Images
 
//Structs
typedef struct {
    float x;
    float y;
    unsigned char active;
 
}ShortWall;

typedef struct {
    float x;
    float y;
    float yVel;
    unsigned char active;
}StructBullet;
    //Setting up stuff
ShortWall walls[WallNum];
StructBullet bulletsd[bulletNum];


// ColorPalette
const unsigned int colorpalette[80] = {0x000000, 0x4D4DFF, 0x004ECC, 0xFFD800, 0xFFFFFF, 0xEFC700, 0x639AFC, 0xBED4FC, 0x572903, 0xA05E12, 0x0B371D, 0x735005, 0xFF8707, 0x724A27, 0x562E02}; // 15 ELE TOTAL
// 0/-1 = Black/Transparent, 1 = NESBLUE/SKY, 2 = Fur Peng, 3 = Peng Feet 1, 4 = White, 5 = Peng Feet2, 7 = Ice Blue 1, 6 = Ice Blue 2, 8 = DarkDirt, 9 = Light Dirt
//No.12 = Orange, No. 13 = Brown, No. 14 = dark brown


//States & Stats & Words | Basically Other Section
int GameOverStartx = 112;
int GameOverY = 112;
int GameState = 0;
int TitleNameX = 144 - 39;
int Middlex = 144;
int Middley = 108;
int Rmin = 0;
int Rmax = 1;

 
//Sound Tracks
    //Sq Wave
unsigned char Track1SqGameOver[160] = {
    31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33
};
    // Main game Tracks
unsigned char Track2Sq[160] = {
    31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35
};
    // Tri Wave
unsigned char Track1Tri[160] = {
    31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35
};
    //Track Index
unsigned char GameTIndex = 0;

//Menu tracks
    //Saw Wave
unsigned char SawToothMenu[160] = { // This is nolonger Swatooth Sawtooth was Cut this is Sq
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
};
    //Tri Wave
unsigned char TriMenu[160] = {
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
};
//Track Related Variables
    // Track Index Main
unsigned char TrackInd = 0;
    // Track Index Game Over
unsigned char GameOverTrackInd = 0;
    // Frequency Notes
float NotesFreqs[53] = { 4186.01, 3951.07, 3520.00, 3135.96, 2793.83, 2637.02, 2349.32, 2090.00, 1975.53, 1760.00, 1567.98, 1396.91, 1318.51, 1174.66, 1046.50, 987.77, 880.00, 783.99, 698.46, 659.25, 587.33, 523.25, 493.88, 440.00, 392.00, 349.23, 329.63, 293.66, 261.63, 213.47, 220.00, 196.00, 174.61, 164.81, 146.83, 130.81, 123.47, 110.00, 98.00, 87.31, 82.41, 73.42, 65.41, 61.74, 55.00, 49.00, 43.65, 41.20, 36.71, 32.70, 30.87, 27.50, 0.0};
                        // 0        1       2        3        4        5       6        7         8       9        10        11       12       13        14      15      16      17        18    19      20       21     22       23      24     25       26     27      28      29      30      31       32     33      34      35      36      37      38      39     40     41    42     43     44      45     46    47    48      49     50     51   
// Different Levels for Inf Runner
    //Volume Variables
unsigned char inputPlay = 0;
unsigned char inputPlay2 = 0;
unsigned char JumpPlay = 0;
unsigned int JumpPlayLast = 0;
unsigned int inputPlay2Last = 0;
unsigned char StartButtFlashNum = 0;
unsigned int lastIPlay = 0;
unsigned char maxIplay = 80;
float freq = 440.0f;
float Sound_Inc = 0.0f;
float volume = 4000.0f;
float VolumeAmount = 0.75f;
double phasesaw = 0;
double phasesaw2 = 0;
double phasessq = 0;
double phasessq2 = 0;
double phasetri = 0;
int sample_count = 0; 
//Audio Buffers Last 20ms
short audio_bufferSq[882];
short audio_bufferTri[882];
short audio_bufferSq2[882]; //1.764kb per buffer
//Sound Variables
int SoundSeed = 1;
HWAVEOUT hWaveOut;
WAVEHDR header = {0};
short SbuffA[882], SbuffB[882], SbuffC[882];
WAVEHDR headerA = {0}, headerB = {0}, headerC = {0};
double phase2 = 0.0;
HANDLE hAudioEvent;
 


//Variables
//Window and Looping Variables
unsigned char playing = 1;
void* memory_buffer; //bPtr
HDC memory_dc;
int bW = 288;
int bH = 216;


//Game Variables
float g = 0.1635; //A little stronger than gravity by x10 realgravity is 0.1635
float snow_friction = 0.9;

//Player's Variables
float playerX = 65;
float playerY = 0;
 
int PplayerX = 0;
int PplayerY = 0;
unsigned char backward = 0;
unsigned char forward = 0;
//Velocites
float playerYvel = 0;
float playerXvel = 0;

//Accelerations
float playerXacc = 0;
float playermaxacc = 0.5;
float playermaxvel = 4.5;
float playermaxvelWalk = 1.8;
float playermaxaccWalk = 0.5;

unsigned char playerRun = 0;
unsigned char playerWalk = 0;


//Plr State; Values Ranging form 0-1 ints
int player_state = 0;
//Player Cooldowns & stopping double jump scaling
unsigned char jumpcooldown_max = 250;
unsigned int jumpcooldown_lastjump = 0;
unsigned char falling = 0;
//NON PLAYER THINGS
int GroundOffset = 0;
int GroundOffset2 = 0;

unsigned int CurrentTime = 0; // This is Current Time

int enemyvel = 0;
float Predator_dist = 0;

//Early Variables
//Game Var
unsigned int CooldownJ2 = 0;

unsigned char anim_cooldown = 30;
unsigned char slowdown_wait = 150;
unsigned int last_tick = 0;
int random = 0;
unsigned int lastrandomcheck = 0;
int last_pixelmove = 0;
float current_pixelmove = 0;
unsigned char anim_cooldown_run = 20;
int SpawnMaxLimit = 8000;
unsigned char can_moveX = 1;
unsigned char playerW = 0;
unsigned char playerH = 16;
unsigned char OnGround = 0;
int CollisionBefore = 0;
unsigned int CooldownSlide = 0;

//Start Var
unsigned char start_button_var = 0;
unsigned int lc_start_button = 0;
unsigned int ml_start_button = 150;
unsigned int ArrowY = 0;
unsigned int SettingY = 0;
unsigned int QuitY = 0;
unsigned char settingSelect = 1;

unsigned char bulletVel = 10;

// Game Functions - Not Near the Actual Game
int Noiserandom(void){
    SoundSeed = (int)phase2 * 1103515245 + 31415;//1234567 67 67 67 get it ;D LOL
    return (unsigned int)(SoundSeed / 65536) % 32768;
}
void Yikes(unsigned char* Song, int OctaveDec){
    for(int i = 0; i < 160; i++){
        if(Song[i] + OctaveDec < 52){
            Song[i] += OctaveDec;
        }
    }
}
int my_round(float x){
    if(x < 0){
       return (int)(x - 0.5);
    } else if(x > 0){
       return (int)(x + 0.5);
    } else{ return 0;}
}

unsigned int Unsigned_round(float x){
    if(x < 0){
       return (unsigned int)(1);
    } else if(x > 0){
       return (unsigned int)(x + 0.5);
    } else{ return 0;}
}

void SoundMain(short* buffer, int type, float freq1, double* clock, float vol){ 
    //Init Sound Main
    double phaseinc = freq1 / 44100;
    double currentraw = 0;
    double lastsamp = 0;
    float CorrectVolPer = vol * vol;
    float TrueVol = volume * CorrectVolPer;
    // Main For Loop
    for(int i = 0; i < 882; i++){
        //int x = sample_count % period;
        short sample = 0;
        float tri = 0;
        float saw = 0;
        switch(type) {
            case 0: // Square Wave
                //sample = (x < phase2 / 2) ? volume : -volume;//Use to have period instead of phase
                currentraw = (*clock < 0.5f) ? TrueVol : -TrueVol;
                break;
            case 1: // Traingle Wave
                tri = (*clock * 4.0f) - 2.0f;
                if (tri < 0) {tri = -tri;} 
                currentraw = (short)((tri - 1.0f) * TrueVol);
                break;
            case 2: //Noise Wave
                currentraw = (short)((Noiserandom() % (int)(volume * 2)) - volume);
                break;
            case 3: // Sawtooth wave
                saw = (*clock * 2.0f) - 1.0f;
                currentraw = (short)(saw * (double)TrueVol);
                break;
 
        }
        double smooth = (currentraw + lastsamp) * 0.5;
        lastsamp = currentraw;
        buffer[i] = (short)smooth;
        *clock += phaseinc;
        if(*clock >= 1){*clock -= 1;}
    }
}
void EmptyBuff(short* buffer){
    for(unsigned int i = 0; i < 882; i++){
        buffer[i] = 0;      
    }
}
void InitAudio(){
    WAVEFORMATEX wfx = {WAVE_FORMAT_PCM, 1, 44100, 88200, 2, 16, 0};
    hAudioEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    MMRESULT res = waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, (DWORD_PTR)hAudioEvent, 0, CALLBACK_EVENT);
 
    if (res != MMSYSERR_NOERROR) {
        return; 
    }
    ResetEvent(hAudioEvent);
    // Header A
    headerA.lpData = (LPSTR)SbuffA;
    headerA.dwBufferLength = 882 * sizeof(short);
    waveOutPrepareHeader(hWaveOut, &headerA, sizeof(WAVEHDR));
    //HEADER B
    headerB.lpData = (LPSTR)SbuffB;
    headerB.dwBufferLength = 882 * sizeof(short);
    waveOutPrepareHeader(hWaveOut, &headerB, sizeof(WAVEHDR));
    // HEADER C
    headerC.lpData = (LPSTR)SbuffC;
    headerC.dwBufferLength = 882 * sizeof(short);
    waveOutPrepareHeader(hWaveOut, &headerC, sizeof(WAVEHDR));
    // Send audio buff
    waveOutWrite(hWaveOut, &headerA, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &headerB, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &headerC, sizeof(WAVEHDR));
 // Decrease Frequency of menu tracks
    Yikes(TriMenu, 30);
    Yikes(SawToothMenu, 25);
}
// This inputs sound for different sections
void fillBuffSound(WAVEHDR* hdr, short* Output, float freq) { //
    if(hdr->dwFlags & WHDR_DONE) {
        if(GameState == 0 || GameState == 3){ // Menu SCreens
            SoundMain(audio_bufferSq, 0, NotesFreqs[SawToothMenu[TrackInd]], &phasessq, VolumeAmount); //Square Voice 1
            SoundMain(audio_bufferTri, 1, NotesFreqs[TriMenu[TrackInd]], &phasetri, VolumeAmount); //Triangle Voice
            TrackInd++;
 
            if(TrackInd >= 160){TrackInd = 0;}
        }
        else if(GameState == 2){ // Gameover Screen
            EmptyBuff(audio_bufferTri);

            GameOverTrackInd++;
            if(GameOverTrackInd >= 160){GameOverTrackInd = 0;}
            
            SoundMain(audio_bufferSq, 0, NotesFreqs[Track1SqGameOver[GameOverTrackInd]], &phasessq, VolumeAmount);
        }
        else if(GameState == 1){ // Game Running Screen
            GameTIndex++;
            if(GameTIndex >= 160){GameTIndex = 0;}
            SoundMain(audio_bufferSq, 0, NotesFreqs[Track2Sq[GameTIndex]], &phasessq, VolumeAmount);
            SoundMain(audio_bufferTri, 1, NotesFreqs[Track1Tri[GameTIndex]], &phasetri, VolumeAmount);
        } // if not any then don't play a sound
        else{
            EmptyBuff(audio_bufferTri);
            EmptyBuff(audio_bufferSq);
        }

        if(inputPlay){// Input
            SoundMain(audio_bufferSq2, 0, NotesFreqs[25], &phasessq2, VolumeAmount);
        }
        else if(inputPlay2 == 1){ // Limiting to one input noise
            SoundMain(audio_bufferSq2, 0, NotesFreqs[28], &phasessq2, VolumeAmount);
        }
        else {
            EmptyBuff(audio_bufferSq2);
        }

        if(JumpPlay){ // If jump Play a tri wave. This also Drops Game Running Music Triangle base like the ACTUAL SMB1!
            SoundMain(audio_bufferTri, 1, NotesFreqs[24], &phasessq2, VolumeAmount);
        }
 
        for(int i = 0; i < 882; i++){
            //float mixed = (audio_bufferSaw[i] + audio_bufferSaw2[i] + audio_bufferTri[i]);
            float mixed = (audio_bufferSq[i] + audio_bufferTri[i] + audio_bufferSq2[i]); // Mergin Voices to play
            //int mixed = (audio_bufferSaw[i]);
            if(mixed > 32767){mixed = 32767;}
            if(mixed < -32767){mixed = -32767;}
            Output[i] = (short)mixed;
        }
        waveOutWrite(hWaveOut, hdr, sizeof(WAVEHDR));
    }
}

void Draw(int *pixela, int manualx, int manualy, unsigned char array8x8[], unsigned int wdth, unsigned int hght) {
    //Draw Variables
    unsigned char offy = 0;
    unsigned char offx = 0;
    unsigned int Size = wdth * hght;

    for(unsigned char i = 0; i < Size; i++) {
        //Current Pixel of Image
        int pxPosY = offy + manualy;
        int pxPosX = manualx + offx;
        // Draw pixel if in bounds
        if(pxPosX < 288 && pxPosX >= 0 && pxPosY < 216 && pxPosY >= 0){
            int coord = ((pxPosY) * 288) + (pxPosX);
 
            if(coord < (62208) && coord >= 0 && array8x8[i] > 0){
                pixela[coord] = colorpalette[array8x8[i]];
            }else if(((offy + manualy) * 288) + (manualx + offx) && array8x8[i] == 255){
                pixela[coord] = colorpalette[array8x8[0]];
            }
        }
// Pixel Increment
        offx++;
        if(offx >= wdth){
            offx = 0;
            offy++;
        }
    }
}
void DrawFlippedX(int *pixela, int manualx, int manualy, unsigned char array8x8[], unsigned int wdth, unsigned int hght) {
    // Init
    char offy = 0;
    char offx = wdth - 1; // Flip
    unsigned int Size = wdth * hght;
    // Draw Current Pixel
    for(unsigned char i = 0; i < Size; i++) {
        int pxPosY = offy + manualy;
        int pxPosX = manualx + offx;
        // Draw if in bounds
        if(pxPosX < 288 && pxPosX >= 0 && pxPosY < 216 && pxPosY >= 0){
            int coord = ((pxPosY) * 288) + (pxPosX);
 
            if(coord < (62208) && coord >= 0 && array8x8[i] > 0){
                pixela[coord] = colorpalette[array8x8[i]];
            }else if(((offy + manualy) * 288) + (manualx + offx) && array8x8[i] == 255){
                pixela[coord] = colorpalette[array8x8[0]];
            }
        }
        // Decrease Offset
        offx--;
        if(offx < 0){
            offx = wdth - 1;
            offy++;
        }
    }
}

//Collision Funciton
int collision_detection(float px, float py, float pw, float ph, float wx, float wy, float ww, float wh){
    if(px < wx + ww && py < wy + wh && py + ph > wy && px + pw > wx){ // If touching
        return 1;
    } return 0;
}
//Turns String into PNG & prints it

void WordToScreen(int *buffer, int x, int y, char string[]){ // Index thorugh a string to deliver a words & numbers on a screen
    int size = strlen(string);
    int currentN = 0;
    int currentY = y;
    int currentX = x;
    for(unsigned int i = 0; i < size; i++){
        currentN = string[i];
        switch(currentN) {
            case 'A': case 'a': Draw(buffer, currentX, currentY, letterA, 8, 8); break;
            case 'B': case 'b': Draw(buffer, currentX, currentY, letterB, 8, 8); break;
            case 'C': case 'c': Draw(buffer, currentX, currentY, letterC, 8, 8); break; //FINSIH
            case 'D': case 'd': Draw(buffer, currentX, currentY, letterD, 8, 8); break;
            case 'E': case 'e': Draw(buffer, currentX, currentY, letterE, 8, 8); break;
            case 'F': case 'f': Draw(buffer, currentX, currentY, letterF, 8, 8); break;
            case 'G': case 'g': Draw(buffer, currentX, currentY, letterG, 8, 8); break;
            case 'H': case 'h': Draw(buffer, currentX, currentY, letterH, 8, 8); break;
            case 'I': case 'i': Draw(buffer, currentX, currentY, letterI, 8, 8); break;
            case 'J': case 'j': Draw(buffer, currentX, currentY, letterJ, 8, 8); break;
            case 'K': case 'k': Draw(buffer, currentX, currentY, letterK, 8, 8); break;
            case 'L': case 'l': Draw(buffer, currentX, currentY, letterL, 8, 8); break;
            case 'M': case 'm': Draw(buffer, currentX, currentY, letterM, 8, 8); break;
            case 'N': case 'n': Draw(buffer, currentX, currentY, letterN, 8, 8); break;
            case 'O': case 'o': Draw(buffer, currentX, currentY, letterO, 8, 8); break;
            case 'P': case 'p': Draw(buffer, currentX, currentY, letterP, 8, 8); break;
            case 'Q': case 'q': Draw(buffer, currentX, currentY, letterQ, 8, 8); break;
            case 'R': case 'r': Draw(buffer, currentX, currentY, letterR, 8, 8); break;
            case 'S': case 's': Draw(buffer, currentX, currentY, letterS, 8, 8); break;
            case 'T': case 't': Draw(buffer, currentX, currentY, letterT, 8, 8); break;
            case 'U': case 'u': Draw(buffer, currentX, currentY, letterU, 8, 8); break;
            case 'V': case 'v': Draw(buffer, currentX, currentY, letterV, 8, 8); break;
            case 'W': case 'w': Draw(buffer, currentX, currentY, letterW, 8, 8); break;
            case 'X': case 'x': Draw(buffer, currentX, currentY, letterX, 8, 8); break;
            case 'Y': case 'y': Draw(buffer, currentX, currentY, letterY, 8, 8); break;
            case 'Z': case 'z': Draw(buffer, currentX, currentY, letterZ, 8, 8); break;
            case '1': Draw(buffer, currentX, currentY, number1, 8, 8); break;
            case '2': Draw(buffer, currentX, currentY, number2, 8, 8); break;
            case '3': Draw(buffer, currentX, currentY, number3, 8, 8); break;
            case '4': Draw(buffer, currentX, currentY, number4, 8, 8); break;
            case '5': Draw(buffer, currentX, currentY, number5, 8, 8); break;
            case '6': Draw(buffer, currentX, currentY, number6, 8, 8); break;
            case '7': Draw(buffer, currentX, currentY, number7, 8, 8); break;
            case '8': Draw(buffer, currentX, currentY, number8, 8, 8); break;
            case '9': Draw(buffer, currentX, currentY, number9, 8, 8); break;
            case '0': Draw(buffer, currentX, currentY, letterO, 8, 8); break;
            case '-': Draw(buffer, currentX, currentY, Dash, 8, 8); break;
            case '.': case ',': Draw(buffer, currentX, currentY, numberper, 8, 8); break;
            case '\n': currentY += 8; break;
            case '\\': Draw(buffer, currentX, currentY, CopyRight, 8, 8); break;
            break;
        }
        currentX += 8;
    }
}
// Convert unsigned ints into numbers
char* NumToStr(char Buffer[], int Len, unsigned int NumberConvert){
    int NumberQ = NumberConvert;
    int NumberOnesPlace = 0;
    unsigned int CurrentDiv = 0;
    Buffer[Len - 1] = '\0';
    int LastArray = Len - 2;
    int Index = 0;

    for(unsigned int i = 0; i < Len - 2; i++){
        Buffer[i] = ' ';
    }

    for(unsigned int i = 0; i < Len - 2; i++){
        if (LastArray >= 0 && NumberQ > 0){
            NumberOnesPlace = NumberQ % 10;
            Buffer[i] = NumberOnesPlace + '0';
            LastArray--;
            NumberQ /= 10;
            if(NumberQ <= 0){
                Index = i;
                break;
            }
            Index = i;
        }
        if(NumberConvert == 0){
            Buffer[i] = '0';
            break;
        }
        
    }
    
    int start = 0;
    int end = Index;
    char PlaceHolder = 0;

    while(start < end){
        PlaceHolder = Buffer[start];
        Buffer[start] = Buffer[end];
        Buffer[end] = PlaceHolder;

        start++;
        end--;
    }
    Buffer[Index + 1] = '\0';
    return Buffer;
}


//Start of Game & window
// THIS IS THE START OF THE GAME NOT A ACCESSORY FUNC THE REAL DEAL
LRESULT CALLBACK WindowProcessMessage(HWND, UINT, WPARAM, LPARAM);
 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow){
    WNDCLASS window_class = {0};
    const wchar_t window_class_name[] = L"My Window Class";
    window_class.lpszClassName = window_class_name;
    window_class.lpfnWndProc = WindowProcessMessage;
    window_class.hInstance = hInstance;
    window_class.hCursor = LoadCursor (NULL, IDC_ARROW);
 
    RegisterClass(&window_class);
 
    int width = 1440;
    int height = 1080;
    SetProcessWorkingSetSize(GetCurrentProcess(), (SIZE_T)-1, (SIZE_T)-1);
 
    HWND window_handle = CreateWindow(window_class_name, L"2 Game Collection", WS_POPUP | WS_VISIBLE, 0, 0, width, height, NULL, NULL, hInstance, NULL);
    SetWindowPos(window_handle, HWND_TOPMOST, 0, 0, width, height, SWP_SHOWWINDOW);
    if(window_handle == NULL) {return -1;};
 
    HDC hdc = GetDC(window_handle);
    memory_dc = CreateCompatibleDC(hdc);

    DEVMODEA dm = {0};
    dm.dmSize = sizeof(dm);
    dm.dmPelsWidth = 1440;
    dm.dmPelsHeight = 1080;
    dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

    ChangeDisplaySettingsA(&dm, CDS_FULLSCREEN);
 
    BITMAPINFO bitmap_info = {0};
    bitmap_info.bmiHeader.biSize = sizeof(bitmap_info.bmiHeader);
    bitmap_info.bmiHeader.biWidth = bW;
    bitmap_info.bmiHeader.biHeight = - bH;
    bitmap_info.bmiHeader.biPlanes = 1;
    bitmap_info.bmiHeader.biBitCount = 32;
    bitmap_info.bmiHeader.biCompression = BI_RGB;
 
    HBITMAP bitmap_handle = CreateDIBSection(memory_dc, &bitmap_info, DIB_RGB_COLORS, &memory_buffer, NULL, 0);
    SelectObject(memory_dc, bitmap_handle);
    ReleaseDC(window_handle, hdc);
    ShowWindow(window_handle, nCmdShow);

    InitAudio();
    header.lpData = (LPSTR)audio_bufferSq;
    header.dwBufferLength = 882 * sizeof(short);
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
// Main Loop
 
    //Setting things up
    for(unsigned char i = 0; i < WallNum; i++){
        walls[i].x = 0;
        walls[i].y = 0;
        walls[i].active = 0;
    }
    for(unsigned char i = 0; i < bulletNum; i++){
        bulletsd[i].x = 0;
        bulletsd[i].y = 0;
        bulletsd[i].active = 0;
    }
    //Sound Setup
    fillBuffSound(&headerA, SbuffA, 880.00f);
    fillBuffSound(&headerB, SbuffB, 880.00f);
    fillBuffSound(&headerB, SbuffC, 880.00f);
    waveOutWrite(hWaveOut, &headerA, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &headerB, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &headerC, sizeof(WAVEHDR));

    unsigned int SettingNX = my_round((288 - (8 * 8)) / 2);
    unsigned char maxTickV = 250;

    unsigned int MaxBulletSpawn = 2000;
    unsigned char ShowStartButt = 0;
    unsigned int LastShownButt = 0;
    unsigned int HISCORE1 = 0;
    unsigned int HISCORE2 = 0;
    unsigned int HISCORE3 = 0;
    char Rank1[3] = "AA\0";
    char Rank2[3] = "AA\0";
    char Rank3[3] = "AA\0";
    char InputRank[3] = "AA\0";
    unsigned char OverWriteRank = 0;
    unsigned int FinalScore = 0;
    unsigned char ScoreCheck = 0;
    char KeyBoardStr[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ\0";
    unsigned int KeyBoardX = 40;
    unsigned int CurrKeyBoardX = 0;
    unsigned char KeyBoardIndex = 0;
    unsigned char CurrentOverwriteInput = 0;
    unsigned char Collision = 0;
        
    enemyvel = 3;
    Predator_dist = -1000;


    //Windows Func Related Variables
    unsigned int last_check_time = GetTickCount64();
    int LastTickV = GetTickCount64();
    int lastBulletSpawn = LastTickV;
    playerY = 20;
    // Related Rendering Variables
    int GameStartY = GameOverY - 50;
    int GameStartGameY = 112;

// Actual Loop

    while(playing == 1){
        MSG message;
        while(PeekMessage(&message, NULL, 0, 0, PM_REMOVE)){
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        WaitForSingleObject(hAudioEvent, INFINITE);// Frame Cap
        Sound_Inc = freq / 44100;
        if(GroundOffset <= -288){
            GroundOffset = 0;
        }
        // Variable Resets across all games
        can_moveX = 1;
        SettingY = 120;
        QuitY = 128;
        int GameStartGameX = Middlex - 32;
        CurrentTime = GetTickCount64();

            //Infamous Quit Q Fass Quit
        if((GetAsyncKeyState(0x51) & 0x8000)){
            playing = 0;
        }
        if(GameState == 1){
    //Resetting variables pt 2
            CollisionBefore = 0;
            Collision = 0;
            playerWalk = 0;
            playerRun = 0;
            playerXacc = 0;
            falling = 0;
            backward = 0;
            forward = 0;
            if(player_state == 0) {
                playerW = 9;
                playerH = 16;
            }else{playerW = 16;
                playerH = 9;}
            if(playerY >= 168) {
                OnGround = 1;
                playerY = 168;
            }
        //Gravity
            if(!OnGround) {
                playerYvel += g;
                falling = 1;
            }
 
    //Plr Movement
            if((GetAsyncKeyState(0x57) & 0x8000) && OnGround) {
                player_state = 0;
            }
        //Jumping
            if((GetAsyncKeyState(VK_SPACE) & 0x8000) && CurrentTime - jumpcooldown_lastjump >= 150 && OnGround && !player_state) {
                playerYvel = -3.1415;
                jumpcooldown_lastjump = CurrentTime;
                pengWCInd = pengLength - 1;
                OnGround = 0;
                JumpPlay = 1;
                JumpPlayLast = CurrentTime;
            }
            //Running
            if((GetAsyncKeyState(VK_LSHIFT) & 0x8000) && (GetAsyncKeyState(0x44) & 0x8000) && CurrentTime - penganim_timer >= 30 && OnGround && !player_state) {
                pengWCInd += 1;
                penganim_timer = CurrentTime;
                if(pengWCInd >= pengLength - 2) {
                    pengWCInd = 0;
                }
 
                playerRun = 1;
                playerXacc += 5;
            }
        //Going Backwards
            if((GetAsyncKeyState(0x41) & 0x8000) && CurrentTime - penganim_timer >= 30 && !playerRun && OnGround && !player_state) {
                pengWCInd += 1;
                penganim_timer = CurrentTime;
                if(pengWCInd >= pengLength - 2) {
                    pengWCInd = 0;
                }
 
                playerXacc = -4;
                playerWalk = 1;
                backward = 1;
                penganim_timer = CurrentTime;
            }
            // Walking
            if((GetAsyncKeyState(0x44) & 0x8000) && CurrentTime - penganim_timer >= anim_cooldown && !backward && !playerRun && OnGround  && !player_state) {
                pengWCInd += 1;
                penganim_timer = CurrentTime;
                if(pengWCInd >= pengLength - 2) {
                    pengWCInd = 0;
                }
 
                playerXacc = 4;
                playerWalk = 1;
                forward = 1;
                penganim_timer = CurrentTime;
            }
        // Animation for Plr Char
            if(CurrentTime - penganim_timer >= (anim_cooldown + 5) && playerYvel < 0) {
                pengWCInd = pengLength - 1;
            } else if(CurrentTime - penganim_timer >= (anim_cooldown + 5)){
                pengWCInd = 0;
            }
            //Cut Feature
            if(player_state){
                playerXacc = 2.5;
                playerXvel += playerXacc;
                if(playerXvel >= 8) {playerXvel = 8;}
            }
            //End of Cut Feature
        // Maxxing Vel & Acc
            if(can_moveX  && !player_state){
                playerXvel += playerXacc;}
        // APPLYING Friction
            if(playerXvel >= snow_friction && !falling) {
                playerXvel -= (snow_friction);
            } else if(playerXvel <= -(snow_friction) && !falling) {
                playerXvel += (snow_friction);
            }
        //Absolute MAximum if walking fails Capping off Velocity
            if(playerXvel >= playermaxvel  && !player_state) {
                playerXvel = playermaxvel;
            }
            if(playerXvel <= -(playermaxvel) && !player_state) {
                playerXvel = -(playermaxvel);
            }
            
        // Capping off acceleration
            if(playerXacc >= playermaxacc && !player_state) {
                playerXacc = playermaxacc;
            }
            if(playerXacc <= -(playermaxacc) && !player_state) {
                playerXacc = -(playermaxacc);
            }
 
            //Walking max
            //Capping off Player walk velocity
            if(playerXvel >= playermaxvelWalk && playerWalk == 1) {
                playerXvel = playermaxvelWalk;
            }
            if(playerXacc >= playermaxaccWalk && playerWalk == 1) {
                playerXacc = playermaxaccWalk;
            }
            // CApping off walking acceleration
            if(playerXvel <= -(playermaxvelWalk) && playerWalk == 1) {
                playerXvel = -(playermaxvelWalk);
            }
            if(playerXacc <= -(playermaxaccWalk) && playerWalk == 1) {
                playerXacc = -(playermaxaccWalk);
            }
            if(!can_moveX && !player_state){
                playerXvel = 0;
                playerXacc = 0;
            }
 
    //Checking for spawning of walls
 
        //Ground
            // Changing the world from the plrs perspective
            GroundOffset -= playerXvel;
        //Total Disance Traveled
            current_pixelmove += playerXvel;
            if(current_pixelmove < 0) {current_pixelmove = 0;}

        // Random Var for random Spawns(Technically not Random also pretty easy to guess)
        unsigned char randomBi = CurrentTime % 4;
        unsigned char ablespawn = 0;
        unsigned char clear_space = 1;

        //Bullet
        if(CurrentTime - lastBulletSpawn > 1000){
            ablespawn = 1;
        }
        
        if(randomBi < 2){
            ablespawn = 0;
        }
        // Spawning Logic
        for (unsigned char i = 0; i < bulletNum; i++){
            if (bulletsd[i].active == 1 && bulletsd[i].x >= 0 && bulletsd[i].x < 4){
                clear_space = 0;
                break;
            }
            // Bullet Spawning Logic
            if(bulletsd[i].active == 0 && clear_space == 1 && ablespawn == 1){//&& clear_space == 1 && ablespawn == 1
                bulletsd[i].active = 1; clear_space = 0; ablespawn = 0;
                bulletsd[i].y = 170 - (CurrentTime % 40);
                bulletsd[i].x = 0;
                bulletsd[i].yVel = 0;
                lastBulletSpawn = CurrentTime;
                inputPlay = 1;
                lastIPlay = CurrentTime;
                break;
            }
        }
        

        //Wall logic
            randomBi = CurrentTime % 8;
            
            ablespawn = 1;
            clear_space = 1;
            
        //Wall Loops
            // Wall Spawning logic This is older code
            for(int i = 0; i < WallNum; i++) {
                if(walls[i].x >= (280 + current_pixelmove) && walls[i].active) {
                    clear_space = 0;
                }
                if(walls[i].active && walls[i].x >= (current_pixelmove + 288)){
                    ablespawn = 0;
                }   
            }
            if(CurrentTime - last_check_time <= SpawnMaxLimit) {
                ablespawn = 0;
            }
        //Spawining logic Wall
            if(randomBi >= 6) {
                ablespawn = 0; // Removing Able Spawn
            }
            // Spawn logic
            for(int i = 0; i < WallNum; i++) {
                if(!walls[i].active && ablespawn && clear_space) {
                    walls[i].x = current_pixelmove + 288;
                    walls[i].y = 168;
                    walls[i].active = 1;
                    last_check_time = CurrentTime;
                    SpawnMaxLimit -= 50;
                    break;
                }
                if(walls[i].active && walls[i].x < (current_pixelmove - 8)) {
                    walls[i].active = 0;
                }
            }
            if(SpawnMaxLimit <= 0) {
                SpawnMaxLimit = 8000;
            }
 
            playerY += playerYvel;

            Predator_dist += enemyvel;
            Predator_dist -= playerXvel;
    //PlayerSlowdown
            if(!playerWalk && !playerRun && playerXvel > 0 && CurrentTime - last_tick > slowdown_wait) {
                playerXvel -= 0.6;
                if(playerXvel < 0) {
                    playerXvel = 0;
                }
                last_tick = CurrentTime;
            }
            if(!playerWalk && !playerRun && playerXvel < 0 && CurrentTime - last_tick > slowdown_wait) {
                playerXvel += 0.6;
                if(playerXvel > 0) {
                    playerXvel = 0;
                }
                last_tick = CurrentTime;
            }
 
            if(playerY >= 168){
                if(falling){jumpcooldown_lastjump = CurrentTime;}
                playerY = 168;
                playerYvel = 0;
                falling = 0;
            }
            if(Predator_dist >= 5) {
                GameState = 2;
                ScoreCheck = 0;
            }
//Collisions
            for(int i = 0; i < WallNum; i++) { // Wall Collison on side vs side
                if(collision_detection(playerX + 1, playerY + 1, playerW - 1, playerH - 2, (walls[i].x - current_pixelmove), 168, 8, 16) && !player_state) {
                    if(walls[i].active){
                        if(playerXvel > 0) {
                            current_pixelmove = (walls[i].x) - (playerX + playerW);
                            CollisionBefore = 1;
                            Collision = 1;
                        } else if(playerXvel < 0) {
                            current_pixelmove = (walls[i].x + 8) - playerX;
                            CollisionBefore = 1;
                            Collision = 1;
                        }
                    }
                }
                if(collision_detection(playerX + 1, playerY, playerW - 2, playerH, (walls[i].x - current_pixelmove), 168, 8, 16) && falling && !player_state) { // On Top Wall Collison
                    if(walls[i].active){ //
                        if(playerYvel > 0) {
                            playerY = 168 - playerH;
                            playerYvel = 0;
                            falling = 0;
                            OnGround = 1;
                            CollisionBefore = 1;
                        }
                    }
                }
                FinalScore = Unsigned_round(current_pixelmove);
            }
            //Bullet Logic
            for(unsigned char i = 0; i < bulletNum; i++){ // Active logic

                if(bulletsd[i].active == 1){
                    if(!Collision){
                        bulletsd[i].x += (bulletVel / 1.7f) - playerXvel;
                    }
                    else{
                        bulletsd[i].x += (bulletVel / 1.7f);
                    }
                    bulletsd[i].yVel += 0.01;
                    bulletsd[i].y += bulletsd[i].yVel;

                    if(bulletsd[i].x >= 288 || bulletsd[i].y >= 216){
                        bulletsd[i].active = 0;
                    }

                    // Bullet Collison
                    if(collision_detection(playerX + 1, playerY, playerW - 2, playerH, bulletsd[i].x, bulletsd[i].y, 4, 3)){
                        GameState = 2;
                        ScoreCheck = 0;
                        bulletsd[i].active = 0;
                        break;
                    }
                }
            }

        }

        if(JumpPlay && CurrentTime - JumpPlayLast >= 150){ // Jump Input
            JumpPlay = 0;
            phasessq2 = 0;
        }
        // UPD plr rendering Pos
        int PplayerX = (int)(playerX + 0.5);
        int PplayerY = (int)(playerY + 0.5);
// Menu
        if(GameState == 0) {
            if((GetAsyncKeyState(0x57) & 0x8000) && CurrentTime - lc_start_button >= ml_start_button){
                //Movement Control Down 's'
                lc_start_button = CurrentTime;
                start_button_var--;
                inputPlay = 1;
                lastIPlay = CurrentTime;
            }
            if((GetAsyncKeyState(0x53) & 0x8000) && CurrentTime - lc_start_button >= ml_start_button){
                //Movement control up 'w'
                lc_start_button = CurrentTime;
                start_button_var++;
                inputPlay = 1;
                lastIPlay = CurrentTime;
            }
            //Checking if its too high or too low a value
            if(start_button_var > 3) {
                start_button_var = 1;
            } 
            else if(start_button_var < 1) {
                start_button_var = 3;
            }
            //Correcting ArrowY
            if(start_button_var == 1) {
                ArrowY = GameStartGameY;
            }
            if(start_button_var == 2) {
                ArrowY = SettingY;
            }
            if(start_button_var == 3) {
                ArrowY = QuitY;
            }
 
        // Confirming with Enter
            if((GetAsyncKeyState(0x0D) & 0x8000)){
                // Starting Game
                if(ArrowY == GameStartGameY && CurrentTime - lc_start_button >= ml_start_button) {
                    GameState = 4; //Play Start Game Anim
                    StartButtFlashNum = 0;
                    lc_start_button = CurrentTime;
                    player_state = 0;
                    for(unsigned char i = 0; i < WallNum; i++){
                        walls[i].x = 0;
                        walls[i].y = 0;
                        walls[i].active = 0;
                    }
                    for(unsigned char i = 0; i < bulletNum; i++){
                        bulletsd[i].x = 0;
                        bulletsd[i].y = 0;
                        bulletsd[i].active = 0;
                    }
                    lastBulletSpawn = CurrentTime;
                    Predator_dist = -1000;
                    current_pixelmove = 0;
                    SpawnMaxLimit = 8000;
                }
                // Enter Settings
                if(ArrowY == SettingY && CurrentTime - lc_start_button >= ml_start_button){
                    lc_start_button = GetTickCount64();
                    GameState = 3;
                    inputPlay = 1;
                    lastIPlay = CurrentTime;
                }
                //Quit Game
                if(ArrowY == QuitY && CurrentTime - lc_start_button >= ml_start_button) {
                    lc_start_button = CurrentTime;
                    playing = 0;
                }
            }
            
        }

        if(GameState == 2){

            //SCORE CHECK
            if(!ScoreCheck){
                // Getting Top Score
                if(FinalScore > HISCORE1){
                    OverWriteRank = 1;

                    Rank3[0] = Rank2[0];
                    Rank3[1] = Rank2[1];

                    Rank2[0] = Rank1[0];
                    Rank2[1] = Rank1[1];

                    HISCORE3 = HISCORE2;
                    HISCORE2 = HISCORE1;
                    HISCORE1 = FinalScore;
                }
                // Getting Second Top Score
                else if (FinalScore > HISCORE2 && FinalScore < HISCORE1 + 1){
                    OverWriteRank = 2;

                    Rank3[0] = Rank2[0];
                    Rank3[1] = Rank2[1];

                    HISCORE3 = HISCORE2;
                    HISCORE2 = FinalScore;
                }
                // Getting Third Top Score
                else if(FinalScore > HISCORE3 && FinalScore < HISCORE2 + 1){
                    OverWriteRank = 3;
                    HISCORE3 = FinalScore;
                }
                // No HISCORE
                else if(FinalScore < HISCORE3){
                    OverWriteRank = 0;
                }
                else { }
                ScoreCheck = 1;
                InputRank[0] = 'A';
                InputRank[1] = InputRank[0];
            }
            // Moving the select Icon left 
            if((GetAsyncKeyState('A') & 0x8000) && CurrentTime - LastTickV >= 250) {
                if(KeyBoardIndex == 0){
                    KeyBoardIndex = 25;
                }
                else{
                    KeyBoardIndex--;
                }
                LastTickV = CurrentTime;
                inputPlay = 1;
                lastIPlay = CurrentTime;
            }
            // Move KeyBoard Select Icon Right
            if((GetAsyncKeyState('D') & 0x8000) && CurrentTime - LastTickV >= 250){
                KeyBoardIndex++;
                LastTickV = CurrentTime;
                if(KeyBoardIndex >= 26){
                    KeyBoardIndex = 0;
                }
                inputPlay = 1;
                lastIPlay = CurrentTime;
            }
            // using Space to confirm letter
            if(((GetAsyncKeyState(0x20) & 0x8000) && CurrentTime - inputPlay2Last >= 300)){
                if(!CurrentOverwriteInput){
                    InputRank[CurrentOverwriteInput] = KeyBoardStr[KeyBoardIndex];
                    CurrentOverwriteInput = 1;
                }
                else{
                    InputRank[CurrentOverwriteInput] = KeyBoardStr[KeyBoardIndex];
                    CurrentOverwriteInput = 0;
                }
                inputPlay2 = 1;
                inputPlay2Last = CurrentTime;
            }
            // Enter key to move on and finalizing new leader board
            if(GetAsyncKeyState(0x0D) & 0x8000){
                CurrentOverwriteInput = 0;

                if(OverWriteRank == 1){
                    Rank1[0] = InputRank[0];
                    Rank1[1] = InputRank[1];
                }
                else if(OverWriteRank == 2){
                    Rank2[0] = InputRank[0];
                    Rank2[1] = InputRank[1];
                }
                else if(OverWriteRank == 3){
                    Rank3[0] = InputRank[0];
                    Rank3[1] = InputRank[1];
                }

                GameState = 0;
                LastTickV = CurrentTime;
                lc_start_button = CurrentTime;
                inputPlay = 1;
                lastIPlay = CurrentTime;
            }
            // Playing a Input enter sound Low Freq
            if(CurrentTime - inputPlay2Last >= 150){
                inputPlay2 = 0;
            }

        }

    // INIT WRITE SYS

        // Settings
        if(GameState == 3){
            // going to right 1 | moving select
            if((GetAsyncKeyState(0x44) & 0x8000) && CurrentTime - LastTickV >= maxTickV){
                LastTickV = CurrentTime;
                settingSelect++;
                if(settingSelect > 3){
                    settingSelect = 1;
                }
                inputPlay = 1;
                lastIPlay = CurrentTime;
            }
            // Going to left 1 moving select
            if((GetAsyncKeyState(0x41) & 0x8000) && CurrentTime - LastTickV >= maxTickV){
                LastTickV = CurrentTime;
                settingSelect--;
                if(settingSelect < 1){
                    settingSelect = 3;
                }
                inputPlay = 1;
                lastIPlay = CurrentTime;
            }
            // Pressing Enter Key | Basically confirming 1 of the choices spefifically the back button
            if(GetAsyncKeyState(0x0D) & 0x8000 && CurrentTime - lc_start_button >= maxTickV){
                lc_start_button = CurrentTime;
                if(settingSelect == 1){
                    GameState = 0;
                }
                inputPlay = 1;
                lastIPlay = CurrentTime;
                
            }
            // Confirming another choice spefifically the audio level
            if(GetAsyncKeyState(0x0D) & 0x8000 && CurrentTime - lc_start_button >= 75){
                if( settingSelect == 2){
                    VolumeAmount -= 0.05;
                    if(VolumeAmount < 0){
                        VolumeAmount = 0;
                    }
                    
                }
                else if( settingSelect == 3){
                    VolumeAmount += 0.05;
                    if(VolumeAmount > 1){
                        VolumeAmount = 1;
                    }
                }
                inputPlay = 1;
                lastIPlay = CurrentTime;
                
            }
        }
// Animation Page
        if(GameState == 4){
            // Flipping Digits on and off and playing a sound if one of them Is on
            // Flipping the digits
            if(CurrentTime - LastShownButt >= 100){
                if(ShowStartButt == 1){
                    ShowStartButt = 0;
                    LastShownButt = CurrentTime;
                    phasessq2 = 0;
                    inputPlay2 = 1;
                }
                else if(ShowStartButt == 0){
                    ShowStartButt = 1;
                    StartButtFlashNum++;
                    LastShownButt = CurrentTime;
                    inputPlay2 = 0;
                }
            }
            // Load Game upon Completion of 5
            if(StartButtFlashNum >= 5){
                StartButtFlashNum = 0;
                GameState = 1;
                ShowStartButt = 0;
                inputPlay2 = 0;
                lc_start_button = CurrentTime;
                player_state = 0;
                for(unsigned char i = 0; i < WallNum; i++){
                    walls[i].x = 0;
                    walls[i].y = 0;
                    walls[i].active = 0;
                }
                for(unsigned char i = 0; i < bulletNum; i++){
                    bulletsd[i].x = 0;
                    bulletsd[i].y = 0;
                    bulletsd[i].active = 0;
                }
                lastBulletSpawn = CurrentTime;
                Predator_dist = -1000;
                current_pixelmove = 0;
                SpawnMaxLimit = 8000;
                
            }
        }

        if(inputPlay){
            // Playing input this is a "Global" input among all Game States
            if(CurrentTime - lastIPlay > maxIplay){
                inputPlay = 0;
                phasessq2 = 0;
            }
        }
//maxIPlay
//inputPlay
//lastIPlay
//Render
    // Renderer
        unsigned int* pixel = (unsigned int*)memory_buffer;
        // Screen Reset
        for(int i = 0; i < (bW * bH); i++ ) {
            pixel[i] = colorpalette[1]; //1 = Blue. Blue = Sky = Reset
        }
    //Menu
        //Render Meny
        if(GameState == 0) {

            char StringB[6];
            //unsigned int HiScoreLblX = TitleNameX - (5 * 8);
            unsigned int HiScoreLblX = 72;
            unsigned int InitialsX = HiScoreLblX + (8 * 10);

            // Rendering Hiscore labels
            WordToScreen(pixel, HiScoreLblX, QuitY + 16, "HI-SCORES");
            WordToScreen(pixel, HiScoreLblX + (8 * 10), QuitY + 16, "INITALS");
            // HiScore 1
            NumToStr(StringB, 6, (HISCORE1));
            WordToScreen(pixel, HiScoreLblX, QuitY + 24, StringB);
            //Hiscore 2
            NumToStr(StringB, 6, (HISCORE2));
            WordToScreen(pixel, HiScoreLblX, QuitY + 32, StringB);
            // Hiscore 3
            NumToStr(StringB, 6, (HISCORE3));
            WordToScreen(pixel, HiScoreLblX, QuitY + 40, StringB);
            //Initals 1
            WordToScreen(pixel, InitialsX, QuitY + 24, Rank1);
            //Initials 2
            WordToScreen(pixel, InitialsX, QuitY + 32, Rank2);
            // initials 3
            WordToScreen(pixel, InitialsX, QuitY + 40, Rank3);
            // TITLE
            WordToScreen(pixel, 100, GameStartY, "PENGUIN RUN");

            // START GAME BUTTON
            WordToScreen(pixel, TitleNameX, GameStartGameY, "START GAME");
            // START GAME BUTTON
            WordToScreen(pixel, TitleNameX, SettingY, "Setting");
            // START GAME BUTTON
            WordToScreen(pixel, TitleNameX, QuitY, "QUIT");
            // Draw ARROW
            Draw(pixel, TitleNameX - 10, ArrowY, Arrow, 8, 8);
            // Credit
            WordToScreen(pixel, 152, 208, "\\2026 Beanie Tech"); // User I go by "\\" is used as the (c) symbol
        }
    //Game Rendering
        if(GameState == 1) {
            int roundedcurrent_pixelmove = my_round(current_pixelmove);
            int GroundOffset = roundedcurrent_pixelmove % 8;
            for(int i = 0; i < 37; i++){
                int GroundX = i * 8;
                GroundX -= GroundOffset;
                // Drawing the ground
                Draw(pixel, GroundX, 184, SnowIceTile, 8, 8); // top
                Draw(pixel, GroundX, 192, SnowCoveredDirt, 8, 8); // 2nd lyr
                Draw(pixel, GroundX, 200, DirtUpper, 8, 8); // 3rd lyr
                Draw(pixel, GroundX, 208, DirtLower, 8, 8); // 4th lyr
            }
        //Structs Render
            // Rendering Wall
            for(int i = 0; i < WallNum; i++) { 
                if(walls[i].active) {
                    int wallx = (int)((walls[i].x - roundedcurrent_pixelmove) + 0.5);
                    int wally = (int)(walls[i].y + 0.5);
                    Draw(pixel, wallx, wally, IceWallUpper, 8, 8);
                    Draw(pixel, wallx, (wally + 8), IceWallLower, 8, 8);
                }
            }
            //Bullet Render
            for(int i = 0; i < bulletNum; i++){
                if(bulletsd[i].active == 1){
                    int bullety = my_round(bulletsd[i].y);
                    int bulletx = my_round(bulletsd[i].x);

                    Draw(pixel, bulletx, bullety, Bullet, 8, 8);
                }
            }
            // Game Render
            char StringB[7];
            unsigned int newVal = (current_pixelmove < 0) ? -current_pixelmove : current_pixelmove;
            NumToStr(StringB, 7, (unsigned int)(newVal));
            WordToScreen(pixel, 0, 0, StringB);

            int DistAway = 0;
            WordToScreen(pixel, 0, 8, "Distance Away");

            newVal = (Predator_dist < 0) ? -Predator_dist : Predator_dist;

            NumToStr(StringB, 7, (unsigned int)(newVal));
            WordToScreen(pixel, 112, 8, StringB);

    //Player render
            if (player_state == 0 && pengWCInd < pengLength){
                if(playerXvel < 0){DrawFlippedX(pixel, PplayerX, PplayerY, pengWalkCycle[pengWCInd], 9, 16);} // Flipped
                else {Draw(pixel, PplayerX, PplayerY, pengWalkCycle[pengWCInd], 9, 16);} // Non Flipped
            }
        }
 
    // GameOver
        if(GameState == 2) {
            Draw(pixel, GameOverStartx, GameOverY, letterG, 8, 8); 
            Draw(pixel, GameOverStartx + 8, GameOverY, letterA, 8, 8);
            Draw(pixel, GameOverStartx + 16, GameOverY, letterM, 8, 8);
            Draw(pixel, GameOverStartx + 23, GameOverY, letterE, 8, 8); // Manual Because for better looking letter spacing
            Draw(pixel, GameOverStartx + 39, GameOverY, letterO, 8, 8);
            Draw(pixel, GameOverStartx + 47, GameOverY, letterV, 8, 8);
            Draw(pixel, GameOverStartx + 55, GameOverY, letterE, 8, 8);
            Draw(pixel, GameOverStartx + 63, GameOverY, letterR, 8, 8);
            // GAme OVer Render
            char StringB[6];
            int newVal = (current_pixelmove < 0) ? -current_pixelmove : current_pixelmove;
            NumToStr(StringB, 6, (int)(newVal));
            WordToScreen(pixel, 148, 80, StringB);
            WordToScreen(pixel, 92 + 8, 80, "Score");

            // Important Info

            WordToScreen(pixel, (288 - (17 * 8)) / 2, GameOverY + 16, "Retry Press Enter");

            WordToScreen(pixel, 92, 144, "TYPE INITIALS");
            WordToScreen(pixel, 136, 152, InputRank);

            WordToScreen(pixel, KeyBoardX, 184, KeyBoardStr); // Put Info at 200
            WordToScreen(pixel, 8, 200, "Confirm Letter, Using Jump Button.");

            CurrKeyBoardX = (KeyBoardIndex * 8) + KeyBoardX;
            Draw(pixel, CurrKeyBoardX, 184, SelectBox, 8, 8);
        }

    // Settings
        if(GameState == 3){
            // Setting Render
            DrawFlippedX(pixel, 0, 0, Arrow, 8, 8); // Back Arrow
            WordToScreen(pixel, SettingNX, 0, "Settings"); // Top Name
            DrawFlippedX(pixel, SettingNX - 16, 112, Arrow, 8, 8); // Lower Volume
            Draw(pixel, SettingNX + 8 + (8*8), 112, Arrow, 8, 8); // More Volume
            WordToScreen(pixel, my_round((288 - (8*6)) / 2), 96, "Volume"); // Name of setting
            if(settingSelect == 1){
                Draw(pixel, 0, 0, SelectBox, 8, 8); // Select box
            }
            else if(settingSelect == 2){
                Draw(pixel, SettingNX - 16, 112, SelectBox, 8, 8); // Land on Decreased Volume
            }
            else if(settingSelect == 3){
                Draw(pixel, SettingNX + 8 + (8*8), 112, SelectBox, 8, 8); // Select More Volume
            }
            char StrBuffB[5]; // String Buffer
            int PrintVal = my_round(VolumeAmount * 100); // print volume
            NumToStr(StrBuffB, 5, PrintVal); // Fill Buffer
            WordToScreen(pixel, ((288 - (8*3)) / 2), 112, StrBuffB); // Print Buffer

        }
        if(GameState == 4){
            // Anim Render
            char StrBuffB[25]; // 
// Debug Render
            NumToStr(StrBuffB, 25, (unsigned int)inputPlay2);
            WordToScreen(pixel, 0, 0, StrBuffB);

            NumToStr(StrBuffB, 25, (unsigned int)ShowStartButt); 
            WordToScreen(pixel, 0, 8, StrBuffB);

            NumToStr(StrBuffB, 25, (unsigned int)LastShownButt);
            WordToScreen(pixel, 0, 16, StrBuffB);

            NumToStr(StrBuffB, 25, (unsigned int)CurrentTime);
            WordToScreen(pixel, 0, 24, StrBuffB);

            NumToStr(StrBuffB, 25, (unsigned int)(CurrentTime - LastShownButt));
            WordToScreen(pixel, 0, 32, StrBuffB);
        // End of Debug Render

            char StringB[6];
            unsigned int HiScoreLblX = 72;
            unsigned int InitialsX = HiScoreLblX + (8 * 10);

            
            // Rendering Hiscore labels
            WordToScreen(pixel, HiScoreLblX, QuitY + 16, "HI-SCORES");
            WordToScreen(pixel, HiScoreLblX + (8 * 10), QuitY + 16, "INITALS");
            // HiScore 1
            NumToStr(StringB, 6, (HISCORE1));
            WordToScreen(pixel, HiScoreLblX, QuitY + 24, StringB);
            //Hiscore 2
            NumToStr(StringB, 6, (HISCORE2));
            WordToScreen(pixel, HiScoreLblX, QuitY + 32, StringB);
            // Hiscore 3
            NumToStr(StringB, 6, (HISCORE3));
            WordToScreen(pixel, HiScoreLblX, QuitY + 40, StringB);
            //Initals 1
            WordToScreen(pixel, InitialsX, QuitY + 24, Rank1);
            //Initials 2
            WordToScreen(pixel, InitialsX, QuitY + 32, Rank2);
            // initials 3
            WordToScreen(pixel, InitialsX, QuitY + 40, Rank3);
            // TITLE
            WordToScreen(pixel, 100, GameStartY, "PENGUIN RUN");

            if(ShowStartButt){ // if we allowed to show start show start

                WordToScreen(pixel, TitleNameX, GameStartGameY, "START GAME");
            }
            // Draw Setting
            WordToScreen(pixel, TitleNameX, SettingY, "Setting");
            // Draw Quit
            WordToScreen(pixel, TitleNameX, QuitY, "Quit");
            // Draw Arrow
            Draw(pixel, TitleNameX - 10, ArrowY, Arrow, 8, 8);
            // Copyright & credits to me
            WordToScreen(pixel, 152, 208, "\\2026 Beanie Tech"); // \\ is used as (c) symbol
        }

    // Stretch the image to 1440x1080
        HDC hdcWindow = GetDC(window_handle);
        StretchBlt(hdcWindow, 0, 0, 1440, 1080, memory_dc, 0, 0, bW, bH, SRCCOPY);
        ReleaseDC(window_handle, hdcWindow);
    //End of Stretch the image to 1440x1080
        //Sound Section

        // Triple sound buffer setup
        if(headerA.dwFlags & WHDR_DONE){ // 1st buffer
            float CurrentFreqN = 880.0f;
            fillBuffSound(&headerA, SbuffA, CurrentFreqN);

            waveOutWrite(hWaveOut, &headerA, sizeof(WAVEHDR));
        }
        if(headerB.dwFlags & WHDR_DONE){ // 2nd Buffer
            float CurrentFreqN = 880.0f;
            fillBuffSound(&headerB, SbuffB, CurrentFreqN);
            waveOutWrite(hWaveOut, &headerB, sizeof(WAVEHDR));
        }
        if(headerC.dwFlags & WHDR_DONE){ // 3rd Buffer
            float CurrentFreqN = 880.0f;
            fillBuffSound(&headerC, SbuffC, CurrentFreqN);
            waveOutWrite(hWaveOut, &headerC, sizeof(WAVEHDR));
        }
    }

    ChangeDisplaySettingsA(NULL, 0);
//Resolution of Game = 288x216
//This uses RGB no AA included
    // Cleanup
        // Clean Audio
    CloseHandle(hAudioEvent);
    waveOutUnprepareHeader(hWaveOut, &headerA, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &headerB, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &headerC, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
    // Clean Image
    SelectObject(memory_dc, bitmap_handle);
    DeleteObject(bitmap_handle);
    DeleteDC(memory_dc);

    return 0;
}
LRESULT CALLBACK WindowProcessMessage(HWND window_handle, UINT message, WPARAM wParam, LPARAM lParam){
    switch(message){
        case WM_QUIT:
        case WM_DESTROY: {
            playing = 0;
        } break;
 
        default: { //Message failure to handle
            return DefWindowProc(window_handle, message, wParam, lParam);
        } break;
    }
    return 0;
}