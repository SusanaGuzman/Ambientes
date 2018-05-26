#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <SoftwareSerial.h>

SoftwareSerial Serial2(10,11);
#define FIREBASE_AUTH "uDYHWVQWA0oxLbcXFPNrNROqtI1XpvLmEDrBwBTT"   
#define FIREBASE_HOST "test-5acb6.firebaseio.com" 
#define WIFI_SSID "Prueba"
#define WIFI_PASSWORD "teamosusy"

//n es el numero del log el numero del log enviado, es decir, la cantidad de mensajes enviados, es decir, se envia un mensaje, y ese va hacer el 1, luego otro y ese el 2 y asi.
int n = 0;

//////////////////////////////////
//guarda el valor de
int temp = 0;

#include "LedControl.h"     //simpre incluimos la libreria de control 

const byte DIN      = D7;   //Lo conectamos en din
const byte CS       = D5;   //Lo conectamos a Load (cs)
const byte CLK      = D3;   //Lo conectarmos a CLK 
const byte QTD_DISP =  1;   //El nuemro de matriz con controlador M72XX

LedControl ledMatrix = LedControl(DIN, CLK, CS, QTD_DISP);

void setup() {

  Serial.begin(9600);
  
 // El MAX72XX está en modo de ahorro de energía en el arranque, tenemos que hacer que despierte
  ledMatrix.shutdown(0, false);  //modo 'shutdown' no display '0' y FALSE
  
  ledMatrix.setIntensity(0, 6);  //intensidad del display '0' y 5 (0~16)
  
  ledMatrix.clearDisplay(0); 

   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);    // nos conectamos al wifi
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);  // nos conectamos al firebase

  //////////////////////////////
  Firebase.set("LED_STATUS",0);
}

void loop(){
  
  byte i=0, col=0, row=0;
  char var;
  char texto[] = "Anarkopink";

  /*
  *en esta parte desplazaremos el texto que esta escrito en la
  *variable char
  */
  
  

   temp = Firebase.getInt("LED_STATUS");
  if(temp==1)
  {
  
 
  /*
  *en esta parte desplazaremos el texto que esta escrito en la
  *variable char
  */

    
    //se imprime en consola que el led se prendio
    Serial.print("LED ON");
    
     ledMatrix.clearDisplay(0);     //borrar pantalla '0'
  ledMatrix.printString(0, 0, "O");
  delay(500);
  
  }
  else if(temp==2)
  {
    Serial.print("LED OFF");
     ledMatrix.clearDisplay(0);     //borrar pantalla '0'
  ledMatrix.printChar(0, 0, 'X');
  delay(500);
  
  
 
   // digitalWrite(D8,LOW);  
  }
  else
  {
    Serial.print("LED OFF");
     ledMatrix.clearDisplay(0);     //borrar pantalla '0'
  ledMatrix.printChar(0, 0, '*');
  delay(500);
  
  
 
   // digitalWrite(D8,LOW);  
  }
  
    delay(100);
 
}




