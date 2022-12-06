// C++ code
//n mm에서 멈춤 후 우로 90도 회전
#include<NewPing.h>
//좌
#define MOTOR_L_EN1 3
#define MOTOR_L_EN2 2
#define MOTOR_L_PWM 5
//우
#define MOTOR_R_EN1 4
#define MOTOR_R_EN2 7
#define MOTOR_R_PWM 6

#define F_Sonar 8
#define R_Sonar 10
#define L_Sonar 11

int line_sensor[5]={0,0,0,0,0};
int maxDistance=400;//cm
float F_distance,L_distance,R_distance;
int time_msec,time_90,speed_nomal,car_line;

int read_line_sensor(){
	int i,line_index;
	int sum=0;
	
	for(i=0;i<5;i++){
		line_sensor[i]=digitalRead(A0+i);
		sum+=line_sensor[i];
		Serial.print(line_sensor[i]);
		Serial.print(" ");
	}
	Serial.print("");
	// line_sensor[0]	line_sensor[1]	line_sensor[2]	line_sensor[3]	line_sensor[4]
	//      -4				-3		-2		-1			0		1		2			3	4
	if(sum == 1){
		if(line_sensor[0]==1)line_index=-4;
		if(line_sensor[1]==1)line_index=-2;
		if(line_sensor[2]==1)line_index=0;
		if(line_sensor[3]==1)line_index=2;
		if(line_sensor[4]==1)line_index=4;
	}
	if(sum == 2){
		if((line_sensor[0]==1)&&(line_sensor[1]==1))line_index=-3;
		if((line_sensor[1]==1)&&(line_sensor[2]==1))line_index=-1;
		if((line_sensor[2]==1)&&(line_sensor[3]==1))line_index=1;
		if((line_sensor[3]==1)&&(line_sensor[4]==1))line_index=3;
	}
	if(sum == 5){
		if((line_sensor[0]==1)&&(line_sensor[1]==1)&&(line_sensor[2]==1)&&(line_sensor[3]==1)&&(line_sensor[4]==1))line_index=-10;
	}
	Serial.print(line_index);
	Serial.print("");
	return line_index;
} //라인센서 구동함수

NewPing Sonar[3]={
NewPing(F_Sonar,F_Sonar,maxDistance),
NewPing(R_Sonar,R_Sonar,maxDistance),
NewPing(L_Sonar,L_Sonar,maxDistance),
};
void M_CTL(int dir_L,int dir_R,int spd_L,int spd_R){
	if((dir_L =1)){
		if(dir_R =1){
			digitalWrite(MOTOR_L_EN1 ,HIGH);
 			digitalWrite(MOTOR_L_EN2 ,LOW);
			analogWrite(MOTOR_L_PWM,spd_L);
			//4,7 다르면 전진
 			digitalWrite(MOTOR_R_EN1 ,HIGH);
  			digitalWrite(MOTOR_R_EN2 ,LOW);
			analogWrite(MOTOR_R_PWM,spd_R);
			}
		else if(dir_R =-1){
			digitalWrite(MOTOR_L_EN1 ,HIGH);
 			digitalWrite(MOTOR_L_EN2 ,LOW);
			analogWrite(MOTOR_L_PWM,spd_L);
			//4,7 다르면 후진
 			digitalWrite(MOTOR_R_EN1 ,LOW);
  			digitalWrite(MOTOR_R_EN2 ,HIGH);
			analogWrite(MOTOR_R_PWM,spd_R);
		}

	}
	else if(dir_L =-1)){
		if(dir_R=-1){
			//2,3 다르면 후진
			digitalWrite(MOTOR_L_EN1 ,LOW);
			digitalWrite(MOTOR_L_EN2 ,HIGH);
			analogWrite(MOTOR_L_PWM,spd_L);
			//4,7 다르면 후진
 			digitalWrite(MOTOR_R_EN1 ,LOW);
 			digitalWrite(MOTOR_R_EN2 ,HIGH);
			analogWrite(MOTOR_R_PWM,spd_R);
			}
		else if(dir_R=1){
			//2,3 다르면 후진
			digitalWrite(MOTOR_L_EN1 ,LOW);
			digitalWrite(MOTOR_L_EN2 ,HIGH);
			analogWrite(MOTOR_L_PWM,spd_L);
			//4,7 다르면 전진
 			digitalWrite(MOTOR_R_EN1 ,HIGH);
  			digitalWrite(MOTOR_R_EN2 ,LOW);
			analogWrite(MOTOR_R_PWM,spd_R);
		}
	}
	else if((dir_L =0)&&(dir_R=0)){
		//2,3 같으면 멈춤
		digitalWrite(MOTOR_L_EN1 ,HIGH);
		digitalWrite(MOTOR_L_EN2 ,HIGH);
		analogWrite(MOTOR_L_PWM,spd_L);
		//4,7 같으면 멈춤
		digitalWrite(MOTOR_R_EN1 ,HIGH);
		digitalWrite(MOTOR_R_EN2 ,HIGH);
		analogWrite(MOTOR_R_PWM,spd_R);
	}
	
}
/*
void on_stop(){
	//2,3 같으면 멈춤
	  digitalWrite(MOTOR_L_EN1 ,HIGH);
	  digitalWrite(MOTOR_L_EN2 ,HIGH);
	analogWrite(MOTOR_L_PWM,speed_nomal);
	  //4,7 같으면 멈춤
	  digitalWrite(MOTOR_R_EN1 ,HIGH);
	  digitalWrite(MOTOR_R_EN2 ,HIGH);
	analogWrite(MOTOR_R_PWM,speed_nomal);
}
void on_FF(int a){
//2,3 다르면 전진
  digitalWrite(MOTOR_L_EN1 ,HIGH);
  digitalWrite(MOTOR_L_EN2 ,LOW);
	analogWrite(MOTOR_L_PWM,speed_nomal);
//4,7 다르면 전진
  digitalWrite(MOTOR_R_EN1 ,HIGH);
  digitalWrite(MOTOR_R_EN2 ,LOW);
	analogWrite(MOTOR_R_PWM,speed_nomal);
	delay(a);
}
void on_FR(int a){
//2,3 다르면 전진
  digitalWrite(MOTOR_L_EN1 ,HIGH);
  digitalWrite(MOTOR_L_EN2 ,LOW);
	analogWrite(MOTOR_L_PWM,speed_nomal);
//4,7 다르면 후진
  digitalWrite(MOTOR_R_EN1 ,LOW);
  digitalWrite(MOTOR_R_EN2 ,HIGH);
	analogWrite(MOTOR_R_PWM,speed_nomal);
	delay(a);
}
void on_FL(int a){
//2,3 다르면 후진
  digitalWrite(MOTOR_L_EN1 ,LOW);
  digitalWrite(MOTOR_L_EN2 ,HIGH);
	analogWrite(MOTOR_L_PWM,speed_nomal);
//4,7 다르면 전진
  digitalWrite(MOTOR_R_EN1 ,HIGH);
  digitalWrite(MOTOR_R_EN2 ,LOW);
	analogWrite(MOTOR_R_PWM,speed_nomal);
	delay(a);
}
void on_BB(int a){
//2,3 다르면 후진
  digitalWrite(MOTOR_L_EN1 ,LOW);
  digitalWrite(MOTOR_L_EN2 ,HIGH);
	analogWrite(MOTOR_L_PWM,speed_nomal);
//4,7 다르면 후진
  digitalWrite(MOTOR_R_EN1 ,LOW);
  digitalWrite(MOTOR_R_EN2 ,HIGH);
	analogWrite(MOTOR_R_PWM,speed_nomal);
	delay(a);
}
void on_BR(int a){
//2,3 다르면 후진
  digitalWrite(MOTOR_L_EN1 ,LOW);
  digitalWrite(MOTOR_L_EN2 ,HIGH);
	analogWrite(MOTOR_L_PWM,speed_nomal);
//4,7 다르면 전진
  digitalWrite(MOTOR_R_EN1 ,HIGH);
  digitalWrite(MOTOR_R_EN2 ,LOW);
	analogWrite(MOTOR_R_PWM,speed_nomal);
	delay(a);
}
void on_BL(int a){
	//2,3 다르면 전진
  digitalWrite(MOTOR_L_EN1 ,HIGH);
  digitalWrite(MOTOR_L_EN2 ,LOW);
	analogWrite(MOTOR_L_PWM,speed_nomal);
//4,7 다르면 후진
  digitalWrite(MOTOR_R_EN1 ,LOW);
  digitalWrite(MOTOR_R_EN2 ,HIGH);
	analogWrite(MOTOR_R_PWM,speed_nomal);
	delay(a);
}
*/

void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(MOTOR_L_EN1 ,OUTPUT);
	pinMode(MOTOR_L_EN2 ,OUTPUT);
	pinMode(MOTOR_L_EN1 ,OUTPUT);
	pinMode(MOTOR_L_EN2 ,OUTPUT);
	
	
	car_line = 1;
	speed_nomal =80;
	analogWrite(MOTOR_L_PWM,speed_nomal);
	analogWrite(MOTOR_R_PWM,speed_nomal);
	time_msec = 1000;
	time_90 = (80/speed_nomal)*950;  //속도가 빠를수록 초는 느려야하니 반비례, 속도 80일때 950이 90도 회전함.
	
		
	
	Serial.begin(115200);
	
}

void loop()
{
	int index;
	index = read_line_sensor();
  //거리 단위 mm
 F_distance = Sonar[0].ping_cm()*10;
 R_distance = Sonar[1].ping_cm()*10;
 L_distance = Sonar[2].ping_cm()*10;
	
	switch(index){
		//정지
		case -10: 
			M_CTL(0,0,0,0);
			break;
		//우회전
		case 1: 
			M_CTL(1,1,70,60);
			break;
		case 2:
			M_CTL(1,1,70,50);
			break;
		case 3:
			M_CTL(1,1,70,40);
			break;
		case 4: 
			M_CTL(1,1,70,30);
			break;
		//전진
		case 0: 
			M_CTL(1,1,70,70);
			break;
		//좌회전
		case -1: 
			M_CTL(1,1,60,70);
			break;
		case -2: 
			M_CTL(1,1,50,70);
			break;
		case -3: 
			M_CTL(1,1,40,70);
			break;
		case -4: 
			M_CTL(1,1,30,70);
			break;
	}
	
}
