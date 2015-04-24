

#include<LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);
int i=0;
int j=0;
int k=0;
boolean lcdClear=true;
float tursayisi=0;
int adimsayisi=0;
int mesafe=0;
const int motorhatvesi=40; //the distance that motor will move in one turn (mm olarak)
int motoradimsayisi=3200; //number of steps in one term
float delayTime;
const int StepPin = 10;
const int DirPin = 9;  
const int mSwitch = 8;
bool check = false;


void setup ()
{
  lcd.begin(16,2);
  lcd.print("Baslatiliyor...");
  pinMode(StepPin, OUTPUT);
  pinMode(DirPin, OUTPUT); 
  pinMode(1,INPUT_PULLUP);
  pinMode(0,INPUT_PULLUP); 
  pinMode(mSwitch, INPUT_PULLUP);// switch pin to protect that motor will not move out of the borders
  Serial.begin(9600);
  
  int mSwitchVal=digitalRead(mSwitch);
 // Serial.println(mSwitch);
  digitalWrite(DirPin,LOW);
 
  while(mSwitchVal==HIGH)
  {
    check=true;
     digitalWrite(StepPin, HIGH); //
        delayMicroseconds(100);//
        digitalWrite(StepPin, LOW); //
        delayMicroseconds(100);//
     mSwitchVal=digitalRead(mSwitch);
    
     if(mSwitchVal ==LOW){
       
         digitalWrite(DirPin,HIGH);
       Serial.println("ortaya gidiyorum ");
         for(int m=0; m<8800; m++){
              digitalWrite(StepPin, HIGH); //
              delayMicroseconds(100);//
              digitalWrite(StepPin, LOW); //
              delayMicroseconds(100);//
     }
     
  }
  
   //Serial.println(mSwitch);
}
if(mSwitchVal==LOW && check == false ){
   digitalWrite(DirPin,HIGH);
       Serial.println("ortaya gidiyorum ");
         for(int m=0; m<8800; m++){
              digitalWrite(StepPin, HIGH); //
              delayMicroseconds(100);//
              digitalWrite(StepPin, LOW); //
              delayMicroseconds(100);//
     }
}}
void loop () {
  int mSwitchVal=digitalRead(mSwitch);
    
  Serial.println(DirPin);
  Serial.println(mSwitch);
  delay(500);
  int enterButton=digitalRead(0); 
  int sensorVal=digitalRead(1);
  
  
  while (enterButton==LOW){
    j++;
    break;
  }
  if(j==0){
    lcd.setCursor(0,0);
    lcd.print("mesafe girin(mm)");
    
    while(sensorVal==LOW){
      ekrani_guncelle(); 
      break;
       
    }
  }
  if(j==1){
    if(lcdClear){
      lcd.clear();
      lcdClear=false;
    }
    lcd.setCursor(0,0);
    lcd.print("hiz girin(mm/s)");
    while(sensorVal==LOW){
      ekrani_guncelle2(); 
      break;
    }
  }
  
  if(j>=2 ) 
  {  
     if(k==0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Error!! Hiz=0");
    lcd.setCursor(0,1);
    lcd.print("Yeniden Baslat");
    delay(2000);
    }
    if(k!= 0){
    mesafe=i;
    tursayisi=(float)mesafe/motorhatvesi;  
    adimsayisi = tursayisi*motoradimsayisi; 
     delayTime=(float)1000000/(k*2* ((float)motoradimsayisi/motorhatvesi));
    Serial.println(delayTime);
    Serial.println(tursayisi);
    Serial.println(adimsayisi);
    int x;
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Mesafe: ");
    lcd.setCursor(8,0);
    lcd.print(i);
    lcd.setCursor(11,0);
    lcd.print("mm");
    
    lcd.setCursor(0,1);
    lcd.print("Hiz: ");
    lcd.setCursor(5,1);
    lcd.print(k);
    lcd.setCursor(8,1);
    lcd.print("mm/sn");
    
    
    for (x=0; x < adimsayisi/2; x++) 
    {
       mSwitchVal=digitalRead(mSwitch);
       while(!mSwitchVal){}
       
      digitalWrite(StepPin, HIGH); //
      delayMicroseconds(delayTime);//
      digitalWrite(StepPin, LOW); //
      delayMicroseconds(delayTime);//
    }
    digitalWrite(DirPin,LOW); //

    while(true){

      for (x=0; x < adimsayisi; x++) 
      { 
         mSwitchVal=digitalRead(mSwitch);
         while(!mSwitchVal){}
         
        digitalWrite(StepPin, HIGH); //
        delayMicroseconds(delayTime);//
        digitalWrite(StepPin, LOW); //
        delayMicroseconds(delayTime);//
      }

      digitalWrite(DirPin,HIGH); 

      for(x=0; x<adimsayisi; x++)
      {
         mSwitchVal=digitalRead(mSwitch);
         while(!mSwitchVal){}
         
        digitalWrite(StepPin, HIGH); //
        delayMicroseconds(delayTime);//
        digitalWrite(StepPin, LOW); //
        delayMicroseconds(delayTime);//
      }
      digitalWrite(DirPin,LOW);
    } 
  }}
}
void ekrani_guncelle()
{
  if(i<=150){
  i=i+1;    
  lcd.setCursor(0,1);
  lcd.print(i); 
  }
  else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Max mesafe=150mm");
    delay(3000);
    lcd.clear();
    i=0;
}}

void ekrani_guncelle2()
{ 
  if(k<=200){
  k=k+1;     /
  lcd.setCursor(0,1);
  lcd.print(k); 
  }
  else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Max hiz=200 mm/sn ");
    delay(3000);
    lcd.clear();
    k=0;
  }
 
}


/* LCD den girdiğimiz mesafe kadar önce saat yönünde sonra
 saat yönünün tersine tur atıyor*/
