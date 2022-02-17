#include "a.h"

// Global Variables
volatile int Hall_State = 0;

// Pins
const int HallPin = 3;
//const int LEDpin[] = {A0,5,6,7,8,9,10,11,12,13};
const int LEDpin[] = {13,12,11,10,9,8,7,6,5,A0};
const int pinA1 = A1;


// Utility functions
void printChar(char letter);
void delay_between_words();



void setup() {
  // setup Serial
  Serial.begin(9600);

  // setup hall sensor interrupt
  pinMode(HallPin,INPUT);//INPUT_PULLUP
  attachInterrupt(digitalPinToInterrupt(HallPin),switch_state,FALLING);//FALLING //RISING

  // setup LED output 
  for(int i = 0; i < 10; i++){
    pinMode(LEDpin[i],OUTPUT);
    digitalWrite(LEDpin[i],HIGH);  // set all LED to High --> turn off light
  }
  Serial.println("OK");

  
}

void loop() {
  
  if(Hall_State == 1){
    print_word();
    //Serial.println("test");
  }
  
}

void delay_between_words(){
  delay(3);
}

void print_word(){
    // 45 ms go to the middle of the fan
    delay(30);
    printChar('A');
    delay_between_words();
    printChar('B');
    delay_between_words();
    printChar('C');
    delay_between_words();
    printChar('D');
    delay_between_words();

    Hall_State = 0;
}


void printChar(char letter){
   
    Serial.println("test");
    //digital_counter++;
    for (int i = 0; i < 7; i++)
    {
        if (letter == 'A')
            setLedstate(letter_A[i]);
        else if (letter == 'B')
            setLedstate(letter_B[i]);
        else if (letter == 'C')
            setLedstate(letter_C[i]);
        else if (letter == 'D')
            setLedstate(letter_D[i]);
        else if (letter == 'E')
            setLedstate(letter_E[i]);
        else if (letter == 'F')
            setLedstate(letter_F[i]);
        else if (letter == 'G')
            setLedstate(letter_G[i]);
        else if (letter == 'H')
            setLedstate(letter_H[i]);
        else if (letter == 'I')
            setLedstate(letter_I[i]);
        else if (letter == 'J')
            setLedstate(letter_J[i]);
        else if (letter == 'K')
            setLedstate(letter_K[i]);
        else if (letter == 'L')
            setLedstate(letter_L[i]);
        else if (letter == 'M')
            setLedstate(letter_M[i]);
        else if (letter == 'N')
            setLedstate(letter_N[i]);
        else if (letter == 'O')
            setLedstate(letter_O[i]);
        else if (letter == 'P')
            setLedstate(letter_P[i]);
        else if (letter == 'Q')
            setLedstate(letter_Q[i]);
        else if (letter == 'R')
            setLedstate(letter_R[i]);
        else if (letter == 'S')
            setLedstate(letter_S[i]);
        else if (letter == 'T')
            setLedstate(letter_T[i]);
        else if (letter == 'U')
            setLedstate(letter_U[i]);
        else if (letter == 'V')
            setLedstate(letter_V[i]);
        else if (letter == 'W')
            setLedstate(letter_W[i]);
        else if (letter == 'X')
            setLedstate(letter_X[i]);
        else if (letter == 'Y')
            setLedstate(letter_Y[i]);
        else if (letter == 'Z')
            setLedstate(letter_Z[i]);
        else if (letter == '.')
            setLedstate(letter_dot[i]);
        delayMicroseconds(700);

        setLedstate(0);

        delayMicroseconds(500);

    }
}

// given an int( 10 bits long), and display it by LED
// 
void setLedstate(int n){
  for(int i=0;i<10;i++){
     if ((n & 1) == 0){
        digitalWrite(LEDpin[i], 1);
     }else{
        digitalWrite(LEDpin[i], 0);
     }
     n /= 2;
  
  }
}



//
void switch_state(){
  
  if(Hall_State == 0){
    Hall_State = 1;
  }
}
