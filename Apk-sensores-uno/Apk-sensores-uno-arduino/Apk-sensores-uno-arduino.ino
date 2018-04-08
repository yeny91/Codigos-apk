 void setup () {
      Serial.begin(9600); //Inicializo el puerto serial a 9600 baudios
}
void loop () {
      if (Serial.available()) { //Si está disponible
            char c = Serial.read(); //Guardamos la lectura en una variable char
            if (c == 'M') { //Si es una 'H', enciendo el LED
                  Serial.println("C0 no hay movimiento en la cocina");
            } else if (c == 'G') { //Si es una 'L', apago el LED
                  Serial.println("'G1 la gabeta 1 esta abierta");
            } else {
                  Serial.println("Caracter no reconocido");
            }
      }
}
