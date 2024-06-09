#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


  //Analog Input Declaration  
  int ps1 = A0;
  int tmp = A1;
  int co2 = A2;
  int ps2 = A3;

  int ps1_val = 0;
  int tmp_val = 0;
  int ps2_val = 0;
  int co2_val = 0;

  //Digital Output Declaration
  int fan = 23;
  int SV1 = 27;
  int heater = 29;
  int SV2 = 31;
  int SV3 = 35;
  int SV4 = 39;
  int SV5 = 43;
  int vacc = 47;



void setup() 
{
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  Serial.begin(9600);

  // Declaring sensors as input 
  pinMode(ps1, INPUT);
  pinMode(tmp, INPUT);
  pinMode(co2, INPUT);
  pinMode(ps2, INPUT);


  //Declaring actuators and heater as output
  pinMode(fan, OUTPUT);
  pinMode(SV1, OUTPUT);
  pinMode(heater, OUTPUT);
  pinMode(SV2, OUTPUT);
  pinMode(SV3, OUTPUT);
  pinMode(SV4, OUTPUT);
  pinMode(SV5, OUTPUT);
  pinMode(vacc, OUTPUT);

}

void loop() 
{
  // put your main code here, to run repeatedly:

  // int ps1 = analogRead(A0);
  // int ps1_val = (ps1, 0, 1023, 1, 150);

  // int tmp = analogRead(A1);
  // int tmp_val = (tmp, 900, 450, -200, 258);

  // int co2 = analogRead(A2);
  // int co2_val = (co2, 0, 1023, 400, 10000);

  // int ps2 = analogRead(A3);
  // int ps2_val = (ps2, 0, 1023, 1, 150);

  dis();




  Air_Flow();
  delay(3000);
  vacuum();
  delay(3000);
  heat();
  delay(3000);
  store();
  delay(3000);
  
}

void Air_Flow()
{
  Serial.println(" Air Flow is executing");
  
  int i;

  digitalWrite(SV1, LOW);
  digitalWrite(SV2, LOW);
  digitalWrite(SV3, LOW);
  digitalWrite(SV4, HIGH);
  digitalWrite(SV5, HIGH);
  digitalWrite(fan, LOW);
  digitalWrite(vacc, HIGH);
  digitalWrite(heater, LOW);  
  
  dis();
  //delay(30*60*1000);  //DELAY(total minutes*one min*one sec)
  //delay(3*60*1000);  // delay of 3 min for demonstration
  //delay(1*60*1000);  // delay of 1 min for demonstration
  //delay(5000);// i.e 5 sec delay

  for(i=0;i<=20;i++)
  {
    delay(1000);
    dis();

  }
  //vacuum();
}

void vacuum()
{
  Serial.println(" Vacuum is executing");
  digitalWrite(SV1, HIGH); // Close SV1
  digitalWrite(SV3, HIGH); // Close SV3
  digitalWrite(SV4, HIGH); // Close SV3
  digitalWrite(fan, HIGH); // Switch off fan
  digitalWrite(heater, LOW); // Heater OFF
  digitalWrite(SV2, LOW); // Open SV2
  digitalWrite(SV5, LOW); // Open SV5
  digitalWrite(vacc, LOW); // Compressor ON

  dis();

  delay(3000);

  ps1_check();

  dis();

  delay(3000);
}

void heat()
{
  digitalWrite(SV1, HIGH); // Close SV1
  digitalWrite(SV3, HIGH); // Close SV3
  digitalWrite(SV4, HIGH); // Close SV3
  digitalWrite(fan, LOW); // Switch ON fan
  digitalWrite(heater, HIGH); // Heater ON
  digitalWrite(SV2, HIGH); // Close SV2
  digitalWrite(SV5, HIGH); // Close SV5
  digitalWrite(vacc, HIGH); // Compressor OFF

  dis();

  delay(3000);

  temp_check();

  dis();

  delay(3000);
}

void store()
{
  int ps_final;
  digitalWrite(heater, LOW);

  ps_final=ps1-14+ps2;

  dis();

  delay(3000);

  ps2_check();

  dis();

  delay(3000);
}

void ps1_check()
{
  int ps1_val;
  dis();

  if(ps1_val>14)
  {
    dis();

    delay(3000);
    do
    {
      vacuum();
      dis();
    }
    while(ps1>14);
  }
  else
  {
    dis();

    delay(3000);
    Serial.println(" Vacuum Created ");
    heat();
  }
}

void temp_check()
{ 
  int i, tmp_val;
  for(i=0;i<3;i++)
  { 
    do 
    {
     digitalWrite(heater, HIGH);
     
     dis();

     delay(3000);

    }
    while(tmp_val>=640);

    if(tmp_val>=640)
    {
      do
      {
       digitalWrite(heater, LOW);
       digitalWrite(fan, LOW);
       
       dis();

      
      }
      while(tmp_val>640);
    }
  }
}

void ps2_check()
{
  int ps_final;
  if(ps1>14)
  {
    do
    {
      digitalWrite(SV2, LOW);
      digitalWrite(SV4, LOW);
      digitalWrite(fan, HIGH);
      digitalWrite(vacc, LOW);
      digitalWrite(SV1, HIGH);
      digitalWrite(SV3, HIGH);
      digitalWrite(SV5, HIGH);
      digitalWrite(heater, LOW);

      dis();

      delay(3000);
    }
    while(ps2!=ps_final && ps_final<100 && ps1_val>14);
  }
  else
  {
    dis();

    delay(3000);

    Serial.print(" Chamber empty");
  }
}

void dis()
{
  // int ps1_val, tmp_val, co2_val, ps2_val;
  

  ps1_val = analogRead(ps1);
  //ps1_val = map(ps1_val, 0, 1023, 0, 150);
  lcd.setCursor(0, 0); 
  lcd.print("PS1=");
  lcd.print(ps1_val); // top left
  Serial.println(" Pressure1 is ");
  Serial.println(ps1_val);

  Serial.println(" Temp is ");
  Serial.println(tmp_val);
  tmp_val = analogRead(tmp);
  //int tmp_val = map(tmp, 900, 450, -200, 258);
  lcd.setCursor(8, 0);
  lcd.print("TMP="); // top right
  lcd.print(tmp_val);


  Serial.println(" Pressure2 is ");
  Serial.println(ps2_val);
  ps2_val = analogRead(ps2);
  //int ps2_val = map(ps2, 0, 1023, 1, 150);
  lcd.setCursor(0, 1);
  lcd.print("PS2="); // bottom left
  lcd.print(ps2_val);


  Serial.println(" CO2 concentration is ");
  Serial.println(co2_val);
  co2_val = analogRead(co2);
  //int co2_val = map(co2, 0, 1023, 400, 10000);
  lcd.setCursor(8, 1);
  lcd.print("CO2=");
  lcd.print(co2_val);


}