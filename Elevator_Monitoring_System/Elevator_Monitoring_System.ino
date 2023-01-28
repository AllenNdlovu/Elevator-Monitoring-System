#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

//defining pinouts of pushbuttons
#define REQ 7
#define F1 6
#define F2 5
#define F3 4

//led pinout
#define red  3
#define green 2

//IR Sensor pinout
#define Exit 8
#define Enter 9

int numberPeople =0;
int level=1; //level of elevator
const int maxPeople = 5;



int checkPush(){
     byte req, f1, f2, f3;
     
     req = digitalRead(REQ);
     f1 = digitalRead(F1);
     f2 = digitalRead(F2);
     f3 = digitalRead(F3);

     if( req ==   LOW)
            return 1;
     if( f1 ==   LOW)
            return 2;
     if( f2 ==   LOW)
            return 3;
     if( f3 ==   LOW)
            return 4; 
  return 0;
}
void detect(){

    int i,j=10;

    for(i=0;i<=10;i++){
        if(digitalRead(Exit) != 1 && numberPeople > 0)
              numberPeople--;
        if(digitalRead(Enter) != 1 && numberPeople < maxPeople)
              numberPeople++;
        if(digitalRead(Enter) != 1 && numberPeople ==maxPeople)
              displayStatus(5);   
     delay(500);                          
   }   
}
void door(){

    //opening door
    displayStatus(2);
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);

    //detecting people
    detect();
    
    delay(5000);

    //door closes
    displayStatus(3);
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
  
  
}
void displayStatus(int option){
       
        lcd.setCursor(0,0);
        switch(option){
          case 0: lcd.print("Elevator System ");
          case 1: lcd.print("**REQ ELEVATOR**");break;
          case 2: lcd.print("***DOOR OPEN****");break;
          case 3: lcd.print("**DOOR CLOSED***");break;
          case 4: lcd.print("**ENTER LEVEL***");break;
          case 5: lcd.print("**ELEVATOR FULL*");break;
          case 6: lcd.print("1               ");break;
          case 7: lcd.print("2               ");break;
          case 8: lcd.print("3               ");break;
          
        }

        lcd.setCursor(0,1);
        lcd.print("Level:");
        lcd.print(level);
        lcd.print("     N:");
        lcd.print(numberPeople);
  
}
void setup() {
  
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  
  //pushbutton config
  pinMode(REQ,INPUT_PULLUP);
  pinMode(F1,INPUT_PULLUP);
  pinMode(F2,INPUT_PULLUP);
  pinMode(F3,INPUT_PULLUP);

  //led config
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);

  //IR config
  pinMode(Exit, INPUT);
  pinMode(Enter, INPUT);

  //door closed initially
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    
  displayStatus(0);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  displayStatus(5);
  door();
  checkPush();
  delay(200); //delay for reading pushbutton

}
