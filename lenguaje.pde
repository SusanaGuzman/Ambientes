import oscP5.*;
import netP5.*; 

OscP5 oscP5;
NetAddress myRemoteLocation;

float i;
PImage hola;
PImage chao;
PImage ganzo;
PImage silencio;

void setup () 
{
size (640,480);

oscP5 = new OscP5(this,12000);
myRemoteLocation = new NetAddress("localhost",6448);

hola = loadImage ("hola.jpg");
chao =loadImage ("chao.jpg");
ganzo = loadImage ("ganzo.jpg"); 
silencio = loadImage ("silencio.jpg");
}

void draw ()
{

if (i >= 0 & i<=0.2){
  image (hola, 0,0);
  }
  
  if (i>=0.3 & i<=5){
  image (chao, 0,0);
  }
    if (i>=0.6 & i<=8){
  image (ganzo, 0,0); 
  }
  
  if (i>=0.8 & i<=1){
  image (silencio, 0,0);
  }
 }
 
void oscEvent(OscMessage msn){
if(msn.checkAddrPattern("/wek/outputs")== true){
  float firstValue= msn.get(0).floatValue();
  i = firstValue; 
  
  float dosValue= msn.get(1).floatValue();
  i = dosValue;  
}
}