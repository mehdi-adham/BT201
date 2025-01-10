/**
 * @file BT201_Base.ino
 * @author Mehdi Adham (mehdi.adham@yahoo.com)
 * @brief  This example shows base function of library for BT201.
 * BT-201 module use KT1025A chip. 
 * KT1025A chip is a four-in-one single chip that 
 * supports Bluetooth, U disk and TF card. 
 * 
 * @version 1.0
 * @date 2025-01-10
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "bt201.h"


BT201 my_bt201;

void setup()
{
  my_bt201.begin(Serial2);

#ifdef BT201_DEBUG
  Serial.begin(9600);
#endif

  my_bt201.volume_set(5);
  my_bt201.PlayPause();
  // my_bt201.Next_Song();
  // my_bt201.Last_Song();
  // my_bt201.Volume_UP();
  // my_bt201.Volume_Down();
  my_bt201.Set_Baud_Rate(baudRate_115200);
  // my_bt201.Chip_Reset();
  my_bt201.Chip_Mode(U_disk_mode);
  // my_bt201.Mute(true);
}

void loop()
{
}
