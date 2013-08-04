/*
3,4,5 
 7,8,9
 */
int ma1 = 3;
int ma2 = 4;
int mapwm = 5;

int mb1 = 8;
int mb2 = 7;
int mbpwm = 9;

int led1 = A0;
int led2 = A1;

unsigned long time;
const int high = 255;
const int normal = 130;
int mspeed;

unsigned long tnow;


void setup() {
  // put your setup code here, to run once:
  pinMode(ma1, OUTPUT);
  pinMode(ma2, OUTPUT);
  pinMode(mapwm, OUTPUT);
  pinMode(mb1, OUTPUT);
  pinMode(mb2, OUTPUT);
  pinMode(mbpwm, OUTPUT);

  pinMode(led1, INPUT);
  pinMode(led2, INPUT);

  Serial.begin(9600);
  time = millis();
  mspeed = normal;
}

void loop() { 
  tnow = millis();
  if (tnow - time > 6000)
  {
    mspeed = normal;
    time = tnow;
  }
  else if (tnow - time > 3000)  
  {
    mspeed = high;
  } 

  if (sensors(led1) || sensors(led2)) {
    turn();

  } 
  else {
    forward();
  }

}


void forward() {
  //Serial.println("forward");
  digitalWrite(ma1, HIGH);
  digitalWrite(ma2, LOW);
  digitalWrite(mb1, HIGH);
  digitalWrite(mb2, LOW);
  analogWrite(mapwm, mspeed - 20);
  analogWrite(mbpwm, mspeed);
}

boolean sensors(int sensor) {

  int value = analogRead(sensor);
  Serial.println(value);
  if (value > 800) {
    return true;
  } 
  else {
    return false;
  }
}

void reverse() {
  //Serial.println("forward");
  time = millis();
  mspeed = normal;

  digitalWrite(ma1, LOW);
  digitalWrite(ma2, HIGH);
  digitalWrite(mb1, LOW);
  digitalWrite(mb2, HIGH);
  analogWrite(mapwm, 120);
  analogWrite(mbpwm, 120);
}
void turn() {
  reverse();
  delay(250);
  //Serial.println("turning");
  digitalWrite(ma1, LOW);
  digitalWrite(ma2, HIGH);
  digitalWrite(mb1, HIGH);
  digitalWrite(mb2, LOW);
  analogWrite(mapwm, 120);
  analogWrite(mbpwm, 120);
  delay(500);
  forward();
}


