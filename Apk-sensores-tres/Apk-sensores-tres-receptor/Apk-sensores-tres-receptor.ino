#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
 
const int pinCE = 9;
const int pinCSN = 10;
RF24 radio(pinCE, pinCSN);
 
// Single radio pipe address for the 2 nodes to communicate.
const uint64_t pipe = 0xE8E8F0F0E1LL;
 
float data[3];

//DECLARACION DE VARIABLES PARA EL SENSOR DE MOVIMIENTO
       // pin para el LED
const int PIRPin = 4;         // pin de entrada (for PIR sensor)
 


// INICIALIZACION DE VARIABLES PARA EL SENSOR DE MOVIMIENTO
int pirState = LOW;           // de inicio no hay movimiento
int val = 0;                 // estado del pin

// INICIALIZACION DE VARIABLES PARA EL SENSOR DE CORRIENTE
float Sensibilidad=0.66; //sensibilidad en V/A para nuestro sensor
float offset=0; // Equivale a la amplitud del ruido

//DECLARACION DE VARIABLES PARA EL SENSOR MAGNETICO 

// Definiciones
boolean abierto = false;
int cambios;

// Rutina de Interrupción
void interrupcion()
{
  abierto = true;
//  Serial.print("cambio ");
  if (cambios == 0)
    cambios ++;
  else {
    cambios = 0;
    abierto = false;
  }
  //Serial.println(cambios);
}

// CONTADOR DE HUEVOS 


// this constant won't change:
const int  buttonPin1 = 6;    // the pin that the pushbutton is attached to
const int  buttonPin2 = 7;    // the pin that the pushbutton is attached to

// Variables will change:

int buttonState1 = 0;         // current state of the button
int buttonState2 = 0;         // current state of the button




 
void setup()
{
  //COMUNICACION POR RADIO
   radio.begin();
   Serial.begin(9600); 
   radio.openReadingPipe(1, pipe);
   radio.startListening();

//declaracion sensor de movimiento
 
   pinMode(PIRPin, INPUT);

   //declaracion sensor de flujo

   digitalWrite(3, HIGH);
  attachInterrupt(1,interrupcion,HIGH); // Attaching the ISR to INT0

// CONTADOR HUEVOS 

// initialize the button pin as a input:
  pinMode(buttonPin1, INPUT);
   pinMode(buttonPin2, INPUT);
  // initialize the LED as an output:
  


   
}
 
void loop()
{


  //proceso del sensor de corriente
  float Ip=get_corriente();//obtenemos la corriente pico
  float Irms=Ip*0.707; //Intensidad RMS = Ipico/(2^1/2)
  float P=Irms*110.0; // P=IV watts
// profeso del sensor de movimiento


  
  val = digitalRead(PIRPin);

// filtro sensor magnetico 

if (Serial.available()) { //Si está disponible
     char c = Serial.read(); //Guardamos la lectura en una variable char
     
  
  if (c == 'G') { 
                 
    if (abierto){
    Serial.println("G1: GAVETA1 ABIERTA");
      
    
    
    }
    else{
    Serial.println("G0: GAVETA 1 CERRADA");
       
    
    }

    delay(2000);
  }
// filtro sensor de corriente
  
   if (c == 'C'){
  if (P>13){
  
 
  Serial.println("L1: LICUADORA ENCENDIDA");
  
  }

  else 
  {

  Serial.println("L0: LICUADORA APAGADA");
       
    }
delay(2000);
    
   }
    

     // filtro sensor de movimiento

 if (c == 'M'){
     
   if (val == HIGH)   //si está activado
   {     
      Serial.println("M1: HAY MOVIMIENTO EN LA COCINA");
      }
      else 
      {   
        Serial.println("M0: NO HAY MOVIMIENTO EN LA COCINA");       
        }
        
        delay(2000);
 }

if (c == 'F'){
 
   if (radio.available())
   {    
      radio.read(data,sizeof(data));
      if (data[0]==0) {     
      Serial.println("LV0: LLAVE DE LAVAPLATOS CERRADA");
   }
   else {
    Serial.println("LV1: LLAVE DE LAVAPLATOS ABIERTA");
       
   }
   }
   delay(2000);
}

if (c == 'H'){
  
  
  if ((buttonState1 == HIGH) &&( buttonState2 == HIGH )) {
          
      Serial.println(" 2 HUEVOS"); 
    }
    else if ((buttonState1 == HIGH) || (buttonState2 == HIGH)) {
            
      Serial.println(" 1 HUEVOS");
      
          }
else  {
           
      Serial.println(" 0 HUEVOS");      
    }  

    delay(2000);
}



if (c=='A'){

if (abierto && val==HIGH && P>13){
    Serial.print("HAY ALGUIEN EN LA COCINA, LA GAVETA 1 ESTA ABIERTA Y LA LICUADORA ESTA ENCENDIDA ");
    }
    
  else
    Serial.print("NO HAY NADIE EN LA COCINA, LA GAVETA 1 ESTA CERRADA Y LA LICUADORA ESTA APAGADA, ");

    if (P>13 && val==HIGH){
  Serial.print("HAY ALGUIEN EN LA COCINA Y LA LICUADORA ESTA ENCENDIDA, ");
  }
  else 
  {
  Serial.print("NO HAY NADIE EN LA COCINA Y LA LICUADORA ESTA APAGADA, "); 
    }
if (abierto && val==HIGH)
     Serial.print("HAY ALGUIEN EN LA COCINA Y LA GAVETA 1 ESTA ABIERTA, ");
else 
     Serial.print("NO HAY ALGUIEN EN LA COCINA Y LA GAVETA 1 ESTA CERRADA, ");
     

   if (radio.available())
   {    
      radio.read(data,sizeof(data));
            
      
      if (data[0]==0 && val==LOW) {     
      Serial.print("NO HAY NADIE EN LA COCINA Y LA LLAVE DEL LAVAPLATOS ESTA CERRADA, ");
      
   }
   else {
    Serial.print("HAY ALGUIEN EN LA COCINA Y LA LLAVE DEL LAVAPLATOS ESTA ABIERTA, ");
   }
   delay(2000);
   }

   Serial.println(".   ");

   

  
}










     
}
delay(2000);
}

float get_corriente()
{
  float voltajeSensor;
  float corriente=0;
  long tiempo=millis();
  float Imax=0;
  float Imin=0;
  while(millis()-tiempo<500)//realizamos mediciones durante 0.5 segundos
  { 
    voltajeSensor = analogRead(A0) * (5.0 / 1023.0);//lectura del sensor
    corriente=0.9*corriente+0.1*((voltajeSensor-2.5)/Sensibilidad); //Ecuación  para obtener la corriente
    if(corriente>Imax)Imax=corriente;
    if(corriente<Imin)Imin=corriente;
  }
  return(((Imax-Imin)/2)-offset);
}


