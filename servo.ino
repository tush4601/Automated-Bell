#include <Servo.h>  // include servo library

#define TrigPin 10 //attach pin 10 of ARduino to Trig pin of Sensor
#define EchoPin 11 // attach pin 11 of ARduino to Echo pin of Sensor

//variables
Servo servo;
long time_taken; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

void setup() {
  pinMode(TrigPin, OUTPUT);  // Sets the trigPin as an OUTPUT 
  pinMode(EchoPin, INPUT);   // Sets the echoPin as an INPUT
  
  Serial.begin(9600);        // Serial Communication is starting with 9600 of baudrate speed
  
  Serial.println("Ultrasonic Sensor HC-SR04 starts"); // Printing in Serial Monitor
  
  servo.attach(8);     // servo is attached at Arduino 8th pin
  servo.write(0);      // initializing it at 0 degrees
  pinMode(3,OUTPUT);   // Output pin for a LED 
}

void loop() 
{ 
 digitalWrite(3,1);          // Initializing LED to 1
  //analogWrite(3,20);
  digitalWrite(TrigPin, 0);   // Setting trig pin to 0/Low
  delayMicroseconds(2);       // Sets the trigPin LOW for 2 microseconds
  
  digitalWrite(TrigPin, 1);   // Setting trig pin to 1/High
  delayMicroseconds(10);      // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  
  digitalWrite(TrigPin, 0); // Reads the echoPin, and returns the time taken by sound wave in travelling (in microseconds)
  
  time_taken = pulseIn(EchoPin, HIGH); // pulseIn calculates the time for which echoPin is high 
  
  // Calculating the distance
  distance = time_taken * 0.034 / 2;
  // Duration is in microseconds , multiplying it with speed of light
  // Dividing it by 2 as the time is for going and coming back for wave
  // Displays the distance on the Serial Monitor

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
 
  if(distance<10){
digitalWrite(3,0);   // If distance less than 10, turn off the LED so that one can remove hand from front
  analogWrite(3,0);
   delay(300);         

  servo.write(180);     // To rotate servo motor's arm till 180 degrees from 0
  delay(700);
  servo.write(0);       // To rotate back servo motor's arm to 0
  delay(500);

digitalWrite(3,1);    // Again turning  on the LED, so that someone else can place hand
analogWrite(3,20);
  delay(2000);
}
}
