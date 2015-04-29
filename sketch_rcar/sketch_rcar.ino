// Bluetoothed controlled RC car. Propeller driven with one servo for steering.
// 1/25/2015

#include <Servo.h>

int SERVO_CTRL = 9;
int MOTOR_CTRL = 11;
int S_STATE = 0; // serial state. hold incoming data
int S_FLAG = 0; // Serial Flag to denote transmission
char sbuffer[4]; // Serial read buffer
//int sbuffer = 0;

// global variable definitions
Servo myservo;

void setup(){
  //set pin functions
  myservo.attach(SERVO_CTRL);
  myservo.write(90); // set servo to start position
  pinMode(MOTOR_CTRL, OUTPUT);
  Serial.begin(9600); // default serial baud rate
  
}



void loop(){
  
  //if some data is sent, read it and save it in the state variable
  if(Serial.available() > 0){
    Serial.readBytes(sbuffer, sizeof(sbuffer));
  }
  delay(500);
  
  if(sbuffer){
   Serial.print("Blue RX: ");
   Serial.println(sbuffer);
   
   if(sbuffer[0] == 'T'){
     //execute turn
     turn(sbuffer);
   }
   else if(sbuffer[0] == 'A'){
    //execute accelerate
     accelerate(sbuffer); 
   }
   
  }
  delay(500);
  
  //flush input buffer
  memset(sbuffer, 0, sizeof(sbuffer));
  
}

// Turn serial string starts with "T"i.e. T179
// Accepts values from 30 to 120
void turn(char *pulse)
{
  int angle;
  //angle = map(angle, 0, 179, 30, 60);
  angle = parse(pulse);
  myservo.write(angle);
}

//accelerate string starts with "A" i.e. A255
//pwm controlled "analogWrite" speed values are between 0 and 255
void accelerate(char *pulse)
{
  int v;
  v = parse(pulse);
  if(v >= 0 && v <= 255)
  {
    analogWrite(MOTOR_CTRL, v);
  }
}

int parse(char *str)
{
  char temp[3];
  
  for(int x = 1; x < 5; x++)
  {
     temp[x-1]=str[x];
  }
  
  return atoi(temp);
}


