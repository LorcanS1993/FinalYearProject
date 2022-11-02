#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define MQ3 12
#define InLimit 150 
#define OutOfLimit 400

int red = 25;
int green = 26;
int blue = 27;
float sensorValue;  //variable to store sensor value
const int buzzer = 18; //buzzer to pin 18

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

// set LCD address, number of columns and rows
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup()
{
  // initialize LCD
  lcd.begin();
  // turn on LCD backlight                      
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("The Breathalyser Connection");
  delay(5000);
 // clears the display to print new message
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Final Year Project");
  delay(5000);
  lcd.clear();
  
 pinMode(buzzer, OUTPUT); // Set buzzer - pin 18 as an output
 pinMode(red,OUTPUT);
 pinMode(green,OUTPUT);
 pinMode(blue,OUTPUT);

 Serial.println("MQ3 Starting...");
 delay(20000); // allow the MQ3 to warm up
}
void loop()
{
 digitalWrite(red,HIGH);
 delay(5000);
 digitalWrite(red,LOW);
 digitalWrite(green,HIGH);
 delay(5000);
 digitalWrite(green,LOW);
 digitalWrite(blue,HIGH);
 delay(5000);
 digitalWrite(blue,LOW);


  tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);        // ...for 1sec

  sensorValue = analogRead(MQ3); // read analog input using pin 12 on ESP32
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);

  // Determine the status
  if (sensorValue < InLimit) {

    Serial.println("  |  Status: Sober");
    digitalWrite(green,HIGH);
    delay(5000);
    digitalWrite(green,LOW);

  } else if (sensorValue >= InLimit && sensorValue < OutOfLimit) {

    Serial.println("  |  Status: Alcohol Decteced but within legal limits");

  } else {
    digitalWrite(red,HIGH);
    delay(5000);
    tone(buzzer, 1000); 
    delay(5000);
    Serial.println("  |  Status: DRUNK!!!");
    noTone(buzzer);     // Stopping buzzer sound...
    digitalWrite(red,LOW);
   
  }
}
