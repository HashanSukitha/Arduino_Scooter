
#include <LiquidCrystal.h>
#include <EEPROM.h>


LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

int thisChar = 'a';
String newVal="";

char isScooterOn=0;

int scoterFlag=0;
int isScooterOnByBTon=0;

int Alarm = 8;
int ManualSwitch= 12;
int Display= 10;

int manualKeyOn=0;

void setup() 
{

  
  lcd.begin(16, 2);
  Serial.begin(9600);

  pinMode(Alarm, OUTPUT);
  pinMode(ManualSwitch, INPUT);
  pinMode(Display, OUTPUT);

  
}




void loop() 
{     

     manualKeyOn= digitalRead(ManualSwitch); 
     String serialVal= Serial.readString();  
     Serial.println(manualKeyOn);

     if(serialVal.length()>2)
     {
      reNameScooter(serialVal);
     }

    displayPrint();
    
    if((manualKeyOn==1)&&(isScooterOn==0))
    {
            turnOnScooter();     
    } 
    else if(manualKeyOn==0)
    {      
    
        if((manualKeyOn==0)&&(isScooterOn==1)&&(isScooterOnByBTon==0))
        {
            turnOffScooter();
        }
        
        if((serialVal=="1")&& (isScooterOn==0))
        {
                 
            turnOnScooter();
            isScooterOnByBTon=1;
  
        }
        if((serialVal=="0")&& (isScooterOn==1))
        {         
            turnOffScooter();
            isScooterOnByBTon=0; 
        }
    }  
}
//==============================================================================================================================
void reNameScooter(String val)
{
    //String val= Serial.readString();
           //if(val.length()>2)
            //{
                for(int i=0;i<6;i++)
                {
                EEPROM.write(i,' ');
                }
                
                for(int i=0;i<val.length();i++)
                {
                EEPROM.write(i,val[i]);
 
                }
                //Serial.println(val);
            //} 
            //else if(val.length()==1)
            //{
             // if(manualKeyOn<1)
             // {
              //ScooterBTon(val[0]); 
             //} 
            //}
}
//==============================================================================================================================
void displayPrint()
{
            //Serial.println("im here");
          for(int i=0;i<6;i++)
          {
            char a=EEPROM.read(i);
            newVal=newVal+a;
    
          }
          delay(100);
          lcd.begin(16, 2);
          //lcd.clear();
          lcd.setCursor(1,0);
          lcd.print("Welcome "+newVal);
          lcd.setCursor(1,1);
          lcd.print("Scooter Ready");
    
          newVal="";
}
//==============================================================================================================================
void turnOnScooter()
{
          digitalWrite(Alarm, HIGH);
          delay(1000);
          digitalWrite(Alarm, LOW);
          digitalWrite(9, HIGH);
          digitalWrite(Display, HIGH);
          isScooterOn=1;
}
//==============================================================================================================================
void turnOffScooter()
{
          digitalWrite(Alarm, HIGH);
          delay(250);
          digitalWrite(Alarm, LOW);
          delay(250);
          digitalWrite(Alarm, HIGH);
          delay(250);
          digitalWrite(Alarm, LOW);
          delay(100);   
    
          digitalWrite(9, LOW);
          digitalWrite(Display, LOW);
          isScooterOn=0;
}
//==============================================================================================================================



