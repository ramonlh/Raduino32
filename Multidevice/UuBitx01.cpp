// ---------------------------------------------------------------------------

#include <stdlib.h>
#include <fmx.h>
#pragma hdrstop

#include "UuBitx01.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UuBitx02"
#pragma resource "*.fmx"
#pragma resource ("*.iPhone55in.fmx", _PLAT_IOS)
#pragma resource ("*.Windows.fmx", _PLAT_MSWINDOWS)
#pragma resource ("*.XLgXhdpiTb.fmx", _PLAT_ANDROID)
#pragma resource ("*.LgXhdpiPh.fmx", _PLAT_ANDROID)

#define MAX_BANDS 10
#define maxTemp 8       // número máximo de sondas ds18B20
#define VFO_A 16
#define VFO_B 20

// Commands TCP conection
#define tcptxOn 1
#define tcptxOff 2
#define tcpsplitOn 3
#define tcpisUSB 4
#define tcpcwMode 5
#define tcpritOn 8
#define tcpvfoActive 19
#define tcpbanddn 40
#define tcpbandup 41
#define tcpfreqdn 42
#define tcpfrequp 43
#define tcpCallSign 44
#define tcpfrequency 45
#define tcpfrequencyA 46
#define tcpfrequencyB 47
#define tcptemp1  48
#define tcptemp2  49
#define tcptemp3  50
#define tcptunestep 51
#define tcpwifi 52        // set WiFi on
#define tcpreset 53       // reset remoto
#define tcpframe 54       // framemode
#define tcpminsmeter 55   // valor mínimo smeter
#define tcpmaxsmeter 56   // valor máximo smeter
#define tcpscanst 64
#define tcpkeylock 65
#define tcpattlevel 66
#define tcpifShiftVal 67
#define tcpvtotvalue 68
#define tcpitotvalue 69

#define tcpALL 127

// ****************** PORTS **************************
#define FTPPort     21
#define TCPPort   8084
#define UDPsmeter 8085
#define WSPort    8086
#define UDPfreq   8087
#define WEBPort   8088

String version = "0.197";

typedef uint8_t IPAddress[8];

typedef struct { // datos configuración
	uint8_t LIBRE0;
	int32_t calibration;
	unsigned long usbCarrier;
	unsigned long cwmCarrier;
	uint8_t splitOn;
	// working split, uses VFO B as the transmit frequency                  byte isUSB = 0;   //upper sideband was selected, this is reset to the default for the
	uint8_t isUSB;
	// upper sideband was selected, this is reset to the default for the
	int cwMode;
	// compatible original source, and extend mode //if cwMode == 0, mode check : isUSB, cwMode > 0, mode Check : cwMode
	// iscwMode = 0 : ssbmode, 1 :cwl, 2 : cwu, 3 : cwn (none tx)
	unsigned int cwSpeed; // this is actuall the dot period in milliseconds
	unsigned long cwTimeout;
	// milliseconds to go before the cw transmit line is released and the radio goes back to rx mode
	uint8_t ritOn;
	uint8_t cwModeA; // 0: no CW, 1: CW mode
	uint8_t cwModeB; // 0: no CW, 1: CW mode
	uint8_t attLevel;
	// ATT : RF Gain Control (Receive) <-- IF1 Shift, 0 : Off, ShiftValue is attLevel * 100; attLevel 150 = 15K
	uint8_t sdrModeOn; // SDR MODE ON / OFF
	int TempAlarm;
	int TempTxOff;
	uint8_t framemode;
	// 0: analog meter, 1: frames igital meter, 2:spectrum,  3:Frequencies
	uint8_t frame1mode; // 0:ATT, 1: data (frame0mode=0)
	uint8_t frame2mode; // 0:IFS, 2: data (frame0mode=0)
	uint8_t frame3mode;
	// 0:analog meter (frame0mode=0), 1: bar meter (framemode=1)
	uint8_t vfoActive;
	uint8_t isUSBA; // 0:LSB, 1:USB
	uint8_t isUSBB; // 0:LSB, 1:USB
	float ATUFactor; // ATU correction factor
	float ATUOffset; // ATU correction offset
	unsigned long sideTone;
	uint8_t cwDelayTime;
	uint8_t delayBeforeCWStartTime;
	uint8_t SI5351BX_ADDR;
	// I2C address of Si5351   (variable from Version 1.097)
	uint8_t cwKeyType; // 0: straight, 1 : iambica, 2: iambicb
	uint8_t tuneStepIndex;
	// default Value 6, start Offset is 0 because of check new user
	uint8_t commonOption0;
	// 0: Confirm : CW Frequency Shift,  1 : IF Shift Save
	uint8_t addrADS1115A; // dir ADS 1115 module analog converter
	uint8_t useHamBandCount; // 0 use full range frequency
	uint8_t tuneTXType;
	// 0 : use full range, 1 : just Change Dial speed, 2 : just ham band change, but can general band by tune, 3 : only ham band (just support 0, 2 (0.26 version))
	// 100 : use full range but not TX on general band, 101 : just change dial speed but.. 2 : jut... but.. 3 : only ham band  (just support 100, 102 (0.26 version))
	uint8_t isShiftDisplayCWFreq; // Display Frequency
	unsigned int hamBandRange[MAX_BANDS][2];
	// =  //Khz because reduce use memory
	long freqbyband[MAX_BANDS][2];
	char hamBandName[MAX_BANDS][4];
	uint8_t connMode; // 0: IP,  1: Serial2
	uint8_t serial2Mode; // 0: Debug,  1: Manager
	uint8_t timezone;
	uint8_t LIBRE1[17];
	int ifShiftValue; //
	uint8_t addrADS1115B; // dir ADS 1115 module analog converter
	uint8_t LIBRE2[6];
	int squelchval;
	int ATUIter;
	uint8_t posATUC1;
	uint8_t posATUC2;
	int sMeterLevels[16];
	uint8_t LIBRE3[13]; // NO USADO, LIBRE
	uint8_t userCallsignLength;
	// 7 : display callsign at system startup, 6~0 : callsign length (range : 1~18)
	char CallSign[20];
	uint8_t WsprMSGCount;
	unsigned long frequency; // frequency is the current frequency on the dial
	unsigned long frequencyA; // frequency is the current frequency VFOA
	unsigned long frequencyB; // frequency is the current frequency VFOB
	unsigned long ritRxFrequency;
	unsigned long ritTxFrequency;
	uint8_t scaledSMeter;
	uint8_t wifimode; // default AP
	uint8_t canalAP; // 1 byte, canal ESP en modo AP
	char ssidSTA[20]; // 20 bytes, SSID en modo STA
	char passSTA[20]; // 20 bytes, Password en modo STA
	char ssidAP[20]; // 20 bytes, SSID en modo AP
	char passAP[20]; // 20 bytes, Password en modo AP
	IPAddress EEip; // 4 bytes, dirección IP
	IPAddress EEgw; // 4 bytes, puerta de enlace
	IPAddress EEmask; // 4 bytes, máscara de subred
	IPAddress EEdns; // 4 bytes, servidor DNS primario
	IPAddress EEdns2; // 4 bytes, servidor DNS secundario
	char EEmac[6][3]; // 18 bytes, MAC
	char myippub[16]; // 16 bytes, dirección IP pública
	uint8_t staticIP; // 1 byte, IP estática Sí/No
	uint8_t ftpenable;
	uint8_t LIBRE4[2]; //
	unsigned long firstIF;
	unsigned long arTuneStep[9];
	float latitud;
	float longitud;
	uint8_t lang; // 0=español, 1=inglés, 2=francés, 3=alemán
	uint8_t rstper;
	uint8_t usepassDev; // 1 byte, 0 no usar password,  1 usar password
	uint8_t probecode[maxTemp][8]; // código de sonda
	char userDev[20]; // 20 bytes, usuario device
	char passDev[20]; // 20 bytes, password device
	uint8_t iftttenabled;
	char iftttkey[30]; // 30 bytes, ifttt key
	uint8_t iottweetenable;
	char iottweetuser[10]; // 10 bytes, IoTtweet account user ID
	char iottweetkey[15]; // 15 bytes, IoTtweet account key
	uint8_t mqttenabled;
	char mqttserver[40]; // MQTT broker
	char mqttpath[6][10]; // MQTT path
	uint8_t dweetenabled; // 1 byte, dweet.io desactivado
	uint8_t myjsonenabled;
	char idmyjson[10]; // 10 bytes, ID myjson
	uint8_t idmyjsonST;
	// 1 byte, indica si se ha obtenido y almacenado ya la ID de myjson
	char hostmyip[30]; // 30 bytes, URL del servidor de IP pública
	uint8_t actualBand;
	uint8_t autoWiFi;
	uint8_t scanallf; // 0: scan only ham bands, 1:scan all freq.
	uint8_t TXall; // 0; TX only ham bands
	uint8_t autoMode; // switch mode auto
	uint16_t calData[5]; // calibration TFT touch
	uint8_t memMode; // 0: VFO mode, 1:mem Mode
	int lastmempos;
	int scandelay;
	uint8_t scanmode; // 0: no stop, 1:resume after delay, 2:stop forever
	uint8_t Smeterenabled;
	uint8_t SWRenabled;
	uint8_t DS18B20enabled;
	uint8_t ATUZM2enabled;
	int cwAdcSTFrom; // CW ADC Range
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
	uint8_t TPA2016Gain; // -28 a +30 db
	char watermark[16]; // código de verificación uBitx
	char smeterTit[16][4];
	uint8_t ATUdelay; // en segundos
	uint8_t nprobe[maxTemp]; // estos dos valores van aparejados
	int ftpPort;
	int debugPort;
	int tcpPort;
	int webPort;
	int udpPort;
	int wsPort;
	int serialPort;
	uint8_t LIBRE5[363]; // Reservados usos futuros
} conftype;
// conftype conf;
// uint8_t *buffconf = (uint8_t *) &conf; // acceder a conf como bytes

union {
	conftype c;
	uint8_t d[sizeof(conftype)];
} conf;

void initConf() {
	conf.c.LIBRE0 = 0;
	conf.c.calibration = 180000;
	conf.c.usbCarrier = 11056000;
	conf.c.cwmCarrier = 11056000;
	conf.c.splitOn = 0;
	// working split, uses VFO B as the transmit frequency                  byte isUSB = 0;   //upper sideband was selected, this is reset to the default for the
	conf.c.isUSB = 0;
	// upper sideband was selected, this is reset to the default for the
	conf.c.cwMode = 0;
	// compatible original source, and extend mode //if cwMode == 0, mode check : isUSB, cwMode > 0, mode Check : cwMode
	// iscwMode = 0 : ssbmode, 1 :cwl, 2 : cwu, 3 : cwn (none tx)
	conf.c.cwSpeed = 100; // this is actuall the dot period in milliseconds
	conf.c.cwTimeout = 0;
	// milliseconds to go before the cw transmit line is released and the radio goes back to rx mode
	conf.c.ritOn = 0;
	conf.c.cwModeA = 0; // 0: no CW, 1: CW mode
	conf.c.cwModeB = 0; // 0: no CW, 1: CW mode
	conf.c.attLevel = 0;
	// ATT : RF Gain Control (Receive) <-- IF1 Shift, 0 : Off, ShiftValue is attLevel * 100; attLevel 150 = 15K
	conf.c.sdrModeOn = 0; // SDR MODE ON / OFF
	conf.c.TempAlarm = 45;
	conf.c.TempTxOff = 50;
	conf.c.framemode = 0;
	// 0: analog meter, 1: frames igital meter, 2:spectrum,  3:Frequencies
	conf.c.frame1mode = 0; // 0:ATT, 1: data (frame0mode=0)
	conf.c.frame2mode = 0; // 0:IFS, 2: data (frame0mode=0)
	conf.c.frame3mode = 0;
	// 0:analog meter (frame0mode=0), 1: bar meter (framemode=1)
	conf.c.vfoActive = VFO_A;
	conf.c.isUSBA = 0; // 0:LSB, 1:USB
	conf.c.isUSBB = 1; // 0:LSB, 1:USB
	conf.c.ATUFactor = 0.0; // ATU correction factor
	conf.c.ATUOffset = 0.0; // ATU correction offset
	conf.c.sideTone = 800;
	conf.c.cwDelayTime = 60;
	conf.c.delayBeforeCWStartTime = 50;
	conf.c.SI5351BX_ADDR = 0x60;
	// I2C address of Si5351   (variable from Version 1.097)
	conf.c.cwKeyType = 0; // 0: straight, 1 : iambica, 2: iambicb
	conf.c.tuneStepIndex = 6;
	// default Value 6, start Offset is 0 because of check new user
	conf.c.commonOption0 = 0;
	// 0: Confirm : CW Frequency Shift,  1 : IF Shift Save
	conf.c.addrADS1115A = 0x48; // dir ADS 1115 module analog converter
	conf.c.useHamBandCount = 10; // 0 use full range frequency
	conf.c.tuneTXType = 100;
	// 0 : use full range, 1 : just Change Dial speed, 2 : just ham band change, but can general band by tune, 3 : only ham band (just support 0, 2 (0.26 version))
	// 100 : use full range but not TX on general band, 101 : just change dial speed but.. 2 : jut... but.. 3 : only ham band  (just support 100, 102 (0.26 version))
	conf.c.isShiftDisplayCWFreq = 1; // Display Frequency
	conf.c.hamBandRange[0][0] = 1810;
	conf.c.hamBandRange[0][1] = 2000;
	conf.c.hamBandRange[1][0] = 3500;
	conf.c.hamBandRange[1][1] = 3800;
	conf.c.hamBandRange[2][0] = 5351;
	conf.c.hamBandRange[2][1] = 5367;
	conf.c.hamBandRange[3][0] = 7000;
	conf.c.hamBandRange[3][1] = 7300;
	conf.c.hamBandRange[4][0] = 10100;
	conf.c.hamBandRange[4][1] = 10150;
	conf.c.hamBandRange[5][0] = 14000;
	conf.c.hamBandRange[5][1] = 14350;
	conf.c.hamBandRange[6][0] = 18068;
	conf.c.hamBandRange[6][1] = 18168;
	conf.c.hamBandRange[7][0] = 21000;
	conf.c.hamBandRange[7][1] = 21450;
	conf.c.hamBandRange[8][0] = 24890;
	conf.c.hamBandRange[8][1] = 24999;
	conf.c.hamBandRange[9][0] = 28000;
	conf.c.hamBandRange[9][1] = 29700;
	conf.c.freqbyband[0][0] = 1810000;
	conf.c.freqbyband[0][1] = 1810000;
	conf.c.freqbyband[0][0] = 3500000;
	conf.c.freqbyband[0][1] = 3500000;
	conf.c.freqbyband[0][0] = 5351000;
	conf.c.freqbyband[0][1] = 5351000;
	conf.c.freqbyband[0][0] = 7000000;
	conf.c.freqbyband[0][1] = 7000000;
	conf.c.freqbyband[0][0] = 10100000;
	conf.c.freqbyband[0][1] = 10100000;
	conf.c.freqbyband[0][0] = 14000000;
	conf.c.freqbyband[0][1] = 14000000;
	conf.c.freqbyband[0][0] = 18068000;
	conf.c.freqbyband[0][1] = 18068000;
	conf.c.freqbyband[0][0] = 21000000;
	conf.c.freqbyband[0][1] = 21000000;
	conf.c.freqbyband[0][0] = 24890000;
	conf.c.freqbyband[0][1] = 24890000;
	conf.c.freqbyband[0][0] = 28000000;
	conf.c.freqbyband[0][1] = 28000000;
	strcpy(conf.c.hamBandName[0], "160");
	strcpy(conf.c.hamBandName[1], "160");
	strcpy(conf.c.hamBandName[2], "80");
	strcpy(conf.c.hamBandName[3], "60");
	strcpy(conf.c.hamBandName[4], "40");
	strcpy(conf.c.hamBandName[5], "30");
	strcpy(conf.c.hamBandName[6], "20");
	strcpy(conf.c.hamBandName[7], "17");
	strcpy(conf.c.hamBandName[8], "12");
	strcpy(conf.c.hamBandName[9], "10");
	conf.c.connMode = 0; // 0: IP,  1: Serial2
	conf.c.serial2Mode = 0; // 0: Debug,  1: Manager
	conf.c.timezone = 1;
	memset(conf.c.LIBRE1, 0, sizeof(conf.c.LIBRE1));
	conf.c.ifShiftValue = 0; //
	conf.c.addrADS1115B = 0x49; // dir ADS 1115 module analog converter
	memset(conf.c.LIBRE2, 0, sizeof(conf.c.LIBRE2));
	conf.c.squelchval = 45;
	conf.c.ATUIter = 1;
	conf.c.posATUC1 = 0;
	conf.c.posATUC2 = 0;
	conf.c.sMeterLevels[0] = 16000;
	conf.c.sMeterLevels[1] = 16500;
	conf.c.sMeterLevels[2] = 17000;
	conf.c.sMeterLevels[3] = 17500;
	conf.c.sMeterLevels[4] = 18000;
	conf.c.sMeterLevels[5] = 18500;
	conf.c.sMeterLevels[6] = 19000;
	conf.c.sMeterLevels[7] = 19500;
	conf.c.sMeterLevels[8] = 20000;
	conf.c.sMeterLevels[9] = 20500;
	conf.c.sMeterLevels[10] = 21000;
	conf.c.sMeterLevels[11] = 21500;
	conf.c.sMeterLevels[12] = 22000;
	conf.c.sMeterLevels[13] = 22500;
	conf.c.sMeterLevels[14] = 23000;
	conf.c.sMeterLevels[15] = 23500;
	memset(conf.c.LIBRE3, 0, sizeof(conf.c.LIBRE3));
	conf.c.userCallsignLength = 0;
	// 7 : display callsign at system startup, 6~0 : callsign length (range : 1~18)
	strcpy(conf.c.CallSign, "EA4GZI");
	conf.c.WsprMSGCount = 0;
	conf.c.frequency = 7150000L;
	// frequency is the current frequency on the dial
	conf.c.frequencyA = 7150000L; // frequency is the current frequency VFOA
	conf.c.frequencyB = 14200000L; // frequency is the current frequency VFOB
	conf.c.ritRxFrequency = 7150000;
	conf.c.ritTxFrequency = 7150000;
	conf.c.scaledSMeter = 0;
	conf.c.wifimode = 2; // default AP
	conf.c.canalAP = 3; // 1 byte, canal ESP en modo AP
	strcpy(conf.c.ssidSTA, "yourssid"); // 20 bytes, SSID en modo STA
	strcpy(conf.c.passSTA, "yourpass"); // 20 bytes, Password en modo STA
	strcpy(conf.c.ssidAP, "UBITX"); // 20 bytes, SSID en modo AP
	strcpy(conf.c.passAP, "12341234"); // 20 bytes, Password en modo AP
	conf.c.EEip[0] = 192;
	conf.c.EEip[1] = 168;
	conf.c.EEip[2] = 1;
	conf.c.EEip[3] = 149;
	conf.c.EEgw[0] = 192;
	conf.c.EEgw[1] = 168;
	conf.c.EEgw[2] = 1;
	conf.c.EEgw[3] = 1;
	conf.c.EEmask[0] = 255;
	conf.c.EEmask[1] = 255;
	conf.c.EEmask[2] = 255;
	conf.c.EEmask[3] = 0;
	conf.c.EEdns[0] = 8;
	conf.c.EEdns[1] = 8;
	conf.c.EEdns[2] = 8;
	conf.c.EEdns[3] = 8;
	conf.c.EEdns2[0] = 8;
	conf.c.EEdns2[1] = 8;
	conf.c.EEdns2[2] = 4;
	conf.c.EEdns2[3] = 4;
	for (int i = 0; i < 6; i++)
		strcpy(conf.c.EEmac[i], "00"); // 18 bytes, MAC
	strcpy(conf.c.myippub, ""); // 16 bytes, dirección IP pública
	conf.c.staticIP = 1; // 1 byte, IP estática Sí/No
	conf.c.ftpenable = 1;
	memset(conf.c.LIBRE4, 0, sizeof(conf.c.LIBRE4));
	conf.c.firstIF = 45005000L;
	conf.c.arTuneStep[0] = 100000000;
	conf.c.arTuneStep[1] = 10000000;
	conf.c.arTuneStep[2] = 1000000;
	conf.c.arTuneStep[3] = 100000;
	conf.c.arTuneStep[4] = 10000;
	conf.c.arTuneStep[5] = 1000;
	conf.c.arTuneStep[6] = 100;
	conf.c.arTuneStep[7] = 10;
	conf.c.arTuneStep[8] = 1;
	conf.c.latitud = 0.0;
	conf.c.longitud = 0.0;
	conf.c.lang = 0; // 0=español, 1=inglés, 2=francés, 3=alemán
	conf.c.rstper = 0;
	conf.c.usepassDev = 0; // 1 byte, 0 no usar password,  1 usar password
	memset(conf.c.probecode, 0, sizeof(conf.c.probecode)); ; // código de sonda
	strcpy(conf.c.userDev, "admin"); // 20 bytes, usuario device
	strcpy(conf.c.passDev, "admin"); // 20 bytes, password device
	conf.c.iftttenabled = 0;
	strcpy(conf.c.iftttkey, ""); // 30 bytes, ifttt key
	conf.c.iottweetenable = 0;
	strcpy(conf.c.iottweetuser, ""); // 10 bytes, IoTtweet account user ID
	strcpy(conf.c.iottweetkey, ""); // 15 bytes, IoTtweet account key
	conf.c.mqttenabled = 0;
	strcpy(conf.c.mqttserver, ""); // MQTT broker
	strcpy(conf.c.mqttpath[0], "ubitx");
	strcpy(conf.c.mqttpath[1], "");
	strcpy(conf.c.mqttpath[2], "");
	strcpy(conf.c.mqttpath[3], "");
	strcpy(conf.c.mqttpath[4], "");
	strcpy(conf.c.mqttpath[5], "");
	conf.c.dweetenabled = 0; // 1 byte, dweet.io desactivado
	conf.c.myjsonenabled = 0;
	strcpy(conf.c.idmyjson, ""); // 10 bytes, ID myjson
	conf.c.idmyjsonST = 0;
	// 1 byte, indica si se ha obtenido y almacenado ya la ID de myjson
	strcpy(conf.c.hostmyip, "icanhazip.com");
	// 30 bytes, URL del servidor de IP pública
	conf.c.actualBand = 3;
	conf.c.autoWiFi = 0;
	conf.c.scanallf = 0; // 0: scan only ham bands, 1:scan all freq.
	conf.c.TXall = 0; // 0; TX only ham bands
	conf.c.autoMode = 1; // switch mode auto
	memset(conf.c.calData, 0, sizeof(conf.c.calData)); // calibration TFT touch
	conf.c.memMode = 0; // 0: VFO mode, 1:mem Mode
	conf.c.lastmempos = 0;
	conf.c.scandelay = 3;
	conf.c.scanmode = 0; // 0: no stop, 1:resume after delay, 2:stop forever
	conf.c.Smeterenabled = 0;
	conf.c.SWRenabled = 0;
	conf.c.DS18B20enabled = 0;
	conf.c.ATUZM2enabled = 0;
	conf.c.cwAdcSTFrom = 0; // CW ADC Range
	conf.c.cwAdcSTTo = 0;
	conf.c.cwAdcDotFrom = 0;
	conf.c.cwAdcDotTo = 0;
	conf.c.cwAdcDashFrom = 0;
	conf.c.cwAdcDashTo = 0;
	conf.c.cwAdcBothFrom = 0;
	conf.c.cwAdcBothTo = 0;
	conf.c.TPA2016enabled = 0;
	conf.c.TPA2016Compvalue = 2;
	conf.c.TPA2016Compmaxgain = 12;
	conf.c.TPA2016Gain = 0; // -28 a +30 db
	strcpy(conf.c.watermark, "000000000000000"); // código de verificación uBitx
	strcpy(conf.c.smeterTit[0], "0");
	strcpy(conf.c.smeterTit[1], "1");
	strcpy(conf.c.smeterTit[2], "2");
	strcpy(conf.c.smeterTit[3], "3");
	strcpy(conf.c.smeterTit[4], "4");
	strcpy(conf.c.smeterTit[5], "5");
	strcpy(conf.c.smeterTit[6], "6");
	strcpy(conf.c.smeterTit[7], "7");
	strcpy(conf.c.smeterTit[8], "8");
	strcpy(conf.c.smeterTit[9], "9");
	strcpy(conf.c.smeterTit[10], "+10");
	strcpy(conf.c.smeterTit[11], "+20");
	strcpy(conf.c.smeterTit[12], "+30");
	strcpy(conf.c.smeterTit[13], "+40");
	strcpy(conf.c.smeterTit[14], "+50");
	strcpy(conf.c.smeterTit[15], "+60");
	conf.c.ATUdelay = 3; // en segundos
	memset(conf.c.nprobe, 0, sizeof(conf.c.nprobe));
	// estos dos valores van aparejados
	conf.c.ftpPort = FTPPort;
	conf.c.tcpPort = TCPPort;
	conf.c.webPort = WEBPort;
	conf.c.udpPort = UDPsmeter;
	conf.c.wsPort = WSPort;
	memset(conf.c.LIBRE5, 0, sizeof(conf.c.LIBRE5)); // Reservados usos futuros
}

uint8_t inTX = 0;
uint8_t scanF = 0; // 0: no scan   1:scan-,  2:scan+
uint8_t keylock = 0; // bloqueo teclado y botones
int MbR[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // 0-7 Temperaturas locales
int wheelactval = 0;
int wheelantval = 0;
const char serial2modetext[2][8] = {"Debug", "Manager"};
int minsmeter = 0;
int maxsmeter = 0;
String vtotvalueS;
String itotvalueS;

TF1 *F1;

// ---------------------------------------------------------------------------
__fastcall TF1::TF1(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
uint8_t rev(uint8_t b) {
	return b == 0 ? 1 : 0;
}

void sendData(uint8_t c) {
	char buff[20];
	String buffS;
	char data[60];
	bool sendok = false;
	if (!F1->IdTCPClient1) {
		F1->Memo1->Lines->Add("No Client");
		return;
	}
	else if (!F1->IdTCPClient1->Connected()) {
		F1->Memo1->Lines->Add("Not connected");
		return;
	}
	if (c == tcpsplitOn) {
		strcpy(data, conf.c.splitOn == 0 ? "1" : "0");
		sendok = true;
	}
	else if (c == tcpisUSB) {
		strcpy(data, conf.c.isUSB == 0 ? "1" : "0");
		sendok = true;
	}
	else if (c == tcpcwMode) {
		strcpy(data, conf.c.cwMode == 0 ? "1" : "0");
		sendok = true;
	}
	else if (c == tcpritOn) {
		strcpy(data, conf.c.ritOn == 0 ? "1" : "0");
		sendok = true;
	}
	else if (c == tcpvfoActive) {
		strcpy(data, conf.c.vfoActive == VFO_A ? "20" : "16");
		sendok = true;
	}
	else if (c == tcpbanddn) {
		strcpy(data, "-1");
		sendok = true;
	}
	else if (c == tcpbandup) {
		strcpy(data, "1");
		sendok = true;
	}
	else if (c == tcpfreqdn) {
		strcpy(data, "-1");
		sendok = true;
	}
	else if (c == tcpfrequp) {
		strcpy(data, "1");
		sendok = true;
	}
	else if (c == tcpfrequency) {
		if (conf.c.frequency > 0) {
			snprintf(data, sizeof(data), "%d", conf.c.frequency);
			sendok = true;
		}
	}
	else if (c == tcpframe) {
		strcpy(data, "0");
		sendok = true;
	}
	else if (c == tcpscanst) {
		strcpy(data, scanF == 0 ? "0" : scanF == 1 ? "1" : "2");
		sendok = true;
	}
	else if (c == tcpkeylock) {
		strcpy(data, keylock == 0 ? "1" : "0");
		sendok = true;
	}
	else if (c == tcpattlevel) {
		snprintf(data, sizeof(data), "%d", conf.c.attLevel);
		sendok = true;
	}
	else if (c == tcpifShiftVal) {
		snprintf(data, sizeof(data), "%d", conf.c.ifShiftValue);
		sendok = true;
	}
	else if (c == tcpreset) {
		strcpy(data, "-1");
		sendok = true;
	}
	else if (c == tcpALL) {
		strcpy(data, "all");
		sendok = true;
	}
	if (sendok) {
		try {

			F1->IdTCPClient1->IOHandler->Write(c);
			F1->IdTCPClient1->IOHandler->WriteLn(data);
		}
		catch (const Exception &) {
			F1->Memo3->Lines->Add("Error sendData");
		}
	}
}

void refreshConf() {
	F1->ComboBox1->ItemIndex = conf.c.lang;
	F1->Edit5->Text = conf.c.CallSign;
	F1->Edit6->Text = conf.c.latitud;
	F1->Edit7->Text = conf.c.longitud;
	F1->ComboBox2->ItemIndex = conf.c.TXall;
	F1->ComboBox3->ItemIndex = conf.c.scanallf;
	F1->ComboBox4->ItemIndex = conf.c.autoMode;
	F1->ComboBox5->ItemIndex = conf.c.scanmode;
	F1->SpinBox1->Value = conf.c.scandelay;
	F1->ComboBox6->ItemIndex = conf.c.cwKeyType;
	F1->SpinBox2->Value = (int)(1200 / conf.c.cwSpeed);
	F1->SpinBox3->Value = conf.c.sideTone;
	F1->SpinBox4->Value = conf.c.cwDelayTime;
	F1->SpinBox5->Value = conf.c.delayBeforeCWStartTime;
	F1->ComboBox7->ItemIndex = conf.c.autoWiFi;
	F1->Edit8->Text = conf.c.ssidSTA;
	F1->Edit9->Text = conf.c.passSTA;
	F1->ComboBox8->ItemIndex = conf.c.wifimode;
	F1->ComboBox9->ItemIndex = conf.c.staticIP;
	F1->SpinBox6->Value = conf.c.calibration;
	F1->SpinBox7->Value = conf.c.usbCarrier;
	F1->SpinBox8->Value = conf.c.SI5351BX_ADDR;
	F1->SpinBox9->Value = conf.c.cwAdcDotFrom;
	F1->SpinBox10->Value = conf.c.cwAdcDotTo;
	F1->SpinBox11->Value = conf.c.cwAdcBothFrom;
	F1->SpinBox12->Value = conf.c.cwAdcBothTo;
	F1->SpinBox13->Value = conf.c.cwAdcDashFrom;
	F1->SpinBox14->Value = conf.c.cwAdcDashTo;
	F1->SpinBox15->Value = conf.c.cwAdcSTFrom;
	F1->SpinBox16->Value = conf.c.cwAdcSTTo;
	F1->ComboBox10->ItemIndex = conf.c.ATUZM2enabled;
	F1->ComboBox11->ItemIndex = conf.c.TPA2016enabled;
	F1->ComboBox12->ItemIndex = conf.c.TPA2016Compvalue;
	F1->SpinBox16->Value = conf.c.TPA2016Compmaxgain;
	F1->SpinBox17->Value = conf.c.TPA2016Gain;
	F1->ComboBox14->ItemIndex = conf.c.serial2Mode;
}

void refreshData(uint8_t b) {
	if (b == tcpfrequency) {
		F1->NumberBox1->Value = conf.c.frequency;
	}
	else if (b == tcpsplitOn) {
		F1->Frame22->Rectangle1->Fill->Color = conf.c.splitOn == 1 ? claMaroon :
			claLightgray;
	}
	else if (b == tcpisUSB) {
		F1->Frame27->Rectangle1->Fill->Color = conf.c.isUSB == 1 ? claYellow :
			claLightgray;
		F1->Frame27->Text1->Text = conf.c.isUSB == 1 ? "USB" : "LSB";
	}
	else if (b == tcpcwMode) {
		F1->Frame28->Rectangle1->Fill->Color = conf.c.cwMode > 0 ? claYellow :
			claLightgray;
	}
	else if (b == tcpvfoActive) {
		F1->Button11->Text = conf.c.vfoActive == VFO_A ? "B" : "A";
		F1->Button12->Text = conf.c.vfoActive == VFO_A ? "A" : "B";
	}
	else if (b == tcpritOn) {
		F1->Frame21->Rectangle1->Fill->Color = conf.c.ritOn == 1 ? claAqua :
			claLightgray;
	}
	else if (b == tcpscanst) {
		F1->Frame23->Rectangle1->Fill->Color = scanF == 2 ? claAqua :
			claLightgray;
		F1->Frame24->Rectangle1->Fill->Color = scanF == 1 ? claAqua :
			claLightgray;
	}
	else if (b == tcpkeylock) {
		F1->Frame214->Rectangle1->Fill->Color = keylock == 1 ? claRed :
			claLightgray;
	}

	else if (b == tcpfrequencyA) {
		F1->NumberBox1->Value = conf.c.frequencyA;
	}
	else if (b == tcpfrequencyB) {
		F1->NumberBox2->Value = conf.c.frequencyB;
	}

	else if (b == tcptemp1) {
		F1->Frame221->Text1->Text = MbR[0];
	}
	else if (b == tcptemp2) {
		F1->Frame222->Text1->Text = MbR[1];
	}
	else if (b == tcptemp3) {
		F1->Frame223->Text1->Text = MbR[2];
	}
	else if (b == tcpattlevel) {
		F1->NumberBox6->Value = conf.c.attLevel;
		F1->ScrollBar1->Value = conf.c.attLevel;
	}
	else if (b == tcpifShiftVal) {
		F1->NumberBox7->Value = conf.c.ifShiftValue;
		F1->ScrollBar2->Value = conf.c.ifShiftValue;
	}
	else if (b == tcpvtotvalue) {
		F1->Label61->Text = vtotvalueS;
	}
	else if (b == tcpitotvalue) {
		F1->Label62->Text = itotvalueS;
	}
}

void handleRecData(uint8_t b, String data) {
	char buff[10];
	if (b == tcpfrequency) {
		conf.c.frequency = StrToInt(data);
	} // frequency
	else if (b == tcpsplitOn) {
		conf.c.splitOn = StrToInt(data);
	}
	else if (b == tcpisUSB) {
		conf.c.isUSB = StrToInt(data);
	}
	else if (b == tcpritOn) {
		conf.c.ritOn = StrToInt(data);
	}
	else if (b == tcpcwMode) {
		conf.c.cwMode = StrToInt(data);
	}
	else if (b == tcpvfoActive) {
		conf.c.vfoActive = StrToInt(data);
	}
	else if (b == tcpbanddn) {
		conf.c.vfoActive = StrToInt(data);
	}
	else if (b == tcpbandup) {
		conf.c.vfoActive = StrToInt(data);
	}
	else if (b == tcpCallSign) {
		F1->Label58->Text = data;
	}
	else if (b == tcpfrequencyA) {
		conf.c.frequencyA = StrToInt(data);
	} // frequencyA
	else if (b == tcpfrequencyB) {
		conf.c.frequencyB = StrToInt(data);
	} // frequencyB
	else if (b == tcptemp1) {
		MbR[0] = StrToInt(data) / 100;
	} // temp1
	else if (b == tcptemp2) {
		MbR[1] = StrToInt(data) / 100;
	} // temp2
	else if (b == tcptemp3) {
		MbR[2] = StrToInt(data) / 100;
	} // temp3
	else if (b == tcptunestep) {
		conf.c.tuneStepIndex = StrToInt(data);
	} // tuneStep
	else if (b == tcpminsmeter) {
		minsmeter = StrToInt(data);
	} // min smeter
	else if (b == tcpmaxsmeter) {
		maxsmeter = StrToInt(data);
	} // max smeter
	else if (b == tcpscanst) {
		scanF = StrToInt(data);
	} // scan status
	else if (b == tcpkeylock) {
		keylock = StrToInt(data);
	} // keylock
	else if (b == tcpattlevel) {
		conf.c.attLevel = StrToInt(data);
	} // attlevel
	else if (b == tcpifShiftVal) {
		conf.c.ifShiftValue = StrToInt(data);
	} // ifshift
	else if (b == tcpvtotvalue) {
		vtotvalueS = data;
	} // vtotvalue
	else if (b == tcpitotvalue) {
		itotvalueS = data;
	} // itotvalue
	else if (b == tcpALL) {
		refreshConf();
	}
	refreshData(b);
}

void connectAll() {
	if (!F1->IdTCPClient1->Connected()) {
		F1->IdTCPClient1->Host = F1->Edit1->Text;
		F1->IdTCPClient1->Port = 8084;
		F1->IdTCPClient1->Connect();
		F1->IdUDPServer1->DefaultPort = 8085;
		F1->IdUDPServer1->Active = true;
		F1->IdUDPServer2->DefaultPort = 8087;
		F1->IdUDPServer2->Active = true;
	}
}

void disconnectAll() {
	if (F1->IdTCPClient1->Connected()) {
		F1->IdTCPClient1->Disconnect();
		F1->IdUDPServer1->Active = false;
		F1->IdUDPServer2->Active = false;
		F1->Frame214->Rectangle1->Fill->Color = claLightgray;
	}
}

void __fastcall TF1::Switch1Switch(TObject *Sender) {
	if (ComboBox13->ItemIndex > 0) {
		if (Switch1->IsChecked) {
			connectAll();
		}
		else // not checked
		{
			disconnectAll();
		}
	}
}
// ---------------------------------------------------------------------------

void __fastcall TF1::Frame21Text1Click(TObject *Sender) {
	sendData(tcpritOn);
}
// ---------------------------------------------------------------------------

void __fastcall TF1::Frame22Text1Click(TObject *Sender) {
	sendData(tcpsplitOn);
}
// ---------------------------------------------------------------------------

void __fastcall TF1::IdTCPClient1Connected(TObject *Sender) {
	Memo1->Lines->Add("TCP connected");
	Label11->Text = "CON";
	Label11->TextSettings->FontColor = claLimegreen;
	NumberBox1->Visible = true;
	NumberBox2->Visible = true;
}
// ---------------------------------------------------------------------------

void __fastcall TF1::IdTCPClient1Disconnected(TObject *Sender) {
	Memo1->Lines->Add("TCP disconnected");
	Label11->Text = "DIS";
	Label11->TextSettings->FontColor = claLightgray;
	NumberBox1->Visible = false;
	NumberBox2->Visible = false;
}
// ---------------------------------------------------------------------------

void __fastcall TF1::FormCreate(TObject *Sender) {
	// This defines the default active tab at runtime
	// TabControl1->ActiveTab = TabItem1;
	Label63->Text = version;
}
// ---------------------------------------------------------------------------

void __fastcall TF1::Button1Click(TObject *Sender) {
	sendData(tcpALL);
}
// ---------------------------------------------------------------------------

void __fastcall TF1::Frame23Text1Click(TObject *Sender) {
	if (scanF == 2)
		scanF = 0;
	else
		scanF = 2;
	sendData(tcpscanst);
}
// ---------------------------------------------------------------------------

void __fastcall TF1::Frame24Text1Click(TObject *Sender) {
	if (scanF == 1)
		scanF = 0;
	else
		scanF = 1;
	sendData(tcpscanst);
}
// ---------------------------------------------------------------------------

void __fastcall TF1::Frame27Text1Click(TObject *Sender) {
	sendData(tcpisUSB);
}
// ---------------------------------------------------------------------------

void __fastcall TF1::Frame28Text1Click(TObject *Sender) {
	sendData(tcpcwMode);
}
// ---------------------------------------------------------------------------

void __fastcall TF1::Frame29Text1Click(TObject *Sender) {
	sendData(tcpbanddn);
}
// ---------------------------------------------------------------------------

void __fastcall TF1::Frame211Text1Click(TObject *Sender) {
	sendData(tcpbandup);
}
// ---------------------------------------------------------------------------

void __fastcall TF1::Frame214Text1Click(TObject *Sender) {
	// sendData(tcpkeylock);
}
// ---------------------------------------------------------------------------

void __fastcall TF1::IdUDPServer1UDPRead(TIdUDPListenerThread *AThread,
	const TIdBytes AData, TIdSocketHandle *ABinding) {
	if (IdUDPServer1->Active) {
		char auxc[20];
		for (uint8_t i = 0; i < AData.Length; i++) {
			auxc[i] = AData[i];
		}
		auxc[AData.Length] = '\0';
		ProgressBar1->Value = atoi(auxc);
	}
}
// ---------------------------------------------------------------------------

void __fastcall TF1::Frame219Text1Click(TObject *Sender) {
	sendData(tcpreset);
	disconnectAll();
}
// ---------------------------------------------------------------------------

void __fastcall TF1::ComboBox13Change(TObject *Sender) {
	if (ComboBox13->ItemIndex == 0) {
		Edit1->Text = "0.0.0.0";
		IdTCPClient1->Port = 0;
		ComboBox15->ItemIndex = 0;
	}
	else if (ComboBox13->ItemIndex == 1) // IP as STA
	{
		Edit1->Text = "192.168.1.149";
		IdTCPClient1->Port = 80;
		ComboBox15->ItemIndex = 0;
	}
	else if (ComboBox13->ItemIndex == 2) // IP as AP
	{
		Edit1->Text = "192.168.4.1";
		IdTCPClient1->Port = 80;
		ComboBox15->ItemIndex = 0;
	}
	else if (ComboBox13->ItemIndex == 3) // Serial-IP
	{
		Edit1->Text = "localhost";
		IdTCPClient1->Port = 8282;
		ComboBox15->ItemIndex = 1;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TF1::Button6Click(TObject *Sender) {
	Memo3->Lines->Clear();
}
// ---------------------------------------------------------------------------

void __fastcall TF1::Button7Click(TObject *Sender) {
	sendData(tcpsplitOn);
}
// ---------------------------------------------------------------------------

void __fastcall TF1::Button9Click(TObject *Sender) {
	sendData(tcpALL);
}
// ---------------------------------------------------------------------------

void __fastcall TF1::Button10Click(TObject *Sender) {
	initConf();
	refreshConf();
}
// ---------------------------------------------------------------------------

void __fastcall TF1::Button12Click(TObject *Sender) {
	sendData(tcpvfoActive);
}
// ---------------------------------------------------------------------------

void __fastcall TF1::Button11Click(TObject *Sender) {
	sendData(tcpvfoActive);
}
// ---------------------------------------------------------------------------

void __fastcall TF1::Timer1Timer(TObject *Sender) {
	char buff[10];
	if (!IdTCPClient1) {
		F1->Memo1->Lines->Add("Client Null");
		return;
	}

	if (!IdTCPClient1->Connected()) {
		return;
	}
	else if (IdTCPClient1->Connected()) {
		while (!IdTCPClient1->IOHandler->InputBufferIsEmpty()) {
			try {
				char crec = IdTCPClient1->IOHandler->ReadChar();
				String auxrec = "";
				if ((uint8_t)crec == tcpALL) {
					TByteDynArray auxread;
					IdTCPClient1->IOHandler->ReadBytes(auxread,
						sizeof(conf), false);
					for (int i = 0; i < sizeof(conf); i++) {
						conf.d[i] = auxread[i];
					}
				}
				else {
					auxrec = IdTCPClient1->IOHandler->ReadLn();
					Memo3->Lines->Add(auxrec);
				}
				handleRecData((uint8_t)crec, auxrec);
			}
			catch (const Exception &) {
				Memo3->Lines->Add("ERROR reading buffer");
			}
			catch (int e) {
				Memo3->Lines->Add("ERROR reading buffer");
			}
		}
	}
}
// ---------------------------------------------------------------------------

void __fastcall TF1::Frame225Text1Click(TObject *Sender) {
	if (inTX == 0) {
		sendData(tcptxOn);
		inTX = 1;
	}
	else {
		sendData(tcptxOff);
		inTX = 0;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TF1::NumberBox6Change(TObject *Sender) {
	ScrollBar1->Value = NumberBox6->Value;
	conf.c.attLevel = NumberBox6->Value;
	F1->Frame25->Rectangle1->Fill->Color = conf.c.attLevel > 0 ? claYellow :
		claLightgray;
	sendData(tcpattlevel);
}
// ---------------------------------------------------------------------------

void __fastcall TF1::NumberBox7Change(TObject *Sender) {
	ScrollBar2->Value = NumberBox7->Value;
	conf.c.ifShiftValue = NumberBox7->Value;
	F1->Frame26->Rectangle1->Fill->Color = conf.c.ifShiftValue != 0 ?
		claYellow : claLightgray;
	sendData(tcpifShiftVal);
}
// ---------------------------------------------------------------------------

void __fastcall TF1::ScrollBar1Change(TObject *Sender) {
	NumberBox6->Value = ScrollBar1->Value;
}
// ---------------------------------------------------------------------------

void __fastcall TF1::ScrollBar2Change(TObject *Sender) {
	NumberBox7->Value = ScrollBar2->Value;
}
// ---------------------------------------------------------------------------

void setStep() {
	if (conf.c.tuneStepIndex == 2) {
		F1->NumberBox1->HorzIncrement = 1000000;
	}
	else if (conf.c.tuneStepIndex == 3) {
		F1->NumberBox1->HorzIncrement = 100000;
	}
	else if (conf.c.tuneStepIndex == 4) {
		F1->NumberBox1->HorzIncrement = 10000;
	}
	else if (conf.c.tuneStepIndex == 5) {
		F1->NumberBox1->HorzIncrement = 1000;
	}
	else if (conf.c.tuneStepIndex == 6) {
		F1->NumberBox1->HorzIncrement = 100;
	}
	else if (conf.c.tuneStepIndex == 7) {
		F1->NumberBox1->HorzIncrement = 10;
	}
	else if (conf.c.tuneStepIndex == 8) {
		F1->NumberBox1->HorzIncrement = 1;
	}
}

void __fastcall TF1::Frame217Text1Click(TObject *Sender) {
	if (conf.c.tuneStepIndex > 2)
		conf.c.tuneStepIndex--;
	else
		conf.c.tuneStepIndex = 8;
	setStep();
}
// ---------------------------------------------------------------------------

void __fastcall TF1::Frame216Text1Click(TObject *Sender) {
	if (conf.c.tuneStepIndex < 8)
		conf.c.tuneStepIndex++;
	else
		conf.c.tuneStepIndex = 2;
	setStep();
}
// ---------------------------------------------------------------------------

void __fastcall TF1::IdUDPServer2UDPRead(TIdUDPListenerThread *AThread,
	const TIdBytes AData, TIdSocketHandle *ABinding) {
	if (IdUDPServer2->Active) {
		char auxc[20];
		for (uint8_t i = 0; i < AData.Length; i++) {
			auxc[i] = AData[i];
		}
		auxc[AData.Length] = '\0';
		conf.c.frequency = atoi(auxc);
		NumberBox1->Value = conf.c.frequency;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TF1::NumberBox8MouseWheel(TObject *Sender, TShiftState Shift,
	int WheelDelta, bool &Handled) {
	conf.c.frequency=conf.c.frequency+1000;
	sendData(tcpfrequency);
}
// ---------------------------------------------------------------------------

int valknob, valknobant;

void __fastcall TF1::ArcDial1Change(TObject *Sender)
{
	if (ArcDial1->Value < 0)
		valknob = -ArcDial1->Value; // -1 - -179
	else if (ArcDial1->Value > 0)
		valknob = 360 - ArcDial1->Value; // 1-180
	else
		valknob = ArcDial1->Value; // 0

	if (valknob > valknobant)
	  {
	  conf.c.frequency=conf.c.frequency+1000;
	  sendData(tcpfrequency);
	  }
	else if (valknob < valknobant)
	  {
	  conf.c.frequency=conf.c.frequency-1000;
	  sendData(tcpfrequency);
	  }

	valknobant = valknob;
}
//---------------------------------------------------------------------------



void __fastcall TF1::Button13Click(TObject *Sender)
{
  conf.c.frequency=conf.c.frequency+100;
  conf.c.frequency=conf.c.frequency/100 *100;
  sendData(tcpfrequency);
}
//---------------------------------------------------------------------------

void __fastcall TF1::Button14Click(TObject *Sender)
{
  conf.c.frequency=conf.c.frequency-100;
  conf.c.frequency=conf.c.frequency/100 *100;
  sendData(tcpfrequency);
}
//---------------------------------------------------------------------------

void __fastcall TF1::Button15Click(TObject *Sender)
{
  conf.c.frequency=conf.c.frequency+10;
  conf.c.frequency=conf.c.frequency/10 *10;
  sendData(tcpfrequency);
}
//---------------------------------------------------------------------------

void __fastcall TF1::Button16Click(TObject *Sender)
{
  conf.c.frequency=conf.c.frequency-10;
  conf.c.frequency=conf.c.frequency/10 *10;
  sendData(tcpfrequency);
}
//---------------------------------------------------------------------------

void __fastcall TF1::Button17Click(TObject *Sender)
{
  conf.c.frequency=conf.c.frequency+1;
  sendData(tcpfrequency);
}
//---------------------------------------------------------------------------

void __fastcall TF1::Button18Click(TObject *Sender)
{
  conf.c.frequency=conf.c.frequency-1;
  sendData(tcpfrequency);
}
//---------------------------------------------------------------------------


