// C++ code
//벽과의 거리 n일때 좌,우회전,유턴.
#define IN1PIN 3
#define IN2PIN 2
#define ENPIN1 5

#define IN3PIN 4
#define IN4PIN 7
#define ENPIN2 6

#define F_Sonar 8
#define R_Sonar 10
#define L_Sonar 11

float F_distance,L_distance,R_distance;
int time_msec,time_90,speed_nomal,speed_curve;





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
void on_stop(int a){
  analogWrite(ENPIN1,speed_nomal);
  analogWrite(ENPIN2,speed_nomal);
  //2,3 같으면 멈춤
    digitalWrite(IN1PIN ,HIGH);
    digitalWrite(IN2PIN ,HIGH);
    //4,7 같으면 멈춤
    digitalWrite(IN3PIN ,HIGH);
    digitalWrite(IN4PIN ,HIGH);
  delay(a);
}
void on_FF(int a){
  analogWrite(ENPIN1,speed_nomal);
  analogWrite(ENPIN2,speed_nomal);
//2,3 다르면 전진
  digitalWrite(IN1PIN ,HIGH);
  digitalWrite(IN2PIN ,LOW);
//4,7 다르면 전진
  digitalWrite(IN3PIN ,HIGH);
  digitalWrite(IN4PIN ,LOW);
  delay(a);
}
void on_FFR(int a){
  analogWrite(ENPIN1,speed_nomal);
  analogWrite(ENPIN2,speed_curve);
//2,3 다르면 전진
  digitalWrite(IN1PIN ,HIGH);
  digitalWrite(IN2PIN ,LOW);
//4,7 다르면 전진
  digitalWrite(IN3PIN ,HIGH);
  digitalWrite(IN4PIN ,LOW);
  delay(a);
}
void on_FFL(int a){
  analogWrite(ENPIN1,speed_curve);
  analogWrite(ENPIN2,speed_nomal);
//2,3 다르면 전진
  digitalWrite(IN1PIN ,HIGH);
  digitalWrite(IN2PIN ,LOW);
//4,7 다르면 전진
  digitalWrite(IN3PIN ,HIGH);
  digitalWrite(IN4PIN ,LOW);
  delay(a);
}
void on_FR(int a){
  analogWrite(ENPIN1,speed_nomal);
  analogWrite(ENPIN2,speed_nomal);
//2,3 다르면 전진
  digitalWrite(IN1PIN ,HIGH);
  digitalWrite(IN2PIN ,LOW);
//4,7 다르면 후진
  digitalWrite(IN3PIN ,LOW);
  digitalWrite(IN4PIN ,HIGH);
  delay(a);
}
void on_FL(int a){
  analogWrite(ENPIN1,speed_nomal);
  analogWrite(ENPIN2,speed_nomal);
//2,3 다르면 후진
  digitalWrite(IN1PIN ,LOW);
  digitalWrite(IN2PIN ,HIGH);
//4,7 다르면 전진
  digitalWrite(IN3PIN ,HIGH);
  digitalWrite(IN4PIN ,LOW);
  delay(a);
}
void on_BB(int a){
  analogWrite(ENPIN1,speed_nomal);
  analogWrite(ENPIN2,speed_nomal);
//2,3 다르면 후진
  digitalWrite(IN1PIN ,LOW);
  digitalWrite(IN2PIN ,HIGH);
//4,7 다르면 후진
  digitalWrite(IN3PIN ,LOW);
  digitalWrite(IN4PIN ,HIGH);
  delay(a);
}
void on_BBL(int a){
  analogWrite(ENPIN1,speed_curve);
  analogWrite(ENPIN2,speed_nomal);
//2,3 다르면 후진
  digitalWrite(IN1PIN ,LOW);
  digitalWrite(IN2PIN ,HIGH);
//4,7 다르면 후진
  digitalWrite(IN3PIN ,LOW);
  digitalWrite(IN4PIN ,HIGH);
  delay(a);
}
void on_BBR(int a){
  analogWrite(ENPIN1,speed_nomal);
  analogWrite(ENPIN2,speed_curve);
//2,3 다르면 후진
  digitalWrite(IN1PIN ,LOW);
  digitalWrite(IN2PIN ,HIGH);
//4,7 다르면 후진
  digitalWrite(IN3PIN ,LOW);
  digitalWrite(IN4PIN ,HIGH);
  delay(a);
}
void on_BR(int a){
  analogWrite(ENPIN1,speed_nomal);
  analogWrite(ENPIN2,speed_nomal);
//2,3 다르면 후진
  digitalWrite(IN1PIN ,LOW);
  digitalWrite(IN2PIN ,HIGH);
//4,7 다르면 전진
  digitalWrite(IN3PIN ,HIGH);
  digitalWrite(IN4PIN ,LOW);
  delay(a);
}
void on_BL(int a){
  analogWrite(ENPIN1,speed_nomal);
  analogWrite(ENPIN2,speed_nomal);
  //2,3 다르면 전진
  digitalWrite(IN1PIN ,HIGH);
  digitalWrite(IN2PIN ,LOW);
//4,7 다르면 후진
  digitalWrite(IN3PIN ,LOW);
  digitalWrite(IN4PIN ,HIGH);
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
  speed_nomal =80;
  speed_curve =speed_nomal/4;
  analogWrite(ENPIN1,speed_nomal);
  analogWrite(ENPIN2,speed_nomal);
  time_msec = 1000;
  time_90 = 950;
  Serial.begin(115200);
  
}

void loop()
{
  
  
 F_distance = F_Sonar_sensor();
 R_distance = R_Sonar_sensor();
 L_distance = L_Sonar_sensor();
  if(F_distance <= 170){  //mm 대충 절반만 적용되는듯(?) .. 정면 막히면 아래 실행.
   on_stop(600);
    if((R_distance <=250)&&(L_distance <=250)){  //양쪽 막히면 오른쪽으로 유턴
      on_FR(time_90*2-150);
      on_stop(600);
    }
    
    else if(R_distance <=250){  //오른쪽도 막히면 좌회전
    on_FL(time_90);
    on_stop(600);
    }
    else if(L_distance <=250){  //왼쪽도 막히면 우회전
    on_FR(time_90);
    on_stop(600);
    }
    else {
    on_BB(time_msec);
       }
    
  }
  else{
    //2,3 다르면 전진
    digitalWrite(IN1PIN ,HIGH);
    digitalWrite(IN2PIN ,LOW);
    //4,7 다르면 전진
    digitalWrite(IN3PIN ,HIGH);
    digitalWrite(IN4PIN ,LOW);
    
  }
 
}
//우회전,좌회전,유턴
