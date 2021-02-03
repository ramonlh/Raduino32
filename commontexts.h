////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////  COMUNES   //////////////////////////////////////////////////////////
    
PGM_P(htmlHead_3)=  
    "<meta name=\"viewport\" content=\"width=device-width initial-scale=1\"/>"
    "<meta http-equiv=\"Content-Type\" content=\"text/html charset=ISO-8859-1\"/>"
    
    "<style type=\"text/css\"> a:link { text-decoration:none; }"    // quita subrayado de enlaces
    
    "table.m {font-family:Verdana;font-size:11pt;border-collapse:collapse;}"     
    "table.m th {border-width:2px;padding:8px;border-style:solid;border-color:#666666;background-color:#FDFF9A;}"
    "table.m td {border-width:2px;padding:8px;border-style:solid;border-color:#666666;background-color:#dedede;}"

    // usado en tablas de panel principal
    "table.p {font-family:Verdana;font-size:9pt;border-collapse:collapse;color:#FFFFFF;text-align:left;}"      
    "table.p th {border-color:#666666;border-width:2px;padding:8px;border-style:solid;background-color:#FFFF00;}"
    "table.p td {border-color:#666666;border-width:2px;padding:8px; border-style:solid;font-color:#000000;background-color:#515772;}"

    // usado en tablas de configuración, programación etc NO CENTRADO
    "table.n {font-family:Verdana;font-size:9pt;border-collapse:collapse;text-align:left;}"      
    "table.n th {border-style:solid;border-color:#666666;border-width:2px;padding:4px;background-color:#FFFF00;}"
    "table.n td {border-style:solid;border-color:#666666;border-width:2px;padding:4px;background-color:#DEDEDE;}"
    "</style>";

// textos html NO MODIFICAR

PGM_P(hrefon)="\"on?p=";
PGM_P(json)="j";
PGM_P(jsonconf)="jc";
PGM_P(jsonext)="je";

PGM_P(td)="<td>"; 
PGM_P(td_f)="</td>"; 
PGM_P(th)="<th>";  
PGM_P(th_f)="</th>";  
PGM_P(tr)="<tr>";  
PGM_P(tr_f)="</tr>";   
PGM_P(tmenu)="\"m\"";
PGM_P(tnormal)="\"n\"";
PGM_P(tpanel)="\"p\"";

PGM_P(crlf)="\r\n";  
PGM_P(ON)="ON"; 
PGM_P(OFF)="OFF";
PGM_P(br)="<br />";
PGM_P(size_i)="\" size=\"";  
PGM_P(comilla)="'";
PGM_P(comillas)="\"";
PGM_P(comillascierre)="\"/>";
PGM_P(snehtm)="sne";
PGM_P(snshtm)="sns";

PGM_P(parenguion)=")-";
PGM_P(mayorparen)=">(";
PGM_P(type)="type";
PGM_P(panelhtm)="p";
PGM_P(sshtm)="ss";
PGM_P(srlhtm)="srl";
PGM_P(slkhtm)="sr";
PGM_P(sremhtm)="ssr";
PGM_P(sbhtm)="sb";
PGM_P(sdhtm)="sd";
PGM_P(cwhtm)="cw";
PGM_P(smhtm)="sm";
PGM_P(smehtm)="sme";
PGM_P(sphtm)="sp";
PGM_P(sbphtm)="sbp";
PGM_P(rfhtm)="rf";
PGM_P(rohtm)="ro";
PGM_P(sdremhtm)="sdr";
PGM_P(sdremiohtm)="sdrio";
PGM_P(suhtm)="firm";
PGM_P(rshtm)="rs";
PGM_P(seschtm)="se";
PGM_P(ssechtm)="ssec";
PGM_P(sprghtm)="spr";
PGM_P(ssehtm)="sse";
PGM_P(syhtm)="sy";
PGM_P(swchtm)="swc";
PGM_P(espsyshtm)="es";
PGM_P(fileshtm)="f";
PGM_P(sfhtm)="sf";
PGM_P(loghtm)="l";
PGM_P(scanap)="sc"; 
PGM_P(svhtm)="sv";
PGM_P(siohtm)="sio";
PGM_P(siphtm)="sip";
PGM_P(termhtm)="t";
PGM_P(Off)="Off";
PGM_P(off)="of";
PGM_P(On)="On";
PGM_P(on)="on";
PGM_P(n)="n";
PGM_P(href_f)="</a>";

PGM_P(amper)="&amp;";
PGM_P(ampersand)="&";
PGM_P(login)="l";
PGM_P(ori)="ori";
PGM_P(rjson)="rj";
PGM_P(barrarjc)="/rjc";
PGM_P(igualp)="?p=";

PGM_P(letraa)="a";
PGM_P(letraA)="A";
PGM_P(letrab)="b";
PGM_P(letraB)="B";
PGM_P(letrac)="c";
PGM_P(letraC)="C";
PGM_P(letrad)="d";
PGM_P(letraD)="D";
PGM_P(letrae)="e";
PGM_P(letraf)="f";
PGM_P(letrag)="g";
PGM_P(letrah)="h";
PGM_P(letraH)="H";
PGM_P(letrai)="i";
PGM_P(letraJ)="J";
PGM_P(letral)="l";
PGM_P(letraL)="L";
PGM_P(letrak)="k";
PGM_P(letram)="m";
PGM_P(letraM)="M";
PGM_P(letran)="n";
PGM_P(letrao)="o";
PGM_P(letrap)="p";
PGM_P(letraP)="P";
PGM_P(letrar)="r";
PGM_P(letraR)="R";
PGM_P(letras)="s";
PGM_P(letraS)="S";
PGM_P(letrat)="t";
PGM_P(letraT)="T";
PGM_P(letrau)="u";
PGM_P(letrav)="v";
PGM_P(letraV)="V";
PGM_P(letraw)="w";
PGM_P(letraX)="X";
PGM_P(letray)="y";
PGM_P(letraZ)="Z";
PGM_P(cero)="0";
PGM_P(uno)="1";
PGM_P(dos)="2";
PGM_P(tres)="3";
PGM_P(cuatro)="4";
PGM_P(cinco)="5";
PGM_P(seis)="6";
PGM_P(siete)="7";
PGM_P(b)=" ";
PGM_P(coma)=",";
PGM_P(barra)="/";
PGM_P(barraesp)="/ ";
PGM_P(ig)="=";
PGM_P(menor)="<";
PGM_P(mayor)=">";
PGM_P(mayoroigual)=">=";          
PGM_P(menoroigual)="<=";          
PGM_P(dp)=":";
PGM_P(paren_i)="(";
PGM_P(paren_f)=")";
PGM_P(llave_i)="{";
PGM_P(llave_f)="}";
PGM_P(corchete_i)="[";
PGM_P(corchete_f)="]";
PGM_P(punto)=".";
PGM_P(puntoycoma)=";";
PGM_P(guion)="-";
PGM_P(subray)="_";  
PGM_P(interr)="?";          
PGM_P(aster)="*";     
PGM_P(porcen)="%";
PGM_P(puntossus)="...";
PGM_P(paramn)="?n=";
PGM_P(vacio)="";
PGM_P(amas)="a+";
PGM_P(rmas)="r+";
PGM_P(wmas)="w+";
PGM_P(grados)="ºC";
PGM_P(celsius)="&#8451;";
PGM_P(symsum)="&#8721;";
PGM_P(symhoz)="&#9773;";
PGM_P(symyes)="&#10004;";
PGM_P(symnot)="&#10006;";
PGM_P(tset)="/set";
PGM_P(tstate)="/state";

//////  No convertibles
PGM_P(applicationjson)="application/json; charset=utf-8";
PGM_P(contenttype)="Content-Type";
PGM_P(urlNTPserverpool)="europe.pool.ntp.org";
PGM_P(closet)="close";
PGM_P(t12341234)="12341234";
PGM_P(i2c)="I2C";
PGM_P(diginput)="Dig. Input";
PGM_P(submit)="submit";
PGM_P(rfon)="rfon";
PGM_P(rfoff)="rfoff";
PGM_P(trestart)="Restart";
PGM_P(nohacernada)="No hacer nada";
PGM_P(treset)="Reset";
PGM_P(tresetwifi)="Reset WiFi";
PGM_P(tresetfab)="Reset Fábrica";
PGM_P(modbust)="ModBus";
PGM_P(textplain)="text/plain";
PGM_P(tPOST)="POST";
PGM_P(PUT)="PUT";
PGM_P(table)="table";
PGM_P(texttext)="text";
PGM_P(texthtml)="text/html";
PGM_P(attachfilename)="attachment; filename=";
PGM_P(espere)="<META http-equiv=\"refresh\" content=\"15; URL=/\">OK. Espere...";
PGM_P(apsta)="AP+STA";
PGM_P(ap)="AP";
PGM_P(sta)="STA";
PGM_P(href_i)="<a href=";
PGM_P(dhtt)="DHT";
PGM_P(ONOFF)="ON/OFF";
PGM_P(OFFON)="OFF/ON";
PGM_P(selected)="selected";
PGM_P(checked)="checked";
PGM_P(tvalue)="value";
PGM_P(tguardar)="Guardar";
PGM_P(tejecutar)="Ejecutar";
PGM_P(dataType)="dataType";
PGM_P(ultimovalor)="Last value";
PGM_P(intro)="INTRO";
PGM_P(esc)="ESC";
PGM_P(ups)="PgUp";
PGM_P(downs)="PgDn";
PGM_P(lefts)="LF";
PGM_P(rigths)="RT";

///////////////////////////////

// json codes
PGM_P(aa)="aa";
PGM_P(DV)="DV";
PGM_P(ua0)="ua0";
PGM_P(tel0)="te0";
PGM_P(tel1)="te1";
PGM_P(tsl0)="ts0";
PGM_P(tsl1)="ts1";
PGM_P(MJ)="MJ";
PGM_P(al)="al";
PGM_P(ro)="ro";
PGM_P(thead)="head";
PGM_P(thtml)="html";
PGM_P(io)="I/O";
PGM_P(ID)="ID";
PGM_P(ok)="OK";
PGM_P(ERROR)="ERROR";

