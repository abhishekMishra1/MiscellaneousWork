#include <AFMotor.h>
#include <Servo.h>

#define MIN_DISTANCE 50
#define RADIUS 4.5
#define PIE 3.14
//The speed of the vehicle is calculated by doing practical. Setting the speed value of motor as 255 for both motors, and running for 10 seconds.
//The distance covered in this case comes out to be 150 cm. So, speed is 15cm/sec.
#define SPEED 15
////////////////////GLOBAL VARIABLES - START////////////////
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
Servo myservo;
int pos = 0;
int IRpin = 0;
int distance;
int maxDistance;
int turningDirection;
uint8_t maxDistAngle;
uint8_t turningTime;
enum{
	LEFT=-1,
	BACKSIDE,
	RIGHT
};
////////////////////GLOBAL VARIABLES - END/////////////////

int readDistance(){
  Serial.println(__FUNCTION__);
  return (6762/(analogRead(IRpin)-9))-4;
}

void runmotor(int dire){
  Serial.print("[");
  Serial.print(__TIME__);
  Serial.print("]");
  Serial.print(__FUNCTION__);
  Serial.print(": ");
  Serial.println(dire);
  motor1.run(dire);
  motor2.run(dire);
}

void turning(int directionRight, int directionLeft, int turningTime){
  Serial.println(__FUNCTION__);
	motor1.run(directionRight);
	motor2.run(directionLeft);
	delay(turningTime*1000);
	motor1.run(RELEASE);
	motor2.run(RELEASE);
}
int readMaxDistance(){
  Serial.println(__FUNCTION__);
	myservo.write(0);
	int dist,maxDist;
	for(int pos = 0; pos<=180; pos++){
		myservo.write(pos);
		dist = readDistance();
		if(dist>maxDist){
			maxDist = dist;
			maxDistAngle = pos;
		}
                delay(50);
        }
    return maxDist;
}

int calculateTurningTime(){
  Serial.println(__FUNCTION__);
	//arcLength = (2*PIE*RADIUS*maxDistAngle)/360
	//To fasten the process, let's put the pre-calculated constants' value
	//So, 2*PIE*RADIUS/360 comes out to be 0.55
	int arcLength = 0.55*maxDistAngle;
	
	//Now, time = distance/velocity
	int turningTime = arcLength/15;
  return turningTime;
}


int setTurningDirection(){
  Serial.println(__FUNCTION__);
	if(maxDistAngle>90)
		return LEFT;
	else if(maxDistAngle<90)
		return RIGHT;
	else if(maxDistAngle == 90)
		return BACKSIDE;
	else{
		Serial.println("Something wrong. Shouldn't this statement gets printed");
		return -3;
        }
}

void findPath(){
		runmotor(RELEASE);
         delay(1000);
		maxDistance = readMaxDistance();
                Serial.print("maxDistance ");
                Serial.println(maxDistance);
        delay(1000);
		turningTime = calculateTurningTime();
                Serial.print("turningTime ");
                Serial.println(turningTime);
        delay(1000);
		turningDirection = setTurningDirection();
                Serial.print("turningDirection ");
                Serial.println(turningDirection);
        delay(1000);
		if(RIGHT == turningDirection)
			turning(FORWARD, BACKWARD,turningTime);
		else if(LEFT == turningDirection)
			turning(BACKWARD, FORWARD, turningTime);
		else if(BACKSIDE == turningDirection){
			runmotor(BACKWARD);
			delay(turningTime*1000);
			runmotor(RELEASE);
		}
		else
			Serial.println("No cases matched for direction. Something wrong");

        myservo.write(90);
        delay(1000);

}
//////////////////////////////MAIN FUNCTIONS/////////////////////////////////////
void setup(){
	Serial.begin(9600);           // set up Serial library at 9600 bps
    Serial.println(__FUNCTION__);
	myservo.attach(9);
  
  // turn on motor
	motor1.setSpeed(255);
	motor2.setSpeed(255);
 
	motor1.run(RELEASE);
	motor2.run(RELEASE);
}

void loop() {
  Serial.println(__FUNCTION__);
	distance = readDistance();
	Serial.print("Distance: ");
        Serial.println(distance);
        delay(1000);
	if(distance<MIN_DISTANCE)
          findPath();
	runmotor(FORWARD);
}

//////////////////////////////MAIN FUNCTIONS/////////////////////////////////////
