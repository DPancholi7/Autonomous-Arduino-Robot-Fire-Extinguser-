 /*

Author : Dhvani Pancholi
Assignment : Autonomous Robot Code 
Date : 05-10-2019
Description : Robot Code That Allows Our Robot To Extingish A Flame

*/

/*
                                    Algorithm Description

 Robot Will Move Forward Untill Ultrasonic Sensor Detects An Obstacle Within 50cm.
 When Obstacle Is Detected, Robot Will Turn 90 Degrees Right And Collect The Distance of The Right Side,
 Robot Will Then Turn 90 Degrees Left And Collect The Distance of The Left Side.
 Robot Will Turn And Navigate In The Direction That Has A Greater Average Distance, It Will Than Process The Cycle
 Over And Over Again Untill It Detects The Flame.
 When The Flame Sensor Detects The Flame, It Will Activate The Fan To Extinguish The Flame.

*/

// Including Packages & Libraries
#include <Servo.h> 

 // Component Initialization 
Servo RightWheel;  
Servo LeftWheel;


// Global Variables
int posRight = 180; 
int posLeft = 0;
const int UltraSonicPIN = 13;
const int EchoPIN = 8;
long duration,cm;
double RightWallDistance[10];
double LeftWallDistance [10];
double AverageLeft;
double AverageRight;
double DistanceRight;
double DistanceLeft;
 
void setup() // Setup Function
{ 
  Serial.begin(9600);
  pinMode(UltraSonicPIN,OUTPUT); // Output Initialised 
  pinMode(EchoPIN, INPUT); // Input Initialised
  RightWheel.attach(9); // Right Servo Pin
  LeftWheel.attach(7); // Left Servo Pin
  
} 
 
void loop() // Main Function
{  
 
   RightWheel.write(posRight);
   LeftWheel.write(posLeft);
  

 ReadDistance(); // Reads Distance In The Background
 
 if(cm < 20) {
   
   TurnRight90();
   StopServo();
   ReadRightWall();
   TurnLeft90();
   TurnLeft90();
   StopServo();
   ReadLeftWall();
   TurnRight90();
   StopServo();
   
   if (AverageRight > AverageLeft) {
     StartServo();
     TurnRight90();
     RightWheel.write(posRight);
     LeftWheel.write(posLeft);
     
     
   }
   
   else if (AverageLeft > AverageRight) {
     StartServo();
     TurnLeft90();
     RightWheel.write(posRight);
     LeftWheel.write(posLeft);
     
 }
    
} 

}
  
   long microsecondsToCentimeters(long microseconds) // Conversion Fucntion
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  
  return microseconds / 29 / 2;
}

void ReadDistance() { // Read Distance Using Ultrasonic Sensor
  
  digitalWrite(UltraSonicPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(UltraSonicPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(UltraSonicPIN, LOW);
  
  duration = pulseIn(EchoPIN, HIGH);
  
  cm = microsecondsToCentimeters(duration);
  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(10);
  
  
} 

 void TurnLeft90() { // Turns Robot 90 Degrees Left
       
    RightWheel.write(0);
    LeftWheel.write(0);
    delay(1300);
    
   }
   
   void TurnRight90() { // Turns Robot 90 Degrees Right
       
    RightWheel.write(180);
    LeftWheel.write(180);
    delay(1300);
    
   }

 void StopServo() { // Stops Servo (Time)
     
     RightWheel.detach();
     LeftWheel.detach();
     delay(1000);
     
 }
 void StartServo() {
   
   delay(1000);
   RightWheel.attach(9);
   LeftWheel.attach(7);
   
   
 }
 
 
   int ReadRightWall() {
       
       // Reads Distance And Calculates Average Distance (Right Wall)
      ReadDistance();
      RightWallDistance[0] = cm;
      ReadDistance();
      RightWallDistance[1] = cm;
      ReadDistance();
      RightWallDistance[2] = cm;
      ReadDistance();
      RightWallDistance[3] = cm;
      ReadDistance();
      RightWallDistance[4] = cm;
      ReadDistance();
      RightWallDistance[5] = cm;
      ReadDistance();
      RightWallDistance[6] = cm;
      ReadDistance();
      RightWallDistance[7] = cm;
      ReadDistance();
      RightWallDistance[8] = cm;
      ReadDistance();
      RightWallDistance[9] = cm;
      
       for(int i = 0; i < 10; i++) {
       
       AverageRight += RightWallDistance[i];
       AverageRight = AverageRight/ 10;
       
     } 
     return AverageRight; // Returns AverageRight Distance
       
   }
   
   int ReadLeftWall() {
       
       // Reads Distance And Calculates Average Distance (Left Wall)
      ReadDistance();
      LeftWallDistance[0] = cm;
      ReadDistance();
      LeftWallDistance[1] = cm;
      ReadDistance();
      LeftWallDistance[2] = cm;
      ReadDistance();
      LeftWallDistance[3] = cm;
      ReadDistance();
      LeftWallDistance[4] = cm;
      ReadDistance();
      LeftWallDistance[5] = cm;
      ReadDistance();
      LeftWallDistance[6] = cm;
      ReadDistance();
      LeftWallDistance[7] = cm;
      ReadDistance();
      LeftWallDistance[8] = cm;
      ReadDistance();
      LeftWallDistance[9] = cm;
     
     for(int i = 0; i < 10; i++) {
       
       AverageLeft += LeftWallDistance[i];
       AverageLeft = AverageLeft/ 10;
       
     }
     return AverageLeft; // Returns AverageLeft Distance
       
   }
  
  
  




