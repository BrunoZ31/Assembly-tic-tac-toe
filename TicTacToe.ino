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
  int piscando[5] = {0};
  
  bool ledState = false;

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

ISR(TIMER1_COMPA_vect)
{
  ledState =!ledState;
  for(int n=0; n<5; n++){
    if(piscando[n] != 0){
    digitalWrite(piscando[n], ledState);
    }
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

  TCCR1A = 0;                      //Reset Timer1 control Registor A

  bitClear(TCCR1B, WGM13);         //Set CTC mode
  bitSet(TCCR1B, WGM12);


  bitSet(TCCR1B, CS12);            //Set prescaler to 1024
  bitClear(TCCR1B, CS11);
  bitSet(TCCR1B, CS10);

  //Reset Timer1
  TCNT1 = 0;

  //set compare value
  //OCR1A = 3906;     //for 0.25sec
  OCR1A = 7812;    //for 0.5sec
  //OCR1A = 15625;   //for 1sec
  //OCR1A = 31250;   //for 2sec

  bitSet(TIMSK1, OCIE1A); // Enable Timer1 compare interrupt
  sei();                  // Enable global interrupts
}

void clearBoard(int board[3][3]){
  for(int i=0;i < 3; i++){
    for (int j = 0; j < 3; j++)
    {
      board[i][j] = 0;
    }
  }
  for(int n=0; n<5; n++){
      piscando[n]=0;
    }
}

void loop() {
  // read the input pin:
  bool buttonState;
  int gameon = 1;
  bool vez = 1;
  int counter = 0;
  int turno = 0;
  
  
  clearBoard(board);
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
        
    // END GAME CHECK
    if(gameOver(board)){ //pattern x
      gameon = 0;
      delay(1500);
      clearBoard(board);
      x_win();
      break;      
    }

    if(turno == 4){ //all lights
      gameon = 0;
      delay(1500);
      clearBoard(board);
      padrao();
      break;      
    }
    
    delay(20);

    
    // AI
    //Win if possible:
    //Check lines
      int i = 0;
      while ((i<3)&&(vez == 0))
        {
          counter = 0;
          for (int j=0; j<3; j++)
            {
              if (board[i][j] == 2)
              {
                counter = counter + 1;
              }
            }
          if (counter == 2) //If there is a winning move in the line
          for (int j = 0; j<3; j++)
            if (board[i][j]==0)
            {
              board[i][j] = 2;
              vez = 1;
              piscando[turno] = LEDlist[i][j];
            }
          i++;
        }
      
    //Check columns
      i = 0;
      while ((i<3)&&(vez == 0))
        {
          counter = 0;
          for (int j=0; j<3; j++)
            {
              if (board[j][i] == 2)
              {
                counter = counter + 1;
              }
            }
          if (counter == 2) //If there is a winning move in the line
          for (int j = 0; j<3; j++)
            if (board[j][i]==0)
            {
              board[j][i] = 2;
              vez = 1;
              piscando[turno] = LEDlist[j][i];
            }
          i++;
        }
      
      //Check diagonals
      counter = 0;
      for (i=0; i<3; i++)
        {
          if (board[i][i] == 2)
              {
                counter = counter + 1;
              }
        }
      if (counter == 2) //If there is a winning move in the diagonal
      for (i = 0; i<3; i++)
        {
          if (board[i][i]==0)
            {
              board[i][i] = 2;
              vez = 1;
              piscando[turno] = LEDlist[i][i];
            }  
        }   


      counter = 0;
      for (i=0; i<3; i++)
        {
          if (board[i][2-i] == 2)
              {
                counter = counter + 1;
              }
        }
      if (counter == 2) //If there is a winning move in the diagonal
      for (i = 0; i<3; i++)
        {
          if (board[i][2-i]==0)
            {
              board[i][2-i] = 2;
              vez = 1;
              piscando[turno] = LEDlist[i][2-i];
            }  
        }   
        


    //Block winning player moves
        int j = 0;
    //Check lines
      i = 0;
      while ((i<3)&&(vez == 0))
        {
          counter = 0;
          for (j=0; j<3; j++)
            {
              if (board[i][j] == 1)
              {
                counter = counter + 1;
              }
            }
          if (counter == 2) //If there is a winning move in the line
          for (j = 0; j<3; j++)
            if (board[i][j]==0)
            {
              board[i][j] = 2;
              vez = 1;
              piscando[turno] = LEDlist[i][j];
            }
          i++;
        }
      
    //Check columns
      i = 0;
      while ((i<3)&&(vez == 0))
        {
          counter = 0;
          for (j=0; j<3; j++)
            {
              if (board[j][i] == 1)
              {
                counter = counter + 1;
              }
            }
          if (counter == 2) //If there is a winning move in the line
          for (j = 0; j<3; j++)
            if (board[j][i]==0)
            {
              board[j][i] = 2;
              vez = 1;
              piscando[turno] = LEDlist[j][i];
            }
          i++;
        }
      
      //Check diagonals
      while(vez == 0)
      {
        counter = 0;
        
        for (i=0; i<3; i++)
          {
            if (board[i][i] == 1)
                {
                  counter = counter + 1;
                }
          }
        if (counter == 2){ //If there is a winning move in the diagonal
          for (i = 0; i<3; i++)
          {
            if (board[i][i]==0)
              {
                board[i][i] = 2;
                vez = 1;
                piscando[turno] = LEDlist[i][i];
              }  
          }
        }   


        counter = 0;
        for (i=0; i<3; i++)
          {
            if (board[i][2-i] == 1)
                {
                  counter = counter + 1;
                }
          }
        if (counter == 2){ //If there is a winning move in the diagonal
          for (i = 0; i<3; i++)
          {
            if (board[i][2-i]==0)
              {
                board[i][2-i] = 2;
                vez = 1;
                piscando[turno] = LEDlist[i][2-i];
              }  
          }   
          }

        //If there are no winning moves for either side:
        if (board[1][1]==0&&vez == 0)
          {
            board[1][1] = 2;
            vez = 1;
            piscando[turno] = LEDlist[1][1];
          } 
        if (board[1][0]==0&&vez == 0)
          {
            board[1][0] = 2;
            vez = 1;
            piscando[turno] = LEDlist[1][0];
          } 
        if (board[0][1]==0&&vez == 0)
          {
            board[0][1] = 2;
            vez = 1;
            piscando[turno] = LEDlist[0][1];
          } 
        if (board[1][2]==0&&vez == 0)
          {
            board[1][2] = 2;
            vez = 1;
            piscando[turno] = LEDlist[1][2];
          } 
        if (board[2][1]==0&&vez == 0)
          {
            board[2][1] = 2;
            vez = 1;
            piscando[turno] = LEDlist[2][1];
          } 

        if (board[0][0]==0&&vez == 0)
          {
            board[0][0] = 2;
            vez = 1;
            piscando[turno] = LEDlist[0][0];
          } 
        if (board[2][2]==0&&vez == 0)
          {
            board[2][2] = 2;
            vez = 1;
            piscando[turno] = LEDlist[2][2];
          } 
        if (board[0][2]==0&&vez == 0)
          {
            board[0][2] = 2;
            vez = 1;
            piscando[turno] = LEDlist[0][2];
          } 
        }

        Serial.print("turno: ");
        Serial.println(turno);
        String str;

        Serial.println(str+board[2][2]+" "+board[2][1]+" "+board[2][0]);
        Serial.println(str+board[1][2]+" "+board[1][1]+" "+board[1][0]);
        Serial.println(str+board[0][2]+" "+board[0][1]+" "+board[0][0]);
        turno ++;

        if(gameOver(board)){ //all lights
          gameon = 0;
          delay(1500);
          clearBoard(board);
          o_win();
          break;      
        }
    }
    clearBoard(board);
}
