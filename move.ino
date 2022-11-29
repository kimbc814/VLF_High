
#define IN1PIN 3
#define IN2PIN 2
#define ENPIN1 5

#define IN3PIN 4
#define IN4PIN 7
#define ENPIN2 6
int time_msec;

void on_FF(int a){
//2,3 다르면 전진
  digitalWrite(IN1PIN ,HIGH);
  digitalWrite(IN2PIN ,LOW);
//4,7 다르면 전진
  digitalWrite(IN3PIN ,HIGH);
  digitalWrite(IN4PIN ,LOW);
  delay(a);
}
void on_FR(int a){
//2,3 다르면 전진
  digitalWrite(IN1PIN ,HIGH);
  digitalWrite(IN2PIN ,LOW);
//4,7 같으면 멈춤
  digitalWrite(IN3PIN ,HIGH);
  digitalWrite(IN4PIN ,HIGH);
  delay(a);
}
void on_FL(int a){
//2,3 같으면 멈춤
  digitalWrite(IN1PIN ,HIGH);
  digitalWrite(IN2PIN ,HIGH);
//4,7 다르면 전진
  digitalWrite(IN3PIN ,HIGH);
  digitalWrite(IN4PIN ,LOW);
  delay(a);
}
void on_BB(int a){
//2,3 다르면 후진
  digitalWrite(IN1PIN ,LOW);
  digitalWrite(IN2PIN ,HIGH);
//4,7 다르면 후진
  digitalWrite(IN3PIN ,LOW);
  digitalWrite(IN4PIN ,HIGH);
  delay(a);
}
void on_BR(int a){
//2,3 다르면 후진
  digitalWrite(IN1PIN ,LOW);
  digitalWrite(IN2PIN ,HIGH);
//4,7 같으면 멈춤
  digitalWrite(IN3PIN ,HIGH);
  digitalWrite(IN4PIN ,HIGH);
  delay(a);
}
void on_BL(int a){
//2,3 같으면 멈춤
  digitalWrite(IN1PIN ,HIGH);
  digitalWrite(IN2PIN ,HIGH);
//4,7 다르면 후진
  digitalWrite(IN3PIN ,LOW);
  digitalWrite(IN4PIN ,HIGH);
  delay(a);
}
void setup() {

  pinMode(IN1PIN ,OUTPUT);
  pinMode(IN2PIN ,OUTPUT);
  pinMode(IN1PIN ,OUTPUT);
  pinMode(IN2PIN ,OUTPUT);
  
  analogWrite(ENPIN1,80);
  analogWrite(ENPIN2,80);
  time_msec = 1000;
  Serial.begin(115200);
}

void loop() {
  on_FF(time_msec);
  on_FR(2*time_msec);
  on_FL(2*time_msec);
  on_BB(time_msec);
  on_BL(2*time_msec);
  on_BR(2*time_msec);
  
  
  /*
  if(Serial.available()){
    char in_data;
    in_data= Serial.read();
    Serial.print("data : ");
    Serial.print(in_data);
    
    if(in_data =='1'){
      on_FF();
    }
    else if(in_data =='2'){
      on_FR();
    }
    else if(in_data =='3'){
      on_FL();
    }
    
  }
  */
}
/*  

//2,3 다르면 전진
  digitalWrite(IN1PIN ,HIGH);
  digitalWrite(IN2PIN ,LOW);
//4,7 다르면 전진
  digitalWrite(IN3PIN ,HIGH);
  digitalWrite(IN4PIN ,LOW);
  delay(5000);

//2,3 다르면 후진
  digitalWrite(IN1PIN ,LOW);
  digitalWrite(IN2PIN ,HIGH);
//4,7 다르면 후진
  digitalWrite(IN3PIN ,LOW);
  digitalWrite(IN4PIN ,HIGH);
  delay(5000);


//2,3 같으면 멈춤
  digitalWrite(IN1PIN ,HIGH);
  digitalWrite(IN2PIN ,HIGH);
//4,7 같으면 멈춤
  digitalWrite(IN3PIN ,HIGH);
  digitalWrite(IN4PIN ,HIGH);
  delay(5000);
*/
