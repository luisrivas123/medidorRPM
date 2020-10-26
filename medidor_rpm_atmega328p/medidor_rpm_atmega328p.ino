// Contador de RPM  by: http://elprofegarcia.com
// Conexion de la entrada de la interrupcion 0  por el PIN 2
// Configurar el monitor serial a 57600 Baudios para visualizar los RPM
// Tienda para comprar Materiales http://dinastiatecnologica.com
#include <LiquidCrystal_I2C.h>
//#include <PinChangeInterrupt.h>

LiquidCrystal_I2C lcd(0x27,16,2); // configuraciones degun el fabricante 0x3F , 0x20 , 0x38

const int pininterrupt = 2;

volatile int contador = 0;   // Variable entera que se almacena en la RAM del Micro
 
void setup() {
  Serial.begin(57600);
  //pinMode(pininterrupt,INPUT);
  attachInterrupt(0,interrupcion0,RISING);  // Interrupcion 1 (pin1) // LOW, CHANGE, RISING, FALLING
  //attachInterrupt(digitalPinToInterrupt (pininterrupt),interrupcion0,FALLING);  // Interrupcion 1 (pin1) // LOW, CHANGE, RISING, FALLING
  lcd.init();
  lcd.home();
  lcd.backlight();
  lcd.print("Lector RPM");  // Print a message to the LCD.
  delay(3000);
}  

 
void loop() {
  delay(990);               // retardo de casi 1 segundo
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(contador*60); // Como son dos interrupciones por vuelta (contador * (60/2))
  lcd.print(" RPM            ");    //  El numero 2 depende del numero aspas de la helise del motor en prueba
  lcd.setCursor(0,1);
  lcd.print(contador); // Como son dos interrupciones por vuelta (contador * (60/2))
  lcd.print(" RPS            ");    //  El numero 2 depende del numero aspas de la helise del motor en prueba
  //Serial.print(contador*60); // Como son dos interrupciones por vuelta (contador * (60/2))
  //Serial.println(" RPM            "); 
  contador = 0;
}
 
void interrupcion0()    // Funcion que se ejecuta durante cada interrupion
{
  contador++;           // Se incrementa en uno el contador
}
