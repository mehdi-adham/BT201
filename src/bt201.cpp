#include "Arduino.h"
#include "bt201.h"


typedef enum
{

} BT201_function;

typedef enum
{
  PREV = 0, // Last song
  NEXT,     // Next song
  VOL_DOWN, // Volume -
  VOL_UP,   // Volume +
  MODE,     // Switching Bluetooth and U-disk TF Cards
  PP        // Play pause
} BT201_Key_Function;

// wait for timeOut
void wait_for_timeOut(int timeOut)
{
  int duration;
  unsigned long Curr_time;
  unsigned long Prev_time = millis();

  while (true)
  {
    Curr_time = millis();

    if (Curr_time < Prev_time)
      duration = Curr_time + (UINT_MAX - Prev_time);
    else
      duration = Curr_time - Prev_time;

    if (duration >= timeOut)
      break;
  }
}

// init BT201 Module
void init_BT201()
{
  Serial.begin(9600);
}

bool BT201_Send_CMD(BT201_function fun)
{
}