// Bluetoothed controlled RC car. Propeller driven with one servo for steering.
// 1/25/2015

#include <Servo.h>

int SERVO_CTRL = 9;
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
  Serial.begin(9600); // default serial baud rate
}



void loop(){
  
  //flush input buffer
  memset(sbuffer, 0, sizeof(sbuffer));
  //if some data is sent, read it and save it in the state variable
  if(Serial.available() > 0){
    Serial.readBytes(sbuffer, sizeof(sbuffer));
  }
  delay(1000);
  
  if(sbuffer){
   Serial.print("Blue RX: ");
   Serial.println(sbuffer);
   delay(1000);
   
   if(sbuffer[0] == 'T'){
     //execute turn
     turn(sbuffer);
   }
   else if(sbuffer[0] == 'A'){
    //execute accelerate
     accelerate(3); 
   }
   
  }
  
  
  
}

// Turn serial string starts with "T"i.e. T179
// Convert (0-179) to range of turn radius 30 to 60 degrees on servo
int turn(char *pulse)
{
  char temp[3];
  int angle;
  
  for(int x = 1; x < sizeof(pulse); x++)
  {
     temp[x-1]=pulse[x];
  }
  
  angle = atoi(temp);
  angle = map(angle, 0, 179, 30, 60);
  
  return angle;
}

//accelerate string starts with "A" i.e. A360
// 0-179 is reverse
//180-359 is forward
void accelerate(int pulse)
{
  
}


