/* 
 * SSB_TFT_Display_Demmo
 * Version 0.9
 * May 30, 2020
 * KK4DAS, Dean Souleles, KK4DAS@gmail.com
 * 
 * Demonstration Program for SSB_TFT_Display
 * This demonstrates a basic SSB control panel with the following features:
 *     Dual VFO A/B
 *     Mode indicator  SSB/LSB
 *     Tx/Rx ndicator
 *     TuningStep Inidicator
 *     S Meter
 *     Banner including Call sign
 *  
 * All of the display management is handled in the file SSB_TFT_Display, please read the documentation
 * provided at the top of SSB_TFT_Display.ino
 * 
 * 
 * NOTE TO BUILDERS
 * This is not a complete radio control sketch. It is the Display software only. In the spirit of modular design 
 * it is stand-alone and not dependent on using an SI-5351 or any other specific hardware, or on my particular 
 * hardware selection of switches, buttons and knobs.  The demonstration sketch shows how to update the display,  
 * but you need to provide the code to determine what the actual values should be. You will likely need other 
 * libraries like the Si5351 and a Rotary encoder library aside from the GFX and the ILI9341. 
 *     
*/

#include "SSB_TFT_Display.h"                    // required constants for VFO A/b, Mode LSB/USB, etc 

#define BANNER_TXT "V1.0   RadioDemo   KK4DAS"  // displayed on the bottom line of the screen


//////////////////////////////////////////////////////////////////////
//                 Demo Sketch TEST DATA                            //
// The following variable are used by this demonstration sketch     //
// to show how the Display module works. A complete radio control   //
// sketch will need to implement and manage variables like these.   //
//////////////////////////////////////////////////////////////////////
uint32_t vfoAfreq = 7200000L;   //  7.200.000
uint32_t vfoBfreq = 7074000L;   //  FT-8 7.074.000 
uint32_t increment = 1000;      //  VFO tuning increment in Hz.
int active_vfo = VFOA;          // startup on VFOA
int sideband = LSB;             // startup in LSB
int tx_rx = RX;                 // startup in RX
int s_meter = 0;                // startup s_meter readin

//////////////////////////////////////////////////////////////////////
//       End of Demo Sketch TEST DATA                               //
//////////////////////////////////////////////////////////////////////


void setup() {
  //  To implement in a radio control program add this line to your setup funciton.
  //  Initialize the display with startup values, substitute your own variables as
  //  appropriate
  displaySetup(F(BANNER_TXT),       // version number. call sign
               vfoAfreq, vfoBfreq,  // Initial active and alternate VFO
               active_vfo,          // VFO A/B indicator
               tx_rx,               // TX/RX indicator
               sideband,            // LSB/USB,
               increment,           // Tuning increment  
               s_meter);            // S Meter
}

void loop() {
    //
    // This loop illustrates how to update the various display elements.  In a full radio control sketch this 
    // is where you would make calls to check a rotary encoder to see if the user is changing frequency.
    //
    // For demonstration purposes we will use hard coded values
    //
    delay(3000);        // wait 3 seconds

    // Change the frequency of the active VFO to 7.150.500
    vfoAfreq = 7150500;
    displayActVFO(vfoAfreq);

    // Simulate turning the VFO 25 clicks
    for(int i=1; i<=25; i++){
      vfoAfreq = vfoAfreq + 1000;
      displayActVFO(vfoAfreq);
      delay(200);
    }
    
    // Change the Sideband to USB
    sideband = USB;
    displayMode(sideband);
    delay(1000);

    // Change the Tx/Rx Indicator to Tx
    tx_rx = TX;
    displayTxRx(tx_rx);
    delay(1000);

    // Change the Tuning Increment to 1K
    increment = 1000;
    displayIncr(increment);
    delay(1000);

    //  Change the S Meter to +20dB
    s_meter = 11;
    displaySMeter(s_meter);
    delay(1000);

    // Swap VFOs change the Active VFO to VFOB, the alternate to VFOA and update the indicator
    active_vfo = VFOB;
    displayActVFO(vfoBfreq);
    displayAltVFO(vfoAfreq);
    displayVFOAB(active_vfo);
    delay(1000);

    // Change the Sideband to LSB
    sideband = LSB;
    displayMode(sideband);
    delay(1000);

    // Change the Tx/Rx Indicator to Rx
    tx_rx = RX;
    displayTxRx(tx_rx);
    delay(1000);

    // Make VFO Active and update the display
    active_vfo = VFOA;
    displayActVFO(vfoAfreq);
    displayAltVFO(vfoBfreq);
    displayVFOAB(active_vfo);
    delay(1000);

    // Change the Tuning Increment to 100K
    increment = 100000;
    displayIncr(increment);
    delay(1000);

    //  Change the S Meter to S3
    s_meter = 3;
    displaySMeter(s_meter);
    delay(1000);  

    // Reset to initial values and repeat the demo
    vfoAfreq = 7200000L;
    vfoBfreq = 7074000L; 
    increment = 1000;
    active_vfo = VFOA;
    sideband = LSB;
    tx_rx = RX;
    s_meter = 0;
    displayActVFO(vfoAfreq);
    displayAltVFO(vfoBfreq);
    displayVFOAB(active_vfo);
    displayMode(sideband);
    displayTxRx(tx_rx);
    displayIncr(increment);
    displaySMeter(s_meter);   
  }
