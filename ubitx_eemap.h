/*************************************************************************
  header file for EEProm Address Map by KD8CEC
  It must be protected to protect the factory calibrated calibration.
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
#ifndef _UBITX_EEPOM_HEADER__
#define _UBITX_EEPOM_HEADER__

//==============================================================================
// Factory-shipped EEProm address (factory Firmware) Address : 0 ~ 31
//==============================================================================

//==============================================================================
// KD8CEC EEPROM MAP
// Address : 101 ~ 1023
// 256 is the base address
// 256 ~ 1023 (EEProm Section #1)
// 255 ~ 101  (EEProm Section #2)
//==============================================================================

//0x00 : None, 0x01 : MODE, 0x02:BAND+, 0x03:BAND-, 0x04:TUNE_STEP, 0x05:VFO Toggle, 0x06:SplitOn/Off, 0x07:TX/ON-OFF,  0x08:SDR Mode On / Off, 0x09:Rit Toggle
#define EXTENDED_KEY_RANGE    140 //Extended Key => Set : Start Value, End Value, Key Type, 16 Set (3 * 16 = 48)

//for reduce cw key error, eeprom address
#define CW_ADC_MOST_BIT1      348   //most 2bits of  DOT_TO , DOT_FROM, ST_TO, ST_FROM
#define CW_ADC_ST_FROM        349   //CW ADC Range STRAIGHT KEY from (Lower 8 bit)
#define CW_ADC_ST_TO          350   //CW ADC Range STRAIGHT KEY to   (Lower 8 bit)
#define CW_ADC_DOT_FROM       351   //CW ADC Range DOT  from         (Lower 8 bit)
#define CW_ADC_DOT_TO         352   //CW ADC Range DOT  to           (Lower 8 bit)

#define CW_ADC_MOST_BIT2      353   //most 2bits of BOTH_TO, BOTH_FROM, DASH_TO, DASH_FROM
#define CW_ADC_DASH_FROM      354   //CW ADC Range DASH from         (Lower 8 bit)
#define CW_ADC_DASH_TO        355   //CW ADC Range DASH to           (Lower 8 bit)
#define CW_ADC_BOTH_FROM      356   //CW ADC Range BOTH from         (Lower 8 bit)
#define CW_ADC_BOTH_TO        357   //CW ADC Range BOTH to           (Lower 8 bit)

#define WSPR_COUNT            443   //WSPR_MESSAGE_COUNT
#define WSPR_MESSAGE1         444   //

//USER INFORMATION
#define USER_CALLSIGN_DAT     782   //CALL SIGN DATA  //direct EEPROM to LCD basic offset

//AUTO KEY USE 800 ~ 1023
#define CW_AUTO_MAGIC_KEY     800   //0x73
#define CW_AUTO_COUNT         801   //0 ~ 255
#define CW_AUTO_DATA          803   //[INDEX, INDEX, INDEX,DATA,DATA, DATA (Positon offset is CW_AUTO_DATA
#define CW_DATA_OFSTADJ       CW_AUTO_DATA - USER_CALLSIGN_DAT   //offset adjust for ditect eeprom to lcd (basic offset is USER_CALLSIGN_DAT
#define CW_STATION_LEN        1023  //value range : 4 ~ 30

#endif    //end of if header define

