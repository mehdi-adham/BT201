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
 * @brief Stop it
 *
 * @return true
 * @return false
 */
bool BT201::Stop()
{
  BT201_Serial->print(cmd_Stop);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief Play [pause to start playing, and vice versa]
 *
 * @return true
 * @return false
 */
bool BT201::Play()
{
  BT201_Serial->print(cmd_Play);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief file number (1 - 65535)
 *
 * @param file_number
 * @return true
 * @return false
 */
bool BT201::Play(int file_number)
{
  if (file_number <= 0xffff)
  {
    BT201_Serial->printf(cmd_Play_file_number, file_number);

    if (get_response() == chip_receives_successful)
      return true;
    else
      return false;
  }
  else
    return false;
}

/**
 * @brief Pause [when playback starts pausing, otherwise invalid]
 *
 * @return true
 * @return false
 */
bool BT201::Pause()
{
  BT201_Serial->print(cmd_Pause);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief Play, pause [two state loop switch]
 *
 * @return true
 * @return false
 */
bool BT201::PP()
{
  BT201_Serial->print(cmd_PP);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool BT201::Fast_forward()
{
  BT201_Serial->print(cmd_Fast_forward);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool BT201::Fast_rewind()
{
  BT201_Serial->print(cmd_Fast_rewind);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool BT201::Next_folder()
{
  BT201_Serial->print(cmd_Next_folder);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool BT201::Last_folder()
{
  BT201_Serial->print(cmd_Last_folder);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool BT201::Delete_currently_playing_file()
{
  BT201_Serial->print(cmd_Delete_currently_playing_file);

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

/**
 * @brief true is, turn-off DAC, turn-on DAC is false
 * Turn off DAC, when DAC output is high resistance.
 * @return true
 * @return false
 */
bool BT201::Turn_off_DAC(bool in)
{
  BT201_Serial->print(in == true ? cmd_Turn_off_DAC : cmd_Turn_on_DAC);

  if (get_response() == chip_receives_successful)
    return true;
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
  BT201_Serial->print(cmd_Chip_reset);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief
 *
 * @param in
 * @return true
 * @return false
 */
bool BT201::Silent()
{
  BT201_Serial->print(cmd_silent);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief Restore factory settings and clear all previously remembered parameters.
 *
 * @return true
 * @return false
 */
bool BT201::Restore_factory()
{
  BT201_Serial->print(cmd_Restore_factory);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief The purpose of adding this instruction is to facilitate users.
 * Some customers need to use Bluetooth directly, while others need equipment to enter the device.
 *
 * @param Power_on_Mode
 * @return true
 * @return false
 */
bool BT201::Set_Power_on_Mode(Power_on_Mode_Select Power_on_Mode)
{
  String cmd = "";

  switch (Power_on_Mode)
  {
  case Automatically_Enter_Bluetooth:
    cmd = cmd_Power_on_Automatically_Enter_Bluetooth;
    break;

  case Enters_waiting_state:
    cmd = cmd_Power_on_Automatically_Enter_Bluetooth;
    break;

  case to_make_judgments:
    cmd = cmd_Power_on_Automatically_Enter_Bluetooth;
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
 * @brief 1.If you don&apos;t want to return a message every half a second in Bluetooth,
 * you can turn it off with this command.
 * 2.You don&apos;t want a TF card or a U disk, and you can turn it off by returning messages every second.
 *
 * @param in
 * @return true
 * @return false
 */
bool BT201::Turn_on_auto_return_function(bool in)
{
  BT201_Serial->print(in == true ? cmd_Turn_on_auto_return_function : cmd_Turn_off_auto_return_function);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief For MUSIC playback, we present two application.
 *
 * @param in
 * @return true
 * @return false
 */
bool BT201::Turn_on_Loop_playback(bool in)
{
  BT201_Serial->print(in == true ? cmd_Close_Loop_sequential_playback : cmd_Open_Single_Trigger_Play);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool BT201::Turn_on_recording_function(bool in)
{
  BT201_Serial->print(in == true ? cmd_Turn_on_Recording : cmd_Turn_off_Recording);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief
 *
 * @param in
 * @return true
 * @return false
 */
bool BT201::Turn_on_prompt_tone(bool in)
{
  BT201_Serial->print(in == true ? cmd_Turn_on_prompt_sound : cmd_Turn_off_prompt_sound);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief
 *
 * @param EQ
 * @return true
 * @return false
 */
bool BT201::Set_EQ(EQ_Select EQ)
{
  String cmd = "";

  switch (EQ)
  {
  case Default:
    cmd = cmd_default_EQ;
    break;
  case ROCK:
    cmd = cmd_ROCK_EQ;
    break;
  case POP:
    cmd = cmd_POP_EQ;
    break;
  case CLASSIC:
    cmd = cmd_CLASSIC_EQ;
    break;
  case JAZZ:
    cmd = cmd_JAZZ_EQ;
    break;
  case COUNTRY:
    cmd = cmd_COUNTRY_EQ;
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
 * @brief true - Bluetooth is set to power on and not return.
 * false - Bluetooth is set to call back to the last pair of devices,
 * the main contention for audio default is this
 *
 * @param in
 * @return true
 * @return false
 */
bool BT201::Turn_off_last_pair_of_device(bool in)
{
  BT201_Serial->print(in == true ? cmd_turn_off_last_pair_of_device : cmd_turn_on_last_pair_of_device);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief if Turn off - do not automatically switch to Bluetooth background.
 * if Turn on - currently playing TF card, if Bluetooth has audio or telephone, then
 * automatically switch to Bluetooth.
 *
 * @param in
 * @return true
 * @return false
 */
bool BT201::Turn_on_Bluetooth_Auto_Switch_to_Background(bool in)
{
  BT201_Serial->print(in == true ? cmd_Turn_on_automatically_switch_to_Bluetooth : cmd_Turn_off_automatically_switch_to_Bluetooth);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief Turn-off the AD button - 14 feet of the chip can be pulled up without 22K.
 * Turn on the AD button - the 14 of the chip must be pulled up 22K.
 *
 * @param in
 * @return true
 * @return false
 */
bool BT201::Turn_off_AD_button(bool in)
{
  BT201_Serial->print(in == true ? cmd_Turn_off_AD_button : cmd_Turn_on_AD_button);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief When the chip is turned on, it will actively return information when the chip is
 * powered on or when the state is switched on. The default is this.
 * When the chip is turned off, the active return information will be returned when
 * the chip is powered on or when the state is switched on. This is turned off.
 *
 * @param in
 * @return true
 * @return false
 */
bool BT201::Turn_off_return_information(bool in)
{
  BT201_Serial->print(in == true ? cmd_Turn_off_return_info : cmd_Turn_on_return_info);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief true is open, close is false.
 * This 00 stands for 0x00, closing the paired password, that is,
 * the next connection doesnot require a password to connect directly.
 *
 * @param in
 * @return Bool
 */
bool BT201::open_Bluetooth_Pass(bool in)
{
  BT201_Serial->print(in == true ? cmd_open_Bluetooth_Pass : cmd_close_Bluetooth_Pass);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief true is open, close is false
 *
 * @param in
 * @return true
 * @return false
 */
bool BT201::open_Bluetooth_call(bool in)
{

  BT201_Serial->print(in == true ? cmd_open_Bluetooth_call : cmd_close_Bluetooth_call);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief Here EDR refers to Bluetooth audio and SPP.
 *
 * @param Name
 * @return true
 * @return false
 */
bool BT201::Set_Name_for_EDR_Bluetooth(String Name)
{

  BT201_Serial->printf(cmd_EDR_Name, Name);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief
 *
 * @param Pass
 * @return true
 * @return false
 */
bool BT201::Set_Pass_for_EDR_Bluetooth(String Pass)
{

  BT201_Serial->printf(cmd_EDR_Pass, Pass);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief
 *
 * @param Name
 * @return true
 * @return false
 */
bool BT201::Set_Name_for_BLE_Bluetooth(String Name)
{

  BT201_Serial->printf(cmd_BLE_Name, Name);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief
 *
 * @param Pass
 * @return true
 * @return false
 */
bool BT201::Set_Pass_for_BLE_Bluetooth(String Pass)
{

  BT201_Serial->printf(cmd_BLE_Pass, Pass);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool BT201::Call_back_phone_call()
{
  BT201_Serial->print(cmd_BLctrl_Call_back_phone_call);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool BT201::Disconnect()
{
  BT201_Serial->print(cmd_BLctrl_Disconnect);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool BT201::Refuse_to_accept()
{
  BT201_Serial->print(cmd_BLctrl_Refuse_to_accept);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool BT201::Hang_up()
{
  BT201_Serial->print(cmd_BLctrl_Hang_up);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool BT201::Answer_phone()
{
  BT201_Serial->print(cmd_BLctrl_Answer_phone);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool BT201::Scanning_Device()
{
  BT201_Serial->print(cmd_BLctrl_Scanning_Device);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief true is turn-off, turn-on is false.
 * The function of opening and closing BLE here is convenient for some customers
 * who only need audio and do not need data transmissn.
 * When BLE is off, you can't search for the name of BLE, and the chip won't
 * broadcast to the outside world.The next power-on after setting is valid.
 * @param in
 * @return true
 * @return false
 */
bool BT201::turn_off_BLE(bool in)
{
  BT201_Serial->print(in == true ? cmd_turn_off_BLE : cmd_turn_on_BLE);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief true is turn-off, turn-on is false.
 * If you turn off EDR, then your mobile phone will only search for the name of BLE,
 * and only do data communication.The same next power-on is effective.
 * So that the chip does not have Bluetooth audio playback function,
 * and your mobile phone can not search the name of Bluetooth audio.
 * @param in
 * @return true
 * @return false
 */
bool BT201::turn_off_EDR(bool in)
{
  BT201_Serial->print(in == true ? cmd_turn_off_EDR : cmd_turn_on_EDR);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief
 *
 * @param telephone_number
 * @return true
 * @return false
 */
bool BT201::telephone_number_to_call(String telephone_number)
{
  BT201_Serial->printf(cmd_Number_Dialing, telephone_number);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/**
 * @brief Set MAC Address for EDR.
 * This is a personalized function, which is not needed by ordinary customers. You can look carefully when you need it.
 * Ex1: 123456781234 => MAC Address is: 0x120 X34 0x56 0x78 0x1
 * Ex2: BSABCDEF123456 => MAC Address is: 0xAB 0xCD 0xEF 0x120 X34 0x56
 *
 * @param MAC_Address
 * @return true
 * @return false
 */
bool BT201::Set_MAC_Address_for_EDR(String MAC_Address)
{
  BT201_Serial->printf(cmd_MAC_Address_for_EDR, MAC_Address);

  if (get_response() == chip_receives_successful)
    return true;
  else
    return false;
}

/* Data Returned Process page 14 */
