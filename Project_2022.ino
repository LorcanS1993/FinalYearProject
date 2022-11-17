 #include <LiquidCrystal_I2C.h>
#include <Wire.h>

const int MQ3 = 34;
int red = 25;
int green = 26;
int blue = 27;
float sensorValue;  //variable to store sensor value
const int buzzer = 18; //buzzer to pin 18
const int buttonPin = 2;

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;
int buttonState = 0;

// set LCD address, number of columns and rows
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup()
{
  // initialize LCD
  lcd.begin();
  // turn on LCD backlight                      
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("The Breathalyser");
  lcd.setCursor(0, 1);
  lcd.print("Connection");
  delay(5000);
 // clears the display to print new message
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Final");
  lcd.setCursor(0,1);
  lcd.print("Project");
  delay(5000);
  lcd.clear();

 pinMode(MQ3, INPUT);
 pinMode(buttonPin, INPUT);
 pinMode(buzzer, OUTPUT); // Set buzzer - pin 18 as an output
 pinMode(red,OUTPUT);
 pinMode(green,OUTPUT);
 pinMode(blue,OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("MQ3 Starting....");
  delay(10000);
  lcd.clear();
}
void loop()
  {

  float AlcoValue=0;
  for(int i=0;i<10;i++)
  {
    AlcoValue= analogRead(MQ3);
    delay(10);
  }

    float v = (AlcoValue/10) * (5.0/1024.0);
    float mgL= 0.67 * v;
    Serial.print("BAC:");
    Serial.print(mgL);
    Serial.print(" mg/L");
    lcd.setCursor(0,0);
    lcd.print("BAC: ");
    lcd.print(mgL,4);
    lcd.print(" mg/L        ");
    lcd.setCursor(0,1);

    if(mgL > 0.5)
    { 
      lcd.print("Drunk!!   ");
      Serial.println("    Drunk! PLEASE DO NOT DRIVE!");
      digitalWrite(buzzer, HIGH);
      tone(buzzer, 1000); // Send 1KHz sound signal...
      delay(1000);  
       digitalWrite(red,HIGH);
       delay(5000);
       digitalWrite(red,LOW);
    }
    else
    {
      noTone(buzzer);     // Stop sound...
      delay(1000);        // ...for 1sec 
      lcd.print("Normal  ");
      Serial.println("    Normal");
      digitalWrite(green,HIGH);
      delay(5000);
      digitalWrite(green,LOW);
    }
    delay(100);
  /*
 digitalWrite(red,HIGH);
 delay(5000);
 digitalWrite(red,LOW);
 digitalWrite(green,HIGH);
 delay(5000);
 digitalWrite(green,LOW);
 digitalWrite(blue,HIGH);
 delay(5000);
 digitalWrite(blue,LOW);
 */

 /* delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);        // ...for 1sec 

 buttonState = digitalRead(buttonPin);
if (buttonState == HIGH) {
  sensorValue = analogRead(MQ3); // read analog input using pin 12 on ESP32
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  lcd.setCursor(0, 0);
  lcd.print("Alcohol Level: ");
  delay(5000);
  lcd.setCursor(0, 1);
  lcd.print(sensorValue);
  delay(5000);
  lcd.clear(); 
  } */
  
}
