// Copyright 2026 Beanie_Tech - All Rights Reserved
#define UNICODE
#define _UNICODE
#define Short_Wall 36
#define WallNum 15
#define bulletNum 15
#include <windows.h>
#include <mmsystem.h>

// Game States 0-2 are being used as of 2026-09-02
 
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
//Variables
//Remember ANYTHING is possible as long as you have A language when I mean a language ANY language similiar to C Just remember that. 
unsigned char playing = 1;
void* memory_buffer; //bPtr
HDC memory_dc;
int bW = 288;
int bH = 216;
 
float g = 0.1635; //A little stronger than gravity by x10 realgravity is 0.1635
//X positions
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
float playerYacc = 0;
float playermaxacc = 0.5;
float playermaxvel = 4.5;
float playermaxvelWalk = 1.8;
float playermaxaccWalk = 0.5;
float Predator_dist = 0;
//Plr State; Values Ranging form 0-1 ints
int player_state = 0;
float snow_friction = 0.9;
//Player Cooldowns & stopping double jump scaling
unsigned int jumpcooldown_current = 0;
unsigned char jumpcooldown_max = 250;
unsigned int jumpcooldown_lastjump = 0;
unsigned char falling = 0;
int GroundOffset = 0;
int GroundOffset2 = 0;
unsigned char playerRun = 0;
unsigned char playerWalk = 0;
int enemyvel = 0;
 
const unsigned int colorpalette[256] = {0x000000, 0x4D4DFF, 0x004ECC, 0xFFD800, 0xFFFFFF, 0xEFC700, 0x639AFC, 0xBED4FC, 0x572903, 0xA05E12, 0x0B371D, 0x735005, 0xFF8707, 0x724A27, 0x562E02};
// 0/-1 = Black/Transparent, 1 = NESBLUE/SKY, 2 = Fur Peng, 3 = Peng Feet 1, 4 = White, 5 = Peng Feet2, 7 = Ice Blue 1, 6 = Ice Blue 2, 8 = DarkDirt, 9 = Light Dirt
//No.12 = Orange
//No. 13 = Brown
// No. 14 = dark brown
//States & Stats & Words | Basically Other Section
int GameOverStartx = 112;
int GameOverY = 112;
int GameState = 0;
int TitleNameX = 144 - 39;
int Middlex = 144;
int Middley = 108;
int Rmin = 0;
int Rmax = 1;

unsigned int bulletVel = 10;
//Bg/Tiles data

// REMEMBER 255 is BLACK 0 TRANS
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
 
//DAFont
unsigned char letterA[64] = {0, 0, 0, 0, 0, 0, 0, 0,
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
 
//Sound Tracks
//Sq Wave
unsigned char Track1SqGameOver[160] = {
    31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33
};
unsigned char Track2Sq[160] = {
    31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35
};
// Tri Wave
unsigned char Track1Tri[160] = {
    31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35
};

unsigned char GameTIndex = 0;
//Noise Wave
// unsigned char Track1NoA[160] = {
 
// };
// unsigned char Track1NoASEnvelope[160] = {

// };
// Saw
unsigned char SawToothMenu[160] = {
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
};
unsigned char SawToothMenu2[160] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
unsigned char TriMenu[160] = {
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
};
//Track Related Variables
unsigned char TrackInd = 0;
unsigned char GameOverTrackInd = 0;
float NotesFreqs[53] = { 4186.01, 3951.07, 3520.00, 3135.96, 2793.83, 2637.02, 2349.32, 2090.00, 1975.53, 1760.00, 1567.98, 1396.91, 1318.51, 1174.66, 1046.50, 987.77, 880.00, 783.99, 698.46, 659.25, 587.33, 523.25, 493.88, 440.00, 392.00, 349.23, 329.63, 293.66, 261.63, 213.47, 220.00, 196.00, 174.61, 164.81, 146.83, 130.81, 123.47, 110.00, 98.00, 87.31, 82.41, 73.42, 65.41, 61.74, 55.00, 49.00, 43.65, 41.20, 36.71, 32.70, 30.87, 27.50, 0.0};
                        // 0        1       2        3        4        5       6        7         8       9        10        11       12       13        14      15      16      17        18    19      20       21     22       23      24     25       26     27      28      29      30      31       32     33      34      35      36      37      38      39     40     41    42     43     44      45     46    47    48      49     50     51   
// Different Levels for Inf Runner


//Track Var
// int FirstTrack = 0x00;
// int SecondTrack = 0x00;
//Sound Variables
//NOTE MINIMUM LENGTH IS 20msfff
//float phase = 1;
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
short audio_bufferSq[882];
short audio_bufferTri[882];
//short audio_bufferNoise[882];
//short audio_bufferSaw[882];
short audio_bufferSq2[882]; //1.764kb
int SoundSeed = 1;
HWAVEOUT hWaveOut;
WAVEHDR header = {0};
short SbuffA[882], SbuffB[882], SbuffC[882];
WAVEHDR headerA = {0}, headerB = {0}, headerC = {0};
double phase2 = 0.0;
HANDLE hAudioEvent;

char OUTPUTSTRNUM3DIG[3] = "   ";
 
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
    double phaseinc = freq1 / 44100;
 
    double currentraw = 0;
    double lastsamp = 0;
    float CorrectVolPer = vol * vol;
    float TrueVol = volume * CorrectVolPer;
    //if(period < 2) {
       // period = 2;
   // }
    for(int i = 0; i < 882; i++){
        //int x = sample_count % period;
        short sample = 0;
        float tri = 0;
        float saw = 0;
        switch(type) {
            case 0:
                //sample = (x < phase2 / 2) ? volume : -volume;//Use to have period instead of phase
                currentraw = (*clock < 0.5f) ? TrueVol : -TrueVol;
                break;
            case 1:
                tri = (*clock * 4.0f) - 2.0f;
                if (tri < 0) {tri = -tri;} 
                currentraw = (short)((tri - 1.0f) * TrueVol);
                break;
            case 2: 
                currentraw = (short)((Noiserandom() % (int)(volume * 2)) - volume);
                break;
            case 3:
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
    headerA.lpData = (LPSTR)SbuffA;
    headerA.dwBufferLength = 882 * sizeof(short);
    waveOutPrepareHeader(hWaveOut, &headerA, sizeof(WAVEHDR));
 
    headerB.lpData = (LPSTR)SbuffB;
    headerB.dwBufferLength = 882 * sizeof(short);
    waveOutPrepareHeader(hWaveOut, &headerB, sizeof(WAVEHDR));
 
    headerC.lpData = (LPSTR)SbuffC;
    headerC.dwBufferLength = 882 * sizeof(short);
    waveOutPrepareHeader(hWaveOut, &headerC, sizeof(WAVEHDR));
 
    waveOutWrite(hWaveOut, &headerA, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &headerB, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &headerC, sizeof(WAVEHDR));
 
    Yikes(TriMenu, 30);
    Yikes(SawToothMenu, 25);
}
// This inputs sound for different sections
void fillBuffSound(WAVEHDR* hdr, short* Output, float freq) { //
    if(hdr->dwFlags & WHDR_DONE) {
        if(GameState == 0 || GameState == 3){
            //SoundMain(audio_bufferSq, 0, 0, &phasessq); //Square Voice
            SoundMain(audio_bufferSq, 0, NotesFreqs[SawToothMenu[TrackInd]], &phasessq, VolumeAmount); //SawTooth Voice
            //SoundMain(audio_bufferSaw2, 3, NotesFreqs[SawToothMenu2[TrackInd]], &phasesaw2); // Sawtooth 2nd Voice. Yes Its Special
            SoundMain(audio_bufferTri, 1, NotesFreqs[TriMenu[TrackInd]], &phasetri, VolumeAmount); //Triangle Voice
            //SoundMain(audio_bufferNoise, 2, 0, &phase2); // Noise Voice
            //SoundMain(audio_bufferSaw, 3, 880, &phasesaw);
            TrackInd++;
 
            if(TrackInd >= 160){TrackInd = 0;}
        }
        else if(GameState == 2){
            EmptyBuff(audio_bufferTri);

            GameOverTrackInd++;
            if(GameOverTrackInd >= 160){GameOverTrackInd = 0;}
            
            SoundMain(audio_bufferSq, 0, NotesFreqs[Track1SqGameOver[GameOverTrackInd]], &phasessq, VolumeAmount);
        }
        else if(GameState == 1){
            GameTIndex++;
            if(GameTIndex >= 160){GameTIndex = 0;}
            SoundMain(audio_bufferSq, 0, NotesFreqs[Track2Sq[GameTIndex]], &phasessq, VolumeAmount);
            SoundMain(audio_bufferTri, 1, NotesFreqs[Track1Tri[GameTIndex]], &phasetri, VolumeAmount);
        }
        // else if(GameState == 1 || GameState == 3){
        //     if(TrackInd >= 160){TrackInd = 0;}
        // }
        else{
            EmptyBuff(audio_bufferTri);
            EmptyBuff(audio_bufferSq);
        }

        if(inputPlay){
            SoundMain(audio_bufferSq2, 0, NotesFreqs[25], &phasessq2, VolumeAmount);
        }
        else if(inputPlay2 == 1){
            SoundMain(audio_bufferSq2, 0, NotesFreqs[28], &phasessq2, VolumeAmount);
        }
        else {
            EmptyBuff(audio_bufferSq2);
        }

        if(JumpPlay){
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
// Draws any img that will fit the in the grid filled wtih 8x8 blocks
void Draw8x8(int *pixela, int manualx, int manualy, unsigned char array8x8[]) {
    unsigned char offy = 0;
    unsigned char offx = 0;
    for(unsigned char i = 0; i < 64; i++) {
        int pxPosY = offy + manualy;
        int pxPosX = manualx + offx;
        if(pxPosX < 288 && pxPosX >= 0 && pxPosY < 216 && pxPosY >= 0){
            int coord = ((pxPosY) * 288) + (pxPosX);
 
            if(coord < (62208) && coord >= 0 && array8x8[i] > 0){
                pixela[coord] = colorpalette[array8x8[i]];
            }else if(((offy + manualy) * 288) + (manualx + offx) && array8x8[i] == 255){
                pixela[coord] = colorpalette[array8x8[0]];
            };
        }

        offx++;
        if(offx >= 8){
            offx = 0;
            offy++;
        };
    };
}

void Draw8x8FlippedX(int *pixela, int manualx, int manualy, unsigned char array8x8[]) {
    char offy = 0;
    char offx = 7;
    for(unsigned char i = 0; i < 64; i++) {
        int pxPosY = offy + manualy;
        int pxPosX = manualx + offx;
        if(pxPosX < 288 && pxPosX >= 0 && pxPosY < 216 && pxPosY >= 0){
            int coord = ((pxPosY) * 288) + (pxPosX);
 
            if(coord < (62208) && coord >= 0 && array8x8[i] > 0){
                pixela[coord] = colorpalette[array8x8[i]];
            }else if(((offy + manualy) * 288) + (manualx + offx) && array8x8[i] == 255){
                pixela[coord] = colorpalette[array8x8[0]];
            };
        }
 
        offx--;
        if(offx < 0){
            offx = 7;
            offy++;
        };
    };
}
// This does not manage pengWCInd index for ptr This only draw plr
void DrawPlr(int *pixela, int x, int y, unsigned char array16x9or16x16[]){
    unsigned char offx = 0;
    unsigned char offy = 0;
    if(player_state == 0) {
        //remeber Init, Condition, Increment
        for(unsigned char i = 0; i < 144; i++) {
            int pxPosY = offy + y;
            int pxPosX = offx + x;
            if(pxPosX >= 0 && pxPosX < 288 && pxPosY >= 0 && pxPosY < 216){
                int coord = ((pxPosY) * 288) + (pxPosX);
                if(coord < (62208) && coord >= 0 && array16x9or16x16[i] > 0){
                    pixela[coord] = colorpalette[array16x9or16x16[i]];
                } else if(array16x9or16x16[i] == 255 && array16x9or16x16[i] != 0){
                    pixela[coord] = colorpalette[0];
                };
            };
            offx++;
            if(offx >= 9){
                offx = 0;
                offy++;
            };
        };
    };
    if(player_state > 0) {
        for(unsigned char i = 0; i < 256; i++) {
            int pxPosY = offy + y;
            int pxPosX = offx + x;
            if(pxPosX >= 0 && pxPosX < 288 && pxPosY >= 0 && pxPosY < 216){
                int coord = ((pxPosY) * 288) + (pxPosX);
                if(coord < (62208) && coord >= 0 && array16x9or16x16[i] > 0){
                    pixela[coord] = colorpalette[array16x9or16x16[i]];
                } else if(array16x9or16x16[i] == 255 && array16x9or16x16[i] != 0){
                    pixela[coord] = colorpalette[0];
                };
            };
            offx++;
            if(offx >= 16){
                offx = 0;
                offy++;
            };
        };
    };
};
// This draw flipped player
void DrawPlrFlip(int *pixela, int x, int y, unsigned char array16x9or16x16[]){
    char offx = 8;
    char offy = 0;
    if(player_state == 0) {
        //remeber Init, Condition, Increment
        for(unsigned char i = 0; i < 144; i++) {
            int pxPosY = offy + y;
            int pxPosX = x + offx;
            if(pxPosX >= 0 && pxPosX < 288 && pxPosY >= 0 && pxPosY < 216 && offx >= 0){
                int coord = ((pxPosY) * 288) + (pxPosX);
                if(coord < (62208) && coord >= 0 && array16x9or16x16[i] > 0){
                    pixela[coord] = colorpalette[array16x9or16x16[i]];
                } else if(array16x9or16x16[i] == 255 && array16x9or16x16[i] != 0){
                    pixela[coord] = colorpalette[0];
                };
            };
            offx--;
            if(offx < 0){
                offx = 8;
                offy++;
            };
        };
    };
    if(player_state > 0) {
        int offx = 15;
        int offy = 0;
        for(int i = 0; i < 256; i++) {
            int pxPosY = offy + y;
            int pxPosX = offx + x;
            if(pxPosX >= 0 && pxPosX < 288 && pxPosY >= 0 && pxPosY < 216 && offx >= 0){
                int coord = ((pxPosY) * 288) + (pxPosX);
                if(coord < (62208) && coord >= 0 && array16x9or16x16[i] != 0 && array16x9or16x16[i] != -1){
                    pixela[coord] = colorpalette[array16x9or16x16[i]];
                } else if(array16x9or16x16[i] == 255 && array16x9or16x16[i] != 0){
                    pixela[coord] = colorpalette[0];
                };
            };
            offx--;
            if(offx < 0){
                offx = 15;
                offy++;
            };
        };
    };
};
//Collision Funciton
int collision_detection(float px, float py, float pw, float ph, float wx, float wy, float ww, float wh){
    if(px < wx + ww && py < wy + wh && py + ph > wy && px + pw > wx){
        return 1;
    } return 0;
}
//Turns String into PNG & prints it


// void ConvertNumToFont(int x, int y, int *pixela, char STRING[]) {
//     int LENGTH = lstrlenA(STRING);
//     int newx = x;
//     int newy = y;
//     for(int i = 0; i < LENGTH; i++){
//         char current = STRING[i];
//         unsigned char* ArrayNum = 0;
//         if(current == '0'){
//             ArrayNum = letterO;
//         }
//         else if(current == '1'){
//             ArrayNum = number1;
//         }
//         else if(current == '2'){
//             ArrayNum = number2;
//         }
//         else if(current == '3'){
//             ArrayNum = number3;
//         }
//         else if(current == '4'){
//             ArrayNum = number4;
//         }
//         else if(current == '5'){
//             ArrayNum = number5;
//         }
//         else if(current == '6'){
//             ArrayNum = number6;
//         }
//         else if(current == '7'){
//             ArrayNum = number7;
//         }
//         else if(current == '8'){
//             ArrayNum = number8;
//         }
//         else if(current == '9'){
//             ArrayNum = number9;
//         }
//         else {ArrayNum = letterA;}
//         Draw8x8(pixela, newx, newy, ArrayNum);
//         newx += 8;
//     }
// }

void WordToScreen(int *buffer, int x, int y, char string[]){
    int size = strlen(string);
    int currentN = 0;
    int currentY = y;
    int currentX = x;
    for(unsigned int i = 0; i < size; i++){
        currentN = string[i];
        switch(currentN) {
            case 'A': case 'a': Draw8x8(buffer, currentX, currentY, letterA); break;
            case 'B': case 'b': Draw8x8(buffer, currentX, currentY, letterB); break;
            case 'C': case 'c': Draw8x8(buffer, currentX, currentY, letterC); break; //FINSIH
            case 'D': case 'd': Draw8x8(buffer, currentX, currentY, letterD); break;
            case 'E': case 'e': Draw8x8(buffer, currentX, currentY, letterE); break;
            case 'F': case 'f': Draw8x8(buffer, currentX, currentY, letterF); break;
            case 'G': case 'g': Draw8x8(buffer, currentX, currentY, letterG); break;
            case 'H': case 'h': Draw8x8(buffer, currentX, currentY, letterH); break;
            case 'I': case 'i': Draw8x8(buffer, currentX, currentY, letterI); break;
            case 'J': case 'j': Draw8x8(buffer, currentX, currentY, letterJ); break;
            case 'K': case 'k': Draw8x8(buffer, currentX, currentY, letterK); break;
            case 'L': case 'l': Draw8x8(buffer, currentX, currentY, letterL); break;
            case 'M': case 'm': Draw8x8(buffer, currentX, currentY, letterM); break;
            case 'N': case 'n': Draw8x8(buffer, currentX, currentY, letterN); break;
            case 'O': case 'o': Draw8x8(buffer, currentX, currentY, letterO); break;
            case 'P': case 'p': Draw8x8(buffer, currentX, currentY, letterP); break;
            case 'Q': case 'q': Draw8x8(buffer, currentX, currentY, letterQ); break;
            case 'R': case 'r': Draw8x8(buffer, currentX, currentY, letterR); break;
            case 'S': case 's': Draw8x8(buffer, currentX, currentY, letterS); break;
            case 'T': case 't': Draw8x8(buffer, currentX, currentY, letterT); break;
            case 'U': case 'u': Draw8x8(buffer, currentX, currentY, letterU); break;
            case 'V': case 'v': Draw8x8(buffer, currentX, currentY, letterV); break;
            case 'W': case 'w': Draw8x8(buffer, currentX, currentY, letterW); break;
            case 'X': case 'x': Draw8x8(buffer, currentX, currentY, letterX); break;
            case 'Y': case 'y': Draw8x8(buffer, currentX, currentY, letterY); break;
            case 'Z': case 'z': Draw8x8(buffer, currentX, currentY, letterZ); break;
            case '1': Draw8x8(buffer, currentX, currentY, number1); break;
            case '2': Draw8x8(buffer, currentX, currentY, number2); break;
            case '3': Draw8x8(buffer, currentX, currentY, number3); break;
            case '4': Draw8x8(buffer, currentX, currentY, number4); break;
            case '5': Draw8x8(buffer, currentX, currentY, number5); break;
            case '6': Draw8x8(buffer, currentX, currentY, number6); break;
            case '7': Draw8x8(buffer, currentX, currentY, number7); break;
            case '8': Draw8x8(buffer, currentX, currentY, number8); break;
            case '9': Draw8x8(buffer, currentX, currentY, number9); break;
            case '0': Draw8x8(buffer, currentX, currentY, letterO); break;
            case '-': Draw8x8(buffer, currentX, currentY, Dash); break;
            case '.': case ',': Draw8x8(buffer, currentX, currentY, numberper); break;
            case '\n': currentY += 8; break;
            case '\\': Draw8x8(buffer, currentX, currentY, CopyRight); break;
            break;
        }
        currentX += 8;
    }
}

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
    //intro beep
    //Beep(587, 600); Sleep(50);
    //Beep(494, 600); Sleep(50);
    //Beep(392, 600); Sleep(50);
   // Beep(294, 1000); Sleep(150);
    //Beep(330, 450); Sleep(30);
    //Beep(370, 450); Sleep(30);
    //Beep(392, 450); Sleep(30); 
    //Beep(440, 400); Sleep(30); 
    //Beep(494, 400); Sleep(30); 
   // Beep(440, 1200);

    //Early Variables
    //Game Var
    unsigned int CooldownJ2 = 0;
    playerY = 20;
    unsigned char anim_cooldown = 30;
    unsigned char slowdown_wait = 150;
    unsigned int last_tick = 0;
    int random = 0;
    unsigned int lastrandomcheck = 0;
    int last_pixelmove = 0;
    float current_pixelmove = 0;
    unsigned char anim_cooldown_run = 20;
    unsigned int last_check_time = GetTickCount();
    int SpawnMaxLimit = 8000;
    unsigned char can_moveX = 1;
    unsigned char playerW = 0;
    unsigned char playerH = 16;
    unsigned char OnGround = 0;
    int CollisionBefore = 0;
    unsigned int CooldownSlide = 0;
    enemyvel = 3;
    Predator_dist = -1000;
 
    //Start Var
    unsigned char start_button_var = 0;
    unsigned int lc_start_button = 0;
    unsigned int ml_start_button = 150;
    unsigned int ArrowY = 0;
    unsigned int SettingY = 0;
    unsigned int QuitY = 0;
    unsigned char settingSelect = 0;
 
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
 
 
    //Actaull LooP

    unsigned int SettingNX = my_round((288 - (8 * 8)) / 2);
    int LastTickV = GetTickCount();
    unsigned char maxTickV = 250;

    unsigned int MaxBulletSpawn = 2000;
    int lastBulletSpawn = LastTickV;
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

    while(playing == 1){
        MSG message;
        while(PeekMessage(&message, NULL, 0, 0, PM_REMOVE)){
            TranslateMessage(&message);
            DispatchMessage(&message);
        };
        WaitForSingleObject(hAudioEvent, INFINITE);// Frame Cap
        Sound_Inc = freq / 44100;
        if(GroundOffset <= -288){
            GroundOffset = 0;
        }
        can_moveX = 1;
        int GameStartY = GameOverY - 50;
        int GameStartGameY = 112;
        SettingY = 120;
        QuitY = 128;
        int GameStartGameX = Middlex - 32;
        jumpcooldown_current = GetTickCount();

            //Infamous Quit Q Fass Quit
        if((GetAsyncKeyState(0x51) & 0x8000)){
            playing = 0;
        }
        if(GameState == 1){
    //Resetting variables
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
        // Sliding
            // if((GetAsyncKeyState(0x53) & 0x8000) && OnGround && jumpcooldown_current - CooldownSlide >= 150) {
            //     player_state = 1;
            //     playerXvel = 0;
            //     CooldownSlide = GetTickCount();
            // }
            if((GetAsyncKeyState(0x57) & 0x8000) && OnGround) {
                player_state = 0;
            }
        //Jumping
            if((GetAsyncKeyState(VK_SPACE) & 0x8000) && jumpcooldown_current - jumpcooldown_lastjump >= 150 && OnGround && !player_state) {
                playerYvel = -3.1415;
                jumpcooldown_lastjump = GetTickCount();
                pengWCInd = pengLength - 1;
                OnGround = 0;
                JumpPlay = 1;
                JumpPlayLast = jumpcooldown_current;
            };
            //Running
            if((GetAsyncKeyState(VK_LSHIFT) & 0x8000) && (GetAsyncKeyState(0x44) & 0x8000) && jumpcooldown_current - penganim_timer >= 30 && OnGround && !player_state) {
                pengWCInd += 1;
                penganim_timer = GetTickCount();
                if(pengWCInd >= pengLength - 2) {
                    pengWCInd = 0;
                };
 
                playerRun = 1;
                playerXacc += 5;
            }
        //Going Backwards
            if((GetAsyncKeyState(0x41) & 0x8000) && jumpcooldown_current - penganim_timer >= 30 && !playerRun && OnGround && !player_state) {
                pengWCInd += 1;
                penganim_timer = GetTickCount();
                if(pengWCInd >= pengLength - 2) {
                    pengWCInd = 0;
                };
 
                playerXacc = -4;
                playerWalk = 1;
                backward = 1;
                penganim_timer = GetTickCount();
            }
            // Walking
            if((GetAsyncKeyState(0x44) & 0x8000) && jumpcooldown_current - penganim_timer >= anim_cooldown && !backward && !playerRun && OnGround  && !player_state) {
                pengWCInd += 1;
                penganim_timer = GetTickCount();
                if(pengWCInd >= pengLength - 2) {
                    pengWCInd = 0;
                };
 
                playerXacc = 4;
                playerWalk = 1;
                forward = 1;
                penganim_timer = GetTickCount();
            }
            if(jumpcooldown_current - penganim_timer >= (anim_cooldown + 5) && playerYvel < 0) {
                pengWCInd = pengLength - 1;
            } else if(jumpcooldown_current - penganim_timer >= (anim_cooldown + 5)){
                pengWCInd = 0;
            };
            if(player_state){
                playerXacc = 2.5;
                playerXvel += playerXacc;
                if(playerXvel >= 8) {playerXvel = 8;}
            }
        // Maxxing Vel & Acc
            if(can_moveX  && !player_state){
                playerXvel += playerXacc;}
        // APPLYING Friction
            if(playerXvel >= snow_friction && !falling) {
                playerXvel -= (snow_friction);
            } else if(playerXvel <= -(snow_friction) && !falling) {
                playerXvel += (snow_friction);
            }
        //Absolute MAximum if walking fails
            if(playerXvel >= playermaxvel  && !player_state) {
                playerXvel = playermaxvel;
            }
            if(playerXvel <= -(playermaxvel) && !player_state) {
                playerXvel = -(playermaxvel);
            }
 
            if(playerXacc >= playermaxacc && !player_state) {
                playerXacc = playermaxacc;
            }
            if(playerXacc <= -(playermaxacc) && !player_state) {
                playerXacc = -(playermaxacc);
            }
 
            //Walking max
            if(playerXvel >= playermaxvelWalk && playerWalk == 1) {
                playerXvel = playermaxvelWalk;
            }
            if(playerXacc >= playermaxaccWalk && playerWalk == 1) {
                playerXacc = playermaxaccWalk;
            }
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
            GroundOffset -= playerXvel;
        //Total Disance Traveled
            current_pixelmove += playerXvel;
            if(current_pixelmove < 0) {current_pixelmove = 0;}

        unsigned char randomBi = jumpcooldown_current % 4;
        unsigned char ablespawn = 0;
        unsigned char clear_space = 1;

        //Bullet
        if(jumpcooldown_current - lastBulletSpawn > 1000){
            ablespawn = 1;
        }
        
        if(randomBi < 2){
            ablespawn = 0;
        }
        
        for (unsigned char i = 0; i < bulletNum; i++){
            if (bulletsd[i].active == 1 && bulletsd[i].x >= 0 && bulletsd[i].x < 4){
                clear_space = 0;
                break;
            }

            if(bulletsd[i].active == 0 && clear_space == 1 && ablespawn == 1){//&& clear_space == 1 && ablespawn == 1
                bulletsd[i].active = 1; clear_space = 0; ablespawn = 0;
                bulletsd[i].y = 170 - (jumpcooldown_current % 40);
                bulletsd[i].x = 0;
                bulletsd[i].yVel = 0;
                lastBulletSpawn = jumpcooldown_current;
                inputPlay = 1;
                lastIPlay = jumpcooldown_current;
                break;
            }
        }
        

        //Wall Stuff
            randomBi = jumpcooldown_current % 8;
            
            ablespawn = 1;
            clear_space = 1;
            
        //Wall Loops
 
            for(int i = 0; i < WallNum; i++) {
                if(walls[i].x >= (280 + current_pixelmove) && walls[i].active) {
                    clear_space = 0;
                }
                if(walls[i].active && walls[i].x >= (current_pixelmove + 288)){
                    ablespawn = 0;
                }   
            }
            if(jumpcooldown_current - last_check_time <= SpawnMaxLimit) {
                ablespawn = 0;
            }
        //Spawining first active
            if(randomBi >= 6) {
                ablespawn = 0;
            }
            for(int i = 0; i < WallNum; i++) {
                if(!walls[i].active && ablespawn && clear_space) {
                    walls[i].x = current_pixelmove + 288;
                    walls[i].y = 168;
                    walls[i].active = 1;
                    last_check_time = GetTickCount();
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
            if(!playerWalk && !playerRun && playerXvel > 0 && jumpcooldown_current - last_tick > slowdown_wait) {
                playerXvel -= 0.6;
                if(playerXvel < 0) {
                    playerXvel = 0;
                }
                last_tick = GetTickCount();
            }
            if(!playerWalk && !playerRun && playerXvel < 0 && jumpcooldown_current - last_tick > slowdown_wait) {
                playerXvel += 0.6;
                if(playerXvel > 0) {
                    playerXvel = 0;
                }
                last_tick = GetTickCount();
            }
 
            if(playerY >= 168){
                if(falling){jumpcooldown_lastjump = GetTickCount();}
                playerY = 168;
                playerYvel = 0;
                falling = 0;
            };
            if(Predator_dist >= 5) {
                GameState = 2;
                ScoreCheck = 0;
            }
//Collisions
            for(int i = 0; i < WallNum; i++) {
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
                if(collision_detection(playerX + 1, playerY, playerW - 2, playerH, (walls[i].x - current_pixelmove), 168, 8, 16) && falling && !player_state) {
                    if(walls[i].active){
                        if(playerYvel > 0) {
                            playerY = 168 - playerH;
                            playerYvel = 0;
                            falling = 0;
                            OnGround = 1;
                            CollisionBefore = 1;
                        }
                    }
                }
                if(collision_detection(playerX, playerY, playerW, playerH, (walls[i].x - current_pixelmove), 168, 8, 16) && player_state) {
                    GameState = 2;   // Was 1
                    ScoreCheck = 0;
                    player_state = 0;
                }
                if(!collision_detection(playerX, playerY, playerW, playerH, (walls[i].x - current_pixelmove), 168, 8, 16) && !CollisionBefore && !player_state) {
                    OnGround = 0;
                }
                FinalScore = Unsigned_round(current_pixelmove);
            }
            for(unsigned char i = 0; i < bulletNum; i++){

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

                    if(collision_detection(playerX + 1, playerY, playerW - 2, playerH, bulletsd[i].x, bulletsd[i].y, 4, 3)){
                        GameState = 2;
                        ScoreCheck = 0;
                        bulletsd[i].active = 0;
                        break;
                    }
                }
            }

        }
        
        if(JumpPlay && jumpcooldown_current - JumpPlayLast >= 150){
            JumpPlay = 0;
            phasessq2 = 0;
        }
        int PplayerX = (int)(playerX + 0.5);
        int PplayerY = (int)(playerY + 0.5);
// Menu
        if(GameState == 0) {
            if((GetAsyncKeyState(0x57) & 0x8000) && jumpcooldown_current - lc_start_button >= ml_start_button){
                lc_start_button = GetTickCount();
                start_button_var--;
                inputPlay = 1;
                lastIPlay = jumpcooldown_current;
            }
            if((GetAsyncKeyState(0x53) & 0x8000) && jumpcooldown_current - lc_start_button >= ml_start_button){
                lc_start_button = GetTickCount();
                start_button_var++;
                inputPlay = 1;
                lastIPlay = jumpcooldown_current;
            }
            if(start_button_var > 3) {
                start_button_var = 1;
            } 
            else if(start_button_var < 1) {
                start_button_var = 3;
            }
            if(start_button_var == 1) {
                ArrowY = GameStartGameY;
            }
            if(start_button_var == 2) {
                ArrowY = SettingY;
            }
            if(start_button_var == 3) {
                ArrowY = QuitY;
            }
 
            if((GetAsyncKeyState(0x0D) & 0x8000)){
                if(ArrowY == GameStartGameY && jumpcooldown_current - lc_start_button >= ml_start_button) {
                    GameState = 4;
                    StartButtFlashNum = 0;
                    lc_start_button = GetTickCount();
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
                    lastBulletSpawn = jumpcooldown_current;
                    Predator_dist = -1000;
                    current_pixelmove = 0;
                    SpawnMaxLimit = 8000;
                }
                if(ArrowY == SettingY && jumpcooldown_current - lc_start_button >= ml_start_button){
                    lc_start_button = GetTickCount();
                    GameState = 3;
                    inputPlay = 1;
                    lastIPlay = jumpcooldown_current;
                }
                if(ArrowY == QuitY && jumpcooldown_current - lc_start_button >= ml_start_button) {
                    lc_start_button = GetTickCount();
                    playing = 0;
                }
            }
            
        }

        if(GameState == 2){

            //SCORE CHECK
            if(!ScoreCheck){
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
                else if (FinalScore > HISCORE2 && FinalScore < HISCORE1 + 1){
                    OverWriteRank = 2;

                    Rank3[0] = Rank2[0];
                    Rank3[1] = Rank2[1];

                    HISCORE3 = HISCORE2;
                    HISCORE2 = FinalScore;
                }
                else if(FinalScore > HISCORE3 && FinalScore < HISCORE2 + 1){
                    OverWriteRank = 3;
                    HISCORE3 = FinalScore;
                }
                else if(FinalScore < HISCORE3){
                    OverWriteRank = 0;
                }
                else { }
                ScoreCheck = 1;
                InputRank[0] = 'A';
                InputRank[1] = InputRank[0];
            }

            if((GetAsyncKeyState('A') & 0x8000) && jumpcooldown_current - LastTickV >= 250) {
                if(KeyBoardIndex == 0){
                    KeyBoardIndex = 25;
                }
                else{
                    KeyBoardIndex--;
                }
                LastTickV = jumpcooldown_current;
                inputPlay = 1;
                lastIPlay = jumpcooldown_current;
            }
            if((GetAsyncKeyState('D') & 0x8000) && jumpcooldown_current - LastTickV >= 250){
                KeyBoardIndex++;
                LastTickV = jumpcooldown_current;
                if(KeyBoardIndex >= 26){
                    KeyBoardIndex = 0;
                }
                inputPlay = 1;
                lastIPlay = jumpcooldown_current;
            }

            if(((GetAsyncKeyState(0x20) & 0x8000) && jumpcooldown_current - inputPlay2Last >= 300)){
                if(!CurrentOverwriteInput){
                    InputRank[CurrentOverwriteInput] = KeyBoardStr[KeyBoardIndex];
                    CurrentOverwriteInput = 1;
                }
                else{
                    InputRank[CurrentOverwriteInput] = KeyBoardStr[KeyBoardIndex];
                    CurrentOverwriteInput = 0;
                }
                inputPlay2 = 1;
                inputPlay2Last = jumpcooldown_current;
            }

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
                LastTickV = jumpcooldown_current;
                lc_start_button = jumpcooldown_current;
                inputPlay = 1;
                lastIPlay = jumpcooldown_current;
            }

            if(jumpcooldown_current - inputPlay2Last >= 150){
                inputPlay2 = 0;
            }

        }

    // INIT WRITE SYS

        if(GameState == 3){
            if((GetAsyncKeyState(0x44) & 0x8000) && jumpcooldown_current - LastTickV >= maxTickV){
                LastTickV = jumpcooldown_current;
                settingSelect++;
                if(settingSelect > 2){
                    settingSelect = 0;
                }
                inputPlay = 1;
                lastIPlay = jumpcooldown_current;
            }
            if((GetAsyncKeyState(0x41) & 0x8000) && jumpcooldown_current - LastTickV >= maxTickV){
                LastTickV = jumpcooldown_current;
                settingSelect--;
                if(settingSelect < 0){
                    settingSelect = 2;
                }
                inputPlay = 1;
                lastIPlay = jumpcooldown_current;
            }
            if(GetAsyncKeyState(0x0D) & 0x8000 && jumpcooldown_current - lc_start_button >= maxTickV){
                lc_start_button = jumpcooldown_current;
                if(settingSelect == 0){
                    GameState = 0;
                }
                inputPlay = 1;
                lastIPlay = jumpcooldown_current;
                
            }

            if(GetAsyncKeyState(0x0D) & 0x8000 && jumpcooldown_current - lc_start_button >= 75){
                if( settingSelect == 1){
                    VolumeAmount -= 0.05;
                    if(VolumeAmount < 0){
                        VolumeAmount = 0;
                    }
                    
                }
                else if( settingSelect == 2){
                    VolumeAmount += 0.05;
                    if(VolumeAmount > 1){
                        VolumeAmount = 1;
                    }
                }
                inputPlay = 1;
                lastIPlay = jumpcooldown_current;
                
            }
        }

        if(GameState == 4){
            if(jumpcooldown_current - LastShownButt >= 100){
                if(ShowStartButt == 1){
                    ShowStartButt = 0;
                    LastShownButt = jumpcooldown_current;
                    phasessq2 = 0;
                    inputPlay2 = 1;
                }
                else if(ShowStartButt == 0){
                    ShowStartButt = 1;
                    StartButtFlashNum++;
                    LastShownButt = jumpcooldown_current;
                    inputPlay2 = 0;
                }
            }
            if(StartButtFlashNum >= 5){
                StartButtFlashNum = 0;
                GameState = 1;
                ShowStartButt = 0;
                inputPlay2 = 0;
                lc_start_button = GetTickCount();
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
                lastBulletSpawn = jumpcooldown_current;
                Predator_dist = -1000;
                current_pixelmove = 0;
                SpawnMaxLimit = 8000;
                
            }
        }

        if(inputPlay){
            if(jumpcooldown_current - lastIPlay > maxIplay){
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
        };
    //Menu
        if(GameState == 0) {

            char StringB[6];
            //unsigned int HiScoreLblX = TitleNameX - (5 * 8);
            unsigned int HiScoreLblX = 72;
            unsigned int InitialsX = HiScoreLblX + (8 * 10);

            
            WordToScreen(pixel, HiScoreLblX, QuitY + 16, "HI-SCORES");
            WordToScreen(pixel, HiScoreLblX + (8 * 10), QuitY + 16, "INITALS");

            NumToStr(StringB, 6, (HISCORE1));
            WordToScreen(pixel, HiScoreLblX, QuitY + 24, StringB);

            NumToStr(StringB, 6, (HISCORE2));
            WordToScreen(pixel, HiScoreLblX, QuitY + 32, StringB);

            NumToStr(StringB, 6, (HISCORE3));
            WordToScreen(pixel, HiScoreLblX, QuitY + 40, StringB);

            WordToScreen(pixel, InitialsX, QuitY + 24, Rank1);

            WordToScreen(pixel, InitialsX, QuitY + 32, Rank2);

            WordToScreen(pixel, InitialsX, QuitY + 40, Rank3);
 
            WordToScreen(pixel, 100, GameStartY, "PENGUIN RUN");
 
            Draw8x8(pixel, TitleNameX, GameStartGameY, letterS2);
            Draw8x8(pixel, TitleNameX + 8, GameStartGameY, letterT);
            Draw8x8(pixel, TitleNameX + 16, GameStartGameY, letterA);
            Draw8x8(pixel, TitleNameX + 24, GameStartGameY, letterR);
            Draw8x8(pixel, TitleNameX + 32, GameStartGameY, letterT);
            Draw8x8(pixel, TitleNameX + 48, GameStartGameY, letterG);
            Draw8x8(pixel, TitleNameX + 56, GameStartGameY, letterA);
            Draw8x8(pixel, TitleNameX + 64, GameStartGameY, letterM);
            Draw8x8(pixel, TitleNameX + 72, GameStartGameY, letterE);
 
            Draw8x8(pixel, TitleNameX, SettingY, letterS2);
            Draw8x8(pixel, TitleNameX + 8, SettingY, letterE);
            Draw8x8(pixel, TitleNameX + 16, SettingY, letterT);
            Draw8x8(pixel, TitleNameX + 24, SettingY, letterT);
            Draw8x8(pixel, TitleNameX + 32, SettingY, letterI);
            Draw8x8(pixel, TitleNameX + 40, SettingY, letterN);
            Draw8x8(pixel, TitleNameX + 48, SettingY, letterG);
 
            Draw8x8(pixel, TitleNameX, QuitY, letterQ);
            Draw8x8(pixel, TitleNameX + 8, QuitY, letterU);
            Draw8x8(pixel, TitleNameX + 16, QuitY, letterI);
            Draw8x8(pixel, TitleNameX + 24, QuitY, letterT);
 
            Draw8x8(pixel, TitleNameX - 10, ArrowY, Arrow);

            WordToScreen(pixel, 184, 208, "\\2026 Louise");
        };
    //Game Rendering
        if(GameState == 1) {
            int roundedcurrent_pixelmove = my_round(current_pixelmove);
            int GroundOffset = roundedcurrent_pixelmove % 8;
            for(int i = 0; i < 37; i++){
                int GroundX = i * 8;
                GroundX -= GroundOffset;
                Draw8x8(pixel, GroundX, 184, SnowIceTile);
                Draw8x8(pixel, GroundX, 192, SnowCoveredDirt);
                Draw8x8(pixel, GroundX, 200, DirtUpper);
                Draw8x8(pixel, GroundX, 208, DirtLower);
            }
        //Walls
            for(int i = 0; i < WallNum; i++) {
                if(walls[i].active) {
                    int wallx = (int)((walls[i].x - roundedcurrent_pixelmove) + 0.5);
                    int wally = (int)(walls[i].y + 0.5);
                    Draw8x8(pixel, wallx, wally, IceWallUpper);
                    Draw8x8(pixel, wallx, (wally + 8), IceWallLower);
                }
            }

            for(int i = 0; i < bulletNum; i++){
                if(bulletsd[i].active == 1){
                    int bullety = my_round(bulletsd[i].y);
                    int bulletx = my_round(bulletsd[i].x);

                    Draw8x8(pixel, bulletx, bullety, Bullet);
                    //Draw8x8(pixel, bulletx, bullety, IceWallLower);
                }
            }

            char StringB[7];
            unsigned int newVal = (current_pixelmove < 0) ? -current_pixelmove : current_pixelmove;
            NumToStr(StringB, 7, (unsigned int)(newVal));
            WordToScreen(pixel, 0, 0, StringB);

            int DistAway = 0;
            WordToScreen(pixel, 0, 8, "Distance Away");

            newVal = (Predator_dist < 0) ? -Predator_dist : Predator_dist;

            NumToStr(StringB, 7, (unsigned int)(newVal));
            WordToScreen(pixel, 112, 8, StringB);
 
        //Player Always on top
    //Player
            if (player_state == 0 && pengWCInd < pengLength){
                if(playerXvel < 0){DrawPlrFlip(pixel, PplayerX, PplayerY, pengWalkCycle[pengWCInd]);}
                else {DrawPlr(pixel, PplayerX, PplayerY, pengWalkCycle[pengWCInd]);}
            }else if(player_state > 0) {DrawPlr(pixel, PplayerX, PplayerY, Efox);}
        }
 
    // GameOver
        if(GameState == 2) {
            Draw8x8(pixel, GameOverStartx, GameOverY, letterG); 
            Draw8x8(pixel, GameOverStartx + 8, GameOverY, letterA);
            Draw8x8(pixel, GameOverStartx + 16, GameOverY, letterM);
            Draw8x8(pixel, GameOverStartx + 23, GameOverY, letterE);
            Draw8x8(pixel, GameOverStartx + 39, GameOverY, letterO);
            Draw8x8(pixel, GameOverStartx + 47, GameOverY, letterV);
            Draw8x8(pixel, GameOverStartx + 55, GameOverY, letterE);
            Draw8x8(pixel, GameOverStartx + 63, GameOverY, letterR);

            char StringB[6];
            int newVal = (current_pixelmove < 0) ? -current_pixelmove : current_pixelmove;
            NumToStr(StringB, 6, (int)(newVal));
            WordToScreen(pixel, 148, 80, StringB);
            WordToScreen(pixel, 92 + 8, 80, "Score");

            WordToScreen(pixel, (288 - (17 * 8)) / 2, GameOverY + 16, "Retry Press Enter");

            WordToScreen(pixel, 92, 144, "TYPE INITIALS");
            WordToScreen(pixel, 136, 152, InputRank);

            WordToScreen(pixel, KeyBoardX, 184, KeyBoardStr); // Put Info at 200
            WordToScreen(pixel, 8, 200, "Confirm Letter, Using Jump Button.");

            CurrKeyBoardX = (KeyBoardIndex * 8) + KeyBoardX;
            Draw8x8(pixel, CurrKeyBoardX, 184, SelectBox);
        };

    // Settings
        if(GameState == 3){
            Draw8x8FlippedX(pixel, 0, 0, Arrow); // Back Arrow
            WordToScreen(pixel, SettingNX, 0, "Settings");
            Draw8x8FlippedX(pixel, SettingNX - 16, 112, Arrow);
            Draw8x8(pixel, SettingNX + 8 + (8*8), 112, Arrow);
            WordToScreen(pixel, my_round((288 - (8*6)) / 2), 96, "Volume");
            if(settingSelect == 0){
                Draw8x8(pixel, 0, 0, SelectBox);
            }
            else if(settingSelect == 1){
                Draw8x8(pixel, SettingNX - 16, 112, SelectBox);
            }
            else if(settingSelect == 2){
                Draw8x8(pixel, SettingNX + 8 + (8*8), 112, SelectBox);
            }
            char StrBuffB[5];
            int PrintVal = my_round(VolumeAmount * 100);
            NumToStr(StrBuffB, 5, PrintVal);
            WordToScreen(pixel, ((288 - (8*3)) / 2), 112, StrBuffB);

        }
        if(GameState == 4){

            char StrBuffB[25];
            NumToStr(StrBuffB, 25, (unsigned int)inputPlay2);
            WordToScreen(pixel, 0, 0, StrBuffB);

            NumToStr(StrBuffB, 25, (unsigned int)ShowStartButt);
            WordToScreen(pixel, 0, 8, StrBuffB);

            NumToStr(StrBuffB, 25, (unsigned int)LastShownButt);
            WordToScreen(pixel, 0, 16, StrBuffB);

            NumToStr(StrBuffB, 25, (unsigned int)jumpcooldown_current);
            WordToScreen(pixel, 0, 24, StrBuffB);

            NumToStr(StrBuffB, 25, (unsigned int)(jumpcooldown_current - LastShownButt));
            WordToScreen(pixel, 0, 32, StrBuffB);

            char StringB[6];
            //unsigned int HiScoreLblX = TitleNameX - (5 * 8);
            unsigned int HiScoreLblX = 72;
            unsigned int InitialsX = HiScoreLblX + (8 * 10);

            
            WordToScreen(pixel, HiScoreLblX, QuitY + 16, "HI-SCORES");
            WordToScreen(pixel, HiScoreLblX + (8 * 10), QuitY + 16, "INITALS");

            NumToStr(StringB, 6, (HISCORE1));
            WordToScreen(pixel, HiScoreLblX, QuitY + 24, StringB);

            NumToStr(StringB, 6, (HISCORE2));
            WordToScreen(pixel, HiScoreLblX, QuitY + 32, StringB);

            NumToStr(StringB, 6, (HISCORE3));
            WordToScreen(pixel, HiScoreLblX, QuitY + 40, StringB);

            WordToScreen(pixel, InitialsX, QuitY + 24, Rank1);

            WordToScreen(pixel, InitialsX, QuitY + 32, Rank2);

            WordToScreen(pixel, InitialsX, QuitY + 40, Rank3);
 
            WordToScreen(pixel, 100, GameStartY, "PENGUIN RUN");

            if(ShowStartButt){
                Draw8x8(pixel, TitleNameX, GameStartGameY, letterS2);
                Draw8x8(pixel, TitleNameX + 8, GameStartGameY, letterT);
                Draw8x8(pixel, TitleNameX + 16, GameStartGameY, letterA);
                Draw8x8(pixel, TitleNameX + 24, GameStartGameY, letterR);
                Draw8x8(pixel, TitleNameX + 32, GameStartGameY, letterT);
                Draw8x8(pixel, TitleNameX + 48, GameStartGameY, letterG);
                Draw8x8(pixel, TitleNameX + 56, GameStartGameY, letterA);
                Draw8x8(pixel, TitleNameX + 64, GameStartGameY, letterM);
                Draw8x8(pixel, TitleNameX + 72, GameStartGameY, letterE);
            }
 
            Draw8x8(pixel, TitleNameX, SettingY, letterS2);
            Draw8x8(pixel, TitleNameX + 8, SettingY, letterE);
            Draw8x8(pixel, TitleNameX + 16, SettingY, letterT);
            Draw8x8(pixel, TitleNameX + 24, SettingY, letterT);
            Draw8x8(pixel, TitleNameX + 32, SettingY, letterI);
            Draw8x8(pixel, TitleNameX + 40, SettingY, letterN);
            Draw8x8(pixel, TitleNameX + 48, SettingY, letterG);
 
            Draw8x8(pixel, TitleNameX, QuitY, letterQ);
            Draw8x8(pixel, TitleNameX + 8, QuitY, letterU);
            Draw8x8(pixel, TitleNameX + 16, QuitY, letterI);
            Draw8x8(pixel, TitleNameX + 24, QuitY, letterT);
 
            Draw8x8(pixel, TitleNameX - 10, ArrowY, Arrow);

            WordToScreen(pixel, 184, 208, "\\2026 Louise");
        }

        HDC hdcWindow = GetDC(window_handle);
 
        StretchBlt(hdcWindow, 0, 0, 1440, 1080, memory_dc, 0, 0, bW, bH, SRCCOPY);
        ReleaseDC(window_handle, hdcWindow);
        //Sound Section
 

        //if(header.dwFlags & WHDR_PREPARED){
          //  waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
 
            //waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
            //waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
        //}
        //fillBuffSound(&headerA, SbuffA, 880.00f);
        //fillBuffSound(&headerB, SbuffB, 880.00f);

        if(headerA.dwFlags & WHDR_DONE){
            float CurrentFreqN = 880.0f;
            //waveOutUnprepareHeader(hWaveOut, &headerA, sizeof(WAVEHDR));
            fillBuffSound(&headerA, SbuffA, CurrentFreqN);
 
            //waveOutPrepareHeader(hWaveOut, &headerA, sizeof(WAVEHDR));
            waveOutWrite(hWaveOut, &headerA, sizeof(WAVEHDR));
        }
        if(headerB.dwFlags & WHDR_DONE){
            float CurrentFreqN = 880.0f;
            //waveOutUnprepareHeader(hWaveOut, &headerB, sizeof(WAVEHDR));
            fillBuffSound(&headerB, SbuffB, CurrentFreqN);
 
            //waveOutPrepareHeader(hWaveOut, &headerB, sizeof(WAVEHDR));
            waveOutWrite(hWaveOut, &headerB, sizeof(WAVEHDR));
        }
        if(headerC.dwFlags & WHDR_DONE){
            float CurrentFreqN = 880.0f;
            //waveOutUnprepareHeader(hWaveOut, &headerB, sizeof(WAVEHDR));
            fillBuffSound(&headerC, SbuffC, CurrentFreqN);
 
            //waveOutPrepareHeader(hWaveOut, &headerB, sizeof(WAVEHDR));
            waveOutWrite(hWaveOut, &headerC, sizeof(WAVEHDR));
        }
 
        //waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
        //if (waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR)) == MMSYSERR_NOERROR) {
 
        //}
 
        //Sleep(16.6666666667); //60Frame Cap
    };

    ChangeDisplaySettingsA(NULL, 0);
//Resolution of Game = 288x216
//This uses RGB no AA included
    CloseHandle(hAudioEvent);
    waveOutUnprepareHeader(hWaveOut, &headerA, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &headerB, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &headerC, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
    return 0;
};
LRESULT CALLBACK WindowProcessMessage(HWND window_handle, UINT message, WPARAM wParam, LPARAM lParam){
    switch(message){
        case WM_QUIT:
        case WM_DESTROY: {
            playing = 0;
        } break;
 
        default: { //Message failure to handle
            return DefWindowProc(window_handle, message, wParam, lParam);
        } break;
    };
    return 0;
};