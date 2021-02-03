/*************************************************************************
  KD8CEC's Memory Keyer for HAM
  
  This source code is written for All amateur radio operator, 
  I have not had amateur radio communication for a long time. CW has been 
  around for a long time, and I do not know what kind of keyer and keying 
  software is fashionable. So I implemented the functions I need mainly.

  To minimize the use of memory space, we used bitwise operations.
  For the alphabet, I put Morsecode in 1 byte. The front 4Bit is the length 
  and the 4Bit is the Morse code. Because the number is fixed in length, 
  there is no separate length information. The 5Bit on the right side is 
  the Morse code.

  I wrote this code myself, so there is no license restriction. 
  So this code allows anyone to write with confidence.
  But keep it as long as the original author of the code.
  DE Ian KD8CEC
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
//#include <avr/pgmspace.h>
#include <pgmspace.h>   //EA4GZI

//27 + 10 + 18 + 1(SPACE) = //56 
const PROGMEM uint8_t cwAZTable[27] = {0b00100100 , 0b01001000 , 0b01001010 , 0b00111000 , 0b00010000, 0b01000010, 0b00111100, 0b01000000 , //A ~ H
0b00100000, 0b01000111 ,0b00111010, 0b01000100, 0b00101100, 0b00101000 , 0b00111110, 0b01000110, 0b01001101, 0b00110100, //I ~ R
0b00110000, 0b00011000, 0b00110010, 0b01000001, 0b00110110, 0b01001001, 0b01001011, 0b01001100};  //S ~ Z
PGM_P pCwAZTable = reinterpret_cast<PGM_P>(cwAZTable);

const PROGMEM uint8_t cw09Table[27] = {0b00011111, 0b00001111, 0b00000111, 0b00000011, 0b00000001, 0b00000000, 0b00010000, 0b00011000, 0b00011100, 0b00011110};
PGM_P pcw09Table = reinterpret_cast<PGM_P>(cw09Table);

//# : AR, ~:BT, [:AS, ]:SK, ^:KN
const PROGMEM uint8_t cwSymbolIndex[] =  {'.',         ',',        '?',         '"',       '!',         '/',      '(',       ')',        '&',        ':',        ';',         '=',        '+',        '-',        '_',        '\'',       '@',          '#',         '~',        '[',        ']',        '^' };
PGM_P pCwSymbolIndex = reinterpret_cast<PGM_P>(cwSymbolIndex);

const PROGMEM uint8_t cwSymbolTable[]  = {0b11010101, 0b11110011, 0b11001100, 0b11011110, 0b11101011, 0b10100100, 0b10101100, 0b11101101, 0b10010000, 0b11111000, 0b11101010, 0b10100010, 0b10010100, 0b11100001, 0b11001101, 0b11010010,  0b11011010,  0b10010100, 0b10100010, 0b10010000, 0b11000101, 0b10101100};
PGM_P pCwSymbolTable = reinterpret_cast<PGM_P>(cwSymbolTable);
////const PROGMEM uint8_t cwSymbolLength[] = {6,          6,          6,         6,           6,          5,          5,          6,          5,          6,          6,          5,          5,          6,          6,          6,         6,         5,          5,          5,           6,          5};

// ":(Start"),   ':(End "), >: My callsign, <:QSO Callsign (Second Callsign), #:AR, ~:BT, [:AS, ]:SK

byte knobPosition = 0;
//byte cwTextData[30];                        //Maximum 30  Remarked by KD8CE -> Direct Read EEPROM
byte autoCWSendCharEndIndex = 0;
byte autoCWSendCharIndex = 0;
unsigned long autoCWbeforeTime = 0;         //for interval time between chars
byte pttBeforeStatus = 1;                   //PTT : default high
byte isKeyStatusAfterCWStart = 0;           //0 : Init, 1 : Keyup after auto CW Start, 2 : Keydown after
byte selectedCWTextIndex = 0;
unsigned long autoCWKeydownCheckTime = 0;   //for interval time between chars
byte changeReserveStatus = 0;
byte isAutoCWHold = 0;                      //auto CW Pause => Manual Keying => auto

void autoSendPTTCheck()
{
    if (isCWAutoMode == 2) {                           //Sending Mode
        //check PTT Button
        //short Press => reservation or cancel
        //long Press => Hold
        if (digitalRead(PTT) == LOW)
        {
          //if (isKeyStatusAfterCWStart == 0)          //Yet Press PTT from start TX
          //{
          //}
          
          if (isKeyStatusAfterCWStart == 1)            //while auto cw send, ptt up and ptt down again
          {
            //Start Time
            autoCWKeydownCheckTime = millis() + 200;   //Long push time
            isKeyStatusAfterCWStart = 2;               //Change status => ptt down agian
          }
          else if (isKeyStatusAfterCWStart == 2 && autoCWKeydownCheckTime < millis())
          {
            //Hold Mode
            isAutoCWHold = 1;
            isKeyStatusAfterCWStart = 3;
          }
          else if (isKeyStatusAfterCWStart == 3)
          {
            autoCWKeydownCheckTime = millis() + 200;
          }
        }
        else
        {
          //PTT UP
          if (isKeyStatusAfterCWStart == 2)            //0 (down before cw start) -> 1 (up while cw sending) -> 2 (down while cw sending)
          {
            if (autoCWKeydownCheckTime > millis())     //Short : Reservation or cancel Next Text
            {
              if (autoCWSendReservCount == 0 || 
                  (autoCWSendReservCount < AUTO_CW_RESERVE_MAX &&
                autoCWSendReserv[autoCWSendReservCount - 1] != selectedCWTextIndex))
              {
                //Reserve
                autoCWSendReserv[autoCWSendReservCount++] = selectedCWTextIndex;
                changeReserveStatus = 1;
              }
              else if (autoCWSendReservCount > 0 && autoCWSendReserv[autoCWSendReservCount - 1] == selectedCWTextIndex)
              {
                autoCWSendReservCount--;
                changeReserveStatus = 1;
              }
            } // end of Short Key up
          }
          else if (isKeyStatusAfterCWStart == 3)    //play from Hold (pause Auto CW Send)
          {
            isAutoCWHold = 0;
          }

          isKeyStatusAfterCWStart = 1;                        //Change status => ptt up (while cw send mode)
        }     //end of PTT UP  
    }
}

//Send 1 char
void sendCWChar(char cwKeyChar)
{
  byte sendBuff[7];
  byte i, j, charLength;
  byte tmpChar;

  //For Macrofunction
  //replace > and  < to My callsign, qso callsign, use recursive function call
  if (cwKeyChar == '>' || cwKeyChar == '<')
    {
    uint16_t callsignStartIndex = 0;
    uint16_t callsignEndIndex = 0;
    
    if (cwKeyChar == '>') //replace my callsign
      {
      if (conf.userCallsignLength > 0)
        {
        callsignStartIndex = 0;
        callsignEndIndex = conf.userCallsignLength;
        }
      }
    else if (cwKeyChar == '<')  //replace qso callsign
      {
      //ReadLength
      callsignEndIndex = EEPROM.read(CW_STATION_LEN);
      if (callsignEndIndex > 0)
        {
        callsignStartIndex = CW_STATION_LEN - callsignEndIndex - USER_CALLSIGN_DAT;
        callsignEndIndex = callsignStartIndex + callsignEndIndex;
        }
      }

    if (callsignStartIndex == 0 && callsignEndIndex == 0)
      return;

    for (uint16_t i = callsignStartIndex; i <= callsignEndIndex; i++)
      {
      sendCWChar(EEPROM.read(USER_CALLSIGN_DAT + i));
      autoSendPTTCheck(); //for reserve and cancel next CW Text
      if (changeReserveStatus == 1)
        {
        changeReserveStatus = 0;
        updateDisplay(1);
        }
      if (i < callsignEndIndex) delay_background(conf.cwSpeed * 3, 4,0); //
      }
    
    return;
  }
  else if (cwKeyChar >= 'A' && cwKeyChar <= 'Z')  //Encode Char by KD8CEC
  {
    tmpChar = pgm_read_byte(pCwAZTable + (cwKeyChar - 'A'));
    charLength = (tmpChar >> 4) & 0x0F;
    for (i = 0; i < charLength; i++)
      sendBuff[i] = (tmpChar << i) & 0x08;
  }
  else if (cwKeyChar >= '0' && cwKeyChar <= '9')
  {
    charLength = 5;
    for (i = 0; i < charLength; i++)
      sendBuff[i] = (pgm_read_byte(pcw09Table + (cwKeyChar - '0')) << i) & 0x10;
  }
  else if (cwKeyChar == ' ')
  {
    charLength = 0;
    delay_background(conf.cwSpeed * 4, 4,0); //7 -> basic interval is 3
  }
  else if (cwKeyChar == '$')  //7 digit
  {
    charLength = 7;
    for (i = 0; i < 7; i++)
      sendBuff[i] = (0b00010010 << i) & 0x80; //...1..1
  }
  else
  {
    //symbol
    for (i = 0; i < 22; i++)
    {
      if (pgm_read_byte(pCwSymbolIndex + i) == cwKeyChar)
      {
        tmpChar = pgm_read_byte(pCwSymbolTable + i);
        charLength = ((tmpChar >> 6) & 0x03) + 3;
        
        for (j = 0; j < charLength; j++)
          sendBuff[j] = (tmpChar << (j + 2)) & 0x80;

        break;
      }
      else
      {
        charLength = 0;
      }
    }
  }

  for (i = 0; i < charLength; i++)
  {
    cwKeydown();
    delay_background(sendBuff[i] == 0?conf.cwSpeed:conf.cwSpeed * 3, 4,0);
    cwKeyUp();
    if (i != charLength -1)
      delay_background(conf.cwSpeed, 4,0);
  }
}
