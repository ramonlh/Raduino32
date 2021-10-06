
const char* serverIndex = "<form method='POST' action='/update' enctype='multipart/form-data'><input type='file' name='update'><input type='submit' value='Update'></form>";

void ICACHE_FLASH_ATTR printColspan(int ancho)
  { printP(c(tdcolspan_i)); printI(ancho); printP(comillas, mayor);}
  
void ICACHE_FLASH_ATTR cell(PGM_P texto) { printP(td,texto,td_f); }
void ICACHE_FLASH_ATTR cell(int num) { printPiP(td,num,td_f); }
void ICACHE_FLASH_ATTR cell(float num, byte deci) { printP(td); printF(num,deci); printP(td_f); }

void ICACHE_FLASH_ATTR ccell(int ntexto) { printP(td,c(ntexto),td_f); }
void ICACHE_FLASH_ATTR tcell(int ntexto) { printP(td,t(ntexto),td_f); }

void ICACHE_FLASH_ATTR pt(int pos)
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
  printP(auxdesc);
}

void ICACHE_FLASH_ATTR pc(int pos)
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
  printP(auxdesc);
}

void ICACHE_FLASH_ATTR espacioSep(int col)  //  espacio separación
  { printP(tr); printColspan(col);printP(td_f,tr_f);  }

void printfincampo() { printP(mayor, menor, barra, c(tinput), mayor); }
void printdisabled() { printP(c(ttext)); printP(comillas,b,c(disabled)); printP(ig,comillas, c(disabled)); }
void printselected(boolean check) { printP(b, check?checked:selected); }

void ICACHE_FLASH_ATTR printcampoI(int numpar, int valactual, byte tam, boolean enabled,boolean printtd)
{
  if (printtd) printP(td);
  printP(menor, c(tinput), b, type, ig, comillas);  
  if (!enabled) printdisabled();
  printP(c(ttext), comillas, b);
  printP(c(namet), ig,comillas);
  printI(numpar);
  printP(comillas,b, tvalue, ig,comillas);
  printI(valactual);
  printP(comillas,b,c(max_length));
  printIP(tam, size_i);
  printIP(tam,comillas);
  printfincampo();
  if (printtd) printP(td_f);
}

void ICACHE_FLASH_ATTR printcampoL(int numpar, long valactual, byte tam, boolean enabled,boolean printtd)
{
  if (printtd) printP(td);
  printP(menor, c(tinput), b, type, ig, comillas);
  if (!enabled) printdisabled();
  printP(c(ttext), comillas, b);
  printP(c(namet), ig,comillas);
  printI(numpar);
  printP(comillas,b, tvalue, ig,comillas);
  printI(valactual);
  printP(comillas,b,c(max_length));
  printIP(tam, size_i);
  printIP(tam, comillas);
  printfincampo();
  if (printtd) printP(td_f);
}

void ICACHE_FLASH_ATTR printcampoF(int numpar, float valactual, int deci)
{
  printP(menor, c(tinput), b, type, ig, comillas);
  printP(c(ttext), comillas, b);
  printP(c(namet), ig,comillas);
  printI(numpar);
  printP(comillas,b, tvalue, ig,comillas);
  printF(valactual, deci);
  printP(comillas,b,c(max_length));
  printIP(10,size_i);
  printIP(10,comillas);
  printfincampo();
}

void ICACHE_FLASH_ATTR printcampoC(int numpar, char *valactual, byte tam, boolean visible, boolean enabled, boolean pass,boolean printtd)
{
  if (printtd) printP(td);
  printP(menor, c(tinput), b, type, ig, comillas);
  if (visible)  {
    printP(pass?c(tpassword):c(ttext));
    if ((!enabled) && (!pass)) { printP(comillas, b, c(disabled)); printP(ig, comillas, c(disabled)); }
    printP(comillas);   }
  else
    {
    printP(c(ttext), comillas, b);
    printP(c(invis), b);  }
  printP(b, c(namet), ig );
  printPiP(comillas,numpar, comillas);
  printP(b, tvalue, ig, comillas, valactual);
  printP(comillas,b, c(max_length));
  printIP(tam-1, size_i);
  printIP(tam-1, comillas);
  printfincampo();
  if (printtd) printP(td_f);
}

void ICACHE_FLASH_ATTR printparCP(const char *titulo, int numpar, char valactual[], byte tam, boolean pass)
{
  printP(tr);
  cell(titulo);
  printcampoC(numpar, valactual, tam, true, true, pass,true);
  printP(tr_f);
}

void ICACHE_FLASH_ATTR printcampoSiNo(int numpar, int valactual)
  {
  printP(c(Select_name), comillas);
  printIP(numpar, comillas);
  printP(mayor, c(optionvalue),comillas, cero, comillas);
  if (valactual==0) printselected(false);
  printP(mayor, OFF, c(option_f));
  printP(c(optionvalue));
  printPiP(comillas, 1, comillas);
  if (valactual) printselected(false);
  printP(mayor, ON, c(option_f));
  printP(c(select_f));
  }

void ICACHE_FLASH_ATTR printparentesis(PGM_P letra, int numero)
{
  printP(paren_i,letra);
  printI(numero);
  printP(paren_f, b, b);
}

void ICACHE_FLASH_ATTR checkBox(int numpar, bool selected, boolean printtd)
{
  if (printtd) printP(td);
  printP(menor, c(tinput), b, type, ig, comillas);
  printP(c(checkbox), comillas, b);
  printP(c(namet), ig,comillas);
  printI(numpar);
  printP(comillas,b, tvalue, ig,comillas);
  printP(uno,comillas);
  if (selected) printselected(true);
  printfincampo();
  if (printtd) printP(td_f);
}

void ICACHE_FLASH_ATTR writeHeader(boolean refreshmode, boolean ajaxmode)
{
  printP(menor, thtml);
  printP(b, c(xmlns), mayor);
  printP(menor, thead, mayor, menor, c(title), mayor);
  printP(c(uBitx));
  printP(c(web));
  printP(c(tserver), menor, barra);
  printP(c(title));
  printP(mayor,htmlHead_3);
  printP(ajaxscript);
  printP(c(head_f));
}

void printinicampoCB(int numpar)
{
  printP(c(Select_name), comillas);
  printIP(numpar, comillas);
  printP(mayor);
}

void ICACHE_FLASH_ATTR printcampoCB(int numpar, int valact, int pri, int ult, boolean printtd)
{
  if (printtd) printP(td);
  printinicampoCB(numpar);
  for (byte j=pri; j<=ult; j++)   {
    printP(c(optionvalue));
    printPiP(comillas, j, comillas);
    if (valact==j) printselected(false);
    printPiP(mayor, j, c(option_f));   }
  printP(c(select_f));
  if (printtd) printP(td_f);
}

void ICACHE_FLASH_ATTR printcampoCB(int numpar, int valact, byte lon, PGM_P t[], boolean printtd)
{
  if (printtd) printP(td);
  printinicampoCB(numpar);
  for (byte j=0;j<lon;j++)   {
    printP(c(optionvalue));
    printPiP(comillas, j, comillas);
    if (valact==j) printselected(false);
    printP(mayor,t[j]);
    printP(c(option_f));   }
  printP(c(select_f));
  if (printtd) printP(td_f);
}

void ICACHE_FLASH_ATTR printcampoCB(int numpar, int valact, PGM_P t0, PGM_P t1, boolean printtd)
{
  PGM_P t[]={t0,t1};
  printcampoCB(numpar,valact,sizeof(t)/sizeof(t[0]),t,printtd);
}

void ICACHE_FLASH_ATTR printcampoCB(int numpar, int valact, PGM_P t0, PGM_P t1, PGM_P t2, boolean printtd)
{
  PGM_P t[]={t0,t1,t2};
  printcampoCB(numpar,valact,sizeof(t)/sizeof(t[0]),t,printtd);
}

void ICACHE_FLASH_ATTR printcampoCB(int numpar, int valact, PGM_P t0, PGM_P t1, PGM_P t2, PGM_P t3, boolean printtd)
{
  PGM_P t[]={t0,t1,t2,t3};
  printcampoCB(numpar,valact,sizeof(t)/sizeof(t[0]),t,printtd);
}

void ICACHE_FLASH_ATTR printcampoCB(int numpar, int valact, PGM_P t0, PGM_P t1, PGM_P t2, PGM_P t3, PGM_P t4, boolean printtd)
{
  PGM_P t[]={t0,t1,t2,t3,t4};
  printcampoCB(numpar,valact,sizeof(t)/sizeof(t[0]),t,printtd);
}

void ICACHE_FLASH_ATTR printcampoCB(int numpar, int valact, PGM_P t0, PGM_P t1, PGM_P t2, PGM_P t3, PGM_P t4, PGM_P t5, boolean printtd)
{
  PGM_P t[]={t0,t1,t2,t3,t4,t5};
  printcampoCB(numpar,valact,sizeof(t)/sizeof(t[0]),t,printtd);
}

void ICACHE_FLASH_ATTR selectProbe(int numpar, int valact, boolean printtd)
{
  if (printtd) printP(td);
  printinicampoCB(numpar);
  for (byte i=0;i<nTemp+1;i++)   
    {
    printP(c(optionvalue));
    printPiP(comillas, i, comillas);
    if (valact==i) printselected(false);
    printP(mayor); 
    if (i==0)
      printP("No probe");
    else 
      for (uint8_t j=0;j<8;j++) { if (addr1Wire[i-1][j]<16) printP(cero); printH(addr1Wire[i-1][j]); }   
    printP(c(option_f));   }
  printP(c(select_f));
  if (printtd) printP(td_f);
}

void ICACHE_FLASH_ATTR tituloFila(PGM_P texto, int num, PGM_P letra, int indice)
{
  printP(td, paren_i);
  printPiP(letra, indice, paren_f);
  printP(b, b, texto);
  printPiP(b, num, td_f);
}

int ICACHE_FLASH_ATTR getMyIP()
{
  msg=vacio;
  printP(barra);
  HTTPClient http;
  http.begin(conf.hostmyip, 80, msg);
//  http.setConnectTimeout(conf.timeoutNTP);
  http.setConnectTimeout(1000);
  int httpCode=http.GET();
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) { msg=http.getString(); msg.toCharArray(conf.myippub, msg.length());  } }
  http.end();
  msg=vacio;
  return httpCode;
}

int ICACHE_FLASH_ATTR checkMyIP()
{
  char auxip[16];
  strcpy(auxip, conf.myippub);
  int auxR=getMyIP();    // busca actual y la guarda en conf.txt
  if (strcmp(conf.myippub, auxip) != 0) // son diferentes
    {
    saveconf();
    //if (conf.iftttenabled) ifttttrigger(conucochar, conf.iftttkey, conf.aliasdevice, "NewIP", conf.myippub);
    }
  return auxR;
}

void printTime()
{
  printI(day()); printPiP(barra, month(), barra); printIP(year(),b);
  if (hour()<10) printP(cero); printI(hour()); printP(dp);
  if (minute()<10) printP(cero); printI(minute()); printP(dp);
  if (second()<10) printP(cero); printI(second());
}

void HtmlGetStateData(byte ind)    // 
{
  printP(td);
  if (ind==0) printP("VFO");
  else if (ind==1) printP("Mode");
  else if (ind==2) printP("CW");
  else if (ind==3) printP("RIT");
  else if (ind==4) printP("Split");
  else if (ind==5) printP("VFO A");
  else if (ind==6) printP("VFO B");
  else if (ind==7) printP("Freq. actual");
  printP(td_f,td);
  if (ind==0) printP(conf.vfoActive==VFO_A?"A":"B");
  else if (ind==1) printP(conf.isUSB==1?"USB":"LSB");
  else if (ind==2) printP(conf.cwMode>=1?"ON":"OFF");
  else if (ind==3) printP(conf.ritOn>=1?"ON":"OFF");
  else if (ind==4) printP(conf.splitOn>=1?"ON":"OFF");
  else if (ind==5) printL(conf.frequencyA);
  else if (ind==6) printL(conf.frequencyB);
  else if (ind==7) printL(conf.frequency);
  printP(td_f,td,td_f);
}

void ICACHE_FLASH_ATTR HtmlGetStateTime()
{
  printColspan(3);
  printTime();
  printP(td_f);
}

void ICACHE_FLASH_ATTR writeForm(PGM_P phtm)
{
  printP(c(form_action), phtm);
  printP(comillas,b);
  printP(c(Form_post), menor);
  printP(table, b);
  printP(c(tclass), ig, tnormal, mayor);
}

void ICACHE_FLASH_ATTR writeFooter(int texto, boolean cerrar)
{
  printP(menor, barra, table, mayor);               // final <table>
  printP(menor, c(tinput), b, type, ig, comillas);
  printP(submit);                                   // submit
  printP(comillas, b, tvalue, ig, comillas);      // " value="texto
  pt(texto);                                  
  if (cerrar) printP(comillas, b, c(onclickclose));
  printP(comillas);
  printfincampo();
  printP(c(form_f));
  printP(c(body_f), menor, barra);
  printP(thtml, mayor);
}

void ICACHE_FLASH_ATTR setCookie(byte valor)
{
  msg=vacio;
  printP(c(HTTP11), b);
  printP(c(t301), b, ok, crlf);
  printP(c(setcookie),dp, b);
  printP(c(espsessionid), ig, valor==0?cero:uno);
  printP(crlf,c(location), dp, b, barra, crlf);
  printP(c(cachecontrol),dp, b);
  printP(c(nocache), crlf, crlf);
  server.sendContent(msg);
  msg=vacio;
}

void ICACHE_FLASH_ATTR sendOther(const char *otherURL, int param)
{
  msg=vacio;
  printP(c(HTTP11),b);
  printP(c(t303),b);
  printP(c(seeother),crlf);
  printP(c(location),dp,b,otherURL);
  if (param>=0) { printP(paramn);printI(param);}
  printP(crlf,crlf);
  server.sendContent(msg);
  msg=vacio;
}

void ICACHE_FLASH_ATTR printDiaSem(byte i)
  {
  if (i==0) printP(letraD);  
  if (i==1) printP(letraL);  
  if (i==2) printP(letraM);  
  if (i==3) printP(letraX);  
  if (i==4) printP(letraJ);  
  if (i==5) printP(letraV);  
  if (i==6) printP(letraS);  
  }

void htmlNotFound()
{
  msg=vacio;
  printP("HTTP/1.1", b);
  printP("404", b);
  server.send(404, "text/plain", msg);
  msg=vacio;
}


void panelHTML() {
  msg=vacio;
  if (server.method()==HTTP_POST) return; 
  writeHeader(false,true);
  byte auxI=server.arg(0).toInt();
  writeMenu(1, auxI);
  printP(menor, table,b);
  printP("class", ig, tpanel, mayor,tr);
  
  /////////////  CONTENIDO   ///////////
  printColspan(3);
  printP("uBitx", td_f, tr_f);

  printP(menor,letrat,letrar,b);  printP(c(tid),ig,comilla,letral);
  printI(0);  printP(comilla,mayor);
  HtmlGetStateData(0);
  printP(tr_f);
  
  printP(menor,letrat,letrar,b);  printP(c(tid),ig,comilla,letral);
  printI(1);  printP(comilla,mayor);
  HtmlGetStateData(1);
  printP(tr_f);
  
  printP(menor,letrat,letrar,b);  printP(c(tid),ig,comilla,letral);
  printI(2);  printP(comilla,mayor);
  HtmlGetStateData(2);
  printP(tr_f);
  
  printP(menor,letrat,letrar,b);  printP(c(tid),ig,comilla,letral);
  printI(3);  printP(comilla,mayor);
  HtmlGetStateData(3);
  printP(tr_f);
  
  printP(menor,letrat,letrar,b);  printP(c(tid),ig,comilla,letral);
  printI(4);  printP(comilla,mayor);
  HtmlGetStateData(4);
  printP(tr_f);
  
  printP(menor,letrat,letrar,b);  printP(c(tid),ig,comilla,letral);
  printI(5);  printP(comilla,mayor);
  HtmlGetStateData(5);
  printP(tr_f);
  
  printP(menor,letrat,letrar,b);  printP(c(tid),ig,comilla,letral);
  printI(6);  printP(comilla,mayor);
  HtmlGetStateData(6);
  printP(tr_f);
  
  printP(menor,letrat,letrar,b);  printP(c(tid),ig,comilla,letraf);
  printI(7);  printP(comilla,mayor);
  HtmlGetStateData(7);
  printP(tr_f);
 
  /**for (byte i=0;i<MAX_BANDS;i++)
    {
    printP(tr,td,"Band ",conf.hamBandName[i],b);
    printP(letram,td_f,td); 
    printI(conf.freqbyband[i][0]); printP(td_f, td);
    printI(conf.freqbyband[i][1]); printP(td_f, tr_f);
    }**/
  // final
  printP(menor,letrat,letrar,b,c(tid));
  printP(ig,comilla,letrat,letrat,comilla,mayor);
  HtmlGetStateTime();
  printP(tr_f, menor, barra, table, mayor);
  printP(c(body_f), menor, barra,thtml, mayor);
  serversend200();
}

void ICACHE_FLASH_ATTR indexHTML() 
  {
  panelHTML();
  }

void ICACHE_FLASH_ATTR filesHTML()
{
  if (!autOK()) { sendOther(loghtm,-1); return; }
  msg=vacio;
  writeHeader(false,false);
  if (filesok)
    writeMenu(4, 3);
  else
    printP(t(faltafichero),crlf);
    printP(t(useftp),crlf);
  printP(menor,table, b);
  printP(c(tclass), ig, tnormal, mayor);
  File dir = SPIFFS.open("/");
  File f=dir.openNextFile("r");
//    File dir=SPIFFS.open(barra);
//    File file=dir.openNextFile();
//    if (testfiles) { while (file) { Serial2.print(file.name()); Serial2.print(b); Serial2.println(file.size()); file=dir.openNextFile(); }}
  while (f)   {
    printP(tr, td, href_i, comillas, letrad, letraw);
    printP(interr, letraf, ig);
    msg=msg+f.name();
    printP(comillas, mayor);
    msg=msg+f.name();
    printP(href_f, td_f, td);
    printI(f.size());
    printP(td_f, tr_f);
    f=dir.openNextFile();
    }
  printP(menor, barra, table, mayor);  
  printP(c(body_f), menor, barra);
  printP(thtml, mayor);
  serversend200();
}

void ICACHE_FLASH_ATTR downloadHTML() {
  File download=SPIFFS.open(server.arg(0),letrar);
  if (download) {
    server.sendHeader(contenttype, texttext);     // "Content-Type", "text"
    server.sendHeader(c(contentdisposition), attachfilename+server.arg(0));    //"Content-Disposition","attachment; filename=xxxx" 
    server.sendHeader(c(tconnection), closet);          // "Connection", "close"
    server.streamFile(download, c(applicationoctet));  // "application/octet-stream"
    download.close();
  }
}

void ICACHE_FLASH_ATTR setupioHTML()
{
  if (!autOK()) { sendOther(loghtm,-1); return; }
  msg=vacio;
  mp=1;  // número de parámetros por fila
  if (server.method()==HTTP_POST)
    {
    for (int i=0  ;i<server.args(); i++)
      {
      calcindices(i);
      if (resto==0)    // número y código de sonda
        { 
        conf.nprobe[indice]=server.arg(i).toInt();
        for (byte j=0;j<8;j++) conf.probecode[indice][j]=addr1Wire[server.arg(i).toInt()-1][j];
        } 
      }
    saveconf();
    sendOther(siohtm,-1); return;
    }
  if (server.args() > 0) 
    { 
    saveconf();
    }
  writeHeader(false,false);
  writeMenu(3,1);
  writeForm(siohtm);
  printP(tr);
  tcell(descripcion); 
  printP(td,ID,td_f);
  for (byte i=0; i<3; i++)
    {
    mpi=mp*i;
    printP(tr);
    printP(td);
    printP(i==0?"TR 1":i==1?"TR 2":"DC 5v");
    printP(td_f);
    pc(select_f);
    selectProbe(mpi+0, conf.nprobe[i], true);
    printP(tr_f);
    }
  writeFooter(guardar, false);
  serversend200();
}

void ICACHE_FLASH_ATTR selectTimeZone(int numpar, int valact, boolean printtd)
{
  if (printtd) printP(td);
  printinicampoCB(numpar);
  for (byte i=0;i<38;i++)   
    {
    printP(c(optionvalue));
    printPiP(comillas, i, comillas);
    if (valact==i) printselected(false);
    printP(mayor,timezonetext[i],c(option_f));   }
  printP(c(select_f));
  if (printtd) printP(td_f);
}

void setupDevHTML()
{
  msg=vacio;
  mp=1;
  if (server.method()==HTTP_POST)
    {
    conf.Smeterenabled=0; conf.SWRenabled=0; conf.DS18B20enabled=0; conf.ATUZM2enabled=0;             
    for (int i=0; i<server.args(); i++)
      {
      calcindices(i);
      if (param_number==0) server.arg(i).toCharArray(conf.CallSign, 20); // callsign
      else if (param_number==1) { conf.calibration = server.arg(i).toInt();  }
      else if (param_number==2) { conf.usbCarrier = server.arg(i).toInt();  }
      else if (param_number==3) { conf.latitud = server.arg(i).toFloat();  }
      else if (param_number==4) { conf.longitud = server.arg(i).toFloat(); }
      else if (param_number==5) { conf.lang = server.arg(i).toInt(); }   
      else if (param_number==9) { conf.SI5351BX_ADDR = server.arg(i).toInt(); }
      else if (param_number==10) { conf.scanallf = server.arg(i).toInt(); }   
      else if (param_number==11) { conf.TXall = server.arg(i).toInt(); }   
      else if (param_number==12) { conf.ATUdelay = server.arg(i).toInt(); }
      else if (param_number==13) { conf.ATUFactor = server.arg(i).toFloat();  }
      else if (param_number==14) { conf.ATUOffset = server.arg(i).toFloat(); }
      else if (param_number==15) { conf.TempAlarm = server.arg(i).toInt();  }
      else if (param_number==16) { conf.TempTxOff = server.arg(i).toInt();  }
      else if (param_number==17) { conf.ATUIter = server.arg(i).toInt(); }
      else if (param_number==18) { conf.scanmode = server.arg(i).toInt(); }
      else if (param_number==19) { conf.scandelay = server.arg(i).toInt(); }
      else if (param_number==20) { conf.Smeterenabled = server.arg(i).toInt(); }
      else if (param_number==21) { conf.SWRenabled = server.arg(i).toInt(); }
      else if (param_number==22) { conf.DS18B20enabled = server.arg(i).toInt(); }
      else if (param_number==23) { conf.ATUZM2enabled = server.arg(i).toInt(); }
      else if (param_number==24) { conf.timezone = server.arg(i).toInt(); }
      else if (param_number==99) { conf.rstper = server.arg(i).toInt(); } // período rset automatico
      }
    saveconf();
    sendOther(sdhtm,-1);
    return;
    }

  writeHeader(false,false);
  writeMenu(3, 0);
  writeForm(sdhtm);

  printP(tr,td,"CALLSIGN",td_f);
  printcampoC(0, conf.CallSign, 19, true, true, false, true);
  printP(td,td_f,tr_f);

  printP(tr,td,"Calibration / usbCarrier",td_f); 
  printcampoL(1, conf.calibration, 9, true, true);
  printcampoL(2,  conf.usbCarrier, 9, true, true); 

  printP(tr, td, href_i, comillas);
  pc(thttp);
  pc(gmaps);
  printP(comillas, b, c(newpage), mayor);
  printP(t(latitudt), barraesp);
  printP(t(longitudt), href_f, td_f, td);
  printcampoF(3, conf.latitud, 6);  printP(td_f, td);
  printcampoF(4, conf.longitud, 6);  printP(td_f, tr_f);

  printP(tr, td, t(idioma),b,barra,b);
  printP("Time Zone",td_f);
  printcampoCB(5, conf.lang, PSTR("Español"), PSTR("English"),true); 
  printP(td,"UTC ");
  selectTimeZone(24, conf.timezone,false);
  printP(td_f,tr_f);

  printP(tr);
  printP(td, "S-meter / SWR meter", td_f, conf.Smeterenabled==1 ? th : td);
  checkBox(20,conf.Smeterenabled,false);
  printP(conf.Smeterenabled?th_f:td_f);
  printP(conf.SWRenabled==1 ? th : td);
  checkBox(21,conf.SWRenabled,false);
  printP(conf.SWRenabled?th_f:td_f);
  printP(tr_f);

  printP(tr);
  printP(td, "DS18B20 probes / ATU ZM-2", td_f, conf.DS18B20enabled==1 ? th : td);
  checkBox(22,conf.DS18B20enabled,false);
  printP(conf.DS18B20enabled?th_f:td_f);
  printP(conf.ATUZM2enabled==1 ? th : td);
  checkBox(23,conf.ATUZM2enabled,false);
  printP(conf.ATUZM2enabled?th_f:td_f);
  printP(tr_f);


  printP(tr,td,"ATU time(s) / Iterat. ADC"); 
  printcampoI(12, conf.ATUdelay, 5, true, true); printP(td_f);
  printcampoI(17, conf.ATUIter, 5, true, true); 
  printP(td_f,tr_f);
  
  printP(tr, td, href_i, comillas);
  pc(thttp);
  pc(gmaps);
  printP(comillas, b, c(newpage), mayor);
  printP("ATU  Factor ", barraesp); printP(" Offset", href_f, td_f, td);
  printcampoF(13, conf.ATUFactor, 6);  printP(td_f, td);
  printcampoF(14, conf.ATUOffset, 6);  printP(td_f, tr_f);

  printP(tr,td,"SI5351BX_ADDR"); 
  printcampoI(9, conf.SI5351BX_ADDR, 5, true, true); printP(td_f,td,td_f,tr_f);

  printP(tr, td, "Scan range / TX range",td_f);
  printcampoCB(10, conf.lang, PSTR("Ham bands"), PSTR("All range"),true); 
  printP(td_f);
  printcampoCB(11, conf.lang, PSTR("Ham bands"), PSTR("All range"),true); 
  printP(td_f,tr_f);

  printP(tr, td, "Scan mode / Resume Delay",td_f);
  printcampoCB(18, conf.scanmode, PSTR("No Stop"), PSTR("Stop-resume"),PSTR("Stop"),true); 
  printP(td_f);
  printcampoL(19, conf.scandelay, 5, true, true);
  printP(td_f,tr_f);

  printP(tr,td,"Temp. Alarm ºC / OFF TX ºC",td_f); 
  printcampoL(15, conf.TempAlarm, 5, true, true);
  printcampoL(16,  conf.TempTxOff, 5, true, true); 

  printP(tr, td, "Reset periodico (h)",td_f,td);
  printcampoCB(99,conf.rstper,1,24,false); 
  printP(td_f,td,td_f,tr_f);

  writeFooter(guardar, false);
  serversend200();
}

void setupCWHTML()
{
  msg=vacio;
  mp=1;
  if (server.method()==HTTP_POST)
    {
    conf.Smeterenabled=0; conf.SWRenabled=0; conf.DS18B20enabled=0; conf.ATUZM2enabled=0;             
    for (int i=0; i<server.args(); i++)
      {
      calcindices(i);
      if (param_number==0) { conf.cwKeyType = server.arg(i).toInt(); }
      else if (param_number==1) { conf.cwSpeed = server.arg(i).toInt(); }
      else if (param_number==2) { conf.cwDelayTime = server.arg(i).toInt(); }
      else if (param_number==3) { conf.cwAdcDotFrom = server.arg(i).toInt(); }
      else if (param_number==4) { conf.cwAdcDotTo = server.arg(i).toInt(); }
      else if (param_number==5) { conf.cwAdcDashFrom = server.arg(i).toInt(); }
      else if (param_number==6) { conf.cwAdcDashTo = server.arg(i).toInt(); }
      else if (param_number==7) { conf.cwAdcBothFrom = server.arg(i).toInt(); }
      else if (param_number==8) { conf.cwAdcBothTo = server.arg(i).toInt(); }
      else if (param_number==9) { conf.cwAdcSTFrom = server.arg(i).toInt(); }
      else if (param_number==10) { conf.cwAdcSTTo = server.arg(i).toInt(); }
      }
    saveconf();
    sendOther(cwhtm,-1);
    return;
    }

  writeHeader(false,false);
  writeMenu(3, 7);
  writeForm(cwhtm);
  printP(tr,td,"cwKeyType",td_f); 
  printcampoCB(0, conf.cwKeyType, "straight", "iambica", "iambicb", true); 
  printP(td,td_f);
  printP(tr,td,"CW Speed / Delay time"); 
  printcampoI(1, conf.cwSpeed, 5, true, true); printP(td_f);
  printcampoI(2, conf.cwDelayTime, 5, true, true); printP(td_f,tr_f);
  printP(tr,td,"DOT from / to"); 
  printcampoI(3, conf.cwAdcDotFrom, 5, true, true); printP(td_f);
  printcampoI(4, conf.cwAdcDotTo, 5, true, true); printP(td_f,tr_f);
  printP(tr,td,"DASH from / to"); 
  printcampoI(5, conf.cwAdcDashFrom, 5, true, true); printP(td_f);
  printcampoI(6, conf.cwAdcDashTo, 5, true, true); printP(td_f,tr_f);
  
  printP(tr,td,"BOTH from / to"); 
  printcampoI(7, conf.cwAdcBothFrom, 5, true, true); printP(td_f);
  printcampoI(8, conf.cwAdcBothTo, 5, true, true); printP(td_f,tr_f);
  
  printP(tr,td,"ST from / to"); 
  printcampoI(9, conf.cwAdcSTFrom, 5, true, true); printP(td_f);
  printcampoI(10, conf.cwAdcSTTo, 5, true, true); printP(td_f,tr_f);
  
  writeFooter(guardar, false);
  serversend200();
}

void setupMemHTML()
{
  msg=vacio;
  mp=12;
  if (server.method()==HTTP_POST)
    {
    memset(memo.act,0,sizeof(memo.act));
    memset(memo.ritOn,0,sizeof(memo.ritOn));
    memset(memo.splitOn,0,sizeof(memo.splitOn));
    for (int i=0; i<server.args(); i++)
      {
      calcindices(i);
      if (resto==0) memo.act[indice]=server.arg(i).toInt();
      else if (resto==1) server.arg(i).toCharArray(memo.descr[indice], 20);
      else if (resto==2) memo.frequency[indice]=server.arg(i).toInt();
      else if (resto==3) memo.isUSB[indice]=server.arg(i).toInt();
      else if (resto==4) memo.cwMode[indice]=server.arg(i).toInt();
      else if (resto==5) memo.vfoActive[indice]=server.arg(i).toInt()==0?VFO_A:VFO_B;
      else if (resto==6) memo.ritOn[indice]=server.arg(i).toInt();
      else if (resto==7) memo.ritTxFrequency[indice]=server.arg(i).toInt();
      else if (resto==8) memo.splitOn[indice]=server.arg(i).toInt();
      else if (resto==9) memo.ftxspl[indice]=server.arg(i).toInt();
      else if (resto==10) memo.splitOn[indice]=server.arg(i).toInt();
      else if (resto==11) memo.cwModespl[indice]=server.arg(i).toInt();
      }
    savememo();
   // readmemo();
    sendOther(smhtm,-1);
    return;
    }

  writeHeader(false,false);
  writeMenu(3,5);
  writeForm(smhtm);
  
  printP(tr); printColspan(7); printP(td_f);
  printColspan(2);  printP("RIT",td_f);
  printColspan(4);  printP("SPLIT",td_f,tr);
  printP(tr,td,"Canal",td_f);
  printP(td,"Act.",td_f,td,"Descr.",td_f);
  printP(td,"Freq.",td_f,td,"SSB mode",td_f);
  printP(td,"CW mode",td_f,td,"VFO",td_f);
  printP(td,"En.",td_f,td,"TX Freq.",td_f);
  printP(td,"En.",td_f,td,"TX Freq.",td_f);
  printP(td,"Mmode",td_f,td,"CW",td_f);
  printP(tr_f);
//  for (byte i=0;i<maxMem;i++)
  for (byte i=0;i<10;i++)
    {
    printP(tr); printPiP(td,i+1,b); printP(td_f); 
    printP(memo.act[i]==1?th:td);
    checkBox(mp*i,memo.act[i],false);
    printP(memo.act[i]?th_f:td_f);
    printcampoC(mp*i+1, memo.descr[i], 10, true, true, false,true);
    printcampoL(mp*i+2, memo.frequency[i], 9, true, true);
    printcampoCB(mp*i+3, memo.isUSB[i],"LSB","USB",true);
    printcampoCB(mp*i+4, memo.cwMode[i],"None","CW",true);
    printcampoCB(mp*i+5, memo.vfoActive[i],"VFO A","VFO B",true);
    printP(memo.ritOn[i]==1?th:td);
    checkBox(mp*i+6,memo.ritOn[i],false);
    printP(memo.ritOn[i]?th_f:td_f);
    printcampoL(mp*i+7, memo.ritTxFrequency[i], 9, true, true);
    printP(memo.splitOn[i]==1?th:td);
    checkBox(mp*i+8,memo.splitOn[i],false);
    printP(memo.splitOn[i]?th_f:td_f);
    printcampoL(mp*i+9, memo.ftxspl[i], 9, true, true);
    printcampoCB(mp*i+10, memo.splitOn[i],"LSB","USB",true);
    printcampoCB(mp*i+11, memo.cwModespl[i],"None","CW",true);
    printP(tr_f);  
    }
    
  writeFooter(guardar, false);
  serversend200();
}

void setupBandHTML()
{
  msg=vacio;
  mp=2;
  if (server.method()==HTTP_POST)
    {
    for (int i=0; i<server.args(); i++)
      {
      calcindices(i);
      if (resto==0)      conf.hamBandRange[indice][0]=server.arg(i).toInt();
      else if (resto==1) conf.hamBandRange[indice][1]=server.arg(i).toInt();
      }
    saveconf();
    sendOther(sbhtm,-1);
    return;
    }

  writeHeader(false,false);
  writeMenu(3,2);
  writeForm(sbhtm);
  printP(tr,td,"Banda",td_f,td);
  printP("desde",td_f,td," hasta   khz",td_f);
  printP(tr_f);
  for (byte i=0;i<MAX_BANDS;i++)
    {
    printP(tr);
    printP(td,conf.hamBandName[i],b,letram,td_f); 
    printcampoI(2*i, conf.hamBandRange[i][0], 10, true, true);
    printcampoI(2*i+1, conf.hamBandRange[i][1], 10, true, true);
    printP(tr_f);  
    }
  writeFooter(guardar, false);
  serversend200();
}

void calcSmeterScale()
{
  const float D0[16]={1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0,14.0,15.0,16.0};
  const float D1[16]={1.0,2.0,4.0,8.0,16.0,32.0,63.0,126.0,251.0,502.0,1600.0,5000.0,16000.0,50000.0,160000.0,500000.0};
  if (conf.modecalsmeter==0)
    {
    for (int i=1;i<15;i++)
      {
      float auxf=D0[i]/D0[15];
      conf.sMeterLevels[i]=((conf.sMeterLevels[15]-conf.sMeterLevels[0])*auxf) + conf.sMeterLevels[0];
      }
    }
  else  if(conf.modecalsmeter==1)
    {
    for (int i=1;i<15;i++)
      {
      float auxf=D1[i]/D1[15];
      conf.sMeterLevels[i]=((conf.sMeterLevels[15]-conf.sMeterLevels[0])*auxf) + conf.sMeterLevels[0];
      }
    }
}

void setupSmeterHTML()
{
  msg=vacio;
  mp=2;
  if (server.method()==HTTP_POST)
    {
    for (int i=0; i<server.args(); i++)
      {
      calcindices(i);
      if (param_number==35) { conf.modecalsmeter = server.arg(i).toInt();  }
      else
        {
        if (resto==0) conf.sMeterLevels[indice]=server.arg(i).toInt();
        else if (resto==1) server.arg(i).toCharArray(conf.smeterTit[indice], 4);
        }
      }
    calcSmeterScale();
    calSmeterReq=false;
    saveconf();
    sendOther(smehtm,-1);
    return;
    }

  writeHeader(false,false);
  writeMenu(3,6);
  writeForm(smehtm);

  printP(tr,td,"Min / Max",td_f);
  printPiP(td,minsmeter,td_f);
  printPiP(td,maxsmeter,td_f);
  printP(tr_f);
  
  printP(tr, td, "Modo");
  printcampoCB(35, conf.modecalsmeter, PSTR("Lineal"), PSTR("Real"), PSTR("Usuario"), true); 
  printP(td);
  printP(td_f,tr_f);

  printP(tr,td,"Valor",td_f,td);
  printP("ADC value",td_f,td,"Tit.",td_f,tr_f);
  for (byte i=0;i<16;i++)
    {
    mpi=mp*i;
    printP(tr,td);
    printI(i);
    printP(td_f); 
    if ((conf.modecalsmeter==0) || (i==0) || (i==15))
      {
      printcampoI(mpi, conf.sMeterLevels[i], 6, true, true);
      }
    else
      {
      printI(conf.sMeterLevels[i]);
      }
    printP(td);
    printcampoC(mpi+1, conf.smeterTit[i], 4, true, true, false,false);
    printP(td_f, tr_f);
    }
    
    writeFooter(guardar, false);
  serversend200();
}

void ICACHE_FLASH_ATTR setupNetHTML()
{
  if (!autOK()) { sendOther(loghtm,-1); return; }
  msg=vacio;
  mp=1;
  if (server.method()==HTTP_POST)
    {
    conf.staticIP=0;conf.autoWiFi=0;
    for (int i = 0; i < server.args(); i++)
      {
      calcindices(i);
      if (param_number>=0 && param_number <= 5) { server.arg(i).toCharArray(conf.EEmac[i], 3);  }
      else if (param_number>=6 && param_number <= 8)
        {
        conf.EEip[param_number-6]=server.arg(i).toInt();
        conf.EEgw[2]=conf.EEip[2];
        strcpy(hostraiz,itoa(conf.EEip[0],buff,10)); strcat(hostraiz, punto);
        strcat(hostraiz,itoa(conf.EEip[1],buff,10)); strcat(hostraiz, punto);
        strcat(hostraiz,itoa(conf.EEip[2],buff,10)); strcat(hostraiz, punto);
        }
      else if (param_number>=10 && param_number <= 13) { conf.EEmask[param_number-10] = server.arg(i).toInt(); }
      else if (param_number>=14 && param_number <= 17) { conf.EEgw[param_number-14] = server.arg(i).toInt();   }
      else if (param_number>=18 && param_number <= 21) { conf.EEdns[param_number-18] = server.arg(i).toInt();  }
      else if (param_number==22) { conf.webPort = server.arg(i).toInt();  }
      else if (param_number==41) { conf.wifimode = server.arg(i).toInt(); }
      else if (param_number==42) { server.arg(i).toCharArray(conf.ssidSTA, 20);}
      else if (param_number==43) { server.arg(i).toCharArray(conf.passSTA, 20); }
      //      else if (param_number == 44) {server.arg(i).toCharArray(conf.ssidAP,20);}
      else if (param_number==45) { server.arg(i).toCharArray(conf.passAP, 9); }
      else if (param_number==46) { conf.staticIP = server.arg(i).toInt(); }
      else if (param_number>=47 && param_number <= 50) { conf.EEdns2[param_number - 47] = server.arg(i).toInt(); }
      else if (param_number==56) { conf.canalAP = server.arg(i).toInt()+1; }
      else if (param_number==57) { conf.autoWiFi = server.arg(i).toInt(); }
      }
    //
    //    nAP = 0;
    saveconf();
    sendOther(snehtm,-1); return;
    }

  writeHeader(false,false);
  writeMenu(3, 3);
  writeForm(snehtm);

  printP(tr, td, "Auto WiFi", td_f, conf.autoWiFi==1 ? th : td);
  checkBox(57,conf.autoWiFi,false);
  printP(conf.autoWiFi?th_f:td_f,tr_f);
  
  printP(tr, td, t(Modo), b, td_f);
  printcampoCB(41, conf.wifimode, "OFF", sta, ap, apsta,true);
  printP(tr_f);

  // ssid
  printP(tr);
  ccell(routerssid);
  printP(td);
  printcampoC(42, conf.ssidSTA, 20, true, true, false,false);
  printP(href_i, comillas, scanap, comillas,mayor, b);
  printP(t(explorar), href_f, td_f, tr_f);

  printparCP(c(routerpass), 43, conf.passSTA, 20, false); 

  printP(tr);
  ccell(apssid);
  cell(conf.ssidAP);
  printP(tr_f);
  printparCP(c(appass), 45, conf.passAP, 9, false);
  printP(tr, td, t(canal), td_f, td);
  printP(c(Select_name),comillas);
  printIP(56, comillas);
  printP(mayor);
  for (byte j = 0; j < 13; j++)   { // canales
    pc(optionvalue);
    printPiP(comillas, j, comillas);
    if (conf.canalAP-1==j) printP(b, selected, ig, comillas, selected, comillas);
    printPiP(mayor, j+1, c(option_f));
  }
  printP(c(select_f), td_f, tr_f);

  espacioSep(2);
  printP(tr);
  ccell(MAC);
  printP(td);
  for (byte i=0; i<5; i++) printP(conf.EEmac[i]); printP(conf.EEmac[5]); 
  printP(td_f, tr_f);
  printP(tr, td, t(staticip), td_f, conf.staticIP ? th : td);
  checkBox(46,conf.staticIP,false);
  printP(conf.staticIP?th_f:td_f,tr_f);

  // print the current IP
  printP(tr, td, t(DIRIP), td_f, td);
  for (byte i=0; i<3; i++) { printI(conf.EEip[i]); printP(punto);  }  printI(conf.EEip[3]);
  printP(td_f, tr_f);

  printP(tr);
  ccell(tIP);
  printP(td);
  for (byte i=0; i<4; i++) printcampoI(6+i, conf.EEip[i],3,i!=3,false);
  printP(td_f, tr_f,tr);
  ccell(tmask);
  printP(td);
  for (byte i=0; i<4; i++) printcampoI(i+10, conf.EEmask[i], 3, true,false);
  printP(td_f, tr_f);
  
  printP(tr, td, c(ngateway), td_f, td);
  for (byte i=0; i<4; i++) printcampoI(i+14, i==2?conf.EEip[i]:conf.EEgw[i],3,i!=2,false);
  printP(td_f, tr_f);

  printP(tr,td);
  printP("DNS");
  printP(td_f,td);
  for (byte i=0; i<4; i++) printcampoI(i+18, conf.EEdns[i], 3, true,false);
  printP(td_f, tr_f);
  
  printP(tr, td, t(ippublica), td_f, td);
  printP(conf.myippub, td_f, tr_f);

  //  printP(tr,td,ttimeoutrem,td_f,td);
  //  printcampoL(53, timeoutrem, 5,true);
  //  printP(td_f,tr_f);
  //  printP(tr,td,c(ttimeoutNTP),td_f,td);
  //  printcampoL(54, conf.timeoutNTP, 5,true);
  //  printP(td_f,tr_f);

  printP(menor, barra, table, mayor, menor, c(tinput));
  printP(b, type, ig, comillas, submit, comillas);
  printP(b, tvalue, ig, comillas);
  printP(tguardar, comillas);
  printP(mayor, menor, barra, c(tinput), mayor);
  pc(form_f);
  printP(c(body_f), menor, barra);
  printP(thtml, mayor);
  serversend200();
}


void ICACHE_FLASH_ATTR systemHTML()
{
  msg =vacio;
  if (server.method()==HTTP_GET)
  {
    for (int i=0; i<server.args(); i++)
      {
      if (server.argName(i).compareTo(PSTR("si")) == 0)   {
        nAPact=server.arg(i-1).toInt();
        WiFi.SSID(nAPact).toCharArray(conf.ssidSTA, 20);
        saveconf();
        sendOther(snehtm,-1); return;
        }
      }
    sendOther(panelhtm, 0);
  }
}

void senddashtag(File f, int tag)
{ f.print(comillas); f.print(c(tag)); f.print(comillas); f.print(dp); }
void senddashint(File f, long data, boolean wcoma)
{ f.print(data); if (wcoma) f.print(coma); }
void senddashfloat(File f, float data, boolean wcoma)
{ f.print(comillas); f.print(data); f.print(comillas); if (wcoma) f.print(coma); }
void senddashbool(File f, boolean data, boolean wcoma)
{ if (data) f.print(c(ttrue)); else f.print(c(tfalse)); if (wcoma) f.print(coma); }
void senddashtext(File f, int ntext, boolean wcoma)
{ f.print(comillas); f.print(c(ntext)); f.print(comillas); if (wcoma) f.print(coma); }
void senddashtext(File f, PGM_P data, boolean wcoma)
{ f.print(comillas); f.print(data); f.print(comillas); if (wcoma) f.print(coma); }

void senddashpub(File f, int npin, boolean wcoma, PGM_P suf)
{
  strcpy(auxdesc,conf.mqttpath[0]); strcat(auxdesc,barra);
  for (byte j=1;j<6;j++) { if (strlen(conf.mqttpath[j])>0) { strcat(auxdesc,conf.mqttpath[j]); strcat(auxdesc,"/"); } }
  strcat(auxdesc,idpin[npin]); strcat(auxdesc,suf);
  f.print(comillas); f.print(auxdesc); f.print(comillas); if (wcoma) f.print(coma);
}

void senddashi2c(File f, byte rem, int npin, boolean wcoma, PGM_P suf)
{
  strcpy(auxdesc,conf.mqttpath[0]); strcat(auxdesc,barra);
  for (byte j=1;j<6;j++) { if (strlen(conf.mqttpath[j])>0) { strcat(auxdesc,conf.mqttpath[j]); strcat(auxdesc,"/"); }  }
  strcat(auxdesc,letrar); strcat(auxdesc,itoa(rem,buff,10)); strcat(auxdesc,suf);
  f.print(comillas); f.print(auxdesc); f.print(comillas); if (wcoma) f.print(coma);
}

void senddashtap(File f, int npin, boolean wcoma, PGM_P suf)
{
  strcpy(auxdesc,comillas);
  strcat(auxdesc,"app.publish");
  strcat(auxdesc,paren_i);strcat(auxdesc,comilla);
  strcat(auxdesc,conf.mqttpath[0]); strcat(auxdesc,barra);
  for (byte j=1;j<6;j++) { if (strlen(conf.mqttpath[j])>0) { strcat(auxdesc,conf.mqttpath[j]); strcat(auxdesc,"/"); } }
  strcat(auxdesc,idpin[npin]); strcat(auxdesc,suf);
  f.print(auxdesc); 
  f.print(comilla);f.print(coma);
  f.print(c(eventdatalast01));f.print(comillas); 
  if (wcoma) f.print(coma);
}

void senddashrec(File f)
{
  f.print(comillas);
  f.print(c(ifeventdata));
  f.print(c(evendatalast));
  f.print(comillas);f.print(coma);
}

boolean primero=true;

void sendcomunes(File f, byte i)
{
  if (!primero) f.print(coma);
  primero=false;
  f.print(llave_i);
  senddashtag(f, dashenableIntermediateState);  senddashbool(f, true, true); 
  senddashtag(f, dashenteredIntermediateStateAt);  senddashint(f, 1, true); 
  senddashtag(f, dashintermediateStateTimeout);  senddashint(f, 1, true); 
  senddashtag(f, dashqos);  senddashint(f, 0, true); 
  senddashtag(f, dashretained);  senddashbool(f, false, true); 
  senddashtag(f, dashjsOnReceive);  senddashtext(f, vacio, true); 
  senddashtag(f, dashjsonPath);  senddashtext(f, vacio, true);
  senddashtag(f, dashlastActivity);  senddashint(f, 0, true);
  senddashtag(f, dashupdateLastPayloadOnPub);  senddashbool(f, true, true); 
  senddashtag(f, dashjsBlinkExpression);  senddashtext(f, vacio, true); 
  senddashtag(f, dashenablePub);  senddashbool(f, true, true); 
  senddashtag(f, dashjsOnTap);  senddashtext(f, vacio, true); 
  senddashtag(f, dashjsOnDisplay);  senddashtext(f, vacio, true); 
  senddashtag(f, dashid);  senddashint(f, i+1, true);
  senddashtag(f, dashlongId);  senddashint(f, i+1 , true); 
}

boolean ICACHE_FLASH_ATTR mqttreconnect() 
  { 
  String clientID="ubitx-";
  for (byte i=0;i<6;i++) clientID += conf.EEmac[i];
  if (PSclient.connect(clientID.c_str())) 
    { PSclient.publish("ubitx/g","conectado"); }
  return PSclient.connected(); 
  }

void createdashfile()
{
  File f=SPIFFS.open(filedash,letraw);
  if (f)  
    { 
    primero=true;
    f.print(corchete_i); 
    for (int i=0;i<31;i++)     
      { 
      if (i<=30) 
        { sendcomunes(f,i); }        
      if (i<=30)      // señales locales
        {
        if (i<=7)     // sondas
          {
          senddashtag(f, dashlastPayload);  senddashfloat(f, 0.0, true);
          senddashtag(f, dashmainTextSize);  senddashtext(f, medium,true); 
          senddashtag(f, dashtextcolor);  senddashint(f, 0x334CFF, true); 
          senddashtag(f, dashprefix);  senddashtext(f, vacio, true); 
          senddashtag(f, dashtopicPub); senddashpub(f, i, true,(i<=2)?tset:vacio); 
          senddashtag(f, dashpostfix);  senddashtext(f, i<=2?grados:vacio, true); 
          senddashtag(f, dashtype); senddashint(f, 1, true); 
          senddashtag(f, dashtopic); senddashpub(f, i, true, vacio); 
         // senddashtag(f, dashname); senddashlocal(f, i, false); 
          f.print(llave_f); 
          }
        else if (i<=11)     // entradas digitales
          {
          senddashtag(f, dashlastPayload);  senddashtext(f, cero, true);
          senddashtag(f, dashoffcolor);  senddashint(f, -1,true); 
          senddashtag(f, dashoncolor);  senddashint(f, -192,true); 
          senddashtag(f, dashpayloadoff);  senddashtext(f, cero,true); 
          senddashtag(f, dashpayloadon);  senddashtext(f, uno,true); 
          senddashtag(f, dashtopicPub); senddashpub(f, i, true, tstate); 
          senddashtag(f, dashtype); senddashint(f, 2, true); 
          senddashtag(f, dashtopic); senddashpub(f, i, true, vacio); 
       //   senddashtag(f, dashname); senddashlocal(f, i, false); 
          f.print(llave_f); 
          }
        else if (i<=19)   // salidas digitales
          { 
          senddashtag(f, dashlastPayload);  senddashtext(f, cero, true);
          senddashtag(f, dashoffcolor);  senddashint(f, -1,true); 
          senddashtag(f, dashoncolor);  senddashint(f, -192,true); 
          senddashtag(f, dashpayloadoff);  senddashtext(f, cero,true); 
          senddashtag(f, dashpayloadon);  senddashtext(f, uno,true); 
          senddashtag(f, dashiconoff);  senddashtext(f, i<=5?ic_radio_button_unchecked:ic_settings_poweroff,true); 
          senddashtag(f, dashtopicPub); senddashpub(f, i, true, tset); 
          senddashtag(f, dashiconon);  senddashtext(f, ic_settings_poweron,true); 
          senddashtag(f, dashtype); senddashint(f, 2, true); 
          senddashtag(f, dashtopic); senddashpub(f, i, true, vacio); 
       //   senddashtag(f, dashname); senddashlocal(f, i, false); 
          f.print(llave_f); 
          }
        else if (i<=22)        // id, ip, ipp
          {
          senddashtag(f, dashlastPayload);  senddashint(f, 0, true);
//          senddashtag(f, dashmainTextSize);  senddashtext(f, small,true); 
          senddashtag(f, dashmainTextSize);  senddashtext(f, "SMALL",true); 
          senddashtag(f, dashtextcolor);  senddashint(f, -192, true); 
          senddashtag(f, dashprefix);  senddashtext(f, vacio, true); 
          senddashtag(f, dashtopicPub); senddashpub(f, i, true, tstate);  
          senddashtag(f, dashpostfix); senddashtext(f, vacio,true);
          senddashtag(f, dashtype); senddashint(f, 1, true); 
          senddashtag(f, dashname); senddashtext(f, i==22?maindevice:i==23?localip:publicip,true); 
          senddashtag(f, dashtopic); senddashpub(f, i, false, vacio);
          f.print(llave_f); 
          }
        }
      }
    f.print(corchete_f);
    f.close();   
    }
  // publicar datos
  if (conf.mqttenabled) {
    File f=SPIFFS.open(filedash,"r");
    if (f)  {
      if (!PSclient.connected()) 
        mqttreconnect();
      if (PSclient.beginPublish("conuco/dash", f.size(), false))
        {
        char auxb[1];
        for (int i=0;i<f.size();i++) { f.readBytes(auxb,1); PSclient.write(auxb[0]); }
        PSclient.endPublish();
        }
      f.close();    }  }    
}

void ICACHE_FLASH_ATTR setupNetServHTML()
{
  msg=vacio;
  mp=1;
  if (server.method() == HTTP_POST)
    {
    conf.ftpenable=0; conf.debugenable=0; conf.tcpenable=0;
    conf.udpenable=0;  conf.wsenable=0;  conf.seripenable=0;
    conf.webenable=0;
    conf.mqttenabled=0; conf.iottweetenable=0; conf.iftttenabled=0;
 
    for (int i=0; i<server.args(); i++)
      {
      calcindices(i);
      if (param_number==0) { server.arg(i).toCharArray(conf.hostmyip, 30); }
      else if (param_number==21) { conf.ftpenable=server.arg(i).toInt();  } // ftp server enabled      }
      else if (param_number==22) { conf.debugenable=server.arg(i).toInt();  } // ftp server enabled      }
      else if (param_number==23) { conf.tcpenable=server.arg(i).toInt();  } // ftp server enabled      }
      else if (param_number==24) { conf.udpenable=server.arg(i).toInt();  } // ftp server enabled      }
      else if (param_number==25) { conf.wsenable=server.arg(i).toInt();  } // ftp server enabled      }
      else if (param_number==26) { conf.seripenable=server.arg(i).toInt();  } // ftp server enabled      }
      else if (param_number==27) { conf.webenable=server.arg(i).toInt();  } // ftp server enabled      }
      else if (param_number==2) { conf.iftttenabled=server.arg(i).toInt(); } // enable IFTTT
      else if (param_number==3) { server.arg(i).toCharArray(conf.iftttkey, 30); }
      else if (param_number==6) { conf.iottweetenable=server.arg(i).toInt();  } // iottweet enabled      }
      else if (param_number==7) { server.arg(i).toCharArray(conf.iottweetuser, 10); }
      else if (param_number==8) { server.arg(i).toCharArray(conf.iottweetkey, 15);  }
      else if (param_number==9) { conf.mqttenabled=server.arg(i).toInt(); } // enable MQTT
      else if (param_number==10) { server.arg(i).toCharArray(conf.mqttserver, 40);  }
      else if (param_number>=11) { server.arg(i).toCharArray(conf.mqttpath[param_number-11], 10);  }
      }
    saveconf();
    createdashfile();
    sendOther(snshtm,-1);
    return;
    }

  writeHeader(false,false);
  writeMenu(3, 4);
  writeForm(snshtm);

  printP(tr);
  tcell(ippubserver);
  printP(td, td_f);
  printColspan(2);
  printcampoC(0, conf.hostmyip, 30, true, true, false,false);
  printP(td_f, tr_f);

  printP(tr);
  tcell(tftpserver);
  checkBox(21, conf.ftpenable,true);
  printColspan(2);
  printP("Port "); printI(conf.ftpPort);
  printP(td_f,tr_f);

  printP(tr);
  tcell(tdebugserver);
  checkBox(22, conf.debugenable,true);
  printColspan(2);
  printP("Port "); printI(conf.debugPort);
  printP(td_f,tr_f);

  printP(tr);
  tcell(ttcpserver);
  checkBox(23, conf.tcpenable,true);
  printColspan(2);
  printP("Port "); printI(conf.tcpPort);
  printP(td_f,tr_f);

  printP(tr);
  tcell(tudpserver);
  checkBox(24, conf.udpenable,true);
  printColspan(2);
  printP("Port "); printI(conf.udpPort);
  printP(td_f,tr_f);

  printP(tr);
  tcell(twsserver);
  checkBox(25, conf.wsenable,true);
  printColspan(2);
  printP("Port "); printI(conf.wsPort);
  printP(td_f,tr_f);

  printP(tr);
  tcell(tseripserver);
  checkBox(26, conf.seripenable,true);
  printColspan(2);
  printP(tr_f);

  printP(tr);
  tcell(twebserver);
  checkBox(27, conf.webenable,true);
  printColspan(2);
  printP("Port "); printI(conf.webPort);
  printP(td_f,tr_f);

  printP(tr, td, href_i, comillas);
  pc(thttps);
  pc(iftttcom);
  printP(comillas, b, c(newpage), mayor);
  pc(ifttt);
  printP(barraesp,c(Key), href_f, td_f, conf.iftttenabled?th:td);
  checkBox(2, conf.iftttenabled,false);
  printP(conf.iftttenabled?th_f:td_f);
  printColspan(2);
  printcampoC(3, conf.iftttkey, 30, true, true, false,false);
  printP(td_f, tr_f);

  printP(tr, td, href_i, comillas);
  pc(thttp);
  pc(iottweetcom);
  printP(comillas, b, c(newpage), mayor);
  pc(iottweett);
  printP(barraesp, t(usuario), barraesp);
  printP(c(Key), href_f, td_f, conf.iottweetenable == 1 ? th : td);
  checkBox(6, conf.iottweetenable,false);
  printP(conf.iottweetenable==1?th_f:td_f);
  printcampoC(7, conf.iottweetuser, 10, true, true, false,true);
  printcampoC(8, conf.iottweetkey, 15, true, true, false,true);
  printP(tr_f);

  printP(tr,td,c(mqtt),b);
  printP(c(tserver),td_f);
  printP(conf.mqttenabled==1?th:td);
  checkBox(9, conf.mqttenabled,false);
  printP(td_f);
  printColspan(2);
  printcampoC(10, conf.mqttserver, 40, true, true, false,false);
  printP(conf.mqttenabled==1?th_f:td_f,tr_f);
  
  for (byte i=0;i<3;i++)
    {
    printP(tr);
    printColspan(2);
    if (i==0) { printP(c(mqtt),b); pc(tpath); }
    printP(td_f,td);
    printcampoC(11+(i*2), conf.mqttpath[i*2], 10, true, true, false,false);
    printP(barra,td_f,td);
    printcampoC(12+(i*2), conf.mqttpath[i*2+1], 10, true, true, false,false);
    printP(barra,td_f,tr_f); 
    }
  writeFooter(guardarexportar, false);
  serversend200();
}

void ICACHE_FLASH_ATTR setupSegHTML()
{
  if (!autOK()) { sendOther(loghtm,-1); return; }
  msg=vacio;
  mp=1;
  char passDevtemp1[20];
  char passDevtemp2[20];
  if (server.method()==HTTP_POST)
    {
    conf.usepassDev = 0;
    for (int i=0; i<server.args(); i++)
      {
      calcindices(i);
      if (param_number==0) conf.usepassDev = server.arg(i).toInt();
      else if (param_number==1) server.arg(i).toCharArray(conf.userDev, 20);
      else if (param_number==2) server.arg(i).toCharArray(passDevtemp1, 20);
      else if (param_number==3) server.arg(i).toCharArray(passDevtemp2, 20);
      }
    if (conf.usepassDev)    // contraseña activa
      {
      if (strcmp(passDevtemp1, passDevtemp2)==0)   // si coinciden ambas password se almacena
        strcpy(conf.passDev, passDevtemp1);
      else
        conf.usepassDev=0; // no se guarda y se desactiva contraseña
      }
    else    // contraseña NO activa
      if (strcmp(passDevtemp1, conf.passDev) != 0)  // si no se da la contraseña correcta, no se desactiva
        conf.usepassDev = 1;
    saveconf();
    sendOther(sshtm,-1); return;
    }

  /////////////////////
  writeHeader(false,false);
  writeMenu(4, 5);
  writeForm(sshtm);

  printP(tr, td, t(autenticacion), td_f, conf.usepassDev ? th : td);
  checkBox(0, conf.usepassDev,false);
  if (conf.usepassDev) printP(th_f, tr_f); else printP(td_f, tr_f);
  printparCP(t(usuario), 1, conf.userDev, 20, false);
  printparCP(t(contrasena), 2, "", 20, true);
  printparCP(t(confcontrasena), 3, "", 20, true);
  writeFooter(guardar, false);
  serversend200();
}

void ICACHE_FLASH_ATTR scanapHTML()
{
  nAPact=0;
  nAP=WiFi.scanNetworks(false, false);
  msg=vacio;
  writeHeader(false,false);
  printP(menor,table, b);
  printP(c(tclass), ig, tnormal, mayor);
  printP(tr,td,"nAP",td_f,td);
  printI(nAP);
  printP(td_f,tr_f);
  for (int i=0; i<nAP; i++)
    {
    WiFi.SSID(i).toCharArray(auxchar, 20);
    printP(tr, td);
    printP(href_i, syhtm,interr,letran,ig);
    printI(i);
    printP(amper, letras,letrai, ig, cero, mayor);
    printP(auxchar, td_f, td);
    printI(WiFi.RSSI(i));
    printP(b, c(dbm), td_f, tr_f);
    }
  printP(menor, barra, table, mayor);  
  printP(c(body_f), menor, barra);
  printP(thtml, mayor);
  serversend200();
}

void initupdateserver()
{
  server.on("/firm", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", serverIndex);
  });
  server.on("/update", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.send(HTTP_CODE_OK, "text/plain", (Update.hasError())?"FAIL":"OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial2.setDebugOutput(true);
      s2("Update: "); s2(upload.filename.c_str());
      clearTFT();
      tft.setTextSize(2);
      tft.drawString("Actualizando firmware...",0,20);
      tft.drawString("No apague el equipo",0,40);
      if (!Update.begin()) { //start with max available size
        Update.printError(Serial2);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial2);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
        { s2("Update Success: Rebooting..."); s2(upload.totalSize); s2(crlf); }
      } else {
        Update.printError(Serial);
      }
      Serial2.setDebugOutput(false);
    }
  });
}

void ICACHE_FLASH_ATTR espsysHTML()
{
  msg=vacio;
  writeHeader(false,false);
  writeMenu(4, 4);
  printP(menor,table, b);
  printP(c(tclass), ig, tnormal, mayor);
  printP(tr, td, c(Time), td_f, td); printtiempo(millis() / 1000); printP(td_f, tr_f);
//  printP(tr, td, c(Chipid), td_f, td); printL(system_get_chip_id()); printP(td_f, tr_f);
//  printP(tr, td, c(ChipFlashSize), td_f, td);  printL(ESP.getFlashChipRealSize()); printP(td_f, tr_f);
//  printP(tr, td, c(Chipspeed), td_f, td);  printL(ESP.getFlashChipSpeed()); printP(td_f, tr_f);
//  printP(tr, td, c(sdkversion), td_f, td); printP(system_get_sdk_version()); printP(td_f, tr_f);
//  printP(tr, td, c(vdd33), td_f, td); printL(system_get_vdd33()); printP(td_f, tr_f);
//  printP(tr, td, c(adc_read), td_f, td); printL(system_adc_read()); printP(td_f, tr_f);
//  printP(tr, td, c(boot_version), td_f, td); printL(system_get_boot_version());   printP(td_f, tr_f);
//  printP(tr, td, c(Time), td_f, td); printI(conf.wifimode); printP(td_f, tr_f);
//  printP(tr, td, c(boot_mode), td_f, td); printI(system_get_boot_mode());   printP(td_f, tr_f);
//  printP(tr, td, c(userbin_addr), td_f, td); printL(system_get_userbin_addr());   printP(td_f, tr_f);
//  printP(tr, td, c(cpu_freq), td_f, td); printL(system_get_cpu_freq());   printP(td_f, tr_f);
//  printP(tr, td, c(flash_get_id), td_f, td); printL(spi_flash_get_id());   printP(td_f, tr_f);
//  printP(tr, td, c(opmode), td_f, td); printI(wifi_get_opmode());   printP(td_f, tr_f);
//  printP(tr, td, c(opmode_default), td_f, td); printI(wifi_get_opmode_default());   printP(td_f, tr_f);
//  printP(tr, td, c(auto_connect), td_f, td); printI(wifi_get_opmode());   printP(td_f, tr_f);
//  printP(tr, td, c(sleep_type), td_f, td); printI(wifi_get_sleep_type());   printP(td_f, tr_f);
//  printP(tr, td, c(broadcast_if), td_f, td); printI(wifi_get_broadcast_if());   printP(td_f, tr_f);
//  printP(tr, td, c(user_limit_rate_mask), td_f, td); printL(wifi_get_user_limit_rate_mask());   printP(td_f, tr_f);
//  printP(tr, td, c(channelt), td_f, td); printI(wifi_get_channel());   printP(td_f, tr_f);
//  printP(tr, td, c(dhcps_status), td_f, td); printI(wifi_softap_dhcps_status());   printP(td_f, tr_f);
//  printP(tr, td, c(phy_mode), td_f, td); printI(wifi_get_phy_mode());   printP(td_f, tr_f);
  if (conf.wifimode!=1)
    {
//    printP(tr, td, c(connect_status), td_f, td); printI(wifi_station_get_connect_status());   printP(td_f, tr_f);
//    printP(tr, td, c(hostnamet), td_f, td); printP(wifi_station_get_hostname());   printP(td_f, tr_f);
//    printP(tr, td, c(station_num), td_f, td); printI(wifi_softap_get_station_num());   printP(td_f, tr_f);
//    printP(tr, td, c(get_current_ap_id), td_f, td); printI(wifi_station_get_current_ap_id());   printP(td_f, tr_f);
    }
  printP(menor, barra, table, mayor);  
  printP(c(body_f), menor, barra);
  printP(thtml, mayor);
  serversend200();
}

void ICACHE_FLASH_ATTR loginHTML()
{
  msg=vacio;
  if (server.method()==HTTP_POST)
    {
    if (server.hasArg("0") && server.hasArg("1"))
      {
      if ((server.arg(0)==conf.userDev) && (server.arg(1)==conf.passDev))
        { setCookie(1);  return; }
      }
    }
  if (server.hasArg("DISCONNECT")) { setCookie(0); return; }

  writeHeader(false,false);
  pc(body_i);
  pc(form_action);
  printP(loghtm,comillas,b);
  pc(Form_post);
  printP(menor,table,b);
  printP(c(tclass), ig, tnormal, mayor);
  printparCP(t(usuario), 0, conf.userDev, 20, false);
  printparCP(t(contrasena), 1, "", 20, true);
  printP(menor, barra, table, mayor);
  printP(menor, c(tinput), b, type, ig, comillas);
  printP(submit, comillas, b, tvalue, ig, comillas);
  printP(tguardar, comillas, mayor);
  printP(menor, barra, c(tinput), mayor);
  pc(form_f);
  pc(body_f);
  printP(menor, barra, thtml, mayor);
  serversend200();
}

void initFab(void)
{
  s2(t(reiniciando)); s2(b); s2(t(fabrica)); s2(crlf);
  initConf();                  // variables de estructura Conf
  resetWiFi();                 // WiFi y Red
  saveconf();
}

void ICACHE_FLASH_ATTR resetHTML()
{
  msg=vacio;
  if (server.method() == HTTP_POST)
    {
    for (int i=0; i<server.args(); i++)
      {
      if (server.argName(i).toInt()==0)
        {
        int idaccion = server.arg(i).toInt();
        if (idaccion > 0)
          {
          writeHeader(false,false);
          server.sendHeader("Connection", "close");
          server.sendHeader("Access-Control-Allow-Origin", "*");
          server.send(HTTP_CODE_OK, "text/html", espere);
          if (idaccion==1)      { ESP.restart(); }
          else if (idaccion==2) { ESP.restart(); }
          else if (idaccion==3) { resetWiFi();  }
          else if (idaccion==4) { initFab(); ESP.restart(); }
          }
        }
      }
    return;
    }
  writeHeader(false,false);
  writeMenu(4, 2);
  writeForm(rshtm);
  printP(tr);
  printP(td, treset, barra);
  printP(trestart, td_f);
  printcampoCB(0, 0, nohacernada, treset, trestart, tresetwifi,tresetfab,true);
  printP(tr_f);
  writeFooter(ejecutar, false);
  serversend200();
}

void handleStateTime() { msg=vacio; HtmlGetStateTime(); serversend200();  }
void handleStateData0() { msg=vacio; HtmlGetStateData(0); serversend200(); }
void handleStateData1() { msg=vacio; HtmlGetStateData(1); serversend200(); }
void handleStateData2() { msg=vacio; HtmlGetStateData(2); serversend200(); }
void handleStateData3() { msg=vacio; HtmlGetStateData(3); serversend200(); }
void handleStateData4() { msg=vacio; HtmlGetStateData(4); serversend200(); }
void handleStateData5() { msg=vacio; HtmlGetStateData(5); serversend200(); }
void handleStateData6() { msg=vacio; HtmlGetStateData(6); serversend200(); }
void handleStateData7() { msg=vacio; HtmlGetStateData(7); serversend200(); }

void handleStateDataf0() { msg=vacio; HtmlGetStateData(0); serversend200(); }
void handleStateDataf1() { msg=vacio; HtmlGetStateData(1); serversend200(); }
void handleStateDataf2() { msg=vacio; HtmlGetStateData(2); serversend200(); }
void handleStateDataf3() { msg=vacio; HtmlGetStateData(3); serversend200(); }
void handleStateDataf4() { msg=vacio; HtmlGetStateData(4); serversend200(); }
void handleStateDataf5() { msg=vacio; HtmlGetStateData(5); serversend200(); }
void handleStateDataf6() { msg=vacio; HtmlGetStateData(6); serversend200(); }
void handleStateDataf7() { msg=vacio; HtmlGetStateData(7); serversend200(); }

void initHTML()
{
  server.onNotFound (htmlNotFound);
  initupdateserver();
  server.on("/sy", systemHTML);
  /**if (!checkfiles()) { server.on("/", filesHTML); return;  }*/
  server.on("/f", filesHTML);
  server.on("/", indexHTML);
  server.on("/p", panelHTML);
  server.on("/cw", setupCWHTML);
  server.on("/sd", setupDevHTML);
  server.on("/sm", setupMemHTML);
  server.on("/sne", setupNetHTML);
  server.on("/sc", scanapHTML);
  server.on("/sns", setupNetServHTML);
  server.on("/es", espsysHTML);
  server.on("/l", loginHTML);
  server.on("/ss", setupSegHTML);
  server.on("/rs", resetHTML);
  server.on("/sb", setupBandHTML);
  server.on("/sme", setupSmeterHTML);
  server.on("/sio", setupioHTML);
  server.on("/dw", downloadHTML);
/*  server.on("/j", jsonHTML);
  server.on("/jc", jsonconfHTML);
  server.on("/je", jsonextHTML);
  server.on("/on", onCmd);
  server.on("/of", offCmd);**/
  /**server.on("/rj", rjsonHTML);
  server.on("/rjc", rjsonconfHTML);
  server.on("/rf", setuprfHTML);
  server.on("/sbp", setupbyPanelHTML);
  server.on("/sdr", setupDevRemHTML);
  server.on("/sdrio", setupDevRemioHTML);
  server.on("/se", setupEscHTML);
  server.on("/sf", setupFecHTML);
  server.on("/sp", setupPanelHTML);
  server.on("/spr", setupPrgHTML);
  server.on("/sr", setupremHTML);
  server.on("/s150", setupdev150HTML);
  server.on("/ssr", setupsalremHTML);
  server.on("/sse", setupSemHTML);
  server.on("/sv", setupEveHTML);
  server.on("/swc", setupWebCallHTML);
  server.on("/t", termostatoHTML);
  server.on("/v", voicecommandHTML);
  **/
  
  server.on("/l0", handleStateData0);       // data
  server.on("/l1", handleStateData1);       // data
  server.on("/l2", handleStateData2);       // data
  server.on("/l3", handleStateData3);       // data
  server.on("/l4", handleStateData4);       // data
  server.on("/l5", handleStateData5);       // data
  server.on("/l6", handleStateData6);       // data
  server.on("/l7", handleStateData7);       // data
  
  server.on("/f0", handleStateDataf0);       // data fast
  server.on("/f1", handleStateDataf1);       // data fast
  server.on("/f2", handleStateDataf2);       // data fast
  server.on("/f3", handleStateDataf3);       // data fast
  server.on("/f4", handleStateDataf4);       // data fast
  server.on("/f5", handleStateDataf5);       // data fast
  server.on("/f6", handleStateDataf6);       // data fast
  server.on("/f7", handleStateDataf7);       // data fast
  server.on("/tt", handleStateTime);         // Pie
}

int checkInternet()
{
  msg=vacio;
  printP(barra);
  HTTPClient http;
  Serial2.print("hostmyip:"); Serial2.println(conf.hostmyip);
  http.begin("www.google.com", 80, msg);
  http.setConnectTimeout(2000);
  Serial2.print("checkInternet ");Serial2.print("host:");Serial2.print("www.google.com");
  Serial2.print(":");Serial2.print(80); Serial2.print(msg);Serial2.print("=");
  int httpCode=http.GET();
  Serial2.print(" ");Serial2.println(httpCode);
  http.end();
  msg=vacio;
  return httpCode;
}
