// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
int val,val2,val3;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int alarm =0;
int h=0;
int m=0;
int s=40;
int h_a=0;
int m_a=0;
int s_a=0;
long prev=0;
int alarm_sounded=0;

const int temperatureSensorPin = A0;
const int inPin=6;
const int inPin3=8;
const int inPin2=7;
const int buzzer=10;
const int lightPin=A1;

int trigPin = 7;    // Trigger
int echoPin = 6;    // Echo
int distance = 0;
int cm = 0;


uint8_t heart_f[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
uint8_t heart_e[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
uint8_t heart_h[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
  B11111
};
uint8_t heart_qf[8] = {
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
uint8_t heart_qe[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
//======================Functions===============================//
long readUltrasonicDistance(int triggerPin, int echoPin)
	{pinMode(triggerPin, OUTPUT);digitalWrite(triggerPin, LOW);
     delayMicroseconds(2);
     // trigger 10(s,e-6) sound pulses
     digitalWrite(triggerPin, HIGH);delayMicroseconds(10);
     digitalWrite(triggerPin, LOW);
     pinMode(echoPin, INPUT);
     //echo pin read,return travel time of sound pulses
     return pulseIn(echoPin, HIGH);}
//============== rutina calcul distanta in cm ===============//
     void calcul(){
       cm = 0.01723 * readUltrasonicDistance(13, 9);
     }
//======================SETUP===============================//
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.createChar(3, heart_f);
  lcd.createChar(4, heart_e);
  lcd.createChar(5, heart_h);
  lcd.createChar(6, heart_qf);
  lcd.createChar(7, heart_qe);
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  pinMode(inPin, INPUT);
  pinMode(inPin2, INPUT);
  pinMode(inPin3, INPUT);
 pinMode(buzzer,OUTPUT);
  pinMode(temperatureSensorPin,INPUT);
  pinMode(lightPin,INPUT);
}
//======================LOOP=================================//

void loop() {
 
 //delay(1000);
 
 val = digitalRead(inPin);
 val2 = digitalRead(inPin2);
 val3 = digitalRead(inPin3);
 
 if(val == HIGH)
 {
   if (alarm==0)
   {
     alarm=1;
   }
   else if (alarm==1)
   {
     alarm=0;
   }
   
   delay(800);
 }
  
 else if(val2 == HIGH)
 {
   m_a++;
   if (m_a>60)
   {
     m_a=0;
     h_a++;
   }
   lcd.setCursor(0,1);
   lcd.print(h_a);
   lcd.print(":");
   lcd.print(m_a);
   delay(800);
 }
 else if(val3 == HIGH)
 {
   h_a++;
   if (h_a>24)
   {
     h_a=0;
   }
   lcd.setCursor(0,1);
   lcd.print(h_a);
   lcd.print(":");
   lcd.print(m_a);
   delay(800);
 }
  
  if ((millis()-prev)>1000)
  {
    s++;
    if (s>60)
    {
      m++;
      s=0;
      if (m>60)
      {
        m=0;
        h++;
      	if (h>24)
        {
          h=0;
        }
      }
    }
   lcd.setCursor(0,0);
   lcd.print(h);
   lcd.print(":");
   lcd.print(m);
   lcd.print(":");
   lcd.print(s);
  
  if (alarm==0)
  {
    lcd.print(" Alarm Off  ");
  }
    else if (alarm==1)
    {
      lcd.print("  Alarm ON  ");
      lcd.setCursor(0,1);
   lcd.print(h_a);
   lcd.print(":");
   lcd.print(m_a);
      if (h==h_a &&  m==m_a)
      {
        alarm_sounded=1;
      }
    }
    prev=millis();
  }
   float temperature = 0;
  temperature = (analogRead(temperatureSensorPin) * 0.48828125) - 49.95;
  int L=analogRead(lightPin);
  Serial.println(L);
  lcd.setCursor(6,1);
  lcd.print("B");
  if (L>600)
  {
  lcd.print("\x03");
  }else if (L>300 && L<600)
  {
  lcd.print("\x06");
  }if (L>100 && L<300)
  {
  lcd.print("\x05");
  }if (L>10 && L<100)
  {
  lcd.print("\x07");
  }if (L<10)
  {
  lcd.print("\x04");
  }
  //lcd.print(L);
  lcd.setCursor(8,1);
  lcd.print(" ");
  lcd.setCursor(10,1);
  lcd.print(temperature);
  lcd.print(" C");
  if (alarm_sounded==1)
  {		
    calcul();
		int distance = cm;
    Serial.println(distance);
        tone(buzzer,1000);
        delay(400);
        noTone(buzzer);
    if (distance<20)
    {
      alarm_sounded=0;
      lcd.setCursor(0,0);
   lcd.print(h);
   lcd.print(":");
   lcd.print(m);
   lcd.print(":");
   lcd.print(s);
    lcd.print("  Alarm ON  ");
      alarm=0;
      h_a=0;
      m_a=0;
   lcd.setCursor(0,1);
   lcd.print(h_a);
   lcd.print(":");
   lcd.print(m_a);
    }
  }
}
 
