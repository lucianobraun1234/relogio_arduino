
#include <Wire.h>  //INCLUSÃƒO DE BIBLIOTECA
#include <LiquidCrystal_I2C.h> //INCLUSÃƒO DE BIBLIOTECA

#include <EEPROM.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); //FUNÃ‡ÃƒO DO TIPO "LiquidCrystal_I2C"
 #include <DHT.h> 
#define DHTPIN D5 //Pino digital D2 (GPIO5) conectado ao DHT11
#define DHTTYPE DHT11 //Tipo do sensor DHT11

DHT dht(DHTPIN, DHTTYPE); //Inicializando o objeto dht do tipo DHT passando como parÃ¢metro o pino (DHTPIN) e o tipo do sensor (DHTTYPE)

int temperatura; //variÃ¡vel para armazenar a temperatura
int umidade; //VariÃ¡vel para armazenar a umidade

#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
#include <Ticker.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
WiFiClient wifiClient;
int inicial=0;
int hora=0;
int hora1=0;
int minuto=0;
int segundo=0;
int resposta=0;
int muda=0;
unsigned long tempo=0;
int dia=0;
unsigned long mes=0;
unsigned long constante=0;
int mes1=0;
int ano=0;
const char *ssid     = "Lu&Dry.2G";
const char *password = "aablcoa12";
int diadata=0;
int mesdata=0;
int abrirwifi=0;
Ticker flipper;
bool mudames=false;
int timeZone = -3;
WiFiUDP udp;
NTPClient timeClient(
    udp,                    //socket udp
    "0.br.pool.ntp.org",    //URL do servwer NTP
    timeZone*3600,          //Deslocamento do horÃ¡rio em relacÃ£o ao GMT 0
    60000);       
void flip() {
  if(abrirwifi==0){
    abrirwifi=1;
  }
  //Serial.print("abrir wifi:");
 // Serial.println(abrirwifi);
  
  
  segundo+=1;
 // Serial.print("hora:");
 //   Serial.print(hora);
    //Serial.print(" minuto:");
    //Serial.print(minuto);
    //Serial.print(" segundo:");
   // Serial.println(segundo);
    hora1=hora*100;
    resposta=hora1+minuto;
    hora1=0;
    if(mudames==false){
      Serial.println("é igual a false");
      
       //mes1=EEPROM.read(0);
       //dia=EEPROM.read(1);
        Serial.print(" dia:");
    Serial.println(diadata);
    Serial.print("mes:");
  Serial.println(mes1);
    }
     //Serial.print("dias separados:");
  //Serial.print(diadata);
  //Serial.print("/");
  //Serial.print(mes1);
  //Serial.print("/");
  //Serial.println(ano);
    
    
  // Serial.print("mes1:");
  //Serial.println(mes1);
  //Serial.print("dias:");
  //Serial.println(dia);
    

   if(hora <10){
     lcd.setCursor(0, 0); //SETA A POSIÃ‡ÃƒO EM QUE O CURSOR INCIALIZA(LINHA 1)
    lcd.print("0"); 
    //ESCREVE O TEXTO NA PRIMEIRA LINHA DO DISPLAY LCD
     lcd.setCursor(1, 0); //SETA A POSIÃ‡ÃƒO EM QUE O CURSOR INCIALIZA(LINHA 1)
    lcd.print(hora); //ESCREVE O TEXTO NA PRIMEIRA LINHA DO DISPLAY LCD
     lcd.setCursor(2, 0); //SETA A POSIÃ‡ÃƒO EM QUE O CURSOR INCIALIZA(LINHA 1)
    lcd.print(":"); //ESCREVE O TEXTO NA PRIMEIRA LINHA DO DISPLAY LCD
   
   }
   else{
     lcd.setCursor(0, 0); //SETA A POSIÃ‡ÃƒO EM QUE O CURSOR INCIALIZA(LINHA 1)
   
    lcd.print(hora); //ESCREVE O TEXTO NA PRIMEIRA LINHA DO DISPLAY LCD
     lcd.setCursor(2, 0); //SETA A POSIÃ‡ÃƒO EM QUE O CURSOR INCIALIZA(LINHA 1)
    lcd.print(":"); 
   }
   
     if(minuto <10){
    lcd.setCursor(3, 0); //SETA A POSIÃ‡ÃƒO EM QUE O CURSOR INCIALIZA(LINHA 1)
    lcd.print("0"); //ESCREVE O TEXTO NA PRIMEIRA LINHA DO DISPLAY LCD
    lcd.setCursor(4, 0); //SETA A POSIÃ‡ÃƒO EM QUE O CURSOR INCIALIZA(LINHA 1)
    lcd.print(minuto); //ESCREVE O TEXTO NA PRIMEIRA LINHA DO DISPLAY LCD
   }
   else{
     lcd.setCursor(3, 0); //SETA A POSIÃ‡ÃƒO EM QUE O CURSOR INCIALIZA(LINHA 1)
   
    lcd.print(minuto); //ESCREVE O TEXTO NA PRIMEIRA LINHA DO DISPLAY LCD

   }
    //lcd.setCursor(0, 1); //SETA A POSIÃ‡ÃƒO EM QUE O CURSOR RECEBE O TEXTO A SER MOSTRADO(LINHA 2)      
    //lcd.print("----NODEMCU----"); //ESCREVE O TEXTO NA SEGUNDA LINHA DO DISPLAY LCD
    muda+=1;
    lcd.setCursor(6, 0); //SETA A POSIÃ‡ÃƒO EM QUE O CURSOR INCIALIZA(LINHA 1)
    lcd.print(muda); //ESCREVE O TEXTO NA PRIMEIRA LINHA DO DISPLAY LCD
    lcd.setCursor(8,0);
    if(diadata<10){
    lcd.print("0");
      }
 
  lcd.print(diadata);
  lcd.print("/");
 
  if(mes1<9){
   lcd.setCursor(11,0);
    lcd.print("0");
     lcd.print(mes1);
  }
  if(mes1>=10){
    lcd.setCursor(11,0);
    
     lcd.print(mes1);
  }
  
 
 
  lcd.print("/");
  lcd.print(ano);
  if(diadata<10){
    lcd.setCursor(11,1);
    lcd.print("0");
     lcd.print(diadata);
  }
  if (diadata>=10){
     lcd.setCursor(11,1);
   
     lcd.print(diadata);
  }
  lcd.print("/");
   if(mesdata<10){
    lcd.setCursor(14,1);
    lcd.print("0");
     lcd.print(mesdata);
  }
  if (mesdata>=10){
     lcd.setCursor(14,1);
   
     lcd.print(mesdata);
  }


   
  if(segundo >59){
    segundo=0;
    minuto+=1;
  }
  if(minuto >59){
    minuto=0;
    hora+=1;
  }
  if(hora >23){
    hora=0;
    dia=dia+1;
    
  }
  if(mes1==1 and dia>31){
    mes1=2;
    dia=1;
  }
   if(mes1==2 and dia>28){
    mes1=3;
    dia=1;
  }
   if(mes1==3 and dia>31){
    mes1=4;
    dia=1;
  }
   if(mes1==4 and dia>30){
    mes1=5;
    dia=1;
  }
   if(mes1==5 and dia>31){
    mes1=6;
    dia=1;
  }
  if(mes1==6 and dia>30){
    mes1=7;
    dia=1;
  }
  if(mes1==7 and dia>31){
    mes1=8;
    dia=1;
  }
  if(mes1==8 and dia>31){
    mes1=9;
    dia=1;
  }
  if(mes1==9 and dia>30){
    mes1=10;
    dia=1;
  }
  if(mes1==10 and dia>31){
    mes1=11;
    dia=1;
  }
  if(mes1==11 and dia>30){
    mes1=12;
    dia=1;
  }
  
  if(mes1==12 and dia>31){
    mes1=1;
    dia=1;
    ano+=1;
  }
  
   
    
  mudames=true;

   
 
}
void setup(){
  Serial.begin(115200);
   Wire.begin(D4,D3);
   delay(50); 
   EEPROM.begin(4);
    lcd.init();   // INICIALIZA O DISPLAY LCD
  lcd.backlight(); // HABILITA O BACKLIGHT (LUZ DE FUNDO) 
  lcd.setCursor(0,0);
  lcd.println("Entrando no WIFI");
  lcd.setCursor(1,1);
  lcd.println("Adriel Lucas");
 dht.begin(); //Inicializa o sensor DHT11
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
 
}
void handleRoot()
{
  String state = server.arg("funcao");
  
  if(state=="maisdia"){
    diadata+=1;
    Serial.print("dia:");
    Serial.println(diadata);

   
  }
  if(state=="menosdia"){
    diadata-=1;
    Serial.print("dia:");
    Serial.println(diadata);

   
  }
  if(state=="maismes"){
    mesdata+=1;
    Serial.print("dia:");
    Serial.println(mesdata);

   
  }
  if(state=="menosmes"){
    mesdata-=1;
    Serial.print("dia:");
    Serial.println(mesdata);

   
  }
  if(diadata>31){
    diadata=0;
  }
  if(diadata<1){
    diadata=31;
  }
  if(mesdata>12){
    mesdata=0;
  }
  if(mesdata<1){
    mesdata=12;
  }
  // HTML da pagina principal
  String html = "<html><meta charset='UTF-8' language='pt-br'><title>Eletrônica e utilidades</title><body><center>";
  html+="<style type='text/css' media='all'>body{background-color:#D3D3D3;color:#2F4F4F;width: 90%;}";
  html+=".btn{background-color:#00008B;color:white;font-size:20px;font-family:Arial,Verdana}.btn:hover{background-color:white;color:#00008B;font-size:23px}";
  html+=".btn1{background-color:#B0C4DE;color:blue;font-size:20px;font-family:Arial,Verdana}.btn1:hover{background-color:#000080;color:white;font-size:23px}";
  html+="</style><h1>Eletrônica e utilidades</h1><div style='background-color:#D3D3D3;color:#00008B;;font-size:23px'><p>relogio da casa do adriel</p>";
  html+="</div><div style='background-color:#191970;color:#191970;width:50%;height:6%;font-size:23px'>";
  html+="</div>";
html+="<div style='background-color:#00008B;color:white;height:60%;width:50%'>";
html +="<div style='background-color:#B0C4DE;color:#F8F8FF;height:60%;width:70%;margin: auto'><br><br>";
html +="<a href='/?funcao=maisdia' class='btn1'>+dia</a>";
 html +="&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href='/?funcao=menosdia' class='btn1'>-dia</a>";
 html +="<br><br><a href='/?funcao=maismes' class='btn1'>+mes</a>";
 html +="&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href='/?funcao=menosmes' class='btn1'>-mes</a>";
   html +="</div></div></center></body></html>";



  ;
  //Script JS para não abrir uma nova página Bootstrap
  html += "<script language='JavaScript' type='text/javascript'>";
  html += "var a=document.getElementsByTagName('a');";
  html += "for(var i=0;i<a.length;i++)";
  html += "{";
  html += "a[i].onclick=function()";
  html += "{";
  html += "window.location=this.getAttribute('href');";
  html += "return false";
  html += "}";
  html += "}";
  html += "</script>";
  //Fim da instrução
  html += "</center></div>";

  html += "</body></html>";
  // Enviando HTML para o servidor
  server.send(200, "text/html", html);
}
void parseJSON(String json){
  DynamicJsonDocument buffer(1024);
  deserializeJson(buffer,json);
  String datas=buffer["utc_datetime"];
  String Ano=datas.substring(2,4);
  ano= Ano.toInt();
  String Mes1=datas.substring(5,7);
  mes1=Mes1.toInt();
  String Dia=datas.substring(8,10);
  diadata=Dia.toInt();
  diadata=diadata-1;
  Serial.print("dias separados:");
  Serial.print(diadata);
  Serial.print("/");
  Serial.print(mes1);
  Serial.print("/");
  Serial.println(Ano);
  }
void loop() {
  
  if (inicial==0){
   
  
  timeClient.update();
 
 
  delay(1000);
  
  hora=timeClient.getHours();
  minuto=timeClient.getMinutes();
  segundo=timeClient.getSeconds();
  dia= timeClient.getDay();
 
  
    Serial.print("hora:");
    Serial.print(hora);
    Serial.print(" minuto:");
    Serial.print(minuto);
    Serial.print(" segundo:");
    Serial.println(segundo);
    
    inicial=1;
      temperatura = dht.readTemperature();  //Realiza a leitura da temperatura
       umidade = dht.readHumidity(); //Realiza a leitura da umidade
       lcd.clear();
       lcd.setCursor(0, 1); //SETA A POSIÃ‡ÃƒO EM QUE O CURSOR RECEBE O TEXTO A SER MOSTRADO(LINHA 2) 
       lcd.print("t:");  
       lcd.setCursor(2, 1);   
       lcd.print(temperatura); //ESCREVE O TEXTO NA SEGUNDA LINHA DO DISPLAY LCD
       
       lcd.setCursor(5, 1); //SETA A POSIÃ‡ÃƒO EM QUE O CURSOR RECEBE O TEXTO A SER MOSTRADO(LINHA 2)      
        lcd.print("h:");
         lcd.setCursor(7, 1);
       lcd.print(umidade); //ESCREVE O TEXTO NA SEGUNDA LINHA DO DISPLAY LCD
        Serial.print("umidade:");
        Serial.println(umidade);
//metodo antigo pra separar o tempo
        
    // fim da abstracao da data--------------------------------------------
//metodo novo
HTTPClient http;
http.begin(wifiClient,"http://worldtimeapi.org/api/timezone/America/Sao_Paulo");
int httpCode=http.GET();
if(httpCode==HTTP_CODE_OK){
  Serial.println("funcionou,ate que enfim");
  parseJSON(http.getString());
}
// fim da abstracao
    }
    if( inicial==1){
      inicial=2;
        flipper.attach(1, flip);
    }
  
 if (muda>8){
       muda=0;
       lcd.clear();
    
       temperatura = dht.readTemperature();  //Realiza a leitura da temperatura
       umidade = dht.readHumidity(); //Realiza a leitura da umidade
       lcd.setCursor(0, 1); //SETA A POSIÃ‡ÃƒO EM QUE O CURSOR RECEBE O TEXTO A SER MOSTRADO(LINHA 2) 
       lcd.print("t:");  
       lcd.setCursor(2, 1);   
       lcd.print(temperatura); //ESCREVE O TEXTO NA SEGUNDA LINHA DO DISPLAY LCD
       
       lcd.setCursor(5, 1); //SETA A POSIÃ‡ÃƒO EM QUE O CURSOR RECEBE O TEXTO A SER MOSTRADO(LINHA 2)      
        lcd.print("h:");
         lcd.setCursor(7, 1);
       lcd.print(umidade); //ESCREVE O TEXTO NA SEGUNDA LINHA DO DISPLAY LCD
        //Serial.print("umidade:");
       // Serial.println(umidade);
    }

    if(abrirwifi==1){
      WiFi.softAP("casa Adriel","adriellucas");//nome da rede e senha do AP
     IPAddress myIP = WiFi.softAPIP();


  // Apresenta dados da conexão
      Serial.println("");
        Serial.print("Connected to ");
        Serial.println("192.168.4.1");
        Serial.print("IP address: ");
 



  // Atribuindo urls para funções
  // Quando não especificado método, uma função trata todos
        server.on("/", handleRoot);
 
 
        server.begin();
        Serial.println("HTTP server started");
  // Apenas informando que servidor iniciou
       Serial.println("HTTP server started");
      abrirwifi=2;
      //codigo da abertura do wifi aqui
    }
    if(abrirwifi==2){
       server.handleClient();
    }
  //delay(1000);
}
