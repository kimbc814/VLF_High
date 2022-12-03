// C++ code
//n mm에서 멈춤 후 우로 90도 회전
#include<NewPing.h>
//좌
#define IN1PIN 3
#define IN2PIN 2
#define ENPIN1 5
//우
#define IN3PIN 4
#define IN4PIN 7
#define ENPIN2 6

#define F_Sonar 8
#define R_Sonar 10
#define L_Sonar 11
int maxDistance=400;//cm
NewPing Sonar[3]={
NewPing(F_Sonar,F_Sonar,maxDistance);
NewPing(R_Sonar,R_Sonar,maxDistance);
NewPing(L_Sonar,L_Sonar,maxDistance);
};
/*
float F_Sonar_sensor(){
  float duration =0.0;
  float distance =0.0;
  pinMode(F_Sonar,OUTPUT);
  digitalWrite(F_Sonar,LOW);
  digitalWrite(F_Sonar,HIGH);
  delay(10);
  digitalWrite(F_Sonar,LOW);
  pinMode(F_Sonar,INPUT);
  duration = pulseIn(F_Sonar,HIGH);
  distance=(duration *340.0)/2.0/1000.0;
  return distance;
}

float L_Sonar_sensor(){
  float duration =0.0;
  float distance =0.0;
  pinMode(L_Sonar,OUTPUT);
  digitalWrite(L_Sonar,LOW);
  digitalWrite(L_Sonar,HIGH);
  delay(10);
  digitalWrite(L_Sonar,LOW);
  pinMode(L_Sonar,INPUT);
  
  duration = pulseIn(L_Sonar,HIGH);
  distance=(duration *340.0)/2.0/1000.0;
  return distance;
}

float R_Sonar_sensor(){
  float duration =0.0;
  float distance =0.0;
  pinMode(R_Sonar,OUTPUT);
  digitalWrite(R_Sonar,LOW);
  digitalWrite(R_Sonar,HIGH);
  delay(10);
  digitalWrite(R_Sonar,LOW);
  pinMode(R_Sonar,INPUT);
  duration = pulseIn(R_Sonar,HIGH);
  distance=(duration *340.0)/2.0/1000.0;
  return distance;
}
*/
void on_stop(int a){
	
	//2,3 같으면 멈춤
	  digitalWrite(IN1PIN ,HIGH);
	  digitalWrite(IN2PIN ,HIGH);
	analogWrite(ENPIN1,speed_nomal);
	  //4,7 같으면 멈춤
	  digitalWrite(IN3PIN ,HIGH);
	  digitalWrite(IN4PIN ,HIGH);
	analogWrite(ENPIN2,speed_nomal);
	delay(a);
}
void on_FF(int a){
//2,3 다르면 전진
  digitalWrite(IN1PIN ,HIGH);
  digitalWrite(IN2PIN ,LOW);
	analogWrite(ENPIN1,speed_nomal);
//4,7 다르면 전진
  digitalWrite(IN3PIN ,HIGH);
  digitalWrite(IN4PIN ,LOW);
	analogWrite(ENPIN2,speed_nomal);
	delay(a);
}
void on_FFR(int a){
//2,3 다르면 전진
  digitalWrite(IN1PIN ,HIGH);
  digitalWrite(IN2PIN ,LOW);
	analogWrite(ENPIN1,speed_nomal);
//4,7 다르면 전진
  digitalWrite(IN3PIN ,HIGH);
  digitalWrite(IN4PIN ,LOW);
	analogWrite(ENPIN2,speed_curve);
	delay(a);
}
void on_FFL(int a){
//2,3 다르면 전진
  digitalWrite(IN1PIN ,HIGH);
  digitalWrite(IN2PIN ,LOW);
	analogWrite(ENPIN1,speed_curve);
//4,7 다르면 전진
  digitalWrite(IN3PIN ,HIGH);
  digitalWrite(IN4PIN ,LOW);
	analogWrite(ENPIN2,speed_nomal);
	delay(a);
}
void on_FR(int a){
//2,3 다르면 전진
  digitalWrite(IN1PIN ,HIGH);
  digitalWrite(IN2PIN ,LOW);
	analogWrite(ENPIN1,speed_nomal);
//4,7 다르면 후진
  digitalWrite(IN3PIN ,LOW);
  digitalWrite(IN4PIN ,HIGH);
	analogWrite(ENPIN2,speed_nomal);
	delay(a);
}
void on_FL(int a){
//2,3 다르면 후진
  digitalWrite(IN1PIN ,LOW);
  digitalWrite(IN2PIN ,HIGH);
	analogWrite(ENPIN1,speed_nomal);
//4,7 다르면 전진
  digitalWrite(IN3PIN ,HIGH);
  digitalWrite(IN4PIN ,LOW);
	analogWrite(ENPIN2,speed_nomal);
	delay(a);
}
void on_BB(int a){
//2,3 다르면 후진
  digitalWrite(IN1PIN ,LOW);
  digitalWrite(IN2PIN ,HIGH);
	analogWrite(ENPIN1,speed_nomal);
//4,7 다르면 후진
  digitalWrite(IN3PIN ,LOW);
  digitalWrite(IN4PIN ,HIGH);
	analogWrite(ENPIN2,speed_nomal);
	delay(a);
}
void on_BBL(int a){
//2,3 다르면 후진
  digitalWrite(IN1PIN ,LOW);
  digitalWrite(IN2PIN ,HIGH);
	analogWrite(ENPIN1,speed_curve);
//4,7 다르면 후진
  digitalWrite(IN3PIN ,LOW);
  digitalWrite(IN4PIN ,HIGH);
	analogWrite(ENPIN2,speed_nomal);
	delay(a);
}
void on_BBR(int a){
//2,3 다르면 후진
  digitalWrite(IN1PIN ,LOW);
  digitalWrite(IN2PIN ,HIGH);
	analogWrite(ENPIN1,speed_nomal);
//4,7 다르면 후진
  digitalWrite(IN3PIN ,LOW);
  digitalWrite(IN4PIN ,HIGH);
	analogWrite(ENPIN2,speed_curve);
	delay(a);
}
void on_BR(int a){
//2,3 다르면 후진
  digitalWrite(IN1PIN ,LOW);
  digitalWrite(IN2PIN ,HIGH);
	analogWrite(ENPIN1,speed_nomal);
//4,7 다르면 전진
  digitalWrite(IN3PIN ,HIGH);
  digitalWrite(IN4PIN ,LOW);
	analogWrite(ENPIN2,speed_nomal);
	delay(a);
}
void on_BL(int a){
	//2,3 다르면 전진
  digitalWrite(IN1PIN ,HIGH);
  digitalWrite(IN2PIN ,LOW);
	analogWrite(ENPIN1,speed_nomal);
//4,7 다르면 후진
  digitalWrite(IN3PIN ,LOW);
  digitalWrite(IN4PIN ,HIGH);
	analogWrite(ENPIN2,speed_nomal);
	delay(a);
}


void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(F_Sonar, OUTPUT);
	pinMode(R_Sonar, OUTPUT);
	pinMode(L_Sonar, OUTPUT);
	pinMode(IN1PIN ,OUTPUT);
	pinMode(IN2PIN ,OUTPUT);
	pinMode(IN1PIN ,OUTPUT);
	pinMode(IN2PIN ,OUTPUT);
	
	float F_distance,L_distance,R_distance;
	int time_msec,time_90,speed_nomal,speed_curve,car_line;
	
	car_line = 1;
	speed_nomal =80;
	speed_curve_L =speed_nomal/10;
	analogWrite(ENPIN1,speed_nomal);
	analogWrite(ENPIN2,speed_nomal);
	time_msec = 1000;
	time_90 = (80/speed_nomal)*950;  //속도가 빠를수록 초는 느려야하니 반비례, 속도 80일때 950이 90도 회전함.
	
		
	
	Serial.begin(115200);
	
}

void loop()
{
  
  //거리 단위 mm
 F_distance = Sonar[0].ping_cm()*10;
 R_distance = Sonar[1].ping_cm()*10;
 L_distance = Sonar[2].ping_cm()*10;
  if(F_distance <= 170){  //대충 80퍼 적용되는듯(?) .. 정면 막히면 아래 실행.
	 on_stop(600);
	  if((R_distance <=250)&&(L_distance <=250)){  //양쪽도 막히면 오른쪽으로 유턴
		  on_FR(time_90*2-150);
		  on_stop(600);
	 	 }
	  
	  else if(R_distance <=250){	//오른쪽도 막히면 좌회전
		on_FL(time_90);
		on_stop(600);
		}
	  else if(L_distance <=250){	//왼쪽도 막히면 우회전
		on_FR(time_90);
		on_stop(600);
	 	}
	  else if(car_line == 2){		//전방에 장애물 있을시 2차선이면 1차선으로 변경
		on_FFR(time_90/2);
		  on_stop(600);
		on_FFL(time_90/2);
		  on_stop(600);
		car_line--;
		}
	  else if(car_line == 1){		//전방에 장애물 있을시 1차선이면 2차선으로 변경
		on_FFL(time_90/2);
		  on_stop(600);
		on_FFR(time_90/2);
		  on_stop(600);
		car_line++;
		}
	  
	 
  }
	else{
		on_FF(0);
		
	}
 
}
//우회전,좌회전,유턴