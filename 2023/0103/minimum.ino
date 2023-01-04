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

#define NO_MAX_WAYPOINTS 2

float   F[NO_MAX_WAYPOINTS] = {0,};
float   R[NO_MAX_WAYPOINTS] = {0,};
float L[NO_MAX_WAYPOINTS] = {0,};

int line_sensor[5]={0,0,0,0,0};
int maxDistance=60;//cm
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
int minimum=maxDistance*10+1;
int i_save=0;
void loop()
{
  
  //거리 단위 mm
  
  //시작시 잠시 멈춤
  delay(2000);
  //초음파 센서 측정
  F_distance = Sonar[0].ping_cm()*10;
  R_distance = Sonar[1].ping_cm()*10;
  L_distance = Sonar[2].ping_cm()*10;
  
 

for(int i=0;i<1000;i++){
     F[i%2] = F_distance = Sonar[0].ping_cm()*10;
	float avrF0;
	if(i>0 && F_distance > 50){
		avrF0=(F[0]+F[1])/2;
	}
	
      if(avrF0 < minimum ){
      minimum = F_distance;
      i_save= i;
      Serial.println(minimum);  
    }
     M_CTL(1,-1,90,90);
     delay(1);
    
   
    }
  
  M_CTL(0,0,0,0);
   delay(10);
  
  
 for(int i=1000;i>i_save;i--){

    M_CTL(-1,1,90,90);
    delay(1);
     
    }
  
  M_CTL(0,0,0,0);
   delay(10000);
    

}
