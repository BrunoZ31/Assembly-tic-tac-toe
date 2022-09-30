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
  
  const int LEDlist[3][3] = {{Led1,Led2,Led3},{Led4,Led5,Led6},{Led7,Led8,Led9}};
  const int LEDlist1d[9] = {Led1,Led2,Led3,Led4,Led5,Led6,Led7,Led8,Led9};
  const int butlist[3][3] = {{2,3,4},{5,6,7},{8,9,10}};
  
  int board[3][3];
  
  unsigned long previousMillis = millis();        // will store last time LED was updated
  unsigned long currentMillis = millis();
  int ledState = LOW;

void x_win(){
  for(int i=0;i <= 7; i+=2){
    digitalWrite(LEDlist1d[i], HIGH);
    digitalWrite(LEDlist1d[i+1], LOW);
  }
  digitalWrite(LEDlist1d[8], HIGH);
  delay(3000);
}

void o_win(){
  for(int i=0;i <= 7; i+=2){
    digitalWrite(LEDlist1d[i], LOW);
    digitalWrite(LEDlist1d[i+1], HIGH);
  }
  digitalWrite(LEDlist1d[8], LOW);
  delay(3000);
}
  
void padrao(){
  for(int i=0;i < 3; i++){
    for (int j = 0; j < 3; ++j)
    {
      digitalWrite(LEDlist[i][j], LOW);
    }
  }
  for(int i=0;i < 3; i++){
    for (int j = 0; j < 3; ++j)
    {
      digitalWrite(LEDlist[i][j], HIGH);
      delay(50);
    }
  }
  for(int i=0;i < 3; i++){
    for (int j = 0; j < 3; ++j)
    {
      digitalWrite(LEDlist[i][j], LOW);
      delay(50);
    }
  }
  
}

int ledblink(int ledPin){
  const int interval = 1000;           // interval at which to blink (milliseconds)
  
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
}
}

bool rowCrossed(int board[3][3])
{
    for (int i=0; i<2; i++)
    {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2] && 
            board[i][0] != 0)
            return (true);
    }
    return(false);
}
  
// A function that returns true if any of the column
// is crossed with the same player's move
bool columnCrossed(int board[3][3])
{
    for (int i=0; i<2; i++)
    {
        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i] && 
            board[0][i] != 0)
            return (true);
    }
    return(false);
}
  
// A function that returns true if any of the diagonal
// is crossed with the same player's move
bool diagonalCrossed(int board[3][3])
{
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2] && 
        board[0][0] != 0)
        return(true);
          
    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0] &&
         board[0][2] != 0)
        return(true);
  
    return(false);
}
  
// A function that returns true if the game is over
// else it returns a false
bool gameOver(int board[3][3])
{
    return(rowCrossed(board) || columnCrossed(board)
            || diagonalCrossed(board) );
}

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  for(int i=2;i <= 10; i++){
    pinMode(i, INPUT);  
  }

  for(int i=0;i < 3; i++){
    for (int j = 0; j < 3; ++j){
    pinMode(LEDlist[i][j], OUTPUT);
    }
  }
}
void loop() {
  // read the input pin:
  bool buttonState;
  int gameon = 1;
  bool vez = 1;
  int turno = 0;

  for(int i=0;i < 3; i++){
    for (int j = 0; j < 3; j++)
    {
      board[i][j] = 0;
    }
  }
  // JOGO COMEÇOU
    // padrao de inicio
    padrao();
   

  while(gameon == 1){ 
    
    while (vez == 1){
      
      for(int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
 
          if(digitalRead(butlist[i][j]) == 1){  
            if(0 == board[i][j]){
                vez = 0;
                board[i][j] = 1;
                digitalWrite(LEDlist[i][j], HIGH);
                break;
              }
            }       
          }
        }
      }
      //blink
    
        
    // END GAME CHECK
    if(gameOver(board)){ //pattern x
      gameon = 0;
      x_win();
      break;      
    }

    if(turno == 4){ //all lights
      gameon = 0;
      padrao();
      break;      
    }
    
    delay(2);

    
    // AI
    while (vez == 0){
      
      int i = random(0, 3);
      int j = random(0, 3);     
      if(board[i][j] == 0){
        
        vez = 1;
        board[i][j] = 2;
        digitalWrite(LEDlist[i][j], HIGH);
        break;
      }
    }

    if(gameOver(board)){ //all lights
      gameon = 0;
      o_win();
      break;      
    }

    Serial.print("turno: ");
    Serial.println(turno);
    String str;

    Serial.println(str+board[0][0]+" "+board[0][1]+" "+board[0][2]);
    Serial.println(str+board[1][0]+" "+board[1][1]+" "+board[1][2]);
    Serial.println(str+board[2][0]+" "+board[2][1]+" "+board[0][2]);
    turno ++;
    
}
}

