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

#define speed_nomal 120




int line_sensor[5]={0,0,0,0,0};
int maxDistance=400;//cm
float F_distance,L_distance,R_distance,
		F_distance1,L_distance1,R_distance1,
		d_F_distance,d_R_distance,d_L_distance;
int time_msec,time_90,Road_line;


NewPing Sonar[3]={
NewPing(F_Sonar,F_Sonar,maxDistance),
NewPing(R_Sonar,R_Sonar,maxDistance),
NewPing(L_Sonar,L_Sonar,maxDistance),
};

	void M_CTL(int dir_L,int dir_R,float spd_L,float spd_R){
	if((dir_L ==1)){
		if(dir_R ==1){
			digitalWrite(MOTOR_L_EN1 ,HIGH);
 			digitalWrite(MOTOR_L_EN2 ,LOW);
			analogWrite(MOTOR_L_PWM,spd_L);
			//4,7 다르면 전진
 			digitalWrite(MOTOR_R_EN1 ,HIGH);
  			digitalWrite(MOTOR_R_EN2 ,LOW);
			analogWrite(MOTOR_R_PWM,spd_R);
			}
		else if(dir_R ==-1){
			digitalWrite(MOTOR_L_EN1 ,HIGH);
 			digitalWrite(MOTOR_L_EN2 ,LOW);
			analogWrite(MOTOR_L_PWM,spd_L);
			//4,7 다르면 후진
 			digitalWrite(MOTOR_R_EN1 ,LOW);
  			digitalWrite(MOTOR_R_EN2 ,HIGH);
			analogWrite(MOTOR_R_PWM,spd_R);
		}

	}
	else if(dir_L ==-1){
		if(dir_R==-1){
			//2,3 다르면 후진
			digitalWrite(MOTOR_L_EN1 ,LOW);
			digitalWrite(MOTOR_L_EN2 ,HIGH);
			analogWrite(MOTOR_L_PWM,spd_L);
			//4,7 다르면 후진
 			digitalWrite(MOTOR_R_EN1 ,LOW);
 			digitalWrite(MOTOR_R_EN2 ,HIGH);
			analogWrite(MOTOR_R_PWM,spd_R);
			}
		else if(dir_R==1){
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
	else if((dir_L ==0)&&(dir_R==0)){
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
	



void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(MOTOR_L_EN1 ,OUTPUT);
	pinMode(MOTOR_L_EN2 ,OUTPUT);
	pinMode(MOTOR_L_EN1 ,OUTPUT);
	pinMode(MOTOR_L_EN2 ,OUTPUT);
	
	
	Road_line = 1;
	analogWrite(MOTOR_L_PWM,speed_nomal);
	analogWrite(MOTOR_R_PWM,speed_nomal);
	time_msec = 1000;
	time_90 = (80/speed_nomal)*950;  //속도가 빠를수록 초는 느려야하니 반비례, 속도 80일때 950이 90도 회전함.
	
		
	
	Serial.begin(115200);
	
}

void loop()
{
	
  //거리 단위 mm
	
	//시작시 잠시 멈춤
	delay(5000);
	//초음파 센서 측정
	F_distance = Sonar[0].ping_cm()*10;
	R_distance = Sonar[1].ping_cm()*10;
	L_distance = Sonar[2].ping_cm()*10;
	//전진 명령
	M_CTL(1,1,70,70);
	delay(1000);
	//정지 명령
	M_CTL(0,0,0,0);
	delay(100);
	//초음파 센서 측정
	F_distance1 = Sonar[0].ping_cm()*10;
	R_distance1 = Sonar[1].ping_cm()*10;
	L_distance1 = Sonar[2].ping_cm()*10;
	//거리계산
	d_F_distance = F_distance1-F_distance;
	d_R_distance = R_distance1-R_distance;
	d_L_distance = L_distance1-L_distance;
	//계산 결과 시리얼 출력
	/*
	Serial.print("F_distance : ");
		Serial.println(F_distance);
		Serial.print("R_distance : ");
		Serial.println(R_distance);
		Serial.print("L_distance : ");
		Serial.println(L_distance);
	Serial.println("");
	
	Serial.print("F_distance1 : ");
		Serial.println(F_distance1);
		Serial.print("R_distance1 : ");
		Serial.println(R_distance1);
		Serial.print("L_distance1 : ");
		Serial.println(L_distance1);
	Serial.println("");
	
	Serial.print("d_F_distance : ");
		Serial.println(d_F_distance);
		Serial.print("d_R_distance : ");
		Serial.println(d_R_distance);
		Serial.print("d_L_distance : ");
		Serial.println(d_L_distance);
	*/
		Serial.print("deg : ");
	
	Serial.println(atan(d_R_distance/d_F_distance)*180/3.14);
	delay(10000);
	
	/*
	if(atan(d_R_distance/d_F_distance)*180/3.14 > 0){
		M_CTL(1,-1,40,40);
		delay(100);
	}
	else{
		M_CTL(-1,1,40,40);
		delay(100);
	}
	*/


}
