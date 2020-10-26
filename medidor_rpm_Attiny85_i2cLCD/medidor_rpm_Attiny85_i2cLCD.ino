#include <TinyWireM.h>
#include <USI_TWI_Master.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <PinChangeInterrupt.h>
 
#define I2C_ADDR    0x27 // <<----- Add your address here.  Find it from I2C Scanner
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7 

const int Banda = 150;
long Time = 0;
const int pininterrupt = 1;
LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

volatile int contador = 0;   // Variable entera que se almacena en la RAM del Micro
 
void setup() {

  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt (pininterrupt),interrupcion0,FALLING);  // Interrupcion 1 (pin1) // LOW, CHANGE, RISING, FALLING
  pinMode(pininterrupt,INPUT);
  //attachInterrupt(1,interrupcion0,RISING);
  TinyWireM.begin();                    // initialize I2C lib
  lcd.begin (16,2); // 
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home();
  lcd.print("Lector RPM"); // Print a message to the LCD.
  delay(3000);
}  

 
void loop() {
  delay(999);               // retardo de casi 1 segundo
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(contador*60); // Como son dos interrupciones por vuelta (contador * (60/2))
  lcd.print(" RPM          ");    //  El numero 2 depende del numero aspas de la helise del motor en prueba
  lcd.setCursor(0,1);
  lcd.print(contador); // Como son dos interrupciones por vuelta (contador * (60/2))
  lcd.print(" RPS          ");    //  El numero 2 depende del numero aspas de la helise del motor en prueba
  contador = 0;
}
 
void interrupcion0()    // Funcion que se ejecuta durante cada interrupion
{
  contador++;           // Se incrementa en uno el contador
  //
  /*if(millis() - Time > Banda){
    contador++;
    Time = millis();
  }*/
}
