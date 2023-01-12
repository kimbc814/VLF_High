

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

#define speed_nomal 100
#define maxDistance 700//cm


float  F_distance = 0.0,L_distance = 0.0,R_distance = 0.0,
    F_distance_old = 0.0,L_distance_old = 0.0,R_distance_old = 0.0,
    F_distance_error = 0.0,L_distance_error = 0.0,R_distance_error = 0.0, distance_error=0.0;

int index;
int mission_flag =-1;
int turn_num=0;
int motor_diff =0;
int line_sensor[5]={0,0,0,0,0};
int R_num=80/speed_nomal*800;

float robot_width=159;
float mazor_width=1300;
float mazor_width_tolerance=0.1*mazor_width;

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
  // line_sensor[0] line_sensor[1]  line_sensor[2]  line_sensor[3]  line_sensor[4]
  //      -4        -3    -2    -1      0   1   2     3 4
  if(sum == 1){
    if(line_sensor[0]==1)line_index=-4;
    if(line_sensor[1]==1)line_index=-2;
    if(line_sensor[2]==1)line_index=0;
    if(line_sensor[3]==1)line_index=2;
    if(line_sensor[4]==1)line_index=4;
  }
  else if(sum == 2){
    if((line_sensor[0]==1)&&(line_sensor[1]==1))line_index=-3;
    if((line_sensor[1]==1)&&(line_sensor[2]==1))line_index=-1;
    if((line_sensor[2]==1)&&(line_sensor[3]==1))line_index=1;
    if((line_sensor[3]==1)&&(line_sensor[4]==1))line_index=3;
  }
  else if(sum == 5){
    if((line_sensor[0]==1)&&(line_sensor[1]==1)&&(line_sensor[2]==1)&&(line_sensor[3]==1)&&(line_sensor[4]==1))line_index=-10;
  }
  else line_index = -5555;
  Serial.print(line_index);
  Serial.print("");
  return line_index;
} //라인센서 구동함수

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
void find_wall_obstacle(){
	read_sonar_sensor();
	if(F_distance <=200){
      while(1){
        M_CTL(0,0,100);
        read_sonar_sensor();
     	 if(F_distance > 100)break;	
  	  }
    }
	if((R_distance+L_distance+robot_width >= mazor_width-mazor_width_tolerance) && (R_distance+L_distance+robot_width <= mazor_width+mazor_width_tolerance))
		mission_flag = 2;
}
void cos_line(){

	
	index = read_line_sensor();
	
	switch(index){
    //정지
    case -10: 
      M_CTL(0,0,100);
      break;
    //우회전
    case 1: 
      M_CTL(speed_nomal,0.45*speed_nomal,1);
      break;
    case 2:
      M_CTL(speed_nomal,0.35*speed_nomal,1);
      break;
    case 3:
      M_CTL(speed_nomal,0.3*speed_nomal,1);
      break;
    case 4: 
      while(1){
		  M_CTL(speed_nomal,-0.3*speed_nomal,1);
		  index = read_line_sensor();
		  read_sonar_sensor();
		  if((index != 4)&&(index != 2) || ((R_distance+L_distance+robot_width >= mazor_width-mazor_width_tolerance) && (R_distance+L_distance+robot_width <= mazor_width+mazor_width_tolerance)))
			  break;
      }
      break;
    //전진
    case 0: 
      M_CTL(speed_nomal,speed_nomal,1);
      break;
    //좌회전
    case -1: 
      M_CTL(0.45*speed_nomal,speed_nomal,1);
      break;
    case -2: 
      M_CTL(0.35*speed_nomal,speed_nomal,1);
      break;
    case -3: 
      M_CTL(0.3*speed_nomal,speed_nomal,1);
      break;
    case -4: 
      while(1){
      M_CTL(-0.3*speed_nomal,speed_nomal,1);
      index = read_line_sensor();
		  read_sonar_sensor();
      if((index != -4)&&(index != -2) || ((R_distance+L_distance+robot_width >= mazor_width-mazor_width_tolerance) && (R_distance+L_distance+robot_width <= mazor_width+mazor_width_tolerance))){
        break;
        }
      }
      break;
      
  }
	
}
void turn_R(){
	M_CTL(0,0,10);
    M_CTL(speed_nomal,-speed_nomal,R_num);
	turn_num =1;
}
void line_set_mid(){
	 M_CTL(0,0,10);
    M_CTL(speed_nomal,-speed_nomal,R_num/2);
    int turn_dix =0;
    
    //선찾기
    while(1){
      index = read_line_sensor();
      read_sonar_sensor();
      if(index != -5555){
        M_CTL(speed_nomal,speed_nomal,100);
        
        if(turn_dix % 2 == 0){
          M_CTL(0,0,10);
          M_CTL(-speed_nomal,speed_nomal,R_num/2);
			
        }
        else if(turn_dix % 2 == 1){
          M_CTL(0,0,10);
          M_CTL(speed_nomal,-speed_nomal,R_num/2);
			
          }
        
        break;
      }
      else if(F_distance <120 && index ==-5555){
        if(turn_dix % 2 == 0){
          M_CTL(0,0,10);
          M_CTL(-speed_nomal,speed_nomal,R_num/2);
          turn_dix++;
        }
        else {
          M_CTL(0,0,10);
          M_CTL(speed_nomal,-speed_nomal,R_num/2);
          turn_dix++;
        }
      } 
      else {
      M_CTL(0,0,1);
      M_CTL(speed_nomal,speed_nomal,30);
      }
  }
}
void cos_miro(){
	
    read_sonar_sensor();
    update_sonar_error();
    update_sonar_old();
      update_sonar_error_RL();
    
    if(F_distance < 200 ){
		if(turn_num == 0)turn_R();
		else{
			turn_R();
			line_set_mid();
			mission_flag = 3;
		}
	}
	else if((distance_error<mazor_width_tolerance) && (distance_error>-mazor_width_tolerance)){
        //각도가 오차범위 내라면 전진
        M_CTL(speed_nomal,speed_nomal,50);
      }
	else if(distance_error<-mazor_width_tolerance || L_distance_error > mazor_width_tolerance/2){
        //좌측으로 붙기.
        M_CTL(speed_nomal*0.4,speed_nomal,50);
      }
	else if(distance_error>mazor_width_tolerance || L_distance_error < -mazor_width_tolerance/2){
        //우측으로 붙기.
        M_CTL(speed_nomal,speed_nomal*0.4,50);
      }   
  
  
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
  
  while(mission_flag == -1){
  read_sonar_sensor();
  index = read_line_sensor();
  if(index !=-5555 ){
	  M_CTL(0,0,100);
	  mission_flag = 1;
  }
  }
  Serial.print(R_distance); Serial.print(" ");
  Serial.print(L_distance); Serial.print(" ");
  Serial.println(distance_error);
  
switch(mission_flag){
	case -1:
		delay(100);
		break;
	case 1:
		cos_line();
		find_wall_obstacle();
	case 3:
		cos_line();
	break;	
	
	case 2:
		cos_miro();
		break;
}
  
}
