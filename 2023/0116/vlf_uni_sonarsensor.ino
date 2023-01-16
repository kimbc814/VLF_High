//VLF_대학 초음파 센서
#include <NewPing.h>
//초음파 센서 
#define L_TRIG 3
#define L_ECHO 8
#define F_TRIG 9
#define F_ECHO 10
#define R_TRIG 11
#define R_ECHO 12
//모터
#define MOTOR_DIR 4
#define MOTOR_PWM 5


#define maxDistance 800//cm

//초음파 데이터
float  F_distance = 0.0,L_distance = 0.0,R_distance = 0.0;

NewPing Sonar[3]={
NewPing(F_TRIG,F_ECHO,maxDistance),
NewPing(L_TRIG,L_ECHO,maxDistance),
NewPing(R_TRIG,R_ECHO,maxDistance)
};

void Read_sonar_sensor(){
  F_distance = Sonar[0].ping_cm()*10;
  L_distance = Sonar[1].ping_cm()*10;
  R_distance = Sonar[2].ping_cm()*10;
  if(R_distance == 0) R_distance = maxDistance * 10.0;
  if(L_distance == 0) L_distance = maxDistance * 10.0;
  if(F_distance == 0) F_distance = maxDistance * 10.0;
	
	Serial.print("R_distance : ");
	Serial.print(R_distance);
	Serial.print("mm  ");
	
	Serial.print("F_distance : ");
	Serial.print(F_distance);
	Serial.print("mm  ");
	
	Serial.print("L_distance : ");
	Serial.print(L_distance);
	Serial.println("mm");
}

void setup() {

pinMode(MOTOR_DIR,OUTPUT);
pinMode(MOTOR_PWM,OUTPUT);
	
  Serial.begin(115200);
	
}

void loop() {
	
	digitalWrite(MOTOR_DIR,1); //digitalWrite(MOTOR_DIR,0);
	analogWrite(MOTOR_PWM,50);
	
  delay(2000);
  Read_sonar_sensor();
	
}