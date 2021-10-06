#include <EEPROM.h>
#include <Arduino.h>  // for type definitions

template <class T> int EEPROM_writeAnything(int ee, const T& value)
{
    const byte* p = (const byte*)(const void*)&value;
    unsigned int i;
    for (i=0; i<sizeof(value); i++) EEPROM.write(ee++, *p++);
    return i;
}

template <class T> int EEPROM_readAnything(int ee, T& value)
{
    byte* p=(byte*)(void*)&value;
    unsigned int i;
    for (i=0; i<sizeof(value); i++) *p++=EEPROM.read(ee++);
    return i;
}

void ICACHE_FLASH_ATTR s2(String texto) { Serial2.print(texto); }
void ICACHE_FLASH_ATTR s2(char* texto) { Serial2.print(texto); }
void ICACHE_FLASH_ATTR s2(PGM_P texto) { Serial2.print(texto); }
void ICACHE_FLASH_ATTR s2(int valor) { Serial2.print(valor); }
void ICACHE_FLASH_ATTR s2(IPAddress ip) { Serial2.print(ip); }
void ICACHE_FLASH_ATTR s2h(int valor) { Serial2.print(valor,HEX); }

char* ICACHE_FLASH_ATTR readdescr(char* namefile, byte ind, byte len)
{
  File auxfile=SPIFFS.open(namefile,letrar);
  if (auxfile)
    {
    auxfile.seek((len+2)*(ind), SeekSet);
    auxfile.readBytes(auxdesc,len+2);
    auxfile.close();
    auxdesc[len-1]='\0';
    byte n=strlen(auxdesc);
    while ((n>0) && ((auxdesc[n-1]==' ')||(auxdesc[n-1]=='\n')||(auxdesc[n-1]=='\r'))) n--;
    auxdesc[n]='\0';
    }
  else
    {
    s2("ERROR OPENNING FILE "); s2(namefile); s2(crlf);  
    }
  return auxdesc;
}

char* ICACHE_FLASH_ATTR t(int pos)
{
  char auxlang[20]="";
  if (conf.lang==0) strcpy(auxlang,filespanish);
  if (conf.lang==1) strcpy(auxlang,fileenglish);
  File auxfile=SPIFFS.open(auxlang,letrar);
  if (auxfile)
    {
    auxfile.seek(42*(pos-1), SeekSet);
    auxfile.readBytes(auxdesc,42);
    auxfile.close();
    auxdesc[41]='\0';
    byte n=strlen(auxdesc);
    while ((n>0) && ((auxdesc[n-1]==' ')||(auxdesc[n-1]=='\n')||(auxdesc[n-1]=='\r'))) n--;
    auxdesc[n]='\0';
    }
  else
    {
    s2("ERROR OPENNING FILE "); s2(auxlang); s2(crlf);  
    }
  return auxdesc;
}

char* ICACHE_FLASH_ATTR c(int pos)
{
  File auxfile=SPIFFS.open(filecommon,letrar);
  if (auxfile)
    {
    auxfile.seek(42*(pos-1), SeekSet);
    auxfile.readBytes(auxdesc,42);
    auxfile.close();
    auxdesc[41]='\0';
    byte n=strlen(auxdesc);
    while ((n>0) && ((auxdesc[n-1]==' ')||(auxdesc[n-1]=='\n')||(auxdesc[n-1]=='\r'))) n--;
    auxdesc[n]='\0';
    }
  else
    {
    s2("ERROR OPENNING FILE "); s2(filecommon); s2(crlf);  
    }
  return auxdesc;
}

void ICACHE_FLASH_ATTR savedescr(char* namefile, char* descr, byte ind, byte len)
{
  File auxfile=SPIFFS.open(namefile, wmas);
  if (auxfile)
    {
    if (auxfile.seek((len+2)*(ind), SeekSet)) 
      {
      for (byte i=strlen(descr);i<len-1;i++) descr[i]=' ';  
      descr[len-1]='\0';
      auxfile.print(descr);auxfile.print('\0');
      auxfile.print(crlf);
      auxfile.close();   
      }
    }
  else 
    {
    s2("ERROR OPENNING FILE "); s2(namefile); s2(crlf);
    }
}

void ICACHE_FLASH_ATTR addlog(File fileact)
{
  if (day()<10) fileact.print(cero); fileact.print(day()); fileact.print(barra);
  if (month()<10) fileact.print(cero); fileact.print(month()); fileact.print(barra);
  if (year()<10) fileact.print(cero); fileact.print(year()); fileact.print(b);
  if (hour()<10) fileact.print(cero); fileact.print(hour()); fileact.print(dp);
  if (minute()<10) fileact.print(cero); fileact.print(minute()); fileact.print(dp);
  if (second()<10) fileact.print(cero); fileact.print(second()); fileact.print(b);
}

void ICACHE_FLASH_ATTR addlog(byte tipo, int code, char *texto)
{
  File auxfile=SPIFFS.open("/log.txt","a+");
  if (auxfile)  
    { 
    if (day()<10) auxfile.print(cero); auxfile.print(day()); auxfile.print(barra);
    if (month()<10) auxfile.print(cero); auxfile.print(month()); auxfile.print(barra);
    if (year()<10) auxfile.print(cero); auxfile.print(year()); auxfile.print(b);
    if (hour()<10) auxfile.print(cero); auxfile.print(hour()); auxfile.print(dp);
    if (minute()<10) auxfile.print(cero); auxfile.print(minute()); auxfile.print(dp);
    if (second()<10) auxfile.print(cero); auxfile.print(second()); auxfile.print(b);
    auxfile.print(code); auxfile.print(b);
    auxfile.print(texto);
    auxfile.println(crlf); 
    auxfile.close();   
    }
}

void ICACHE_FLASH_ATTR addlog(byte tipo, int code, PGM_P texto)
{
//  File auxfile=SPIFFS.open("/log.txt",amas);
  File auxfile=SPIFFS.open("/log.txt","a+");
  if (auxfile)  
    { 
    if (day()<10) auxfile.print(cero); auxfile.print(day()); auxfile.print(barra);
    if (month()<10) auxfile.print(cero); auxfile.print(month()); auxfile.print(barra);
    if (year()<10) auxfile.print(cero); auxfile.print(year()); auxfile.print(b);
    if (hour()<10) auxfile.print(cero); auxfile.print(hour()); auxfile.print(dp);
    if (minute()<10) auxfile.print(cero); auxfile.print(minute()); auxfile.print(dp);
    if (second()<10) auxfile.print(cero); auxfile.print(second()); auxfile.print(b);
    auxfile.print(code); auxfile.print(b);
    auxfile.println(texto); 
    auxfile.close();   }
}

byte ICACHE_FLASH_ATTR getbit8(byte tabla[], byte pin)
  {  return ((tabla[pin/8] & tab[(pin % 8)])>0)?1:0;}

void ICACHE_FLASH_ATTR setbit8(byte tabla[], byte pin, byte value)  {
  tabla[pin/8]=((value==0)?tabla[pin/8]&(255^tab[(pin%8)]):tabla[pin/8]|tab[(pin%8)]);}

void ICACHE_FLASH_ATTR printconceros(int value)  {  if (value<10) s2(0); s2(value); }

void ICACHE_FLASH_ATTR printhora() {
  printconceros(hour()); s2(dp);
  printconceros(minute()); s2(dp);
  printconceros(second());  
  }

void saveconfEEPROM()
{
  for (int i=0;i<sizeof(conf);i++) { EEPROM.write(i,buffconf[i]); }
  EEPROM.commit();
}

int readconfEEPROM()
{
  int mysize=sizeof(conf);
  for (int i=0;i<mysize;i++) { buffconf[i]=EEPROM.read(i); }
  Serial2.print("readconfEEPROM:");Serial2.println(mysize);
  return(mysize);
}


void ICACHE_FLASH_ATTR saveconf()
{
  saveconfEEPROM();
  return;
  
  File auxfile=SPIFFS.open(fileconf, wmas);
  if (auxfile) 
    { 
    int byteswriten=auxfile.write(buffconf,sizeof(conf)); 
    if (byteswriten!=sizeof(conf)) 
      {
      s2("ERROR SAVING FILE CONF");
      s2(" bytes writen:"); s2(byteswriten); s2(crlf);
      }
    auxfile.close();  
    }
  else { s2("ERROR OPENNING FILE CONF");s2(crlf); }
}

int ICACHE_FLASH_ATTR readconf()
{
  int count=0;
  File auxfile=SPIFFS.open(fileconf,letrar);
  if (auxfile)
    {
    for (count=0;count<sizeof(conf);count++) *(buffconf+count)=auxfile.read();
    auxfile.close();
    if ((count!=sizeof(conf)) || (strcmp(conf.watermark,watermarkref)!=0))    // se han leído distinto número de bytes que el tamaño de Conf
      { 
      initConf();
      strcpy(conf.watermark,watermarkref);
      saveconf(); 
      }
    s2("Config file size:");  s2(sizeof(conf)); s2(" read:"); s2(count);
    s2(count==sizeof(conf)?" OK":" ERROR"); s2(crlf);
    s2("Watermark:"); s2(conf.watermark); s2(crlf);
  
    // para nuevas variables
    if (conf.addrADS1115A!=0x48) conf.addrADS1115A=0x48; 
    if (conf.addrADS1115B!=0x49) conf.addrADS1115A=0x49; 
    }
  else 
    {
    s2("ERROR OPENNING FILE "); s2(fileconf); s2(crlf);
    
    }
  return count;
}

int ICACHE_FLASH_ATTR readmemo()
{
  int count=0;
  File auxfile=SPIFFS.open(filememo,letrar);
  if (auxfile)
    {
    for (count=0;count<sizeof(memo);count++)*(buffmemo+count)=auxfile.read();
    auxfile.close();
    }
  else 
    {
    s2("ERROR OPENNING FILE "); s2(filememo); s2(crlf);
    }
  return count;
}

void ICACHE_FLASH_ATTR savememo()
{
  File auxfile=SPIFFS.open(filememo, wmas);
  if (auxfile) 
    { 
    int byteswriten=auxfile.write(buffmemo,sizeof(memo)); 
    if (byteswriten!=sizeof(memo)) s2("ERROR AL GUARDAR FICHERO memo");
    auxfile.close();  
    }
  else
    {
    s2("ERROR OPENNING FILE MEMO");
    }
}

void ICACHE_FLASH_ATTR printlinea(PGM_P texto) { for (byte i=0;i<20;i++) s2(texto); s2(crlf); }

void calcindices(int i)
{
  param_number=server.argName(i).toInt();
  if (mp<=0) mp=1;
  indice=param_number/mp;
  resto=param_number%mp;
  mival=server.arg(i).toInt();
}

void initSerial2(long baud) { Serial2.begin(baud, SERIAL_8N2, RXD2, TXD2); Serial2.flush(); }

boolean checkfile(char* namefile)
{  if (!SPIFFS.exists(namefile)) { s2(namefile); s2(" no existe");  s2(crlf); return false; }  return true; }

boolean checkfiles()
{
  boolean auxB=true;
  //auxB=auxB && checkfile(fileconf); 
  auxB=auxB && checkfile(filememo); 
  auxB=auxB && checkfile(filecommon); 
  auxB=auxB && checkfile(filespanish); 
  auxB=auxB && checkfile(fileenglish); 
  filesok=auxB;
  return auxB;
}

void ICACHE_FLASH_ATTR printP(PGM_P texto1) { char c;  while ((c = pgm_read_byte(texto1++))) msg += c; }
void ICACHE_FLASH_ATTR printP(PGM_P texto1, PGM_P texto2) { printP(texto1); printP(texto2);}
void ICACHE_FLASH_ATTR printP(PGM_P texto1, PGM_P texto2, PGM_P texto3) { printP(texto1, texto2); printP(texto3);}
void ICACHE_FLASH_ATTR printP(PGM_P texto1, PGM_P texto2, PGM_P texto3, PGM_P texto4)
  { printP(texto1,texto2);  printP(texto3,texto4); }
void ICACHE_FLASH_ATTR printP(PGM_P texto1, PGM_P texto2, PGM_P texto3, PGM_P texto4, PGM_P texto5)
  { printP(texto1, texto2, texto3, texto4);  printP(texto5); }
void ICACHE_FLASH_ATTR printP(PGM_P texto1, PGM_P texto2, PGM_P texto3, PGM_P texto4, PGM_P texto5, PGM_P texto6)
  { printP(texto1, texto2, texto3, texto4, texto5); printP(texto6); }

void ICACHE_FLASH_ATTR printI(int value)  { printP(itoa(value, buff, 10));  }
void ICACHE_FLASH_ATTR printH(int value)  { printP(itoa(value, buff, 16));  }
void ICACHE_FLASH_ATTR printL(long value)  { printP(ltoa(value, buff, 10));  }

void ICACHE_FLASH_ATTR printF(float value, byte deci) {
  float pdec=value-int(value);
  printI(int(value)); if (deci>0) printP(punto);  
  for (byte i=0;i<deci;i++) if (int(pdec*pow(10,i+1))%10==0) printP(cero); else printI(abs(int(pdec*pow(10,i+1))%10));
  }
  
void ICACHE_FLASH_ATTR printIP(long valor, const  char *texto) { printI(valor); printP(texto); }

void ICACHE_FLASH_ATTR printPiP(const char *texto1, int num, const char *texto2)
  { printP(texto1); printI(num); printP(texto2);}

bool ICACHE_FLASH_ATTR autOK()
{
  return true;      // provisional
  if (conf.usepassDev == 0) return true;
  if (server.hasHeader("Cookie"))
    if (server.header("Cookie").indexOf("ESPSESSIONID=1") != -1)
      return true;
  return false;
}

void ICACHE_FLASH_ATTR printOpc(boolean colorea, boolean activa, char* texto)
{
  if (activa)
    printP(th, texto, th_f);
  else  {
    printP(colorea?th:td, href_i, comillas, auxchar, comillas, mayor);
    printP(texto, href_f, colorea?th_f:td_f);
  }
}

void ICACHE_FLASH_ATTR printOpc(boolean colorea, boolean activa, PGM_P texto)
{
  if (activa)
    printP(th, texto, th_f);
  else  {
    printP(colorea?th:td, href_i, comillas, auxchar, comillas, mayor);
    printP(texto, href_f, colorea?th_f:td_f);
  }
}

void ICACHE_FLASH_ATTR printOpc(boolean colorea, boolean activa, PGM_P texto, PGM_P link)
{
  if (activa)
    printP(th, texto, th_f);
  else  {
    printP(colorea?th:td, href_i, comillas, link, comillas, mayor);
    printP(texto, href_f, colorea ? th_f : td_f);
  }
}

void ICACHE_FLASH_ATTR printOpc(boolean colorea, boolean activa, PGM_P texto, PGM_P link, byte i)
{
  if (activa)
    printP(th, texto, th_f);
  else  {
    printP(colorea?th:td, href_i, comillas, link, interr, letran);
    printP(ig);
    printI(i);
    printP(comillas, mayor, texto, href_f, colorea ? th_f : td_f);
  }
}

void ICACHE_FLASH_ATTR resetWiFi(void)
{
  s2(t(reiniciando)); s2(b); s2(c(twifi)); s2(crlf);
  conf.wifimode = 2;      // AP
  strcpy(conf.ssidSTA, c(tssid)); strcat(conf.ssidSTA, subray); strcat(conf.ssidSTA, sta);
  strcpy(conf.passSTA, c(tpass)); strcat(conf.passSTA, subray); strcat(conf.passSTA, sta);
  strcpy(conf.ssidAP, "UBITX"); strcat(conf.ssidAP, subray); strcat(conf.ssidAP, conf.CallSign);
  strcpy(conf.passAP, t12341234);
  conf.canalAP=3;
  for (byte i=0; i<6; i++) strcpy(conf.EEmac[i],cero);
  conf.staticIP=1;
  conf.EEip={192,168,1,149};  
  conf.EEmask={255,255,255,0};
  conf.EEgw={192,168,1,1};
  conf.EEdns={8,8,8,8};
  conf.EEdns={8,8,4,4};
  conf.webPort=88;
  strcpy(conf.hostmyip,c(icanhazip));
  saveconf();
}

void writeMenu(byte opcprin, byte opcsec)
{
  printP(c(body_i), menor);
  printP(table, b);
  printP(c(tclass));
  printP(ig, tmenu, mayor, tr); // formato menú
  printOpc(false, (opcprin==1), c(panel), panelhtm); // PANEL
  printOpc(false, (opcprin==3), t(configuracion), sdhtm); // CONFIGURACIÓN
  //printOpc(false, (opcprin==2), t(programas), sprghtm); // Programas
  printOpc(false, (opcprin==4), t(sistema), espsyshtm); // Sistema

  if (conf.usepassDev)
  {
    printP(td, href_i, comillas, barra, loghtm);
    if (autOK())
      printP(interr, c(DISCONNECTYES), comillas, mayor, t(des));
    else
      printP(comillas, b, c(color000000), mayor);
    printP(t(conectar), href_f, td_f);
  }
  printP(tr_f, menor, barra, table, mayor);
  printP(menor, table, b);
  printP(c(tclass), ig);
  printP(tmenu, mayor, tr);  // formato menú
  if (opcprin == 1) // PANELES
    {
    }
  else if (opcprin==2) // PROGRAMACIÓN
    {
    printOpc(false, opcsec==5, t(programas), sprghtm);
    printOpc(false, opcsec==1, t(semanal), ssehtm);
    printOpc(false, opcsec==2, t(condiciones), svhtm);
    printOpc(false, opcsec==3, t(fecha), sfhtm);
    printOpc(false, opcsec==4, t(escenas), seschtm);
    printOpc(false, opcsec==7, t(webcalls), swchtm);
    }
  else if (opcprin==3) // CONFIGURACIÓN
    {
    printOpc(false, opcsec==0, t(dispositivo), sdhtm);
    printOpc(false, opcsec==2, t(bandas), sbhtm);
    printOpc(false, opcsec==5, t(tmemorias), smhtm);
    printOpc(false, opcsec==7, "CW", cwhtm);
    printOpc(false, opcsec==6, "S-meter", smehtm);
    printOpc(false, opcsec==3, t(tred), snehtm);
    printOpc(false, opcsec==4, t(servred), snshtm);
    printOpc(false, opcsec==1, c(senales), siohtm);
    }
  else if (opcprin==4) // SISTEMA
    {
    printOpc(false, opcsec==4, t(statust), espsyshtm);
    printOpc(false, opcsec==3, t(files), fileshtm);
    printOpc(false, opcsec==5, t(seguridad), sshtm);
    printOpc(false, opcsec==1, t(actualizar), suhtm);
    printOpc(false, opcsec==2, treset, rshtm);
    }
  printP(tr_f, menor, barra, table, mayor, br);
}

void ICACHE_FLASH_ATTR serversend200() { server.send(HTTP_CODE_OK, texthtml, msg); msg=vacio; }
void ICACHE_FLASH_ATTR printtiempo(unsigned long segundos)
{
  if (segundos < 60)  {
    printIP(segundos, comillas);
    }
  else     {
    unsigned long minutos = segundos / 60;
    segundos = segundos % 60;
    if (minutos < 60)     {
      printIP(minutos, comilla);
      printPiP(b, segundos, comillas);
      }
    else      {
      unsigned long horas = minutos / 60;
      minutos = minutos % 60;
      if (horas < 24)  {
        printIP(horas, letrah);
        printPiP(b, minutos, comilla);
      }
      else          {
        unsigned int dias = horas / 24;
        horas = horas % 24;
        printIP(dias, letrad);
        printPiP(b, horas, letrah);
        }
      }
    }
}

/**void checkFlash()
{
  FSInfo fs_info;
  SPIFFS.info(fs_info);
  
  float fileTotalKB = (float)fs_info.totalBytes / 1024.0;
  float fileUsedKB = (float)fs_info.usedBytes / 1024.0;
  
  float flashChipSize = (float)ESP.getFlashChipSize() / 1024.0 / 1024.0;
  float realFlashChipSize = (float)ESP.getFlashChipRealSize() / 1024.0 / 1024.0;
  float flashFreq = (float)ESP.getFlashChipSpeed() / 1000.0 / 1000.0;
  FlashMode_t ideMode = ESP.getFlashChipMode();
  Serial2.printf("\n#####################\n");
  Serial2.printf("__________________________\n\n");
  Serial2.println("Firmware: ");
  Serial2.printf(" Chip Id: %08X\n", ESP.getChipId());
  Serial2.print(" Core version: "); Serial2.println(ESP.getCoreVersion());
  Serial2.print(" SDK version: "); Serial2.println(ESP.getSdkVersion());
  Serial2.print(" Boot version: "); Serial2.println(ESP.getBootVersion());
  Serial2.print(" Boot mode: "); Serial2.println(ESP.getBootMode());
  Serial2.printf("__________________________\n\n");

  Serial2.println("Flash chip information: ");
  Serial2.printf(" Flash chip Id: %08X (for example: Id=001640E0 Manuf=E0, Device=4016 (swap bytes))\n", ESP.getFlashChipId());
  Serial2.printf(" Sketch thinks Flash RAM is size: "); Serial2.print(flashChipSize); Serial2.println(" MB");
  Serial2.print(" Actual size based on chip Id: "); Serial2.print(realFlashChipSize); Serial2.println(" MB ... given by (2^( "Device" - 1) / 8 / 1024");
  Serial2.print(" Flash frequency: "); Serial2.print(flashFreq); Serial2.println(" MHz");
  Serial2.printf(" Flash write mode: %s\n", (ideMode == FM_QIO ? "QIO" : ideMode == FM_QOUT ? "QOUT" : ideMode == FM_DIO ? "DIO" : ideMode == FM_DOUT ? "DOUT" : "UNKNOWN"));
  Serial2.printf("__________________________\n\n");
  Serial2.println("File system (SPIFFS): ");
  Serial2.print(" Total KB: "); Serial2.print(fileTotalKB); Serial2.println(" KB");
  Serial2.print(" Used KB: "); Serial2.print(fileUsedKB); Serial2.println(" KB");
  Serial2.printf(" Block size: %lu\n", fs_info.blockSize);
  Serial2.printf(" Page size: %lu\n", fs_info.pageSize);
  Serial2.printf(" Maximum open files: %lu\n", fs_info.maxOpenFiles);
  Serial2.printf(" Maximum path length: %lu\n\n", fs_info.maxPathLength);
  
  Dir dir = SPIFFS.openDir("/");
  Serial2.println("SPIFFS directory {/} :");
  while (dir.next()) {
    Serial2.print(" "); Serial2.println(dir.fileName());
    Serial2.println(" "); Serial2.println(dir.fileSize());
  }
  Serial2.printf("__________________________\n\n");
  Serial2.printf("CPU frequency: %u MHz\n\n", ESP.getCpuFreqMHz());
  Serial2.print("#####################");
  // open file for reading
  File f = SPIFFS.open("/login.txt", "r");
  if (!f) { Serial2.println("file open failed"); } 
  Serial2.println("====== Reading from SPIFFS file =======");
  // write 10 strings to file
  for (int i=1; i<=10; i++){
    String s=f.readStringUntil('\n');
    Serial2.print(i); Serial2.print(":"); Serial2.println(s);
    }
}  **/
