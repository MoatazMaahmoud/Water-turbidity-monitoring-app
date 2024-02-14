//code el arduino wallahy el 3azem
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial (5,6);//rx-->d2 , tx-->d1
LiquidCrystal_I2C lcd(0x27, 2, 16);
const int buzzerPin = 9;
int sensorPin = A0; //A0 FOR ARDUINO/ 36 FOR ESP
int threshold=20;
void setup()
{ 
   pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
   mySerial.begin(115200);//esp's
  //initialize LCD
  lcd.init();
  //turn on LCD backlight                      
  lcd.backlight();
}
void loop() {
  if (mySerial.available()) {
    // Read the string from ESP32
    String receivedString = mySerial.readStringUntil('\n');

    // Convert the string to an integer
    int receivedInt = receivedString.toInt();
    threshold=receivedInt;
    
  }
  
  int sensorValue = analogRead(sensorPin);
  int turbidity = map(sensorValue, 0, 750, 100, 0);
  Serial.println(turbidity);
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("Turbidity:");
  lcd.print("   ");
  lcd.setCursor(10, 0);
  lcd.print(turbidity);
  
  delay(100);
  if (turbidity <=threshold) {
    lcd.setCursor(0, 1);
    lcd.print(" its safe ");
    digitalWrite(buzzerPin, LOW);
    Serial.print(" its safe ");
  }
  
  if (turbidity >threshold) {
    lcd.setCursor(0, 1);
    lcd.print(" its not safe ");
    digitalWrite(buzzerPin, HIGH);
    Serial.print(" its not safe ");
  }
}
