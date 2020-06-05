#ifndef SSB_TFT_Display
#define SSB_TFT_Display

/*
 * SSB_TFT_Display.h
 * KK4DAS, Dean Souleles, KK4DAS@gmail.com
 * May 30, 2020
 * 
 * Constants used in the SSB_TFT_Display Routines
 * This file needs to be in included in the main sketch
 * 
 */

// ===========================Symbolic Constants==================================
#define VFOA 0 
#define VFOB 1

#define USB 0
#define LSB 1

#define RX 0
#define TX 1

// ===========================Function Prototypes==================================
void displayClearScreen();
void displayPrintat(String s, int x, int y, int fontsize, int color);
void displayPrintat(int i, int x, int y, int fontsize, int color);
void displayDrawBoundingBox(int len, int x, int y, int fontsize, int fillcolor);
void displayDrawTextBox(String s, int x, int y, int fontsize, int color, int fillcolor);
void displaySMeter(int level);
void displayBanner(String s);
void displayActVFO(uint32_t freq);
void displayAltVFO(uint32_t freq);
void displayVFOAB(int vfo);
void displayTxRx(int tx_rx);
void displayMode(int mode);
void displayIncr(int increment);
void displaySetup(String banner,
                  uint32_t vfoActfreq, uint32_t vfoAltfreq,
                  uint32_t activeVFO,
                  int tx_rx,
                  int sideband,
                  int increment,
                  int s_meter);
                  
#endif
