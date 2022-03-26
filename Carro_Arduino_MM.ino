
/*
 * Este codigo esta realizado para la comunicacion con la siguiente app
 * https://play.google.com/store/apps/details?id=braulio.calle.bluetoothRCcontroller&hl=es_AR&gl=US
 * Bluetooth RC Controller
 */
#include <SoftwareSerial.h>
SoftwareSerial bt(7,8); //RX,TX para BT

const int motorB2  = 9;    // Pin A-1A de L9110.
const int motorB1  = 3;    // Pin A-1B de L9110.
const int motorA2  = 11;   // Pin B-1B de L9110.
const int motorA1  = 10;   // Pin B-1B de L9110.

const int buzzer = 12;   // PIN D12 para buzzer, a implementar
const int LedAtras = 6; // PIN D6 para led atras, a implementar
const int LedAdelante = 5; PIN D5 para led adelante, a implementar

//variables utiles
int i = 0;
int j = 0;
int state_rec;
int vSpeed = 200;   // Establezce la velocidad predeterminada 0 < x < 255.(200 default)
char state;

void setup() {
  // Inicializar puertos como entrada y salida.
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(BTState, INPUT);

  // Inicializa la comunicación serie a 9600 bits.
  //Serial para pc y serial BT
  Serial.begin(9600);
  Serial.println("iniciando");
  bt.begin(9600);
}

void loop() {
 
  // Guarda los valores de la variable 'state'
   if(bt.available()){    
    state_rec = bt.read();
    state = state_rec;
    //Serial.write(state_rec);    
  }
  
 // Cambia la velocidad de acuerdo a los valores especificados.
  if (state == '0') {
    vSpeed = 0;
  }
  else if (state == '4') {
    vSpeed = 100;
  }
  else if (state == '6') {
    vSpeed = 155;
  }
  else if (state == '7') {
    vSpeed = 180;
  }
  else if (state == '8') {
    vSpeed = 200;
  }
  else if (state == '9') {
    vSpeed = 230;
  }
  else if (state == 'q') {
    vSpeed = 255;
  }

  if (state != 'S') {
    Serial.print(state);
  }

  // Si el estado recibido es igual a 'F', el auto avanza.
  if (state == 'F') {
    analogWrite(motorB1, vSpeed);
    analogWrite(motorA1, vSpeed);
    analogWrite(motorA2, 0);
    analogWrite(motorB2, 0);
  }
// Si el estado recibido es igual a 'I', el automóvil se mueve hacia la parte delantera izquierda.
    else if (state == 'I') {  
    analogWrite(motorA1, vSpeed); 
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 100);    
    analogWrite(motorB2, 0);
  }

// Si el estado recibido es igual a 'G', el automóvil se mueve hacia la parte delantera derecha.
    else if (state == 'G') {  
    analogWrite(motorA1, 100); 
    analogWrite(motorA2, 0);
    analogWrite(motorB1, vSpeed);      
    analogWrite(motorB2, 0);
  }
// Si el estado recibido es igual a 'B', el auto se mueve hacia atrás.
  else if (state == 'B') {
    analogWrite(motorA1, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, vSpeed);
    analogWrite(motorA2, vSpeed);
  }
// Si el estado recibido es igual a 'H', el automóvil se mueve hacia atrás a la izquierda.
   else if (state == 'H') {  
    analogWrite(motorA1, 0);   
    analogWrite(motorA2, vSpeed);
    analogWrite(motorB1, 0); 
    analogWrite(motorB2, 100);
  }
// Si el estado recibido es igual a 'J', el automóvil se mueve hacia atrás a la derecha.  
  else if (state == 'J') {  
    analogWrite(motorA1, 0);   
    analogWrite(motorA2, 100);
    analogWrite(motorB1, 0);   
    analogWrite(motorB2, vSpeed);
  }
// Si el estado recibido es igual a 'L', el auto se mueve hacia la izquierda.
  else if (state == 'L') {   
    analogWrite(motorA1, 0);
    analogWrite(motorA2, vSpeed);
    analogWrite(motorB1, vSpeed);
    analogWrite(motorB2, 0);
  // Si el estado recibido es igual a 'R', el auto se mueve hacia la derecha.}
  else if (state == 'R') {   
    analogWrite(motorA1, vSpeed);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, vSpeed);
  }
  // Si el estado recibido es igual a 'S', el auto permanece parado.
  else if (state == 'S') {   
    analogWrite(motorA1, 0);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 0);
  }
// Si el estado recibido es igual a 'V', suena la bocina.
  else if (state == 'V') { 
    if (j == 0) {
      tone(buzzer, 1000);
      j = 1;
    }
    else if (j == 1) {
      noTone(buzzer);
      j = 0;
    }
    state = 'n';
  }


}
