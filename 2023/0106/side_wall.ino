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

#define speed_nomal 80
#define maxDistance 150//cm
#define p_gain 1.5

float  F_distance = 0.0,L_distance = 0.0,R_distance = 0.0,
    F_distance_old = 0.0,L_distance_old = 0.0,R_distance_old = 0.0,
    F_distance_error = 0.0,L_distance_error = 0.0,R_distance_error = 0.0, distance_error=0.0;

int cos_num =0;
int motor_diff =0;

float robot_width=159;
float mazor_width=470;
float mazor_width_tolerance=0.1*mazor_width;

NewPing Sonar[3]={
NewPing(F_Sonar,F_Sonar,maxDistance),
NewPing(R_Sonar,R_Sonar,maxDistance),
NewPing(L_Sonar,L_Sonar,maxDistance),
};

  void M_CTL(float spd_L,float spd_R,int delay_time){
  if(spd_L >0){
    digitalWrite(MOTOR_L_EN1 ,HIGH);
      digitalWrite(MOTOR_L_EN2 ,LOW);
      analogWrite(MOTOR_L_PWM,spd_L);
  }
  else if(spd_L ==0){
     digitalWrite(MOTOR_L_EN1 ,HIGH);
    digitalWrite(MOTOR_L_EN2 ,HIGH);
    analogWrite(MOTOR_L_PWM,spd_L);
  }
  else{
    spd_L = -spd_L;
    digitalWrite(MOTOR_L_EN1 ,LOW);
      digitalWrite(MOTOR_L_EN2 ,HIGH);
      analogWrite(MOTOR_L_PWM,spd_L);
  }
  if(spd_R >0){
    digitalWrite(MOTOR_R_EN1 ,HIGH);
      digitalWrite(MOTOR_R_EN2 ,LOW);
      analogWrite(MOTOR_R_PWM,spd_R);
  }
  else if(spd_R ==0){
     digitalWrite(MOTOR_R_EN1 ,HIGH);
    digitalWrite(MOTOR_R_EN2 ,HIGH);
    analogWrite(MOTOR_R_PWM,spd_R);
  }
  else{
    spd_R = -spd_R;
    digitalWrite(MOTOR_R_EN1 ,LOW);
      digitalWrite(MOTOR_R_EN2 ,HIGH);
      analogWrite(MOTOR_R_PWM,spd_R);
  }
  delay(delay_time);
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
void update_sonar_error_RL(){
  distance_error = R_distance - L_distance;
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
  M_CTL(speed_nomal,speed_nomal,1);
  read_sonar_sensor();
  
  Serial.print(R_distance); Serial.print(" ");
  Serial.print(L_distance); Serial.print(" ");
  Serial.println(distance_error);
  if((R_distance+L_distance+robot_width >= mazor_width-mazor_width_tolerance) && (R_distance+L_distance+robot_width <= mazor_width+mazor_width_tolerance)){
    cos_num =1;
    while(1){
      /*int index;
      //index = read_line_sensor();
      if((R_distance+L_distance+robot_width > mazor_width+mazor_width_tolerance) && index != -5555){
        cos_num ++;
        break;
      }     */
  read_sonar_sensor();
      update_sonar_error_RL();
      //motor_diff = distance_error *p_gain;
      
      if(distance_error>mazor_width_tolerance){
        //좌측으로 붙기.
        M_CTL(speed_nomal*0.5,speed_nomal,300);
      }
      if(distance_error<mazor_width_tolerance){
        
        //우측으로 붙기.
        M_CTL(speed_nomal,speed_nomal*0.5,300);
      }
	if((distance_error<mazor_width_tolerance) && (distance_error>-mazor_width_tolerance)){
        //각도가 오차범위 내라면 전진
        M_CTL(speed_nomal,speed_nomal,300);
      }
    }
  }
  
  
  
}
