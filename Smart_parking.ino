#include <Servo.h>
#include <LiquidCrystal.h>

const int rs= 6, en=4,rw=5,d4=3,d5=2,d6=30,d7=31;
LiquidCrystal lcd(rs, en, rw, d4, d5, d6, d7);
int backLight=7;

Servo gate_servo;

int ir_in=A0;
int ir_out=A1;
int ir_1=A2;
int ir_2=A3;
int ir_3=A4;
int ir_4=A5;

int red=10;
int green=11;

int in=1;
int out=1;
int full=0;

int c1=0;
int c2=0;
int c3=0;
int c4=0;
int i;

void setup() {
  Serial.begin(9600);
  
  pinMode(ir_in,INPUT);
  pinMode(ir_out,INPUT);
  pinMode(ir_1,INPUT);
  pinMode(ir_2,INPUT);
  pinMode(ir_3,INPUT);
  pinMode(ir_4,INPUT);

  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  
  gate_servo.attach(9);
  gate_servo.write(10);

  pinMode(backLight, OUTPUT);
  digitalWrite(backLight,HIGH);
  lcd.begin(16,2);
}

void loop() {
 
   if(analogRead(ir_1)<500)
   {
    c1=1;
   }
   else
   {
    c1=0;
    i++;
   }
  
   if(analogRead(ir_2)<500)
   {
    c2=2;
   }
   else
   {
    c2=0;
    i++;
   }
  
   if(analogRead(ir_3)<500)
   {
    c3=3;
   }
   else
   {
    c3=0;
    i++;
   }
  
   if(analogRead(ir_4)<800) //this IR sensor sometimes 
   {
    c4=4;
   }
    else
   {
    c4=0;
    i++;
   }
  
   if(c1==1 && c2==2 && c3==3 && c4==4)
   {
    full=1;
    digitalWrite(red,HIGH);
    digitalWrite(green,LOW);
    Serial.println("Park is Full");
    
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("Park is Full");
    lcd.setCursor(4,1);
    lcd.print("Thankyou");
    delay(100);
   }
   else
   {
    full=0;
    digitalWrite(red,LOW);
    digitalWrite(green,HIGH);
    
    Serial.print("Empty Slot-> ");
    Serial.print(c1);
    Serial.print(", ");
    Serial.print(c2);
    Serial.print(", ");
    Serial.print(c3);
    Serial.print(", ");
    Serial.print(c4);
    Serial.println( );

    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("Empty Slot:");
    
    lcd.setCursor(13,0);
    lcd.print(i);
    
    lcd.setCursor(1,1);
    lcd.print("Go->");

    if(c1==0)
    {
      lcd.print("1");
      lcd.print("  ");
    }
    if(c2==0)
    {
      lcd.print("2");
      lcd.print("  ");
    }
    
    if(c3==0)
    {
      lcd.print("3");
      lcd.print("  ");
    }

    if(c4==0)
    {
      lcd.print("4");
    }
    delay(100);
   }
  
  if(analogRead(ir_in)<500 && in==1 && full==0)
  {
    out=0;
    gate_servo.write(90);        
  }
  else if(analogRead(ir_out)<500 && out==0)
  {
    out=1;
    delay(3000);
    gate_servo.write(10);
    delay(3000);                
  }

  else if(analogRead(ir_out)<500 && out==1)
  {
    in=0;
    gate_servo.write(90);
  }
  else if(analogRead(ir_in)<500 && in==0)
  {
    in=1;
    delay(3000);
    gate_servo.write(10);
    delay(3000);
  }
  i=0;
}
