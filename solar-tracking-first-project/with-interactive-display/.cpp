#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <String.h>

LiquidCrystal_I2C lcd(0x27,16,2);

Servo servo1;
Servo servo2;

//sensitivity
int sens = 640;
int repos = 100;
int posval = 900;
int sdelay = 20;

//button pin
int buttonup = 2;
int buttondown = 3;
int buttonset = 4;
int up;
int down;
int mode;
int selection = 0;
String select_icon = "^";

//limitation of the servo rotation
int minup = 90;
int maxdown = 160;
int minleft = 1;
int maxright = 179;

//position of the servo can be edited
int pos1 = 90;
int pos2 = 130;

//pins of the dalight sensor
int upperright = A0;
int upperleft = A1;
int buttomright = A2;
int buttomleft = A3;

//reads the value of each sensor pins
int upr;
int upl;
int butr;
int butl;

//store the value of each sensors
int val1;
int val2;
int val3;
int val4;

int sens1 = 0;
int sens2 = 0;
int sens3 = 0;
int sens4 = 0;




void setup()
{
  pinMode(buttonup, INPUT);
  pinMode(buttondown, INPUT);
  pinMode(buttonset, INPUT);

  lcd.init(); 
  lcd.init();
  lcd.backlight();
  
  servo1.attach(9);
  servo1.write(pos1);
  servo2.attach(10);
  servo2.write(pos2);
  
  
  pinMode(upperright, INPUT);
  pinMode(upperleft, INPUT);
  pinMode(buttomright, INPUT);
  pinMode(buttomleft, INPUT);
  
  Serial.begin(9600);
  
}

void loop()
{
  upr = analogRead(upperright); 
  upl = analogRead(upperleft);
  butr = analogRead(buttomright);
  butl = analogRead(buttomleft);
  up = digitalRead(buttonup);
  down = digitalRead(buttondown);
  mode = digitalRead(buttonset);
  
  val1 = upr;
  val2 = upl;
  
  val3 = butr;
  val4 = butl;

  //FOR THE SELECTION
  if (up == HIGH)
  {
    selection += 1;
    delay(300);
  }
  if (down == HIGH)
  {
    selection -= 1;
    delay(300);
  }

  if (selection > 4)
  {
    selection = 0;
    delay(100);
  }
  else 
  {
    selection = 4;
    delay(100);
  }

  //for the icon
  if (selection == 1 || selection == 3)
  {
    lcd.setCursor(0, 0);
    lcd.print(select_icon);
    lcd.setCursor(0, 1);
    lcd.print(" ");
  }
  else if (selection == 2 || selection == 4)
  {
    lcd.setCursor(0, 1);
    lcd.print(select_icon);
    lcd.setCursor(0, 0);
    lcd.print(" ");
  }

  //for the LCD
  if (selection == 1 || selection == 2)
  {
    if (selection == 1)
    {
      lcd.setCursor(1, 0);
      lcd.print("SENS:");
      lcd.setCursor(1, 1);
      lcd.print("SERV:");
    
      if (up == HIGH){
        sens = 900;
      }
      if (down == HIGH){
        sens = 600;
      }

      if (sens == 600){
        lcd.setCursor(6, 0);
        lcd.print("LOW ");
      }
      else {
        lcd.setCursor(6, 0);
        lcd.print("HIGH ");
      }

    }
    else 
    {
      lcd.setCursor(6, 0);
      lcd.print("         ");
    }
  

    if (selection == 2)
    {
      if (up == HIGH){
        sdelay += 1;
        if (sdelay > 30){
          sdelay = 30;
        }
        delay(100);
      }
      if (down == HIGH){
        sdelay -= 1;
        if (sdelay < 10){
          sdelay = 10;
        }
        delay(100);
      }
      lcd.setCursor(6, 1);
      lcd.print(sdelay);
    }
  }
  
  else if (selection == 3 || selection == 4) {
    if (selection == 3){
      lcd.setCursor(1, 0);
      lcd.print("POS:");
      lcd.setCursor(1, 1);
      lcd.print("                   ");

      if (up == HIGH){
        repos += 1;
        delay(100);
      }
      else if (down == HIGH){
        repos -= 1;
        delay(100);
      }
      lcd.setCursor(6, 0);
      lcd.print(repos);
    }
    
    else {
      lcd.setCursor(6, 0);
      lcd.print("     ");
    }
  }
  
  //For the solar tracking system

  if (selection == 0){
    if (val1 > sens || val2 > sens || val3 > sens || val4 > sens)
    {
      if (val1 < sens || val2 < sens || val3 < sens || val4 < sens)
      {
        if (val1 > sens && val2 < sens && val3 < sens && val4 < sens)
        {
          if (pos1 <= minleft)
          {
            servo1.write(pos1 = minleft);
            }
            if (pos2 <= minup) {
              servo2.write(pos2 = minup);
            }
            servo1.write(pos1 -= 1);
            delay(sdelay);
            servo2.write(pos2 -= 1);
            delay(sdelay);
        } else if (val1 < sens && val2 > sens && val3 < sens && val4 < sens)
        {
          if (pos1 >= maxright)
          {
            servo1.write(pos1 = maxright);
          }
          if (pos2 <= minup)
          {
            servo2.write(pos2 = minup);
          }
          servo1.write(pos1 += 1);
          delay(sdelay);
          servo2.write(pos2 -= 1);
          delay(sdelay);
        } else if (val1 < sens && val2 < sens && val3 > sens && val4 < sens) {
          if (pos1 <= minleft) {
            servo1.write(pos1 = minleft);
          }
          if (pos2 >= maxdown) {
            servo2.write(pos2 = maxdown);
          }
          servo1.write(pos1 -= 1);
          delay(sdelay);
          servo2.write(pos2 += 1);
          delay(sdelay);
        } else if (val1 < sens && val2 < sens && val3 < sens && val4 > sens) {
          if (pos1 >= maxright) {
            servo1.write(pos1 = maxright);
          }
          if (pos2 >= maxdown) {
            servo2.write(pos2 = maxdown);
          }
          servo1.write(pos1 += 1);
          delay(sdelay);
          servo2.write(pos2 += 1);
          delay(sdelay);
        } else {
          servo1.write(pos1);
          servo2.write(pos2);
        }
      if (val1 < sens && val3 < sens && val2 > sens && val4 > sens) {
        if (pos1 >= maxright) {
          servo1.write(pos1 = maxright);
        }
        servo1.write(pos1 += 1);
        delay(sdelay);
      } else if (val2 < sens && val4 < sens && val1 > sens && val3 > sens) {
        if (pos1 <= minleft) {
          servo1.write(pos1 = minleft);
        }
        servo1.write(pos1 -= 1);
        delay(sdelay);
      } else if (val1 < sens && val2 < sens && val3 > sens && val4 > sens) {
        if (pos2 >= maxdown) {
          servo2.write(pos2 = maxdown);
        }
        servo2.write(pos2 += 1);
        delay(sdelay);
      } else if (val3 < sens && val4 < sens && val1 > sens && val2 > sens) {
        if (pos2 <= minup) {
          servo2.write(pos2 = minup);
        }
        servo2.write(pos2 -= 1);
        delay(sdelay);
      } else {
        servo1.write(pos1);
        servo2.write(pos2);
      }

  
    }
  }
  
  if ((val1 && val2 && val3 && val4 < repos) && (pos1 != 90 || pos2 != 130))
  {
    delay(2000);
    if (pos2 < 130) {
        while (pos2 < 130) {
            servo2.write(pos2 += 1);
            delay(sdelay);
        }
    } else if (pos2 > 130) {
        while (pos2 > 130) {
            servo2.write(pos2 -= 1);
            delay(sdelay);
        }
    } else {
        servo2.write(pos2);
    }
    if (pos1 < 90) {
        while (pos1 < 90) {
            servo1.write(pos1 += 1);
            delay(sdelay);
        }
    } else if (pos1 > 90) {
        while (pos1 > 90) {
            servo1.write(pos1 -= 1);
            delay(sdelay);
        }
    } else {
        servo1.write(pos1);
    }
  }
  }
  
  Serial.println(pos1);
  Serial.println(pos2);
}