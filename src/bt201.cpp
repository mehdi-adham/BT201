/**
 * @file bt201.cpp
 * @author Mehdi Adham (mehdi.adham@yahoo.com)
 * @brief 
 * @version 1.0
 * @date 2025-01-10
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "bt201.h"

/**
 * @brief begin BT201 Module
 * 
 * @param Serial 
 * @param doReset 
 */
void BT201::begin(HardwareSerial &Serial, bool doReset)
{
  BT201_Serial = &Serial;
  BT201_Serial->begin(baud_rate);
}

/**
 * @brief wait for timeOut
 * 
 * @param timeOut 
 */
void BT201::wait_for_timeOut(int timeOut)
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

/**
 * @brief wait for get response
 * 
 * @param timeOut 
 * @return String 
 */
String BT201::wait_for_get_response(int timeOut)
{
  String data = "";
  int duration;
  unsigned long Curr_time;
  unsigned long Prev_time = millis();

  while (true)
  {
    if (BT201_Serial->available())
    {
      char val = (char)BT201_Serial->read();
      data += val;
      if (val == '\n')
      {
        return data;
      }
    }

    Curr_time = millis();

    if (Curr_time < Prev_time)
      duration = Curr_time + (UINT_MAX - Prev_time);
    else
      duration = Curr_time - Prev_time;

    if (duration >= timeOut)
    {
      return data;
    }
  }
}

/**
 * @brief get response
 * 
 * @return String 
 */
String BT201::get_response()
{
  response = "";
  response = wait_for_get_response(timeOut_for_response);
#ifdef BT201_DEBUG
  Serial.printf("response:[%s]", response);
#endif
  return response;
}

/**
 * @brief  Control Instruction Format: AT+<CMD>[<param>]rn 
 *  All characters, not hexadecimal numbers Data feedback format: <IND>[<param>]rn
 * 
 * @param CMD 
 * @param param 
 * @return true 
 * @return false 
 */
bool BT201::Send_CMD(String CMD, int param)
{
  BT201_Serial->printf("AT+%S%02d\r\n", CMD, param);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief Set the volume
 * 
 * @param vol 
 * @return true 
 * @return false 
 */
bool BT201::volume_set(uint8_t vol)
{
  if (vol < 31)
    BT201_Serial->printf(cmd_set_volume, vol);
  else
    return false;

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief Play Pause
 * 
 * @return true 
 * @return false 
 */
bool BT201::PlayPause()
{
  BT201_Serial->print(cmd_play_pause);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief Next Song
 * 
 * @return true 
 * @return false 
 */
bool BT201::Next_Song()
{
  BT201_Serial->print(cmd_next_song);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief Last Song
 * 
 * @return true 
 * @return false 
 */
bool BT201::Last_Song()
{
  BT201_Serial->print(cmd_last_song);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief Volume UP
 * 
 * @return true 
 * @return false 
 */
bool BT201::Volume_UP()
{
  BT201_Serial->print(cmd_volume_UP);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief Volume Down
 * 
 * @return true 
 * @return false 
 */
bool BT201::Volume_Down()
{
  BT201_Serial->print(cmd_volume_down);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief Set Baud Rate
 * 
 * @param Baud_Rate 
 * @return true 
 * @return false 
 */
bool BT201::Set_Baud_Rate(Baud_Rate_Select Baud_Rate)
{

  String cmd = "";
  int temp_baud_rate;

  switch (Baud_Rate)
  {
  case baudRate_9600:
    cmd = cmd_Baud_Rate_9600;
    temp_baud_rate = 9600;
    break;
  case baudRate_19200:
    cmd = cmd_Baud_Rate_19200;
    temp_baud_rate = 19200;
    break;
  case baudRate_38400:
    cmd = cmd_Baud_Rate_38400;
    temp_baud_rate = 38400;
    break;
  case baudRate_57600:
    cmd = cmd_Baud_Rate_57600;
    temp_baud_rate = 57600;
    break;
  case baudRate_115200:
    cmd = cmd_Baud_Rate_115200;
    temp_baud_rate = 115200;
    break;
  case baudRate_256000:
    cmd = cmd_Baud_Rate_256000;
    temp_baud_rate = 256000;
    break;
  default:
    break;
  }

  BT201_Serial->print(cmd);

  if (get_response() == chip_receives_successful)
  {
    delay(1000);

    // reset chip or restart
    while (max_Resend--)
    {
      if (Chip_Reset() == true)
      {
        // reinit serial
        baud_rate = temp_baud_rate;
        BT201_Serial->begin(baud_rate);
        return true;
      }
    }

    return false;
  }

  else
    return false;
}

/**
 * @brief Chip reset
 * 
 * @return true 
 * @return false 
 */
bool BT201::Chip_Reset()
{
  BT201_Serial->print(Chip_reset);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief Chip Mode
 * 
 * @param Chip_Mode 
 * @return true 
 * @return false 
 */
bool BT201::Chip_Mode(Chip_Mode_Select Chip_Mode)
{
  String cmd = "";

  switch (Chip_Mode)
  {
  case Next_chip_mode:
    cmd = cmd_Next_chip_mode;
    break;
  case Bluetooth_mode:
    cmd = cmd_Bluetooth_mode;
    break;
  case U_disk_mode:
    cmd = cmd_U_disk_mode;
    break;
  case TF_Card_mode:
    cmd = cmd_TF_Card_mode;
    break;
  case music_mode:
    cmd = cmd_music_mode;
    break;
  case Input_AUX_mode:
    cmd = cmd_Input_AUX_mode;
    break;
  case Sound_card:
    cmd = cmd_Sound_card;
    break;
  case idle_mode:
    cmd = cmd_idle_mode;
    break;

  default:
    break;
  }

  BT201_Serial->print(cmd);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief Mute / Un_Mute
 * 
 * @param Mute 
 * @return true 
 * @return false 
 */
bool BT201::Mute(bool Mute)
{
  BT201_Serial->print(Mute == true ? cmd_mute : cmd_un_mute);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}