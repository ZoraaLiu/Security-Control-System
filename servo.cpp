#include <Keypad.h> 
#include <Servo.h>
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
Servo myservo;
int pos = 0;
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char originalKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9,8,7,6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5,4,3,2}; //connect to the column pinouts of the keypad
//initialize an instance of class NewKeypad
Keypad myKeypad = Keypad(makeKeymap(originalKeys), rowPins, colPins, ROWS, COLS);
const int redLedPin = 11; //Red LED
const int greenLedPin = 12; //Green LED
char keycount=0;
char code[4]; //Store pressed keys

void setup(){
pinMode(redLedPin,OUTPUT);
pinMode(greenLedPin,OUTPUT);
digitalWrite(redLedPin,LOW); 
digitalWrite(greenLedPin,LOW); 
lcd.begin(16,2);
lcd.clear();
lcd.setCursor(0,0);
myservo.attach(10);
ServoClose();
lcd.print("Welcome to the");
lcd.setCursor(0,1);
lcd.print("Access control");
delay(3000);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("System");
lcd.setCursor(0,1);
lcd.print("By Jada and Zora");
delay(3000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print(" # --confrim");
delay(1000);
lcd.setCursor(0,1);
lcd.print(" C --clear");
delay(1000);
lcd.clear();
lcd.print("Password Access:");
lcd.setCursor(0,1);
  
  
}

void ServoOpen()
{
  for (pos = 90; pos >= 0; pos -= 1) { // goes from 90 degrees to 0 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void ServoClose()
{
  for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 90 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void lockMessage()
{
lcd.setCursor(0,1);
lcd.print("Door Locked     ");
delay(100);
lcd.setCursor(0,1);
lcd.clear(); 
}



void loop(){
char myKey = myKeypad.getKey(); //Create myKey objects
if (myKey && (myKey !='#') && (myKey !='C')){
// print * and store the password when the password is entered while no special characters are entered
lcd.print('*');    //Display the sign instead of the actual password
code[keycount]=myKey;
keycount++;
}
if(myKey == 'C')      //Cancel/Lock Key is pressed clear display and lock
{
lockMessage();    //display the lock message
keycount=0;
}
if(myKey == '#')   //User confirm the password and the system check check the password 
{
if((code[0]=='1') && (code[1]=='2') && (code[2]=='3') && (code[3]=='4'))  //If the entered password matches the correct password
{
digitalWrite(greenLedPin,HIGH);     //green LED On
lcd.setCursor(0,1);
lcd.print("Door Open      ");
ServoOpen();
delay(8800);  //Keep Door open for 8.8 seconds
lockMessage();
keycount=0;
ServoClose();
digitalWrite(greenLedPin,LOW); // turn green LED off when the door is locked
}
else
{
lcd.setCursor(0,1);
digitalWrite(redLedPin,HIGH);
lcd.print("Invalid Password");  //Display Error Message
delay(2000); //Message delay for 2 s
lockMessage();
keycount=0;
}
}
}
