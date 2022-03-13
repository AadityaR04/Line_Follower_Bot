//For Serial Communication on Other Pins
#include <SoftwareSerial.h>

SoftwareSerial BT(3, 7); // RX, TX

// Motor Variables
int ML_1 = 6;
int ML_2 = 5;

int MR_1 = 11;
int MR_2 = 10;

// Sensor Variables
int L_sense = 2;
int R_sense = 8;

// Speed Control
int speed = 80;

// Bluetooth Control
char data = ' ';

void setup()
{
  // Setting of Motor Variables
  pinMode(MR_1, OUTPUT);
  pinMode(MR_2, OUTPUT);
  pinMode(ML_1, OUTPUT);
  pinMode(ML_2, OUTPUT);

  // Setting on Sensor Variables
  pinMode(L_sense, INPUT);
  pinMode(R_sense, INPUT);

  //Bluetooth Baud Rate
  BT.begin(9600);

}

void loop()
{
  // Reading Sensor Data
  int L_data = digitalRead(L_sense);
  int R_data = digitalRead(R_sense);


  //Checking if Bluetooth Module is reading a Data
  if (BT.available() > 0)
  {
    int temp = BT.read();

    //Speed Control
    
    if (temp == 'z')
    {
      //Speed Doesn't exceed 255
      speed = min(speed + 20, 255);
    }

    else if (temp == 'x')
    {
      //Speed doesn't fall below 0
      speed = max(speed - 20, 0);
    }

    else
    {
      //Which Line to follow data
      data = temp;
    }
  }

  //Line Follower
  if (data == 'o')
  {
    //Stop
    analogWrite(MR_1, 0);
    analogWrite(MR_2, 0);
    analogWrite(ML_1, 0);
    analogWrite(ML_2, 0);
  }

  if (data == 'w')
  {
    // White Line Follower

    if (L_data == 0 && R_data == 1)
    {
      //left
      analogWrite(MR_1, speed);
      analogWrite(MR_2, 0);
      analogWrite(ML_1, 0);
      analogWrite(ML_2, speed);
    }

    else if (L_data == 1 && R_data == 0)
    {
      //right
      analogWrite(MR_1, 0);
      analogWrite(MR_2, speed);
      analogWrite(ML_1, speed);
      analogWrite(ML_2, 0);
    }
    else if (L_data == 1 && R_data == 1)
    {
      //forward
      analogWrite(MR_1, speed);
      analogWrite(MR_2, 0);
      analogWrite(ML_1, speed);
      analogWrite(ML_2, 0);
    }

    else
    {
      //stop
      analogWrite(MR_1, 0);
      analogWrite(MR_2, 0);
      analogWrite(ML_1, 0);
      analogWrite(ML_2, 0);
    }
  }

  if (data == 'b')
  {
    // Black Line Follower
    if (L_data == 1 && R_data == 0)
    {
      //left
      analogWrite(MR_1, speed);
      analogWrite(MR_2, 0);
      analogWrite(ML_1, 0);
      analogWrite(ML_2, speed);
    }

    else if (L_data == 0 && R_data == 1)
    {
      //right
      analogWrite(MR_1, 0);
      analogWrite(MR_2, speed);
      analogWrite(ML_1, speed);
      analogWrite(ML_2, 0);
    }
    else if (L_data == 0 && R_data == 0)
    {
      //forward
      analogWrite(MR_1, speed);
      analogWrite(MR_2, 0);
      analogWrite(ML_1, speed);
      analogWrite(ML_2, 0);
    }

    else
    {
      //stop
      analogWrite(MR_1, 0);
      analogWrite(MR_2, 0);
      analogWrite(ML_1, 0);
      analogWrite(ML_2, 0);
    }
  }

}
