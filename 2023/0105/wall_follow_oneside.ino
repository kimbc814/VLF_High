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
#define maxDistance 150//cm
#define p_gain 5

float  F_distance = 0.0,L_distance = 0.0,R_distance = 0.0,
    F_distance_old = 0.0,L_distance_old = 0.0,R_distance_old = 0.0,
    F_distance_error = 0.0,L_distance_error = 0.0,R_distance_error = 0.0;
int motor_diff =0;


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
      delay(250);
      }
    else if(dir_R ==-1){
      digitalWrite(MOTOR_L_EN1 ,HIGH);
      digitalWrite(MOTOR_L_EN2 ,LOW);
      analogWrite(MOTOR_L_PWM,spd_L);
      //4,7 다르면 후진
      digitalWrite(MOTOR_R_EN1 ,LOW);
        digitalWrite(MOTOR_R_EN2 ,HIGH);
      analogWrite(MOTOR_R_PWM,spd_R);
      delay(250);
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
      delay(250);
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
      delay(250);
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
    delay(250);
  }
  
}

void read_sonar_sensor(){
  F_distance = Sonar[0].ping_cm()*10;
  R_distance = Sonar[1].ping_cm()*10;
  L_distance = Sonar[2].ping_cm()*10;
  if(R_distance == 0) R_distance = maxDistance * 10.0;
  if(L_distance == 0) L_distance = maxDistance * 10.0;
  if(F_distance == 0) F_distance = maxDistance * 10.0;
}

void update_sonar_old(){
  R_distance_old = R_distance;
  L_distance_old = L_distance;
  F_distance_old = F_distance;
  }

void update_sonar_error(){
  R_distance_error = R_distance - R_distance_old;
  L_distance_error = L_distance - L_distance_old;
  F_distance_error = F_distance - F_distance_old;
}


void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(MOTOR_L_EN1 ,OUTPUT);
  pinMode(MOTOR_L_EN2 ,OUTPUT);
  pinMode(MOTOR_L_EN1 ,OUTPUT);
  pinMode(MOTOR_L_EN2 ,OUTPUT);
  
    
  
  Serial.begin(115200);
  
}

void loop()
{
  read_sonar_sensor();
  update_sonar_error();
  update_sonar_old();
  Serial.print(R_distance); Serial.print(" ");
  Serial.print(R_distance_old); Serial.print(" ");
  Serial.println(R_distance_error);
  if(R_distance_error < -200){
    R_distance_error = -10;
  }
  else if(R_distance_error > 200){
    R_distance_error = 10;
  }
  Serial.println(R_distance_error);
  
  if(R_distance < 100){
  motor_diff =R_distance_error*p_gain*(10-R_distance);
  }
  else motor_diff =R_distance_error*p_gain;
  
  if( R_distance_error < -10){
    M_CTL(1,1,80+motor_diff,80-motor_diff);
  }
  else if(R_distance_error >10){
    M_CTL(1,1,80+motor_diff,80-motor_diff);
  }
  else{
    M_CTL(1,1,80,80);
   
  }
delay(100);
}
