///////////////////////////////////////////////////////////////////////
// CW Decoder made by Hjalmar Skovholm Hansen OZ1JHM  VER 1.01       //
// Feel free to change, copy or what ever you like but respect       //
// that license is http://www.gnu.org/copyleft/gpl.html              //
// Discuss and give great ideas on                                   //
// https://groups.yahoo.com/neo/groups/oz1jhm/conversations/messages //
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// Read more here http://en.wikipedia.org/wiki/Goertzel_algorithm        //
// if you want to know about FFT the http://www.dspguide.com/pdfbook.htm //
///////////////////////////////////////////////////////////////////////////

////////////  CW decode /////////////////////
float magnitude ;
int magnitudelimit = 100;
int magnitudelimit_low = 100;
int realstate = LOW;
int realstatebefore = LOW;
int filteredstate = LOW;
int filteredstatebefore = LOW;

///////////////////////////////////////////////////////////
// The sampling frq will be 8928 on a 16 mhz             //
// without any prescaler etc                             //
// because we need the tone in the center of the bins    //
// you can set the tone to 496, 558, 744 or 992          //
// then n the number of samples which give the bandwidth //
// can be (8928 / tone) * 1 or 2 or 3 or 4 etc           //
// init is 8928/558 = 16 *4 = 64 samples                 //
// try to take n = 96 or 128 ;o)                         //
// 48 will give you a bandwidth around 186 hz            //
// 64 will give you a bandwidth around 140 hz            //
// 96 will give you a bandwidth around 94 hz             //
// 128 will give you a bandwidth around 70 hz            //
// BUT remember that high n take a lot of time           //
// so you have to find the compromice - i use 48         //
///////////////////////////////////////////////////////////

float coeff;
float Q1 = 0.0;
float Q2 = 0.0;
float sine;
float cosine;  
float sampling_freq=8928.0;
float target_freq=558.0;    // adjust for your needs see above
int ndata=48;               // if you change her please change next line also 
int testData[48];

// Noise Blanker time which shall be computed so this is initial         
int nbtime = 6;  /// ms noise blanker         

long starttimehigh;
long highduration;
long lasthighduration;
long hightimesavg;
long lowtimesavg;
long startttimelow;
long lowduration;
long laststarttime = 0;

char code[20];
int stop = LOW;
int wpm;

void printascii(int asciinumber){
  s2(asciinumber);
  }

void docode(){
  if (strcmp(code,".-") == 0) printascii(65);
  if (strcmp(code,"-...") == 0) printascii(66);
  if (strcmp(code,"-.-.") == 0) printascii(67);
  if (strcmp(code,"-..") == 0) printascii(68);
  if (strcmp(code,".") == 0) printascii(69);
  if (strcmp(code,"..-.") == 0) printascii(70);
  if (strcmp(code,"--.") == 0) printascii(71);
  if (strcmp(code,"....") == 0) printascii(72);
  if (strcmp(code,"..") == 0) printascii(73);
  if (strcmp(code,".---") == 0) printascii(74);
  if (strcmp(code,"-.-") == 0) printascii(75);
  if (strcmp(code,".-..") == 0) printascii(76);
  if (strcmp(code,"--") == 0) printascii(77);
  if (strcmp(code,"-.") == 0) printascii(78);
  if (strcmp(code,"---") == 0) printascii(79);
  if (strcmp(code,".--.") == 0) printascii(80);
  if (strcmp(code,"--.-") == 0) printascii(81);
  if (strcmp(code,".-.") == 0) printascii(82);
  if (strcmp(code,"...") == 0) printascii(83);
  if (strcmp(code,"-") == 0) printascii(84);
  if (strcmp(code,"..-") == 0) printascii(85);
  if (strcmp(code,"...-") == 0) printascii(86);
  if (strcmp(code,".--") == 0) printascii(87);
  if (strcmp(code,"-..-") == 0) printascii(88);
  if (strcmp(code,"-.--") == 0) printascii(89);
  if (strcmp(code,"--..") == 0) printascii(90);

  if (strcmp(code,".----") == 0) printascii(49);
  if (strcmp(code,"..---") == 0) printascii(50);
  if (strcmp(code,"...--") == 0) printascii(51);
  if (strcmp(code,"....-") == 0) printascii(52);
  if (strcmp(code,".....") == 0) printascii(53);
  if (strcmp(code,"-....") == 0) printascii(54);
  if (strcmp(code,"--...") == 0) printascii(55);
  if (strcmp(code,"---..") == 0) printascii(56);
  if (strcmp(code,"----.") == 0) printascii(57);
  if (strcmp(code,"-----") == 0) printascii(48);

  if (strcmp(code,"..--..") == 0) printascii(63);
  if (strcmp(code,".-.-.-") == 0) printascii(46);
  if (strcmp(code,"--..--") == 0) printascii(44);
  if (strcmp(code,"-.-.--") == 0) printascii(33);
  if (strcmp(code,".--.-.") == 0) printascii(64);
  if (strcmp(code,"---...") == 0) printascii(58);
  if (strcmp(code,"-....-") == 0) printascii(45);
  if (strcmp(code,"-..-.") == 0) printascii(47);

  if (strcmp(code,"-.--.") == 0) printascii(40);
  if (strcmp(code,"-.--.-") == 0) printascii(41);
  if (strcmp(code,".-...") == 0) printascii(95);
  if (strcmp(code,"...-..-") == 0) printascii(36);
  if (strcmp(code,"...-.-") == 0) printascii(62);
  if (strcmp(code,".-.-.") == 0) printascii(60);
  if (strcmp(code,"...-.") == 0) printascii(126);
  // The specials 
  if (strcmp(code,".-.-") == 0) printascii(3);
  if (strcmp(code,"---.") == 0) printascii(4);
  if (strcmp(code,".--.-") == 0) printascii(6);
}

void initDecodeCW() {
// The basic goertzel calculation 
  int k;
  float omega;
  k = (int) (0.5 + ((ndata * target_freq) / sampling_freq));
  omega = (2.0 * PI * k) / ndata;
  sine = sin(omega);
  cosine = cos(omega);
  coeff = 2.0 * cosine;
  s2("k:"); s2(k); s2(crlf);
  s2("omega:"); s2(omega); s2(crlf);
  s2("sine:"); s2(sine); s2(crlf);
  s2("cosine:"); s2(cosine); s2(crlf);
  s2("coeff:"); s2(coeff); s2(crlf);
}

void decodeCW() {
  // The basic where we get the tone
  //readCW(); 
  //s2("cw:"); s2(cwcodevalue); s2(crlf);
  return;
  
  for (byte i = 0; i < ndata; i++)
    {
    readCW();
    testData[i]=cwcodevalue;
    //testData[i]=adsA.readADC_SingleEnded(3); 
    s2(testData[i]); s2("-");
    }
   s2(crlf);
  for (byte i = 0; i < ndata; i++){
	  float Q0;
	  Q0 = coeff * Q1 - Q2 + (float) testData[i];
	  Q2 = Q1;
	  Q1 = Q0;	
    }
  float magnitudeSquared = (Q1*Q1)+(Q2*Q2)-Q1*Q2*coeff;  // we do only need the real part //
  magnitude = sqrt(magnitudeSquared);
  Q2 = 0;
  Q1 = 0;

  //s2(magnitude); s2(crlf);  //// here you can measure magnitude for setup..
  /////////////////////////////////////////////////////////// 
  // here we will try to set the magnitude limit automatic //
  ///////////////////////////////////////////////////////////
  
  if (magnitude > magnitudelimit_low){
    magnitudelimit = (magnitudelimit +((magnitude - magnitudelimit)/6));  /// moving average filter
    }
 
  if (magnitudelimit < magnitudelimit_low)
	  magnitudelimit = magnitudelimit_low;
  
  ////////////////////////////////////
  // now we check for the magnitude //
  ////////////////////////////////////
  if(magnitude > magnitudelimit*0.6) // just to have some space up 
     realstate = HIGH; 
  else
    realstate = LOW; 
  
  ///////////////////////////////////////////////////// 
  // here we clean up the state with a noise blanker //
  /////////////////////////////////////////////////////
 
  if (realstate != realstatebefore){
	  laststarttime = millis();
    }
  if ((millis()-laststarttime)> nbtime){
	  if (realstate != filteredstate){
		  filteredstate = realstate;
	    }
    }
 
 ////////////////////////////////////////////////////////////
 // Then we do want to have some durations on high and low //
 ////////////////////////////////////////////////////////////
 
 if (filteredstate != filteredstatebefore){
   if (filteredstate == HIGH){
		 starttimehigh = millis();
		 lowduration = (millis() - startttimelow);
	   }

	if (filteredstate == LOW){
		startttimelow = millis();
		highduration = (millis() - starttimehigh);
        if (highduration < (2*hightimesavg) || hightimesavg == 0){
			hightimesavg = (highduration+hightimesavg+hightimesavg)/3;     // now we know avg dit time ( rolling 3 avg)
		}
		if (highduration > (5*hightimesavg) ){
			hightimesavg = highduration+hightimesavg;     // if speed decrease fast ..
		}
	}
  }

 ///////////////////////////////////////////////////////////////
 // now we will check which kind of baud we have - dit or dah //
 // and what kind of pause we do have 1 - 3 or 7 pause        //
 // we think that hightimeavg = 1 bit                         //
 ///////////////////////////////////////////////////////////////
 
  if (filteredstate != filteredstatebefore){
    stop = LOW;
    if (filteredstate == LOW){  //// we did end a HIGH
      if (highduration < (hightimesavg*2) && highduration > (hightimesavg*0.6)){ /// 0.6 filter out false dits
	  strcat(code,".");
	  s2(".");
    }
    if (highduration > (hightimesavg*2) && highduration < (hightimesavg*6)){ 
	  strcat(code,"-");
	  s2("-");
	  wpm = (wpm + (1200/((highduration)/3)))/2;  //// the most precise we can do ;o)
    }
  }
  if (filteredstate == HIGH){  //// we did end a LOW
   
  float lacktime = 1;
    if(wpm > 25)lacktime=1.0; ///  when high speeds we have to have a little more pause before new letter or new word 
    if(wpm > 30)lacktime=1.2;
    if(wpm > 35)lacktime=1.5;
   
    if (lowduration > (hightimesavg*(2*lacktime)) && lowduration < hightimesavg*(5*lacktime)){ // letter space
     docode();
	 code[0] = '\0';
	 s2("/");
   }
   if (lowduration >= hightimesavg*(5*lacktime)){ // word space
     docode();
 	 code[0] = '\0';
   printascii(32);
   s2(crlf);
   }
  }
 }
 
 // write if no more letters
  if ((millis() - startttimelow) > (highduration * 6) && stop == LOW){
    docode();
    code[0] = '\0';
    stop = HIGH;
    }

  // the end of main loop clean up
  s2("wpm:"); s2(wpm); s2(crlf);
  realstatebefore = realstate;
  lasthighduration = highduration;
  filteredstatebefore = filteredstate;
  }


////////////////////////////////
// translate cw code to ascii //
////////////////////////////////


