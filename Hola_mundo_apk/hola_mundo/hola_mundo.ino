
void setup() {
Serial.begin(9600);
}
 
 void loop () {
      if (Serial.available()) { //Si está disponible
            char c = Serial.read(); //Guardamos la lectura en una variable char
            if (c == 'H') { //Si es una 'H', enciendo el LED
                  Serial.println("HOLA MUNDO");
            } 
      }
}
 
 
 

