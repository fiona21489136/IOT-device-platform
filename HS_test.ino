//bluetooth name: fiona
#include "a.h"
#include <SoftwareSerial.h>

const int BLUETOOTH_TX = 2;
const int BLUETOOTH_RX = 4;
unsigned long BAUD_RATE = 9600;
SoftwareSerial bluetooth(BLUETOOTH_TX, BLUETOOTH_RX);

/*for game*/
int collide_state = 0; /* 0:safe , -1:collide */
int game_ready = 0;
int map_idx = 0;
/*function*/
void fish_game();
bool check_collision(int, int);
void game_init();


// Global Variables
volatile int Hall_State = 0;
volatile int state;

// Use for RPM mode
volatile int is_rpm_count = 0;
volatile unsigned long int round_time = 0;

// Use to control animation
int pic_cycle = 0;
int pic = 0;
int pic_count = 0;
int pic_flag = 0;

// Use to control player blink frequency
char is_print = 0;

// Pins
const int HallPin = 3;
const int LEDpin[] = {13,12,11,10,9,8,7,6,5,A0};
const int pinA1 = A1;

// Use for Clock
int seconds;
int minutes;
int hours;

//Use for count down
int second=0;
int minute=0;
int hour=0;
int count_down = 0; // 0 and 1 
void ten_to_one(void);
void count_down_time(void);

// for select
int current_select = 0; // for choose clock to setup 
int count_down_select = 0;
int select_print = 0;

//Use for cute animation new_cute
int cute_pic = 0;
int cute_count = 0;
int cute_num = 0; //for select
int cute_flag = 0;

int menu_select = 0;

// Led high is 

void time_mode(void);

// Utility functions
void print_word();
void printChar(char letter);
void delay_between_words(void);
void printNumber(int num);

// Use to control player position
volatile int player_row = 0;
volatile int player_col = 0;

void game_mode(void);

unsigned long PreviousMillis=0;

void receive_bluetooth(void);
void switch_state(void);
//  Modes
void cute_mode(void);

void count_down_time_display(void);


void count_down_end(void); 

void game_win(void);
void game_over(void);
void game_pre_animation(void);





void update_time()
{
    if (++seconds == 60)
    {
        seconds = 0;
        if (++minutes == 60)
        {
            minutes = 0;
            if (++hours == 24)
                hours = 0;
        }
    }
    if( count_down == 1){
       count_down_time();     
    }
}


void setup() {

  // setup Serial
  Serial.begin(BAUD_RATE);
  bluetooth.begin(BAUD_RATE);
  Serial.println("Setup Complete");

  // setup bluetooth sensor interrupt
  attachInterrupt(digitalPinToInterrupt(BLUETOOTH_TX), receive_bluetooth, RISING);

  // setup hall sensor interrupt
  pinMode(HallPin,INPUT);
  attachInterrupt(digitalPinToInterrupt(HallPin), switch_state, FALLING);

  // setup LED output 
  for(int i = 0; i < 10; i++){
    pinMode(LEDpin[i],OUTPUT);
    digitalWrite(LEDpin[i],HIGH);  // set all LED to High --> turn off light
  }
  Serial.println("OK");

  // setup time
  seconds = 22;
  minutes = 58;
  hours = 12;

  //setup initinal state
  state = 10; // menu mode 

  PreviousMillis=millis();

  
}

void loop() { 
  if (millis()-PreviousMillis>=1000) {
    PreviousMillis=millis();
    update_time();
    if(pic_flag){
      pic_cycle++;
    }
  }

  //for testing 
  //Hall_State = 1;
  //state = 2;
  if(Hall_State == 1){
    if(state == 10){
        menu(); 
        //  menu mode to choose modes
    }else if(state == 0){
       // Serial.println("state 0");
       print_word();
    }
    else if(state == 1){
       time_mode();
       
    }
    else if(state == 2){
       
       count_down_time_display();
      
    }
    else if(state == 3){
       
       cute_mode();

    }else if(state == 4){
       //fish_game(); // game mode 
       game_pre_animation();
    }else if(state == 5){
       //game_mode();
       game_mode_Z();
    }else if(state == 6){
      game_over();
    }else if(state == 7){
      game_win();
    }
    else if(state == 9){
       ten_to_one();
    }
    else if(state == 8){
       count_down_end();
    }
    
  }
  
}
//menu


void menu(){
    // 45 ms go to the middle of the fan
    // state = 0 print world mode 
    Serial.println("menu");
    int delay_num = 10;
    //
    if ( menu_select == 0 ){
      delay(delay_num+20);
      printChar('D');
      delay_between_words();
      printChar('I');
      delay_between_words();
      printChar('S');
      delay_between_words();
      printChar('P');
      delay_between_words();
      printChar('L');
      delay_between_words();
      printChar('A');
      delay_between_words();
      printChar('Y');
      



    } else if  ( menu_select == 1 ){
      // Time mode 
      delay(delay_num+5);

      
      printChar('T');
      delay_between_words();
      printChar('I');
      delay_between_words();
      printChar('M');
      delay_between_words();
      printChar('E');
      delay_between_words();
      delay_between_words();
 
      delay_between_words();
      printChar('M');
      delay_between_words();
      printChar('O');
      delay_between_words();
      printChar('D');
      delay_between_words();
      printChar('E');

      
    } else if  ( menu_select == 2 ){
      delay(delay_num+5);
      printChar('T');
      delay_between_words();
      printChar('I');
      delay_between_words();
      printChar('M');
      delay_between_words();
      printChar('E');
      delay_between_words();
      printChar('R');
      delay_between_words();
      delay_between_words();
      printChar('M');
      delay_between_words();
      printChar('O');
      delay_between_words();
      printChar('D');
      delay_between_words();
      printChar('E');


    }else if  ( menu_select == 3 ){
      // Animation
      delay(delay_num+10);
      printChar('A');
      delay_between_words();
      printChar('N');
      delay_between_words();
      printChar('I');
      delay_between_words();
      printChar('M');
      delay_between_words();
      printChar('A');
      delay_between_words();
      printChar('T');
      delay_between_words();
      printChar('I');
      delay_between_words();
      printChar('O');
      delay_between_words();
      printChar('N');
    }else if  ( menu_select == 4 ){
      //game mode 
      delay(delay_num+10);
      printChar('G');
      delay_between_words();
      printChar('A');
      delay_between_words();
      printChar('M');
      delay_between_words();
      printChar('E');
      delay_between_words();
      printChar('.');
      delay_between_words();
      printChar('M');
      delay_between_words();
      printChar('O');
      delay_between_words();
      printChar('D');
      delay_between_words();
      printChar('E');


      
    }
    

    Hall_State = 0;
}

//
//game mode 

void game_mode_Z(){
  game_init();
  fish_game();
}


void game_init(){
  Serial.println("init");
  collide_state = 0;
  map_idx = 0;
  for(int i=0; i<84; i++)
    fish[i] = fish_original[i];
}

/* no collision: after bitwise and > 0  : false */
/* collision: after bitwise and > not 0 : true  */
bool check_collision(int fish_info, int map_info){
  bool collide = false;
  return collide = ((fish_info & map_info) == 0)? collide: true;
}

void up(){
  for(int i=0; i<84; i++){
    fish[i] = fish[i]<<2;
  }
}

void down(){
  for(int i=0; i<84; i++){
    fish[i] = fish[i]>>2;
  }
}

void fish_game(){
  Serial.println("game - start");
  int frame_count = 0;
  while(collide_state == 0){
    if(Hall_State == 1){
      frame_count += 1;
      delay(20);
      for(int i=0; i<84; i++){
        setLedstate( ( fish_map[(i+map_idx)%84] | fish[i] ) );            /* map-rotation  +  display */
        delayMicroseconds(700);
        setLedstate(0);
        delayMicroseconds(300);
        collide_state = check_collision( fish_map[(i+map_idx)%84], fish[i]) ? -1: collide_state;  /* check safe or not */
      }
      if(frame_count >= 2){
        frame_count = 0 ;
        map_idx = (map_idx >= 84)? 0: map_idx+1;                            /* map-rotation */
      }
      Hall_State = 0;
    }
    
    
    if(collide_state == -1){                         /* -1 :dead , 0: safe */
      state = 6;  // game-over
    }

  }
}


void game_mode(){
    int mask = 128;//10000000;
    int  player = 3; //  0b00000011;
    int player_now = player;   player_row;
    for (int i=0 ;i< player_row ;i++){
      player_now = player_now*2;
    }

    // make some delay before
    for (int i = 0; i < 84; i++)
    {
        if (player_col + 2 > 81)
        {
            state = 7; // you win 
            player_row = 0;
            player_col = 0;
        }
        int prints = game_map1[i];

        if (i >= player_col && i <= player_col + 1)
        {
            
            if (prints & player_now)
            {
                state = 6; //  game over 
                player_row = 0;
                player_col = 0;
            }
            if (is_print > 4)
            {
                prints = prints | player_now;
            }
        }

        int n = prints & mask;

        for(int j=0;j<8;j++){
            if ((n & 1) == 0){
              digitalWrite(LEDpin[j+1], 1);
          }else{
              digitalWrite(LEDpin[j+1], 0);
          }
          n /= 2;
  
        }
        
        digitalWrite(LEDpin[0], 0);
        digitalWrite(LEDpin[9], 0);


        delayMicroseconds(600);

        setLedstate(0);
        digitalWrite(LEDpin[0], 0);
        digitalWrite(LEDpin[9], 0);

        delayMicroseconds(600);
    }
    if (is_print > 4)
    {
        is_print = 0;
    }
    is_print++;
}


void game_win()
{
   
    delay(20);
    printChar('Y');
    delay_between_words();
    printChar('O');
    delay_between_words();
    printChar('U');
    delay_between_words();
    delay_between_words();
    printChar('W');
    delay_between_words();
    printChar('I');
    delay_between_words();
    printChar('N');
    Hall_State = 0;
}

void game_over()
{
   
    delay(20);
    printChar('G');

    delay_between_words();
    printChar('A');
    delay_between_words();
  
    printChar('M');
    delay_between_words();
   
    printChar('E');
    delay_between_words();
    
    delay_between_words();
    
    delay_between_words();
    printChar('O');
    delay_between_words();
    
    printChar('V');
    delay_between_words();
    
    printChar('E');
    delay_between_words();
    
    printChar('R');
    Hall_State = 0;
}

void game_pre_animation()
{
    Serial.println("game_pre animation");
    delay(20);
    Hall_State = 0;

    pic_flag = 1;

    printChar('L');
    delay_between_words();
    printChar('O');
    delay_between_words();
    printChar('A');
    delay_between_words();
    printChar('D');
    delay_between_words();
    printChar('I');
    delay_between_words();
    printChar('N');
    delay_between_words();
    printChar('G');
    delay_between_words();
    printChar('.');
  


    if (pic_cycle <= 10)
    { //pic_cycle
       Serial.println(pic_cycle);
        for (int i = 0; i < 9; i++)
        {
            
            setLedstate( walker[pic][i]);
           
            delayMicroseconds(600);
            setLedstate(0);
            delayMicroseconds(400);
        }

        if (pic_count == 1)
        {
            if (pic < 6)
            {
                pic++;
            }
            else
            {
                pic = 0;
            }
            pic_count = 0;
        }
        else
        {
            pic_count++;
        }
    }else{
        pic_cycle = 0;
        pic_flag = 0;
        state = 5;
        //state = 10;   //go to menu
       
  
    }

}

// count down time 
void count_down_end() 
{
    delay(15);

    printChar('O');
    delay_between_words();
    printChar('V');
    delay_between_words();
    printChar('E');
    delay_between_words();
    printChar('R');
    Hall_State = 0;
}

void ten_to_one()  
{
    setLedstate(dot_[second - 1][0]);
    
}

void count_down_time_display()
{
    delay(35);
    Hall_State = 0;

    printNumber(hour / 10);
    Serial.print(hour / 10);
    delay_between_words();
    printNumber(hour % 10);
    Serial.print(hour % 10);
    delay_between_words();
    printNumber(10);
    Serial.print(":");
    printNumber(minute / 10);
    Serial.print(minute / 10);
    delay_between_words();
    printNumber(minute % 10);
    Serial.print(minute % 10);
    delay_between_words();
    printNumber(10);
    Serial.print(":");
    printNumber(second / 10);
    Serial.print(second / 10);
    delay_between_words();
    printNumber(second % 10);
    Serial.println(second % 10);

}

void count_down_time()
{
    second--;
    if (second == 0)
    {
        if (minute == 0)
        {
            if (hour == 0)
            {
                state = 8; // count down end 
                count_down = 0; // count down flag 
            }
            else
            {
                hour--;
            }
        }
        else
        {
            minute--;
        }
    }
    if (second <= 10 && second != 0 && minute == 0 && hour == 0)
    {
        state = 9;  // ten_to_one();
    }
}
//

void time_mode()
{
    //state = 1; //1 for time mode
    // 25 ms go to the middle of the fan
    Serial.println("time");
    delay(35);

    printNumber(hours / 10);
    Serial.print(hours / 10);
    delay_between_words();
    printNumber(hours % 10);
    Serial.print(hours % 10);
    delay_between_words();
    printNumber(10); // :
    Serial.print(":");
    printNumber(minutes / 10);
    Serial.print(minutes / 10);
    delay_between_words();
    printNumber(minutes % 10);
    Serial.print(minutes % 10);
    delay_between_words();
    printNumber(10); // : 
    Serial.print(":");
    printNumber(seconds / 10);
    Serial.print(seconds / 10);
    delay_between_words();
    printNumber(seconds % 10);
    Serial.println(seconds % 10);
    Hall_State = 0;

}

void cute_mode() // animation 
{   
    Serial.println("animation");
    delay(48);
    Hall_State = 0;

    if (cute_num == 0)
    {
        for (int i = 0; i < 9; i++)
        {
            
            setLedstate( heart[cute_pic][i]);
           
            delayMicroseconds(700);
            setLedstate(0);
            delayMicroseconds(600);
        }

        if (cute_count == 1)
        {
            if (cute_pic == 1)
            {
                cute_pic = 0;
            }
            else
            {
                cute_pic = 1;
            }
            cute_count = 0;
        }
        else
        {
            cute_count++;
        }
    }else if (cute_num == 1)
    {
        for (int i = 0; i < 9; i++)
        {
            
            setLedstate( heart[cute_pic][i]);
           
            delayMicroseconds(700);
            setLedstate(0);
            delayMicroseconds(600);
        }

        if (cute_count == 1)
        {
            if (cute_pic == 1)
            {
                cute_pic = 0;
            }
            else
            {
                cute_pic = 1;
            }
            cute_count = 0;
        }
        else
        {
            cute_count++;
        }
    }else if (cute_num == 2)
    {
        for (int i = 0; i < 9; i++)
        {
            
            setLedstate( mushroom[cute_pic][i]);
           
            delayMicroseconds(700);
            setLedstate(0);
            delayMicroseconds(600);
        }

        if (cute_count == 1)
        {
            if (cute_pic == 1)
            {
                cute_pic = 0;
            }
            else
            {
                cute_pic = 1;
            }
            cute_count = 0;
        }
        else
        {
            cute_count++;
        }
    }else if (cute_num == 3)
    {
        for (int i = 0; i < 9; i++)
        {
            
            setLedstate( glass[cute_pic][i]);
           
            delayMicroseconds(700);
            setLedstate(0);
            delayMicroseconds(600);
        }

        if (cute_count == 1)
        {
            if (cute_pic == 1)
            {
                cute_pic = 0;
            }
            else
            {
                cute_pic = 1;
            }
            cute_count = 0;
        }
        else
        {
            cute_count++;
        }
    }
            
}

void print_word(){
    // 45 ms go to the middle of the fan
    Serial.println("display");
    Serial.println(select_print);
    int delay_count = 45;
    if ( select_print == 0 ){
      delay(delay_count);
      printChar('S');
      delay_between_words();
      printChar('A');
      delay_between_words();
      printChar('Y');
      delay_between_words();
      //printChar('U');
      //delay_between_words();
    } else if  ( select_print == 1 ){
      delay(delay_count);
      printChar('.');
      delay_between_words();
      printChar('H');
      delay_between_words();
      printChar('I');
      delay_between_words();
      printChar('.');
      delay_between_words();
    } else if  ( select_print == 2 ){
      delay(delay_count);
      printChar('.');
      delay_between_words();
      printChar('T');
      delay_between_words();
      printChar('O');
      delay_between_words();
      printChar('.');
      delay_between_words();
    } else if  ( select_print == 3 ){
      delay(delay_count);
      printChar('N');
      delay_between_words();
      printChar('Y');
      delay_between_words();
      printChar('C');
      delay_between_words();
      printChar('U');
      delay_between_words();
    }
    
    Hall_State = 0;
}

void delay_between_words(){
  delay(2);
}

void printNumber(int num)
{
    for (int i = 0; i < 5; i++)
    {
        if (num == 0)
            setLedstate(digit_0[i]);
        else if (num == 1)
            setLedstate(digit_1[i]);
        else if (num == 2)
            setLedstate(digit_2[i]);
        else if (num == 3)
            setLedstate(digit_3[i]);
        else if (num == 4)
            setLedstate(digit_4[i]);
        else if (num == 5)
            setLedstate(digit_5[i]);
        else if (num == 6)
            setLedstate(digit_6[i]);
        else if (num == 7)
            setLedstate(digit_7[i]);
        else if (num == 8)
            setLedstate(digit_8[i]);
        else if (num == 9)
            setLedstate(digit_9[i]);
        else if( num == 10)
            setLedstate(colon[i]);
        

        delayMicroseconds(600);
        setLedstate(0);
        delayMicroseconds(300);
    }
    delayMicroseconds(300);

}

void printChar(char letter)
{ 
    //Serial.println("test");
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
            
        delayMicroseconds(550);
        setLedstate(0);
        delayMicroseconds(300);

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


// interrupt fuctions 
// hall sensor interrupt
void switch_state(){

  if(Hall_State == 0){
    Hall_State = 1;
  }
}


// receive bluetooth msgs for controlling 
void receive_bluetooth() {
  
  if (bluetooth.available()) {
    String str = "";
    Serial.print("bluetooth: ");
    
    
    if (bluetooth.available()) {
      str += (char) bluetooth.read();
    }
    Serial.println(str);

    if(state == 10){
      // menu mode 
      if ( str == "0"){
        // up 
        menu_select +=1;
        if(menu_select == 5){
          menu_select = 0;
        }
        
      }else if (str == "1"){
        // down 
        menu_select -=1;
        if(menu_select == -1){
          menu_select = 4;
        }
        
      }else if (str == "2"){
        // right 
        menu_select +=1;
        if(menu_select == 5){
          menu_select = 0;
        }
        
      }else if (str == "3"){
        // back
        state = 10;
      }else if (str == "4"){
        // go
        state = menu_select;
      }

    } else if (state == 0){ 
      // display mode 

      if ( str == "0"){
        // up 
        select_print+=1;
        if (select_print == 4){
          select_print = 0;
        }
        
      }else if (str == "1"){
        // down 
        select_print-=1;
        if (select_print == -1){
          select_print = 3;
        }
        
      }else if (str == "2"){
        // right 
        select_print+=1;
        if (select_print == 4){
          select_print = 0;
        }
        
      }else if (str == "3"){
        // back
        state = 10;
        select_print = 0; // go back to initinal 
        menu_select = 0;
      }
    }  
    else if (state == 1)  
    {  
      //  time mode 
      if(str == "0"){ 
        // up 
        if(current_select == 0){ // hours
           hours++;
           if (hours == 24)
                hours = 0;
        }else if(current_select == 1){ // min
           minutes++;
           if (minutes == 60)
               minutes = 0;
        }else if (current_select == 2){ //sec
           seconds++;
                if (seconds == 60)
                    seconds = 0;
        }
        
      }else if (str == "1") { 
        // down
        if(current_select == 0){ // hours
           hours--;
           if (hours == -1)
                hours = 24;
        }else if(current_select == 1){ // min
           minutes--;
           if (minutes == -1)
               minutes = 0;
        }else if (current_select == 2){ //sec
           seconds--;
          if (seconds == -1)
               seconds = 0;
        }
        
      }else if (str == "2"){  
        // right
        current_select+=1;
        if ( current_select == 4){
          current_select = 0;
        }
        
      }else if (str == "3"){
        // back
        state = 10;
        current_select = 0; // go back to initinal 
        menu_select = 0;
      }
    }
    else if (state == 3)
    {
      // cute mode
      if ( str == "0"){  // left
        cute_num+=1;
        cute_num = cute_num%4;
        
      }else if (str == "1"){  // right
        cute_num-=1;
        cute_num = (cute_num+=4)%4;
        
      } else if (str == "3"){
        // back
        state = 10;
        cute_num = 0; // go back to initinal 
        menu_select = 0;
      }
    }
    // count down mode 
    else if (state == 2)
    {

      if(str == "0"){ // up 
        if(count_down_select == 0){ // hours
           hour++;
           if (hour == 25)
                hour = 0;
        }else if(count_down_select == 1){ // min
           minute++;
           if (minute == 60)
               minute = 0;
        }else if (count_down_select == 2){ //sec
           second++;
           if (second == 60)
               second = 0;
        }
        
      }else if (str == "1") { // down

        if(count_down_select == 0){ // hours
           hour--;
           if (hour == -1)
                hour = 24;
        }else if(count_down_select == 1){ // min
           minute--;
           if (minute == -1)
               minute = 0;
        }else if (count_down_select == 2){ //sec
           second--;
          if (second == -1)
               second = 0;
        }
        
      }else if ( str == "2"){  // right
        count_down_select+=1;
        if ( count_down_select == 4){
          count_down_select = 0;
        }        
      }else if (str == "3"){  
        // go back
        state = 10;
        menu_select = 0;
        count_down_select = 0;

      }else if (str == "4"){  // enter go 
        count_down = 1;
      } 
    }else if (state == 6){  // game finish
      if (str == "3"){  
        // go back
        state = 10;
        menu_select = 0;
      }
      
    }else if(state == 5){  // enter game mode
      if (str == "3"){  
        // go back
        state = 10;
        menu_select = 0;
      } else if (str == "0"){   // up
          up();
      }else if (str == "1"){  //down 
          down();
      }
    }else if(state == 8){   // count down finish
      if (str == "3"){  
        // go back
        state = 10;
        menu_select = 0;
      }
    }else if(state == 7){  // game win 
      if (str == "3"){  
        // go back
        state = 10;
        menu_select = 0;
      }
    }
    
  }
}
