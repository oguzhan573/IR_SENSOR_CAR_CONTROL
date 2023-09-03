
#include <IRremote.h>
#define FORWARD 0XFF18E7 // change these codes as shown by your decoder eg. 0xFFA55B       
#define BACK    0XFF4AB5
#define LEFT    0XFF10EF   
#define RIGHT   0XFF5AA5
const int RECV_PIN = 2;
#define ENB 5   // Left  wheel speed
#define IN1 7   // Left  wheel forward
#define IN2 8   // Left  wheel reverse
#define IN3 9   // Right wheel reverse
#define IN4 11  // Right wheel forward
#define ENA 6   // Right wheel speed
IRrecv irrecv(RECV_PIN);
decode_results results;
#define carSpeed 100  // initial speed of car >=0 to <=255
#define carspeed2 255
//unsigned long preMillis;

void setup() {
 
   irrecv.enableIRIn();
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  stop();
  Serial.begin(9600);
}

void loop() {


if(irrecv.decode(&results))
{ //preMillis=millis(); 
  Serial.println(results.value, HEX);
  if(results.value==FORWARD)
  {
    ileri();

  }
  else if(results.value==BACK)
  {
    geri();

  }
  else if(results.value==RIGHT)
  {
    sag();
  }
  else if(results.value==LEFT)
  {
    sol();
  } 
}
   else
   {
    if(millis()-preMillis>150)
     {
       stop();
       preMillis=millis();
     }
      irrecv.resume();
   }
}

void stop() {
 
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  Serial.println("STOP!");
}
void sag() {
  
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("go right!");


}
void sol() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); 
  Serial.println("go left!");
}
void ileri() {
 


  digitalWrite(ENA, carspeed2);
  digitalWrite(ENB, carspeed2);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("go forward!");
  
}
void geri() {
   digitalWrite(ENA, carspeed2);
  digitalWrite(ENB, carspeed2); 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("go back!");
}