//////////////////////-<
//INPUT
#define SVPin A3
#define SRPin A4
#define SLPin A5
//L298N
#define A1 7
#define A2 8
#define B1 9
#define B2 10
#define SMR 11
#define SML 6
//LED
#define LED 5
/////////////////////->
//Sensor :
int SR,SL,SV;
int VALL = 350,VALR = 350,VALV = 20;
int Speed = 250; //Speed Motor
//Other-----------
bool LOCKL,LOCKR;
int Back = 0;
//----------------
void setup() {
  Serial.begin(9600);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(B1,OUTPUT);
  pinMode(B2,OUTPUT);
  pinMode(SMR,OUTPUT);
  pinMode(SML,OUTPUT);
  pinMode(LED,OUTPUT);
  //CLR(SRPin,SLPin,SVPin,500,5000);
}
void Read(){
  SR = analogRead(SRPin);
  SL = analogRead(SLPin);
  SV = analogRead(SVPin);
  //Print
  Serial.print("SR =");
  Serial.print(SR);
  Serial.print("SL =");
  Serial.print(SL);
  Serial.print("SV =");
  Serial.println(SV);
}
void Sorat(int rast = 0,int chap = 0){
  analogWrite(SMR,rast);
  analogWrite(SML,chap);
}
void AB(){ // Angel Border
  Back++;
  if(Back > 10) ROBOT('D');
}
void ROBOT(char a){
  if(a == 'S'){
    digitalWrite(A1,LOW);
    digitalWrite(A2,LOW);
    digitalWrite(B1,LOW);
    digitalWrite(B2,LOW);
    Sorat(0,0);
  }
  if(a == 'U'){
    digitalWrite(A1,HIGH);
    digitalWrite(A2,LOW);
    digitalWrite(B1,HIGH);
    digitalWrite(B2,LOW);
    Sorat(Speed,Speed);
    Back = 0;
    digitalWrite(LED,1);
  }
  if(a == 'L'){
    digitalWrite(A1,HIGH);
    digitalWrite(A2,LOW);
    digitalWrite(B1,LOW);  
    digitalWrite(B2,HIGH);
    Sorat(Speed,Speed);
    Back = 0;
    digitalWrite(LED,1);
  }
  if(a == 'R'){
    digitalWrite(A1,LOW);
    digitalWrite(A2,HIGH);
    digitalWrite(B1,HIGH);
    digitalWrite(B2,LOW);
  Sorat(Speed,Speed);
  Back = 0;
  digitalWrite(LED,1);
  }
  if(a == 'D'){
    digitalWrite(A1,LOW);
    digitalWrite(A2,HIGH);
    digitalWrite(B1,LOW);
    digitalWrite(B2,HIGH);
  Sorat(Speed,Speed);
  }
}
void Barname(){
  Read();
  if(SV < VALV && SR > VALR && SL > VALL)ROBOT('U');
  else if(SV > VALV && SR > VALR && SL > VALL)AB();
  else if(SV < VALV && SR < VALR && SL < VALL){
    ROBOT('S');
    digitalWrite(LED,1);
    delay(10);
    digitalWrite(LED,0);
    delay(100);
  }
  else if(SL < VALL && SR > VALR ){
    while(1){
      Read();
      ROBOT('L');
      delay(20);
      ROBOT('U');
      delayMicroseconds(100);
      if(SL > VALL && SR > VALR && SV < VALV)break;
    }
  }
  else if(SL > VALL && SR < VALR ){
    while(1){
      Read();
      ROBOT('R');
      delay(20);
      ROBOT('U');
      delayMicroseconds(100);
      if(SL > VALL && SR > VALR && SV < VALV)break;
    }
  }

}

void loop() {
 digitalWrite(LED,0);
 Barname();

}
