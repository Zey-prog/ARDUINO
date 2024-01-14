#include <Servo.h>

Servo servo1;
Servo servo2;

//sensitivity
int sens = 500;
int repos = 60;
int posval = 900;

int sdelay = 15;

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

//storing the value of each sensors
int val1;
int val2;
int val3;
int val4;

//position of the servo set to 0 degree
int pos1 = 90;
int pos2 = 130;

//limit rotation of the servos
int minpos = 4;
int maxpos = 177;

void setup(){
  
  servo1.attach(9);
  servo1.write(pos1);
  servo2.attach(10);
  servo2.write(pos2);
  
  
  pinMode(upperright, INPUT);
  pinMode(upperleft, INPUT);
  pinMode(buttomright, INPUT);
  pinMode(buttomleft, INPUT);
  
}

void loop()
{
  upr = analogRead(upperright); 
  upl = analogRead(upperleft);
  butr = analogRead(buttomright);
  butl = analogRead(buttomleft);
  
  val1 = upr;
  val2 = upl;
  
  val3 = butr;
  val4 = butl;
  
  if (val1 > sens || val2 > sens || val3 > sens || val4 > sens) {

    if (val1 < sens || val2 < sens || val3 < sens || val4 < sens) {
        if (val1 > sens && val2 < sens && val3 < sens && val4 < sens) {
            if (pos1 <= minpos) {
                servo1.write(pos1 = minpos);
            }
            if (pos2 <= minpos) {
                servo2.write(pos2 = minpos);
            }
            servo1.write(pos1 -= 1);
            delay(sdelay);
            servo2.write(pos2 -= 1);
            delay(sdelay);
        } else if (val1 < sens && val2 > sens && val3 < sens && val4 < sens) {
            if (pos1 >= maxpos) {
                servo1.write(pos1 = maxpos);
            }
            if (pos2 <= minpos) {
                servo2.write(pos2 = minpos);
            }
            servo1.write(pos1 += 1);
            delay(sdelay);
            servo2.write(pos2 -= 1);
            delay(sdelay);
        } else if (val1 < sens && val2 < sens && val3 > sens && val4 < sens) {
            if (pos1 <= minpos) {
                servo1.write(pos1 = minpos);
            }
            if (pos2 >= maxpos) {
                servo2.write(pos2 = maxpos);
            }
            servo1.write(pos1 -= 1);
            delay(sdelay);
            servo2.write(pos2 += 1);
            delay(sdelay);
        } else if (val1 < sens && val2 < sens && val3 < sens && val4 > sens) {
            if (pos1 >= maxpos) {
                servo1.write(pos1 = maxpos);
            }
            if (pos2 >= maxpos) {
                servo2.write(pos2 = maxpos);
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
        if (pos1 >= maxpos) {
            servo1.write(pos1 = maxpos);
        }
        servo1.write(pos1 += 1);
        delay(sdelay);
    } else if (val2 < sens && val4 < sens && val1 > sens && val3 > sens) {
        if (pos1 <= minpos) {
            servo1.write(pos1 = minpos);
        }
        servo1.write(pos1 -= 1);
        delay(sdelay);
    } else if (val1 < sens && val2 < sens && val3 > sens && val4 > sens) {
        if (pos2 >= maxpos) {
            servo2.write(pos2 = maxpos);
        }
        servo2.write(pos2 += 1);
        delay(sdelay);
    } else if (val3 < sens && val4 < sens && val1 > sens && val2 > sens) {
        if (pos2 <= minpos) {
            servo2.write(pos2 = minpos);
        }
        servo2.write(pos2 -= 1);
        delay(sdelay);
    } else {
        servo1.write(pos1);
        servo2.write(pos2);
    }

    
    }
  }
  
  if (val1 < repos && val2 < repos && val3 < repos && val4 < repos) {
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