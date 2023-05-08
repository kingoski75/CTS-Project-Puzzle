int randomNumberList[4]; // Creates an array to store random numbers for the sequence the user must copy
int userInputList[4]; // Creates an array to store user input to compare to the random sequence
int listPosition = 0; // creates variable used to change the position the user input is put into the array userInputList
int Level = 1; // creates a variable to check what level the user is on


int ledPins[4] = {5, 4, 3, 2}; // Creates an array with the LED pins to correspond to the arduino input slots
#define BUZZER 12
#define bButton A0
#define yButton A1
#define rButton A2
#define gButton A3
int bState = 0; // creates a variable used to check the state if the button (whether it is pressed or not.)
int yState = 0;
int rState = 0;
int gState = 0;
bool hint = false;


void blue()
{
  bool hasPlayed = false; // boolean to check if function has been run, function will stop running when set as true
  if (!hasPlayed) // play the tone and toggle the LED only if the function has not been called yet
  { 
    digitalWrite(5, HIGH);// activates the led corresponding to the button
    tone(BUZZER, 180); // Set the buzzer play a tone
    delay(500); // Delay for 500ms 
    noTone(BUZZER); // Stop the buzzer
    digitalWrite(5,LOW); //turns off the led
    delay(200);
    hasPlayed = true; // set hasPlayed to true to end the function
  }
}      

void yellow()
{
  bool hasPlayed = false;
  if (!hasPlayed) 
  {
    digitalWrite(4, HIGH);
    tone(BUZZER, 440); 
    delay(500); 
    noTone(BUZZER); 
    digitalWrite(4,LOW);
    hasPlayed = true;
  }
  delay(200);  
}

void red()
{
  bool hasPlayed = false;
  if (!hasPlayed) 
  {
    digitalWrite(3, HIGH);
    tone(BUZZER, 698); 
    delay(500);
    noTone(BUZZER);
    digitalWrite(3,LOW);
    hasPlayed = true;    
  }
  delay(200);  
}

void green()
{
  bool hasPlayed = false;
  if (!hasPlayed) 
  {
    digitalWrite(2, HIGH);
    tone(BUZZER, 960); 
    delay(500); 
    noTone(BUZZER); 
    digitalWrite(2,LOW);
    hasPlayed = true;       
  }
  delay(200);  
}

void setup() 
{
  pinMode(BUZZER, OUTPUT);
  pinMode(bButton, INPUT_PULLUP);
  pinMode(yButton, INPUT_PULLUP);
  pinMode(rButton, INPUT_PULLUP);
  pinMode(gButton, INPUT_PULLUP);
  randomSeed(analogRead(5)); // seed random number generator, making the random numbers generated different each time the program is run by reading the voltage level at analog input 5.

  //creates the random sequence the user must input
  int randomNum1 = 1 + (random() % 4); //Generates a random number between 1-4
  randomNumberList[0] = randomNum1;  //Assigns the value stored in randomNum to the first position of the randomNumberList array
  int randomNum2 = 1 + (random() % 4); 
  randomNumberList[1] = randomNum2;  
  int randomNum3 = 1 + (random() % 4);
  randomNumberList[2] = randomNum3;  
  int randomNum4 = 1 + (random() % 4); 
  randomNumberList[3] = randomNum4;  
}

void userButtonInput()
{
  bState = digitalRead(bButton); //sets the value of the variable to the current state of corresponding button
  if(bState == LOW) //checks if button is pressed
  {
    digitalWrite(5, HIGH);// activates the led corresponding to the button
    tone(BUZZER, 180); // Set the buzzer playing a 1000hz tone
    delay(500); // Delay for 500ms (half a second)
    noTone(BUZZER); // Stop the buzzer
    userInputList[listPosition] = 1;//adds the value 1 to the position stated by the variable "listPosition" in the array userInputList
    listPosition++; // increases variable by 1
  }
  else
  {
    digitalWrite(5,LOW); //turns off the led
    noTone(BUZZER);//turns off button
  }
  yState = digitalRead(yButton);
  if(yState == LOW) 
  {
    digitalWrite(4, HIGH);
    tone(BUZZER, 440); 
    delay(500); 
    noTone(BUZZER); 
    userInputList[listPosition] = 2;
    listPosition++;
  }
  else
  {
    digitalWrite(4,LOW);
    noTone(BUZZER);
  }
    
  rState = digitalRead(rButton);
  if(rState == LOW)
  {
    digitalWrite(3, HIGH);
    tone(BUZZER, 698); 
    delay(500);
    noTone(BUZZER);
    userInputList[listPosition] = 3;
    listPosition++;
  }
  else
  {
    digitalWrite(3,LOW);
    noTone(BUZZER);
  }

  gState = digitalRead(gButton);
  if(gState == LOW) 
  {
    digitalWrite(2, HIGH);
    tone(BUZZER, 960); 
    delay(500); 
    noTone(BUZZER); 
    userInputList[listPosition] = 4;
    listPosition++;
  }
  else
  {
    digitalWrite(2,LOW);
    noTone(BUZZER);
  }                   
}  

void correct()
{
  digitalWrite(5, LOW);  // turn off all the LEDs in the array
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);
  digitalWrite(2, LOW);
  delay(400); 
  tone(BUZZER, 1000); 
  delay(400); 
  tone(BUZZER, 1500); 
  delay(500); 
  noTone(BUZZER); 
  delay(500); 
  
  // Reset the userInputList array and listPosition variable to start over for next level
  listPosition = 0;
  int userInputList[4] = {0}; // clears userInputList
  Level = Level + 1; //increase the level by 1
}
void incorrect()
{
  digitalWrite(5, LOW);  
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);
  digitalWrite(2, LOW);
  delay(400); 
  tone(BUZZER, 800); 
  delay(400); 
  tone(BUZZER, 500);
  delay(500); 
  noTone(BUZZER); 
  delay(500); 

  listPosition = 0;
  int userInputList[4] = {0}; // clears userInputList
}

void loop() 
{
  
  // put your main code here, to run repeatedly:
  if (Level == 1)
  {
    while (!hint) 
    {
      switch (randomNumberList[0]) 
      {
        case 1:
          blue();
          break;
        case 2:
          yellow();
          break;
        case 3:
          red();
          break;
        case 4:
          green();
          break;
      }
      hint = true;
    }
    
    while (hint == true)//while loop to check if the hint sequence has been played.
    {
      if (listPosition < 1) //checks if the variable listPosition is less than 1. This variable gets increased by the users input
      {
        userButtonInput();
      }  
      else 
      {   
        if (userInputList[0] == randomNumberList[0])
        {
          hint = false;
          correct();
        }
        else
        {
          hint = false;
          incorrect();    
        }
      }
    }
  }
  
  else if (Level == 2)
  {
  
    while (!hint) 
    {
      for (int i = 0; i < 2; i++) 
      {
        switch (randomNumberList[i]) 
        {
          case 1:
            blue();
            break;
          case 2:
            yellow();
            break;
          case 3:
            red();
            break;
          case 4:
            green();
            break;
        }
      }
      hint = true;
    }
    while (hint == true)
    {
      if (listPosition < 2) 
      {
        userButtonInput();
      }  
      else 
      {   
        if (userInputList[0] == randomNumberList[0] && userInputList[1] == randomNumberList[1]) 
        {
          hint = false;
          correct();
          delay(100);
        }
        else
        {
          hint = false;
          incorrect();  
          delay(100);
        }
      }
    }
  }
  else if (Level == 3)
  {  
    while (!hint) 
    {
      for (int i = 0; i < 3; i++) 
      {
        switch (randomNumberList[i]) 
        {
          case 1:
            blue();
            break;
          case 2:
            yellow();
            break;
          case 3:
            red();
            break;
          case 4:
            green();
            break;
        }
      }
      hint = true;
    }
    while (hint == true)
    {
      if (listPosition < 3) 
      {
        userButtonInput();
      }  
      else    
      {    
        if (userInputList[0] == randomNumberList[0] && userInputList[1] == randomNumberList[1] && userInputList[2] == randomNumberList[2]) 
        {
          hint = false;
          correct();
          delay(100);
        }
        else
        {
          hint = false;
          incorrect();    
          delay(100);
        }  
      } 
    }
  }
  else if (Level == 4)
  {  
    while (!hint) 
    {
      for (int i = 0; i < 4; i++) 
      {
        switch (randomNumberList[i]) 
        {
          case 1:
            blue();
            break;
          case 2:
            yellow();
            break;
          case 3:
            red();
            break;
          case 4:
            green();
            break;
        }
      }
      hint = true;
    }
    while (hint == true)
    {
      if (listPosition < 4) 
      {
        userButtonInput();
      }  
      else    
      {    
        if (userInputList[0] == randomNumberList[0] && userInputList[1] == randomNumberList[1] && userInputList[2] == randomNumberList[2] && userInputList[3] == randomNumberList[3]) 
        {
          hint = false;
          correct();
          delay(100);
        }
        else
        {
          hint = false;
          incorrect();    
          delay(100);
        }  
      } 
    }
  }
  else if (Level == 5)
  {
      digitalWrite(5, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(2, HIGH);
      tone(BUZZER, 659, 200); 
      delay(100); 
      tone(BUZZER, 784, 200);
      delay(100); 
      tone(BUZZER, 880, 400);
      delay(200); 
      tone(BUZZER, 1047, 400);
      delay(200); 
      noTone(BUZZER); 
      delay(1000); 
      digitalWrite(5, LOW);
      digitalWrite(4, LOW);
      digitalWrite(3, LOW);
      digitalWrite(2, LOW);
      delay(500);
      Level = Level + 1;
  }
}
