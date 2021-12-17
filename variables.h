///////////////////////////////////////////////////////////////////////////////
/* Raduino needs to keep track of current state of the transceiver. These are a few variables that do it */

//****************** PORTS **************************
#define FTPPort    21
#define DEBUGPort  23
#define TCPPort  8084
#define UDPPortS 8085
#define WSPort   8086
#define UDPPortF 8087
#define WEBPort  8088 

  typedef struct {    // datos configuración
      uint8_t LIBRE0;
      int32_t calibration;
      unsigned long usbCarrier;
      unsigned long cwmCarrier;
      uint8_t splitOn;   //working split, uses VFO B as the transmit frequency                  byte isUSB = 0;   //upper sideband was selected, this is reset to the default for the
      uint8_t isUSB;     //upper sideband was selected, this is reset to the default for the
      int cwMode;       //compatible original source, and extend mode //if cwMode == 0, mode check : isUSB, cwMode > 0, mode Check : cwMode
                //iscwMode = 0 : ssbmode, 1 :cwl, 2 : cwu, 3 : cwn (none tx)
      unsigned int cwSpeed; //this is actuall the dot period in milliseconds
      unsigned long cwTimeout;    //milliseconds to go before the cw transmit line is released and the radio goes back to rx mode
      uint8_t ritOn;
      uint8_t cwModeA;     // 0: no CW, 1: CW mode
      uint8_t cwModeB;     // 0: no CW, 1: CW mode
      uint8_t attLevel;    // ATT : RF Gain Control (Receive) <-- IF1 Shift, 0 : Off, ShiftValue is attLevel * 100; attLevel 150 = 15K
      uint8_t sdrModeOn;   // SDR MODE ON / OFF
      int TempAlarm;
      int TempTxOff;
      uint8_t framemode;   // 0: analog meter, 1: frames igital meter, 2:spectrum,  3:Frequencies
      uint8_t frame1mode;  // 0:ATT, 1: data (frame0mode=0)
      uint8_t frame2mode;  // 0:IFS, 2: data (frame0mode=0)
      uint8_t frame3mode;  // 0:analog meter (frame0mode=0), 1: bar meter (framemode=1)
      uint8_t vfoActive;
      uint8_t isUSBA;        //0:LSB, 1:USB
      uint8_t isUSBB;        //0:LSB, 1:USB
      float ATUFactor;         // ATU correction factor
      float ATUOffset;        // ATU correction offset
      unsigned long sideTone;
      uint8_t cwDelayTime;
      uint8_t delayBeforeCWStartTime;
      uint8_t SI5351BX_ADDR;        // I2C address of Si5351   (variable from Version 1.097)
      uint8_t cwKeyType;         //0: straight, 1 : iambica, 2: iambicb
      uint8_t tuneStepIndex;     //default Value 6, start Offset is 0 because of check new user
      uint8_t commonOption0;   //0: Confirm : CW Frequency Shift,  1 : IF Shift Save
      uint8_t addrADS1115A; // dir ADS 1115 module analog converter
      uint8_t useHamBandCount;  //0 use full range frequency
      uint8_t tuneTXType;   //0 : use full range, 1 : just Change Dial speed, 2 : just ham band change, but can general band by tune, 3 : only ham band (just support 0, 2 (0.26 version))
                  //100 : use full range but not TX on general band, 101 : just change dial speed but.. 2 : jut... but.. 3 : only ham band  (just support 100, 102 (0.26 version))
      uint8_t isShiftDisplayCWFreq;  //Display Frequency
      unsigned int hamBandRange[MAX_BANDS][2];    // =  //Khz because reduce use memory
      long freqbyband[MAX_BANDS][2];
      char hamBandName[MAX_BANDS][4];
      uint8_t connMode;     // 0: IP,  1: Serial2
      uint8_t serial2Mode;  // 0: Debug,  1: Manager
      uint8_t timezone;
      uint8_t modecalsmeter=0;
      uint8_t LIBRE1[16];
      int ifShiftValue;   //
      uint8_t addrADS1115B; // dir ADS 1115 module analog converter
      uint8_t LIBRE2[6];
      int squelchval;
      int ATUIter;
      uint8_t posATUC1;
      uint8_t posATUC2;
      int sMeterLevels[16]={8000,9500,10250,11000,11750,12500,13250,14000,14750,15500,16250,17000,17750,18500,19250,20000};
      uint8_t ftpenable=1;
      uint8_t debugenable;
      uint8_t tcpenable;
      uint8_t udpenable;
      uint8_t wsenable;
      uint8_t seripenable=1;
      uint8_t webenable=1;
      uint8_t LIBRE3[6];         // NO USADO, LIBRE
      uint8_t userCallsignLength;    //7 : display callsign at system startup, 6~0 : callsign length (range : 1~18)
      char CallSign[20];
      uint8_t WsprMSGCount;
      unsigned long frequency;     // frequency is the current frequency on the dial
      unsigned long frequencyA;   // frequency is the current frequency VFOA
      unsigned long frequencyB;  // frequency is the current frequency VFOB
      unsigned long ritRxFrequency;
      unsigned long ritTxFrequency;
      uint8_t scaledSMeter;
      uint8_t wifimode;     // default AP
      uint8_t canalAP;      // 1 byte, canal ESP en modo AP
      char ssidSTA[20];      // 20 bytes, SSID en modo STA
      char passSTA[20];      // 20 bytes, Password en modo STA
      char ssidAP[20];          // 20 bytes, SSID en modo AP
      char passAP[20];       // 20 bytes, Password en modo AP
      IPAddress EEip;   // 4 bytes, dirección IP
      IPAddress EEgw;     // 4 bytes, puerta de enlace
      IPAddress EEmask; // 4 bytes, máscara de subred
      IPAddress EEdns;        // 4 bytes, servidor DNS primario
      IPAddress EEdns2;       // 4 bytes, servidor DNS secundario
      char EEmac[6][3];                 // 18 bytes, MAC
      char myippub[16];              // 16 bytes, dirección IP pública
      uint8_t staticIP;               // 1 byte, IP estática Sí/No
      uint8_t LIBRE4[3];                   //
      unsigned long firstIF;
      unsigned long arTuneStep[9];
      float latitud;
      float longitud;
      uint8_t lang;                      // 0=español, 1=inglés, 2=francés, 3=alemán
      uint8_t rstper;
      uint8_t usepassDev;                // 1 byte, 0 no usar password,  1 usar password
      uint8_t probecode[maxTemp][8];    // código de sonda
      char userDev[20];         // 20 bytes, usuario device
      char passDev[20];         // 20 bytes, password device
      uint8_t iftttenabled;
      char iftttkey[30];             // 30 bytes, ifttt key
      uint8_t iottweetenable;
      char iottweetuser[10];         // 10 bytes, IoTtweet account user ID
      char iottweetkey[15];          // 15 bytes, IoTtweet account key
      uint8_t mqttenabled;
      char mqttserver[40];           // MQTT broker
      char mqttpath[6][10];       // MQTT path
      uint8_t LIBRE9;                 
      uint8_t LIBRE6;
      uint8_t LIBRE7[10];             
      uint8_t LIBRE8;               
      char hostmyip[30];// 30 bytes, URL del servidor de IP pública
      uint8_t actualBand;
      uint8_t autoWiFi;
      uint8_t scanallf;                  // 0: scan only ham bands, 1:scan all freq.
      uint8_t TXall;                     // 0; TX only ham bands
      uint8_t autoMode;                  // switch mode auto
      uint16_t calData[5];  // calibration TFT touch
      uint8_t memMode;                   // 0: VFO mode, 1:mem Mode
      int lastmempos;
      int scandelay;
      uint8_t scanmode;          // 0: no stop, 1:resume after delay, 2:stop forever
      uint8_t Smeterenabled;
      uint8_t SWRenabled;
      uint8_t DS18B20enabled;
      uint8_t ATUZM2enabled;
      int cwAdcSTFrom;             //CW ADC Range
      int cwAdcSTTo;
      int cwAdcDotFrom;
      int cwAdcDotTo;
      int cwAdcDashFrom;
      int cwAdcDashTo;
      int cwAdcBothFrom;
      int cwAdcBothTo;
      uint8_t TPA2016enabled;
      uint8_t TPA2016Compvalue;
      uint8_t TPA2016Compmaxgain;
      uint8_t TPA2016Gain;    // -28 a +30 db
      char watermark[16]; // código de verificación uBitx
      char smeterTit[16][4];
      uint8_t ATUdelay;                 // en segundos
      uint8_t nprobe[maxTemp];   // estos dos valores van aparejados
      int ftpPort;
      int debugPort;
      int tcpPort;
      int webPort;
      int udpPortSmeter;
      int wsPort;
      int udpPortFreq;
      uint8_t LIBRE5[363];                 // Reservados usos futuros
} conftype;
      conftype conf;
      uint8_t *buffconf = (uint8_t *) &conf; // acceder a conf2 como bytes

  typedef struct {    // datos memorias
      uint8_t act[maxMem];         // activa o no
      uint8_t vfoActive[maxMem];      // VFO 
      uint8_t isUSB[maxMem];       // mode
      uint8_t cwMode[maxMem];      // CW mode
      uint8_t ritOn[maxMem];       // RIT
      uint8_t splitOn[maxMem];     // SPL
      unsigned long frequency[maxMem];  // frequency
      unsigned long ritTxFrequency[maxMem];  // frequency TX Rit
      uint8_t LIBRE[maxMem];         //  
      uint8_t cwModespl[maxMem];        // CW mode TX split
      unsigned long ftxspl[maxMem];  // frequency TX Split
      char descr[maxMem][20];        // descripción
} memotype;
      memotype memo;
      uint8_t *buffmemo=(uint8_t *) &memo; // acceder a mem como bytes

  // space for save freq actual
  uint8_t vfoActiveAct;      // VFO 
  uint8_t isUSBAct;       // mode
  uint8_t cwModeAct;      // CW mode
  uint8_t ritOnAct;       // RIT
  uint8_t splitOnAct;     // SPL
  unsigned long frequencyAct;  // frequency
  unsigned long ritTxFrequencyAct;  // frequency TX Rit
  uint8_t isUsbsplAct;      // isUSB TX split mode
  uint8_t cwModesplAct;     // CW mode TX split
  unsigned long ftxsplAct;  // frequency TX Split

//////  tratamiento de bits /////////////////////
const byte tab[8]={1,2,4,8,16,32,64,128}; // 8
char watermarkref[16]="uBitx1234567890";  // código de verificación uBitx

String msg;                     // String donde se construye la respuesta HTML qu e se envía al cliente
char buff[20];                  // 20 bytes, auxiliar
char auxchar[130];              // 130 bytes, auxiliar 
char auxdesc[60];               // 60 bytes, auxiliar para lectura de descriptores de archivos
char auxtft[30];                // 30 bytes, auxiliar para varios
byte nTemp=0;                  // número sondas detectadas en cada puerto 1-wire
uint8_t addr1Wire[maxTemp][8];  // tiene los valores conectados
unsigned long mact01,mact1,mact2,mact10,mact60,mact3600; 
int nAP=0;                      // 2 bytes, redes encontradas con scanAP
int nAPact=0;                   // 2 bytes, redes actual
unsigned long countfaulttime=29999;       // veces que ha fallado la sincronización
int param_number=0;             // variables auxiliares para parámetros en POST
int indice=0;                   // variables auxiliares para parámetros en POST
int resto=0;                    // variables auxiliares para parámetros en POST
int mival=0;                    // variables auxiliares para parámetros en POST
int mp=1;                       // variables auxiliares para parámetros en POST
int mpi=0;                      // variables auxiliares para parámetros en POST
boolean colorea;                // variables auxiliares para parámetros en POST
char mac[14]="";                // MAC del dispositivo

char host[16]="";
char hostraiz[16]="192.168.";

int MbR[8]={0,0,0,0,0,0,0,0};      // 0-7 Temperaturas locales
int MbRant[8]={0,0,0,0,0,0,0,0};   // 0-7 Temperaturas locales

boolean filesok=false;
char fileconf[]="/ubitx.cnf";
char filememo[]="/ubitx.mem";
char filecommon[]="/common.txt";
char filespanish[]="/spanish.txt";
char fileenglish[]="/english.txt";
char filegerman[]="/german.txt";
char filedash[]="/dash.txt";
char flecha[4][3]={"<","<<",">>",">"};
byte tftpage=0;
byte tftapactual=0;
byte scanF=0;   // 1: DW, 2: UP
byte keylock=0; // bloqueo teclado y botones
int mempos=0;   // posición actual de memoria
int memlin=0;   // posición actual en la pantalla de lista de memorias

unsigned long tini=0;
char cinput;
String sinput="";
////////////////////////////////////////
int nSWR=100;
float SWR=1.0;
float SWRreal=1.0;
float swrmin=999.99;   
float vFORc; 
float vREFc; 
unsigned long lastswr=0;
unsigned long swrper=10; 
int16_t smetervalue=0;
int16_t smeterlast=0;
int16_t cwcodevalue=0;
float vtotvalue=0.0;    
float itotvalue=0.0;  
int posmin1=180;    // ATU
int posmin2=180;    // ATU
char freqpartant[9][4]={"","","","","","","","",""};
byte squelchenabled=0;
unsigned long OSC0=0;
unsigned long OSC1=0;
unsigned long OSC2=0;
unsigned long IF1=0;
unsigned long IF2=0;
int lastframemode=0;
boolean calSmeterReq=false;
float wFORc;
float wREFc;

// spectrum values
int spval[250];
boolean readingspectrum=false;
int maxvalspectrum=0;
unsigned long lasttimeknob=0;

const char idpin[34][4]={"t0","t1","t2","t3","t4","t5","t6","t7","e0","e1","e2","e3","s0","s1","s2","s3","s4","s5","s6","s7","x1","x2","id","ip","ipp",
                         "c0","c1","c2","c3","c4","c5","c6","c7","all"};
const char wifimodetext[4][7]={"OFF","STA","AP","AP+STA"};
const char connmodetext[5][10]={"OFF","IP as STA","IP as AP","Serial-IP","Serial"};
const char serial2modetext[2][8]={"Debug","Manager"};
char timezonetext[39][7]={"-12","-11","-10","-9:30","-9","-8","-7","-6","-5:30","-5",
                          "-4","-3:30","-3","-2","-1","+0","+1","+2","+3",
                          "+3:30","+4","+4:30","+5","+5:30","+5:45","+6",
                          "+6:30","+7","+8","+8:45","+9","+9:30","+10",
                          "+10:30","+11","+12","+12:45","+13","+14"};
long timezoneval[39]={-43200,-39600,-36000,-34200,-32400,-28800,-25200,-21600,-19800,-18000,
                      -14400,-12600,-10800,-7200,-3600,0,3600,7200,10800,12600,14400,
                      16200,18000,19800,20700,21600,23400,25200,28800,31500,32400,34200,
                      36000,37800,39600,43200,45900,46800,50400};                          

boolean internetON=false;

int maxsmeter=0;
int minsmeter=29999;
boolean remoteclientexits=false;
char udpAddress[16] = "192.168.000.000";
byte isUSBtemp=0;
unsigned long frequencytemp=7000000;


void initConf()
{
  conf.LIBRE0=0;  
  conf.calibration=180000;
  conf.usbCarrier=11056000;
  conf.cwmCarrier=11056000;
  conf.splitOn=0;   //working split, uses VFO B as the transmit frequency                  byte isUSB = 0;   //upper sideband was selected, this is reset to the default for the 
  conf.isUSB=0;     //upper sideband was selected, this is reset to the default for the 
  conf.cwMode=0;       //compatible original source, and extend mode //if cwMode == 0, mode check : isUSB, cwMode > 0, mode Check : cwMode
                      //iscwMode = 0 : ssbmode, 1 :cwl, 2 : cwu, 3 : cwn (none tx)
  conf.cwSpeed=100; //this is actuall the dot period in milliseconds
  conf.cwTimeout=0;    //milliseconds to go before the cw transmit line is released and the radio goes back to rx mode
  conf.ritOn=0;
  conf.cwModeA=0;     // 0: no CW, 1: CW mode
  conf.cwModeB=0;     // 0: no CW, 1: CW mode
  conf.attLevel=0;    // ATT : RF Gain Control (Receive) <-- IF1 Shift, 0 : Off, ShiftValue is attLevel * 100; attLevel 150 = 15K
  conf.sdrModeOn=0;   // SDR MODE ON / OFF
  conf.TempAlarm=45;
  conf.TempTxOff=50;
  conf.framemode=0;   // 0: analog meter, 1: frames igital meter, 2:spectrum,  3:Frequencies
  conf.frame1mode=0;  // 0:ATT, 1: data (frame0mode=0)
  conf.frame2mode=0;  // 0:IFS, 2: data (frame0mode=0)
  conf.frame3mode=0;  // 0:analog meter (frame0mode=0), 1: bar meter (framemode=1)
  conf.vfoActive=VFO_A;
  conf.isUSBA=0;        //0:LSB, 1:USB
  conf.isUSBB=1;        //0:LSB, 1:USB
  conf.ATUFactor=0.0;         // ATU correction factor
  conf.ATUOffset=0.0;        // ATU correction offset 
  conf.sideTone=800;
  conf.cwDelayTime=60;
  conf.delayBeforeCWStartTime=50;
  conf.SI5351BX_ADDR=0x60;        // I2C address of Si5351   (variable from Version 1.097)
  conf.cwKeyType=0;         //0: straight, 1 : iambica, 2: iambicb
  conf.tuneStepIndex=6;     //default Value 6, start Offset is 0 because of check new user
  conf.commonOption0=0;   //0: Confirm : CW Frequency Shift,  1 : IF Shift Save
  conf.addrADS1115A=0x48; // dir ADS 1115 module analog converter
  conf.useHamBandCount=10;  //0 use full range frequency
  conf.tuneTXType=100;   //0 : use full range, 1 : just Change Dial speed, 2 : just ham band change, but can general band by tune, 3 : only ham band (just support 0, 2 (0.26 version))
                            //100 : use full range but not TX on general band, 101 : just change dial speed but.. 2 : jut... but.. 3 : only ham band  (just support 100, 102 (0.26 version))
  conf.isShiftDisplayCWFreq=1;  //Display Frequency 
  conf.hamBandRange[0][0]=1810;conf.hamBandRange[0][1]=2000;
  conf.hamBandRange[1][0]=3500;conf.hamBandRange[1][1]=3800;
  conf.hamBandRange[2][0]=5351;conf.hamBandRange[2][1]=5367;
  conf.hamBandRange[3][0]=7000;conf.hamBandRange[3][1]=7200;
  conf.hamBandRange[4][0]=10100;conf.hamBandRange[4][1]=10150;
  conf.hamBandRange[5][0]=14000;conf.hamBandRange[5][1]=14350;
  conf.hamBandRange[6][0]=18068;conf.hamBandRange[6][1]=18168;
  conf.hamBandRange[7][0]=21000;conf.hamBandRange[7][1]=21450;
  conf.hamBandRange[8][0]=24890;conf.hamBandRange[8][1]=24999;
  conf.hamBandRange[9][0]=28000;conf.hamBandRange[9][1]=29700;
  conf.freqbyband[0][0]=1810000; conf.freqbyband[0][1]=1810000;
  conf.freqbyband[1][0]=3500000; conf.freqbyband[1][1]=3500000;
  conf.freqbyband[2][0]=5351000; conf.freqbyband[2][1]=5351000;
  conf.freqbyband[3][0]=7000000; conf.freqbyband[3][1]=7000000;
  conf.freqbyband[4][0]=10100000; conf.freqbyband[4][1]=10100000;
  conf.freqbyband[5][0]=14000000; conf.freqbyband[5][1]=14000000;
  conf.freqbyband[6][0]=18068000; conf.freqbyband[6][1]=18068000;
  conf.freqbyband[7][0]=21000000; conf.freqbyband[7][1]=21000000;
  conf.freqbyband[8][0]=24890000; conf.freqbyband[8][1]=24890000;
  conf.freqbyband[9][0]=28000000; conf.freqbyband[9][1]=28000000;
  strcpy(conf.hamBandName[0],"160");
  strcpy(conf.hamBandName[1],"160");
  strcpy(conf.hamBandName[2],"80");
  strcpy(conf.hamBandName[3],"60");
  strcpy(conf.hamBandName[4],"40");
  strcpy(conf.hamBandName[5],"30");
  strcpy(conf.hamBandName[6],"20");
  strcpy(conf.hamBandName[7],"17");
  strcpy(conf.hamBandName[8],"12");
  strcpy(conf.hamBandName[9],"10");
  conf.connMode=0;     // 0: IP,  1: Serial2
  conf.serial2Mode=0;  // 0: Debug,  1: Manager
  conf.timezone=1;
  memset(conf.LIBRE1,0,sizeof(conf.LIBRE1));
  conf.ifShiftValue=0;   //
  conf.addrADS1115B=0x49; // dir ADS 1115 module analog converter
  memset(conf.LIBRE2,0,sizeof(conf.LIBRE2));
  conf.squelchval=45;
  conf.ATUIter=1;
  conf.posATUC1=0;
  conf.posATUC2=0;
  conf.sMeterLevels[0]=1;
  conf.sMeterLevels[1]=2;
  conf.sMeterLevels[2]=3;
  conf.sMeterLevels[3]=4;
  conf.sMeterLevels[4]=5;
  conf.sMeterLevels[5]=6;
  conf.sMeterLevels[6]=7;
  conf.sMeterLevels[7]=8;
  conf.sMeterLevels[8]=9;
  conf.sMeterLevels[9]=10;
  conf.sMeterLevels[10]=11;
  conf.sMeterLevels[11]=12;
  conf.sMeterLevels[12]=13;
  conf.sMeterLevels[13]=14;
  conf.sMeterLevels[14]=15;
  conf.sMeterLevels[15]=10000;
  memset(conf.LIBRE3,0,sizeof(conf.LIBRE3));
  conf.userCallsignLength=0;    //7 : display callsign at system startup, 6~0 : callsign length (range : 1~18)
  strcpy(conf.CallSign,"EA4GZI");
  conf.WsprMSGCount=0;
  conf.frequency=7150000L;     // frequency is the current frequency on the dial
  conf.frequencyA=7150000L;   // frequency is the current frequency VFOA
  conf.frequencyB=14200000L;  // frequency is the current frequency VFOB
  conf.ritRxFrequency=7150000;  
  conf.ritTxFrequency=7150000;  
  conf.scaledSMeter=0;
  conf.wifimode=2;     // default AP
  conf.canalAP=3;      // 1 byte, canal ESP en modo AP
  strcpy(conf.ssidSTA,"yourssid");      // 20 bytes, SSID en modo STA
  strcpy(conf.passSTA,"yourpass");      // 20 bytes, Password en modo STA
  strcpy(conf.ssidAP,"UBITX");          // 20 bytes, SSID en modo AP
  strcpy(conf.passAP,"12341234");       // 20 bytes, Password en modo AP
  conf.EEip[0]=192;conf.EEip[1]=168;conf.EEip[2]=1;conf.EEip[3]=149;
  conf.EEgw[0]=192;conf.EEgw[1]=168;conf.EEgw[2]=1;conf.EEgw[3]=1;
  conf.EEmask[0]=255;conf.EEmask[1]=255;conf.EEmask[2]=255;conf.EEmask[3]=0;
  conf.EEdns[0]=8;conf.EEdns[1]=8;conf.EEdns[2]=8;conf.EEdns[3]=8;
  conf.EEdns2[0]=8;conf.EEdns2[1]=8;conf.EEdns2[2]=4;conf.EEdns2[3]=4;
  for (byte i=0;i<6;i++) strcpy(conf.EEmac[i],"00");   // 18 bytes, MAC
  strcpy(conf.myippub,"");              // 16 bytes, dirección IP pública
  conf.staticIP=1;               // 1 byte, IP estática Sí/No
  conf.ftpenable=1;
  conf.debugenable=0;
  conf.tcpenable=1;
  conf.udpenable=1;
  conf.wsenable=0;
  conf.seripenable=0;
  conf.webenable=1;
  memset(conf.LIBRE4,0,sizeof(conf.LIBRE4));
  conf.firstIF=45005000L;
  conf.arTuneStep[0]=100000000;
  conf.arTuneStep[1]=10000000;
  conf.arTuneStep[2]=1000000;
  conf.arTuneStep[3]=100000;
  conf.arTuneStep[4]=10000;
  conf.arTuneStep[5]=1000;
  conf.arTuneStep[6]=100;
  conf.arTuneStep[7]=10;
  conf.arTuneStep[8]=1;
  conf.latitud=0.0;
  conf.longitud=0.0;
  conf.lang=0;                      // 0=español, 1=inglés, 2=francés, 3=alemán
  conf.rstper=0;   
  conf.usepassDev=0;                // 1 byte, 0 no usar password,  1 usar password
  memset(conf.probecode,0,sizeof(conf.probecode)); // código de sonda 
  strcpy(conf.userDev,"admin");         // 20 bytes, usuario device
  strcpy(conf.passDev,"admin");         // 20 bytes, password device
  conf.iftttenabled=0;
  strcpy(conf.iftttkey,"");             // 30 bytes, ifttt key
  conf.iottweetenable=0;
  strcpy(conf.iottweetuser,"");         // 10 bytes, IoTtweet account user ID
  strcpy(conf.iottweetkey,"");          // 15 bytes, IoTtweet account key
  conf.mqttenabled=0;
  strcpy(conf.mqttserver,"");           // MQTT broker
  strcpy(conf.mqttpath[0],"ubitx");
  strcpy(conf.mqttpath[1],"");
  strcpy(conf.mqttpath[2],"");
  strcpy(conf.mqttpath[3],"");
  strcpy(conf.mqttpath[4],"");
  strcpy(conf.mqttpath[5],"");
  strcpy(conf.hostmyip,"icanhazip.com");// 30 bytes, URL del servidor de IP pública
  conf.actualBand=3;
  conf.autoWiFi=0;
  conf.scanallf=0;                  // 0: scan only ham bands, 1:scan all freq.
  conf.TXall=0;                     // 0; TX only ham bands
  conf.autoMode=1;                  // switch mode auto
  memset(conf.calData,0,sizeof(conf.calData));  // calibration TFT touch
  conf.memMode=0;                   // 0: VFO mode, 1:mem Mode
  conf.lastmempos=0;
  conf.scandelay=3;
  conf.scanmode=0;          // 0: no stop, 1:resume after delay, 2:stop forever
  conf.Smeterenabled=0;
  conf.SWRenabled=0;
  conf.DS18B20enabled=0;
  conf.ATUZM2enabled=0;             
  conf.cwAdcSTFrom=0;             //CW ADC Range
  conf.cwAdcSTTo=0;
  conf.cwAdcDotFrom=0;
  conf.cwAdcDotTo=0;
  conf.cwAdcDashFrom=0;
  conf.cwAdcDashTo=0;
  conf.cwAdcBothFrom=0;
  conf.cwAdcBothTo=0;
  conf.TPA2016enabled=0;
  conf.TPA2016Compvalue=2;
  conf.TPA2016Compmaxgain=12;
  conf.TPA2016Gain=0;    // -28 a +30 db
  strcpy(conf.watermark,"000000000000000");  // código de verificación uBitx
  strcpy(conf.smeterTit[0],"0");
  strcpy(conf.smeterTit[1],"1");
  strcpy(conf.smeterTit[2],"2");
  strcpy(conf.smeterTit[3],"3");
  strcpy(conf.smeterTit[4],"4");
  strcpy(conf.smeterTit[5],"5");
  strcpy(conf.smeterTit[6],"6");
  strcpy(conf.smeterTit[7],"7");
  strcpy(conf.smeterTit[8],"8");
  strcpy(conf.smeterTit[9],"9");
  strcpy(conf.smeterTit[10],"+10");
  strcpy(conf.smeterTit[11],"+20");
  strcpy(conf.smeterTit[12],"+30");
  strcpy(conf.smeterTit[13],"+40");
  strcpy(conf.smeterTit[14],"+50");
  strcpy(conf.smeterTit[15],"+60");
  conf.ATUdelay=3;                 // en segundos
  memset(conf.nprobe,0,sizeof(conf.nprobe));   // estos dos valores van aparejados
  conf.ftpPort=FTPPort;
  conf.debugPort=DEBUGPort;
  conf.tcpPort=TCPPort;
  conf.webPort=WEBPort;  
  conf.udpPortSmeter=UDPPortS;
  conf.wsPort=WSPort;
  conf.udpPortFreq=UDPPortF;
  memset(conf.LIBRE5,0,sizeof(conf.LIBRE5));                 // Reservados usos futuros
}
