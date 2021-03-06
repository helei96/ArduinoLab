#include <LiquidCrystal.h>
int count = 0;
bool onCount = true;
/******************************************************************************************************************/
/***********     LCD Initialization Code - Don't change unless you want stuff to stop working! ********************/
/******************************************************************************************************************/
/*
 *      void init_LCD();     Call this function to set up the LCD screen for use
 *      void LCD_off();      Call this function to turn off the backlight of the screen. Note that this leaves the LCD still on, but not visible
 *      void LCD_on();       Call this function to turn the backlight back on. The LCD starts on by default
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */





                      
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(48, 46, 44, 42, 40, 38, 36, 34, 32, 30, 28);
int __counter = 0; //Global counter variable for contrast PWM
void init_LCD(){__init_LCD();}

  void __init_LCD(){
  pinMode(24, OUTPUT); //K
  pinMode(26, OUTPUT); //A
  pinMode(54, OUTPUT); //VSS
 pinMode(52, OUTPUT); //VDD
  pinMode(50, OUTPUT); //Contrasty pin
  digitalWrite(24, LOW); //Backlight
  digitalWrite(26, HIGH); //Backlight
  digitalWrite(54, LOW); //GND
  digitalWrite(52, HIGH); //VDD
 // set up the LCD's number of columns and rows:
  lcd.begin(16, 2); 
  // Timer0 is used for millis() - we'll just interrupt
  // in the middle and call the compA
  OCR0A = 0x01;
  TIMSK0 |= _BV(OCIE0A);
}
SIGNAL(TIMER0_COMPA_vect) 
{
   __counter++;
   if (__counter > 14){
      digitalWrite(50,HIGH);
      __counter = 0;
   }
   else if (__counter > 3){
      digitalWrite(50, LOW);
   }
}


//turn lcd backlight off
void lcd_off(){
  digitalWrite(26, LOW); //Backlight
}

//turn lcd backlight on
void lcd_on(){
  digitalWrite(26, HIGH); //Backlight
}
/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/

void setTimer(String c){
  count = c.toInt();
}
 void startTimer(){
  onCount = true;
 }

 void stopTimer(){
  onCount = false;
 }

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
  init_LCD();

}

void loop() {
  // put your main code here, to run repeatedly;
//  if(Serial.available()){
//        delay(100);
//        lcd.clear();
//        lcd.write(count);
//  }
    if(Serial.available() >0){
      String incoming = Serial.readString();
      Serial.print(incoming);
      Serial.print(incoming[0]);
      if(incoming[0] == 't'){
        setTimer(incoming.substring(1));
      }
      if(incoming == "stop" || incoming == "Stop"){
        stopTimer();
      }
      if(incoming == "start" || incoming == "Start"){
        startTimer();
      }
    }
    delay(1000);
    lcd.clear();
    lcd.print(String(count, DEC));
    if(onCount){
     count += 1;
   }
}
