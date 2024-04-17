#include <Encoder.h>

#include <Keyboard.h>
#include <KeyboardLayout.h>
#include <Keyboard_da_DK.h>
#include <Keyboard_de_DE.h>
#include <Keyboard_es_ES.h>
#include <Keyboard_fr_FR.h>
#include <Keyboard_it_IT.h>
#include <Keyboard_sv_SE.h>

#include <Key.h>
#include <Keypad.h>

//

int mode;
bool debounce_start1 = false;
bool debounce_start2 = false;

#define LED1 A1
#define LED2 A2
#define LED3 A3
#define CLK1 10
#define CLK2 14
#define DT1 16
#define DT2 15
//
Encoder RotaryEncoderA(CLK1, DT1);
Encoder RotaryEncoderB(CLK2, DT2);

long positionEncoderA  = -999;
long positionEncoderB  = -999;

char K;
char keys[4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

const byte n = 4;

byte row[n]={9,8,7,6};
byte col[n]={5,4,3,2};

Keypad keypad = Keypad( makeKeymap(keys), row , col , n , n);

void run(){
  Keyboard.press(KEY_LEFT_GUI);
  delay(20);          
  Keyboard.print("r"); 
  Keyboard.releaseAll();
  delay(200);
  return;
}
void altctrl(char ch){
  Keyboard.press(KEY_LEFT_ALT);
  delay(30);
  Keyboard.press(KEY_LEFT_CTRL);
  delay(30);
  Keyboard.press(ch);
  delay(30);
  Keyboard.releaseAll();
}

void setup()
{
  Serial.begin(9600);
  mode=0;
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);

  digitalWrite(LED1,HIGH);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);

  Keyboard.begin();
}


void encoderA(){
  long newPos = RotaryEncoderA.read()/4; //When the encoder lands on a valley, this is an increment of 4.
  if (newPos != positionEncoderA && newPos > positionEncoderA) {
    positionEncoderA = newPos;
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('z');  
    Keyboard.release(KEY_LEFT_CTRL);
    Keyboard.release('z');
  }
  if (newPos != positionEncoderA && newPos < positionEncoderA) {
    positionEncoderA = newPos;
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('y');  
    Keyboard.release(KEY_LEFT_CTRL);
    Keyboard.release('y');
  }
}

void encoderB(){
  long newPos = RotaryEncoderB.read()/4;
  if (newPos != positionEncoderB && newPos > positionEncoderB) {
    positionEncoderB = newPos;
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('-');
    Keyboard.release(KEY_LEFT_CTRL);
    Keyboard.release('-');
  }

  if (newPos != positionEncoderB && newPos < positionEncoderB) {
    positionEncoderB = newPos;
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('=');
    Keyboard.release(KEY_LEFT_CTRL);
    Keyboard.release('=');
  }
}

void loop()
{
  delay(1);  
  encoderA();
  encoderB();
  if((K = keypad.getKey())!=NO_KEY)
  {
    if (K=='0'){
      mode+=1;
      mode = mode % 3;
      if(mode==0){
        digitalWrite(LED1,HIGH);
        digitalWrite(LED2,LOW);
        digitalWrite(LED3,LOW);  
      }
      else if(mode==1){
        digitalWrite(LED2,HIGH);
      }
      else if(mode==2){
        digitalWrite(LED3,HIGH);
      }
    }
    else{
      if(mode==0){
        switch (K) {
          case '1': 
            run(); Keyboard.println("https://mail.google.com/mail/u/0/#inbox?compose=new");
            break;      
          case '2': 
            run(); Keyboard.println("https://meet.new");
            break;
          case '3':
            run(); Keyboard.println("https://calendar.google.com/calendar/render?action=TEMPLATE");
            break;
          case '4':
            run(); Keyboard.println("https://docs.new");
            break;
          case '5':
            run(); Keyboard.println("https://sheets.new");
            break;
          case '6':
            run(); Keyboard.println("https://slides.new");
            break;
          case '7':
            run(); Keyboard.println("https://bard.google.com");
            break;
          case '8':
            run();
            Keyboard.println("calc");
            delay(1500);
            Keyboard.press(KEY_LEFT_ALT);
            delay(20);
            Keyboard.press("2");
            delay(20);
            Keyboard.releaseAll();
            break;
          case '9':
            run(); Keyboard.println("https://office.com");
            break;
          case 'A':
            //ctrl + shift + A  
            Keyboard.press(KEY_LEFT_CTRL);
            delay(30);
            Keyboard.press(KEY_LEFT_SHIFT);
            delay(30);
            Keyboard.press('a');
            delay(30);
            Keyboard.releaseAll();
            break;
          case'B':              
            //ctrl + shift + T
            Keyboard.press(KEY_LEFT_CTRL);
            delay(30);
            Keyboard.press(KEY_LEFT_SHIFT);
            delay(30);
            Keyboard.press('t');
            delay(30);
            Keyboard.releaseAll();
            break;            
          case 'C':          
            //ctrl + L or Alt + D
            Keyboard.press(KEY_LEFT_ALT);
            delay(30);
            Keyboard.press('d');
            delay(30);
            Keyboard.releaseAll();
            break;
          case 'D':
            // ctrl + shift + esc
            Keyboard.press(KEY_LEFT_CTRL);
            delay(30);
            Keyboard.press(KEY_LEFT_SHIFT);
            delay(30);
            Keyboard.press(KEY_ESC);
            delay(30);
            Keyboard.releaseAll();
            break;
          case '*':
            Keyboard.press(KEY_LEFT_CTRL);
            delay(30);
            Keyboard.press(KEY_LEFT_SHIFT);
            delay(30);
            Keyboard.press(KEY_TAB);
            delay(30);
            Keyboard.releaseAll();
            break;
          case '#':
          //ctrl + tab
            Keyboard.press(KEY_LEFT_CTRL);
            delay(30);
            Keyboard.press(KEY_TAB);
            delay(30);
            Keyboard.releaseAll();
            break;
        }
      }
      else if(mode==1){
        switch (K) {
          case '1': 
            Keyboard.press(KEY_LEFT_CTRL);
            delay(20);
            Keyboard.press(KEY_LEFT_SHIFT);
            delay(20);
            Keyboard.print('t');
            Keyboard.releaseAll();
            break;      
          case '2': 
            Keyboard.press(KEY_LEFT_ALT);
            delay(20);
            Keyboard.press(KEY_LEFT_SHIFT);
            delay(20);
            Keyboard.press('l');
            Keyboard.releaseAll();
            break;
          case '3':
            Keyboard.press(KEY_LEFT_CTRL);
            delay(20);
            Keyboard.print('a');
            delay(20);
            Keyboard.print('g');
            Keyboard.releaseAll();
            break;
          case '4':
            Keyboard.press(KEY_LEFT_ALT);
            delay(20);
            Keyboard.print('1');
            Keyboard.releaseAll();
            break;
          case '5':
            Keyboard.press(KEY_LEFT_CTRL);
            delay(20);
            Keyboard.press(KEY_LEFT_SHIFT);
            delay(20);
            Keyboard.print('f');
            Keyboard.releaseAll();
            break;
          case '6':
            altctrl('p');
            break;
          case '7':
            altctrl('1');
            break;
          case '8':
            altctrl('2');          
            break;
          case '9':
            altctrl('3');
            break;
          case 'A': 
            altctrl(']');
            break;
          case 'B':
            Keyboard.press(KEY_LEFT_CTRL);
            delay(20);
            Keyboard.print(']');
            Keyboard.releaseAll();
            break;
          case 'C':
            Keyboard.press(KEY_LEFT_CTRL);
            delay(20);
            Keyboard.print('[');
            Keyboard.releaseAll();
            break;
          case 'D':
            altctrl('[');
            break;
          case '*':
            Keyboard.press(KEY_LEFT_ALT);
            delay(30);
            Keyboard.press(KEY_LEFT_CTRL);
            delay(30);
            Keyboard.press(KEY_DOWN_ARROW);
            delay(30);
            Keyboard.releaseAll();
            break;
          case '#': 
            Keyboard.press(KEY_LEFT_ALT);
            delay(30);
            Keyboard.press(KEY_LEFT_CTRL);
            delay(30);
            Keyboard.press(KEY_UP_ARROW);
            delay(30);
            Keyboard.releaseAll();
            break;
        }
      }
      else if(mode==2){
        switch (K) {   
          case '1': 
            Keyboard.println("git init");
            break;
          case '2':
            Keyboard.print("echo \"# <Repo-details>\" >> README.md");
            break;
          case '3':
            Keyboard.println("git add README.md");
            break;
          case '4':
            Keyboard.print("git config user.email <email>");
            break;
          case '5':
            Keyboard.print("git config user.name <name>");
            break;
          case '6':
            Keyboard.print("git commit -m \"<commit-details>\"");
            break;
          case '7':
            Keyboard.println("git branch -M main");
            break;
          case '8':
            Keyboard.print("git remote add origin <repo-url>");
            break;
          case '9': 
            Keyboard.println("git push -u origin main");
            break;   
          case 'A': 
            run();
            Keyboard.println("code");
            break;
          case 'B':
            run();
            Keyboard.println("https://github.com");
            break;
          case 'C':
            Keyboard.press(KEY_LEFT_GUI);
            delay(30);
            Keyboard.press('x');
            delay(30);
            Keyboard.releaseAll();
            delay(100);
            Keyboard.print('i');
            break;
          case 'D':
            run();
            Keyboard.println("C:\projects_test");
            break;
          case '*':
            run();
            Keyboard.println("https://stackoverflow.com");
            break;
          case '#': 
            run();
            Keyboard.println("https://colab.research.google.com");
            break;
        }
      }
    }
  }
}