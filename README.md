# SSB_TFT_Display V1.0

## KK4DAS
- Dean Souleles
- KK4DAS@gmail.com
- May 30, 2020

### Features
- Basic radio display panel for a SSB transsceiver
- Designed for a 320x240 Color TFT (non touch)
- Tested with an ILI9341 display
  
### Requires the following libararies
- Adafruit_GFX
- Adafruit_ILI9341
  
###  Implements a basic SSB display console with the following features
     Dual VFO A/B
     Mode indicator  SSB/LSB
     Tx/Rx ndicator
     TuningStep Inidicator
     S Meter
     Banner including Call sign
  
     Fully customizable. Fast display makins use of minimal resources./
     Room is left on the screen for additional features
     There is room on the screen for another row of features
     
     Easily change colors, font sizes and layout
          
 ## Default Screeen Layout
```
  ____________________________________
  |       A 7.200.000 LSB             | -- VFO A/B indicator, Active VFO Freq, LSB/USB inidicator
  |      Rx 7.048.000 100K            | -- Rx/Tx indicator, Alternate VFO Freq, Tuning Increment
  |                                   | 
  |      S |_|_|_|_|_|_|_|_|_|_|_|_|  | -- S Meter
  |         1   3   5   7   9         |
  |                                   |
  |        AGC   SPL   RIT            | -- (Planned) AGC on/of, Split On/Off,  RIT On/OFF
  |                                   |                                        
  |     Ver   Rig Name   Call         |
  |___________________________________|
```  
## This module provides the following radio console dsiplayfunctions:
- displaySetup     - initialize the display and displays the startup values - call once from your setup function
- displayBanner    - Displays a text banner across the bottom of the screen
- displayActVFO    - Displays the frequency of the Active VFO
- displayAltVFO    - Displays the frequency of the Alternate VFO
- displayVFOAB     - Displays the indicator which VFO is active (A or B)
- displayTxRx      - Displays whether the rig is in (Tx or Rx)
- displayMode      - Displays the which sideband is selected (LSB or USB) 
- displayIncr      - Displays the tuning increment (10, 100, 1K 10K, 100K, 1M)
- displaySMeter    - Displays the S Meter (1-9 are gray, +10 +20 and +30 are red
 
## This module also provides the following general purpose displauy functions:
 - displayClearScreen     - fills the screen with the selected backgrond color
 - displayPrintat         - prints text or nubmers on the screen at a specific location
 - displayDrawBoundingBox - draw a box on the screen and fills it with a background color
 - displayDrawTextBox     - displays text inside a boundig box
 
## Design notes and how to use the code
 
## DESIGN PRINCIPLES
 Good software design principles are to use as few hard-coded numbers as possible.  
 Wherever possible I have used #defines  for any number that will be used more than one place in the code.  
 For example  #define DSP_VFO_ACT_X 60 defines the X coordinate (how far from the left of the screen) 
 of the Active VFO frequency display. You will see multiple references to DSP_VFO_ACT_X  throughout the code, 
 but I never use the hardcoded number 60 again.  Change it once – and it is changed throughout.
 
## NOTE TO BUILDERS
 This is not a complete radio control sketch. It is the Display software only. In the spirit of modular design 
 it is stand-alone and not dependent on using an SI-5351 or any other specific hardware, or on my particular 
 hardware selection of switches, buttons and knobs.  The demonstration sketch shows how to update the display,  
 but you need to provide the code to determine what the actual values should be. You will likely need other 
 libraries like the Si5351 and a Rotary encoder library aside from the GFX and the ILI9341. 
 
 ### Taking the S-Meter as an example:
 
 To update the S-Meter display you make a call to displaySMeter(n); where n is an integer from 1 to 12 
 (representing S1-9, +10, +20 +30).  Your sketch will need a way of monitoring signal strength (an analog input 
 pin on the Arduino attached to an appropriate place on your rig) and converting it to the logarithmic S scale.
 
### SCREEN COORDINATES
 Coordinates work differently on displays than a typical graph where the origin 0,0 is in the middle abd positive
 and negative values move you away from the origin. For displays  0,0, the origin, is always upper left hand corner 
 of the display and you only use positive numbers for the coordinates  +X is pixels from the left edge, +Y is pixels 
 down from the top. This particular example based on a 320x240 display but should be easily portable to other 
 display sizes – but you have to keep in mind how the coordinate system works.
 
### SCREEN LAYOUT
 Here are a few notes about how the demonstration display is laid out.  This should help you understand the design 
 concept and allow you to begin to modify it.  
 
 The VFO display is setup for a dual VFO rig.  The currently Active VFO is always on the top and the alternate VFO 
 is just below it.  Your code will need to keep track of whether VFO A or VFO B is currently selected and call the 
 display routines to update the display.   I’ll describe how the VFO displays are are defined and that will give you 
 an idea how you might modify or enhance the display.
 
 ### Active VFO - top center of the screen
 ```
#define DSP_VFO_ACT_X 60   // Active VFO begins 60 pixels from the left hand edge (I picked 60 by experimenting)
#define DSP_VFO_ACT_Y 30   // Active VFO box starts 30 pixels down from the top of the screen
                           // (Try changing it to 50 and see what happens)
#define DSP_VFO_ACT_COLOR ILI9341_GREEN   // This sets the text color for the Frequency display. Use whatever colors you like
#define DSP_VFO_ACT_BK ILI9341_BLACK      // This sets the background color for the Active VFO
#define DSP_VFO_ACT_SZ 3                  // This is text size from Arduino TFT, values 1-5 1 is small 5 is large (2 was too                                                 // small, 4 was too large, 3 was just right)
```
### Alternate VFO – the second VFO is placed directly below the Active VFO on the screen.
There are a couple of things of interest here.  For the X coordinate, instead of putting in a hard coded number I refer back to
the #define that I used for the Active VFO (DSP_VFO_ACT).  That way, if I want to move VFO section to a different part of the
screen I only need  to change one number DSP_VFO_ACT_X, and the alternate VFO will move as well.  Figuring out the Y coordinate
for the  alternate VFO is a little more challenging.  Some math is involved.  Starting with the Y coordinate of the Active VFO 
I need to calculate where how far down the display I need to go to place the second VFO.  To do that I need calculate 
how many pixels tall the text characters in the Active VFO are and use that as an offset.  It turns out we have everything 
we need already defined.  CH_W and CH_H are #defines that specify the height and width of a text character in pixels for 
TFT font size 1.  Size 2 through 5 are even multiples of that – so font height for size 2 is
```
2*CH_H pixels and font width 
```
And for size 4 is
```
4*CH_W
```
pixels and so on.  so we have everything we need to calculate how many pixels the Active VFO takes 
on the screen – we multiply the font size by the character height and add 16 pixels offset. The 16 was determined by 
experimentation for something that looked good.  The code looks like this:
``` 
#define DSP_VFO_ALT_X DSP_VFO_ACT_X
#define DSP_VFO_ALT_Y DSP_VFO_ACT_Y + (DSP_VFO_ACT_SZ * CH_H) + 16 
``` 
Take a look the other sections of the display code and you will see similar references and calculations.  The VFO A//B 
indicator and LSB/USB mode indicator, for example are similarly “pinned” to the Active VFO display, so if you move the 
Active VFO display to another screen location they will move also.

In summary - each object is on the display is defined by a set of constants that indicate the X,Y coordinates
of the object on the screen and various other attributes like text size and color.  The basic user interface display 
object is a bounded/filed text box.  You can control the text size and color, and the box fill color.  With this basic 
set of features you can implement a wide variety of user interface elements. The S-meter, for example, is a row of
filled boxes.
    
## HARDWARE NOTES
My test sketch uses an Arduino Nano. The display is an HiLetgo 2.2 Inch ILI9341 SPI TFT LCD Display 240x320 ILI9341, 
but any ILI9341 display should work. There are many sources.  Please note that the Arduino has 5V logic levels,
but the display requires 3.3V - so you need some sort of level shifter.  I used the"HiLetgo 10pcs 4 Channels IIC I2C 
Logic Level Converter Bi-Directional 3.3V-5V Shifter Module for Arduino"  I used hardware SPI and the pinouts are
standard as follows:
```      
        Arduino 
         Pin       TFT Pin
      -----------|---------    
          8      |  RST  - any free Arduino Pin (not used in this sketch)
          9      |  DC   - any free Arduino Pin
          10     |  CS   - any free Arduino Pin 
          11     |  MOSI - fixed
          12     |  MISO - fixed
          13     |  CLK  - fixed
 ```         
 That is all the wiring you need for the demonstration sketch.
 
 ## BUILDING THE DEMONSTRATION SKETCH
 
 Create a folder called SSB_TFT_Display_Demo
 
 Copy all three files to that folder
 - SSB_TFT_Display_Demo.ino
 - SSB_TFT_Display.h
 - SSB_TFT_Display.ino

 Use the Arduino IDE library manager to install the following libraries
 - Adafruit_GFX
 - Adafruit_ILI9341
    
 Compile and upload the sketch
 
 Question, comments and praisee:  kk4das@gmail.com
