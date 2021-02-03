/*************************************************************************
  header file for C++ by KD8CEC
  modified by EA4GZI
-----------------------------------------------------------------------------
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/
#ifndef _UBITX_HEADER__
#define _UBITX_HEADER__

//==============================================================================
// Compile Option
//==============================================================================

//Select betwen Analog S-Meter and DSP (I2C) Meter
#define USE_I2CSMETER

//#define ENABLE_FACTORYALIGN
#define SMeterLatency   3               // 1 is 0.25 sec

//==============================================================================
// Hardware, Define PIN Usage
//==============================================================================
// for ESP32

// To Raduino
#define ENC_A         34    // INPUT
#define ENC_B         35    // INPUT
#define FBUTTON       36    // INPUT
#define PTT           15    // INPUT
#define ANALOG_KEYER  33    // INPUT ANALOG
#define TX_RX         23   // Relay
#define CW_TONE       16   // OUTPUT PWM
#define TX_LPF_A      25   // OUTPUT Relay, azul
#define TX_LPF_B      26   // OUTPUT Relay, verde
#define TX_LPF_C      27   // OUTPUT Relay, marrón
#define CW_KEY        2    // OUTPUT
#define SDA           18
#define SCL           19

// to external devices
#define W0            4     // sondas DS18B20   // EA4GZI
#define RXD2          39    // UART2            // EA4GZI
#define TXD2          22    // UART2            // EA4GZI

//******************************************************
//DSP (I2C) Meter 
//******************************************************
//S-Meter Address
#define I2CMETER_ADDR     0x58

//*******************************************************
// ADC ports ADS1115
#define VFORp 0
#define VREFp 1
#define SMETERp 2

//*******************************************************
//  Commands TCP conection    // NO USAR 10 NI 13 
#define tcpsplitOn 3
#define tcpisUSB 4
#define tcpcwMode 5
#define tcpritOn 8
#define tcpvfoActive 19
#define tcpisusbA 20
#define tcpisusbB 21
#define tcpcwmodeA 22
#define tcpcwmodeB 23
#define tcpbanddn 40    // band dn
#define tcpbandup 41    // band up
#define tcpfreqdn 42    // freq dn
#define tcpfrequp 43    // freq up
#define tcpCallSign 44
#define tcpfrequency 45
#define tcpfrequencyA 46
#define tcpfrequencyB 47
#define tcptemp1 48     // temp 1
#define tcptemp2 49     // temp 2
#define tcptemp3 50     // temp 3
#define tcptunestep 51    // define step
#define tcpwifi 52        // set WiFi
#define tcpreset 53       // reset remoto
#define tcpframe 54       // framemode
#define tcpminsmeter 55   // valor mínimo smeter
#define tcpmaxsmeter 56   // valor máximo smeter
#define tcpscanst 64
#define tcpkeylock 65

#define tcpALL 127

//==============================================================================
// for public, Variable, functions
//==============================================================================

extern char auxc[30];
extern char auxb[30];
extern void clearTFT(void);
extern void readCW();

#endif    //end of if header define

