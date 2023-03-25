/*
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int i,j,count = 0,check=0;                                          // count = 0
char input[12];
char pdt_name[3][13]={"CRAYON","VIM GEL","JAYA COFFEE"};                                         // character array of size 12  
char pdt_tag[3][13]={"5900D4E1D1BD","5900D4F75E24","5A001E479F9C"};
float total,price[10]={45.50,20,75.50};
void setup()
{
  // set up the LCD's number of columns and rows:
   lcd.begin(16, 2);
   Serial.begin(9600);                                  
   // begin serial port with baud rate 9600bps
}
void loop()
{ 
  digitalWrite(LED_BUILTIN,LOW);
   if(Serial.available())
   {
      count = 0;
      while(Serial.available() && count < 12)          // Read 12 characters and store them in input array
      {
         input[count] = Serial.read();// Read 1 Byte of data and store it in the input[] variable
         count++;
         delay(5);
      }
   // Serial.print("the rfid of card is :");   
  //  Serial.println(input);                             // Print RFID tag number     
      if((input[0] ^ input[2] ^ input[4] ^ input[6] ^ input[8] == input[10]) && 
         (input[1] ^ input[3] ^ input[5] ^ input[7] ^ input[9] == input[11]))
          {
         // Serial.println("card is valid"); 
          delay(500);
           }
      else
           {
            Serial.println("Error");  
           }
           for(j=0;j<3;j++)
           {
               for(i=0;i<12;i++)
               {
                if(pdt_tag[j][i]==input[i])
                {
                  check++;
                }
               }
                if(check>=11)
               {
               lcd.clear();
               lcd.print(pdt_name[j]);
               Serial.println(pdt_name[j]);
               delay(500);
               lcd.clear();
               lcd.print("amount : ");
               lcd.println(price[j]);
               Serial.println(price[j]);
               lcd.setCursor(0, 1);
               lcd.clear();
               total=total+price[j];
               lcd.print("total : ");
               lcd.print(total);
               Serial.println(total);
               }
               check=0;
          }
   }
}
