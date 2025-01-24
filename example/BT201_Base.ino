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

String bluetooth_Name = "Audio_BT";
String bluetooth_password = "1234";

BT201 my_bt201;


void setup()
{
  my_bt201.begin(Serial2);

#ifdef BT201_DEBUG
  Serial.begin(9600);
#endif

  // my_bt201.Set_Baud_Rate(baudRate_115200);
  my_bt201.Set_Name_for_EDR_Bluetooth(bluetooth_Name);
  my_bt201.Set_Pass_for_EDR_Bluetooth(bluetooth_password);
  my_bt201.open_Bluetooth_Pass(true);
  my_bt201.Set_Power_on_Mode(Enters_waiting_state);
  my_bt201.Chip_Reset();
  my_bt201.Chip_Mode(U_disk_mode);
  
  my_bt201.volume_set(15);
  // my_bt201.Volume_UP();
  // my_bt201.Volume_Down();
  // my_bt201.Mute(true);

  // my_bt201.PlayPause();
  // my_bt201.PP();
  // my_bt201.Stop();
  // my_bt201.Play();
   my_bt201.Play(3);
  // my_bt201.Pause();
  // my_bt201.Next_Song();
  // my_bt201.Last_Song();
  // my_bt201.Fast_forward();
  // my_bt201.Fast_rewind();
  // my_bt201.Next_folder();
  // my_bt201.Last_folder();
}

void loop()
{
}
