/*
  PropCar is a propeller driven arduino regulated remote control car.
  v1.0 potentiometer input for steering
*/
#include <Servo.h> // Library functions at http://arduino.cc/en/Reference/Servo

const int VOLTAGE_IN = 0;
const int SERVO_SIG = 9;
const int BUTTON_L = 7;
const int BUTTON_R = 6;
const int MOTOR_PIN = 11;

int gAngle = 90;

Servo servol; //servo 1000 if full counter-clockwise, 2000 full clockwise

/*
  the setup routine runs once when you press reset.
  1. reset position of servo
  2. read state of potentiometer
*/
void setup()
{
    Serial.begin(9600); //initialization of serial COM4
    pinMode(BUTTON_R, INPUT);
    pinMode(BUTTON_L, INPUT);
    servol.attach(SERVO_SIG);
    delay(1000);
    servol.write(gAngle); //reset servo position
    delay(1500);
    
}



void loop() 
{
  int val, buttonR, buttonL;
  
  buttonR = digitalRead(BUTTON_R);
  buttonL = digitalRead(BUTTON_L);
  delay(10); //delay for digital read
  gAngle = determineAngle(gAngle, buttonR, buttonL);
  //val = analogRead(VOLTAGE_IN);
  //angle = map(val, 0, 1023, 0, 179);
  servol.write(gAngle);
  delay(15); //repeat once per second
  
  Serial.print("Current angle: ");
  Serial.println(gAngle);
}

int determineAngle(int angle, int bR, int bL)
{
  /*if(angle < 60)
  {
    angle = 60;
  }
  else if(angle > 120)
  {
    angle = 120;    
  }
  else */ if(bR)
  {
     angle++; 
  }
  else if(bL)
  {
     angle--; 
  }
  //angle = map(angle, 0, 121, 60, 120);
  return angle;
}
