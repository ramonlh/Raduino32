/* The user interface of the ubitx consists of the encoder, the push-button on top of it
 * and the 16x2 LCD display.
 * The upper line of the display is constantly used to display frequency and status
 * of the radio. Occasionally, it is used to provide a two-line information that is 
 * quickly cleared up. */

//by KD8CEC
//VK2ETA meter for S.Meter, power and SWR

 char byteToChar(byte srcByte){ return srcByte < 10?0x30 + srcByte:'A' + srcByte - 10; }

//returns true if the button is pressed
int btnDown(void) { return digitalRead(FBUTTON) == HIGH?0:1; }
int getBtnStatus(){ return digitalRead(FBUTTON) == HIGH?0:1; }

int enc_prev_state = 3;

/**
 * The A7 And A6 are purely analog lines on the Arduino Nano
 * These need to be pulled up externally using two 10 K resistors
 * 
 * There are excellent pages on the Internet about how these encoders work
 * and how they should be used. We have elected to use the simplest way
 * to use these encoders without the complexity of interrupts etc to 
 * keep it understandable.
 * 
 * The enc_state returns a two-bit number such that each bit reflects the current
 * value of each of the two phases of the encoder
 * 
 * The enc_read returns the number of net pulses counted over 50 msecs. 
 * If the puluses are -ve, they were anti-clockwise, if they are +ve, the
 * were in the clockwise directions. Higher the pulses, greater the speed
 * at which the enccoder was spun
 */

byte enc_state (void) {
//  return (digitalRead(ENC_A)==1?1:0) + (digitalRead(ENC_B)==1?2:0);
    return (analogRead(ENC_A) > 500 ? 1 : 0) + (analogRead(ENC_B) > 500 ? 2: 0);
}

int enc_read(void) {
  int result = 0; 
  byte newState;
  int enc_speed = 0;
  unsigned long start_at = millis();
  while (millis() - start_at < 10) { // check if the previous state was stable
//  while (millis() - start_at < 50) { // check if the previous state was stable
    newState = enc_state(); // Get current state  
    if (newState != enc_prev_state)
      delay (1);
    if (enc_state() != newState || newState == enc_prev_state)
      continue; 
    //these transitions point to the encoder being rotated anti-clockwise
    if ((enc_prev_state == 0 && newState == 2) || 
      (enc_prev_state == 2 && newState == 3) || 
      (enc_prev_state == 3 && newState == 1) || 
      (enc_prev_state == 1 && newState == 0)){
        result--;
      }
    //these transitions point o the enccoder being rotated clockwise
    if ((enc_prev_state == 0 && newState == 1) || 
      (enc_prev_state == 1 && newState == 3) || 
      (enc_prev_state == 3 && newState == 2) || 
      (enc_prev_state == 2 && newState == 0)){
        result++;
      }
    enc_prev_state = newState; // Record state for next pulse interpretation
    enc_speed++;
    delay(1);
  }
  return(result);
}

//===================================================================
//I2C Signal Meter, Version 1.097
//===================================================================

// 0xA0 ~ 0xCF : CW Decode Mode + 100Hz ~
// 0xD0 ~ 0xF3 : RTTY Decode Mode + 100Hz ~
// 0x10 ~ 0x30 : Spectrum Mode
int GetI2CSmeterValue(int valueType)
{
  if (valueType > 0)
    {
    Wire.beginTransmission(I2CMETER_ADDR);  //j : S-Meter
    Wire.write(valueType);                  //Y : Get Value Type
    Wire.endTransmission();
    }
  Wire.requestFrom(I2CMETER_ADDR, 1);
  return Wire.available() > 0?Wire.read():0;
}

