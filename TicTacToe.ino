/*
  Control a tictactoe game
*/

  const int Led1 = A0; //A0
  const int Led2 = A1; //A1
  const int Led3 = 13;
  const int Led4 = 16; //A2
  const int Led5 = 17; //A3
  const int Led6 = 12;
  const int Led7 = 18; //A4
  const int Led8 = 19; //A5
  const int Led9 = 11;
  int butlist[9];
  int LEDlist[9];
  int gamelist[9]; //lista que diz se a casa está ocupada ou não
  
  unsigned long previousMillis = millis();        // will store last time LED was updated
  unsigned long currentMillis = millis();
  int ledState = LOW;
// the setup routine runs once when you press reset:

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  for(int i=2;i <= 10; i++){
    pinMode(i, INPUT);  
  }

  // LED
 
  LEDlist[0] = Led1;
  LEDlist[1] = Led2;
  LEDlist[2] = Led3;
  LEDlist[3] = Led4;
  LEDlist[4] = Led5;
  LEDlist[5] = Led6;
  LEDlist[6] = Led7;
  LEDlist[7] = Led8;
  LEDlist[8] = Led9;
  
  for(int i=0;i <= 8; i++){
    pinMode(LEDlist[i], OUTPUT);
    }
}

void x_win(){
  for(int i=0;i <= 7; i+=2){
    digitalWrite(LEDlist[i], HIGH);
    digitalWrite(LEDlist[i+1], LOW);
    }
    digitalWrite(LEDlist[8], HIGH);
  delay(3000);
}
void o_win(){
  for(int i=0;i <= 7; i+=2){
    Serial.print(LEDlist[i+1]);
    Serial.print(" ");
    digitalWrite(LEDlist[i], LOW);
    digitalWrite(LEDlist[i+1], HIGH);    
    }
    digitalWrite(LEDlist[8], LOW);
  delay(3000);
}
  
void padrao(){
  for(int i=0;i <= 8; i++){
    digitalWrite(LEDlist[i], LOW);
  }
  for(int i=0;i <= 8; i++){
    digitalWrite(LEDlist[i], HIGH);
    delay(50);
  }
  for(int i=0;i <= 8; i++){
    digitalWrite(LEDlist[i], LOW);
    delay(50);
  }
}
int jogada(int play,int played, int i){
    if(played == 0){ // nao foi jogado
         return(1);
         }
    else{
      return(0);
    }
}

int ledblink(int ledPin){
  const int interval = 1000;           // interval at which to blink (milliseconds)
  
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    Serial.println(ledState);
    Serial.println(ledPin);
    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
}
}

void loop() {
  // read the input pin:
  bool buttonState;
  int gameon=1;
  bool vez;
  int turno = 0;
  int play;
  int jogadas[5][2];

  
  for(int i=0;i<9;i++){
    gamelist[i]= 0;
  }
  
  
  // JOGO COMEÇOU
    // padrao de inicio
    padrao();
    // 

  for(gameon = 1;gameon > 0; gameon++){ 
    vez = 1;// X    
    while (vez == 1){

      //blink
      if (ledState == LOW) {
                ledState = HIGH;
            } else {
                ledState = LOW;
            }
      for(int i=0;i <= 8; i++){
        
        if(turno>0 && i < turno){        
            
            currentMillis = millis();
            ledblink(jogadas[i][1]);

        }
        
        play = digitalRead(i+2);
        if(play == 1){  
          if(0 == gamelist[i]){
              vez = 0;
              jogadas[turno][0] = i;
              gamelist[i] = 1;
              digitalWrite(LEDlist[i], HIGH);
              break;
        }
    }       
}
    }

    // END GAME CHECK
    if(turno == 4){ //all lights
      gameon = 0;
      o_win();
      x_win();
      break;
      
    }
    
    delay(2);
    while (vez == 0){
      
      play = random(0, 9);
      if(gamelist[play] == 0){
              vez = 1;
              gamelist[play] = 1;
              jogadas[turno][1] = play;
              digitalWrite(LEDlist[play], HIGH);
      }
    }

    Serial.println(turno);
    Serial.print(jogadas[turno][0]);
    Serial.print("  ");
    Serial.println(jogadas[turno][1]);
    turno ++;
    
}
}
