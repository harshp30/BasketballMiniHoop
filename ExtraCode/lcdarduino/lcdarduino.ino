#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

void setup() { 
 lcd.begin(20, 4);
 lcd.clear();
 lcd.backlight();

}
void loop() { 
 lcd.setCursor(0,0);
 lcd.print("Value:");
 int x = 5;
 lcd.setCursor(0, 1);
 lcd.print(x);
}
