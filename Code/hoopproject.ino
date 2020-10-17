#include<Wire.h>
#include <LiquidCrystal_I2C.h>          //Liraries for LCD display
#define button 5

const int MPU_addr=0x68;  // I2C address of the MPU-6050
float AcX,AcY,AcZ,GyX,GyY,GyZ,Tmp;

int trigPin = 9;
int echoPin = 10;    //Digital pin input value

float count_shot = 0;
float made_shot = 0;
float field_pct = 0;
int button_pos = 0;
float toll = 0.05;
float normal_z = 0;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
    
  Serial.begin(9600);
  pinMode(button, INPUT);
  
  pinMode(trigPin, OUTPUT);                 //Ultrasonic Pins
  pinMode(echoPin, INPUT);
  
  
  lcd.begin(20, 4);
  lcd.clear();

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Shot Tracker");
  lcd.setCursor(0, 1);
  lcd.print("Field Goal:");   //LCD Print
  lcd.setCursor(0, 2);
  lcd.print(made_shot, 0);
  lcd.setCursor(1, 2);
  lcd.print("-");
  lcd.setCursor(2, 2);
  lcd.print(count_shot, 0);
}

void loop(){
  for(int ind = 0; ind < 5; ind++) {
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  
    AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)   
    AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)         //X, Y, Z output realing calculations
    AcZ=Wire.read()<<8|Wire.read();
    Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
    GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
    GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
    GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)// 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  
    float normal_z = AcZ/16384;
  }
  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers

  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)   
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)         //X, Y, Z output realing calculations
  AcZ=Wire.read()<<8|Wire.read();
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)// 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  float ac_x = AcX/16384;
  float ac_y = AcY/16384;
  float ac_z = AcZ/16384;
  float gy_x = GyX/131;
  float gy_y = GyY/131;
  float gy_z = GyZ/131;

  double duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);          //Inputs on Ultrasonic distance sensor
  duration=pulseIn(echoPin, HIGH);

  double dist = (duration/2.0/29.1);         //Calculation for distance

  if (dist < 22 or ac_z < (normal_z - toll) or ac_z > (normal_z + toll)) {
    count_shot += 1;

    if (dist < 22) {
      made_shot += 1;
      delay(2000);
    } else {
      bool flag = 0;
      double time1 = millis();
      double time_diff = 0;
      while (flag == 0 and time_diff <= 2000) {
        double duration, distance;
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(1000);
        digitalWrite(trigPin, LOW);          //Inputs on Ultrasonic distance sensor
        duration=pulseIn(echoPin, HIGH);

        double dist = (duration/2.0/29.1); 

        if (dist < 22) {
          made_shot += 1;            //Calculation for whether shot actually went into hoop
          flag = 1;
          delay(2000 - time_diff);    
        }

        double time2 = millis();
        time_diff = time2 - time1;
      }
//      int extra_time = 2000 - time_diff;
//      delay(extra_time);
    }

//    Serial.print("Field Goal: ");
//    Serial.print(made_shot);
//    Serial.print(" / ");
//    Serial.println(count_shot); 
//    delay(1000); 

    if(count_shot > 0) {
      field_pct = made_shot / count_shot * 100;      //Field Goal % Calculation
    } else {
      field_pct = 0;
    }
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Shot Tracker");        //LCD display intially
    lcd.setCursor(0, 1);
    lcd.print("Field Goal:");
    
  
    if(made_shot < 10) {
      lcd.setCursor(0, 2);
      lcd.print(made_shot, 0);
      lcd.setCursor(1, 2);
      lcd.print("-");
      lcd.setCursor(2, 2);
      lcd.print(count_shot, 0);
    } else if(made_shot < 100 and made_shot >= 10) {       
      lcd.setCursor(0, 2);
      lcd.print(made_shot, 0);
      lcd.setCursor(2, 2);
      lcd.print("-");
      lcd.setCursor(3, 2);                                       //LCD Print field goals made / attempted
      lcd.print(count_shot, 0);
    } else {
      lcd.setCursor(0, 2);
      lcd.print(made_shot, 0);
      lcd.setCursor(3, 2);
      lcd.print("-");
      lcd.setCursor(4, 2);
      lcd.print(count_shot, 0);
    }
    
    lcd.setCursor(19, 2);
    lcd.print("%");                                    //LCD print % sign for field goal percentage
    lcd.setCursor(14, 2);
    lcd.print(field_pct, 1);
  }

  //field goal percentage logic

//  Serial.println(field_pct);
  //lcd code
//  LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
//  LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
  

  //reset button code
  button_pos = digitalRead(button);
  if(button_pos == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("RESET");

    made_shot = 0;
    count_shot = 0;
    field_pct = 0;
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Shot Tracker");                //LCD print for if reset button is pressed
    lcd.setCursor(0, 1);
    lcd.print("Field Goal:");
    lcd.setCursor(0, 2);
    lcd.print(made_shot, 0);
    lcd.setCursor(1, 2);
    lcd.print("-");
    lcd.setCursor(2, 2);
    lcd.print(count_shot, 0);
  }
}
 
