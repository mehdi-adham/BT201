/**
 * @file bt201.h
 * @author Mehdi Adham (mehdi.adham@yahoo.com)
 * @brief
 * @version 1.0
 * @date 2025-01-10
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "Arduino.h"

#ifndef bt201_cpp
#define bt201_cpp

#define BT201_DEBUG

// Common Function's
#define CMD_vol_set "CA"
#define CMD_play_pause "CB"
#define CMD_next_song "CC"
#define CMD_last_song "CD"
#define CMD_vol_up "CE"
#define CMD_vol_down "CF"
#define CMD_baud_rate "CT"
#define CMD_mode "CM"
#define CMD_mute "CU"
#define CMD_DAC_High_Res "CS"
#define CMD_Chip_reset "CZ"
#define CMD_Chip_Recovery "CW"
#define CMD_Power_on_mode "CP"
#define CMD_Automatic_Return_Function "CR"
#define CMD_Mono_Trigger_Play "CJ"
#define CMD_Set_prompt_tone "CN"
#define CMD_Setting_Play_EQ "CQ"
#define CMD_Bluetooth_Switching_Background "CK"
#define CMD_Set_button_function_to_close "C1"
#define CMD_Chip_Actively_Returns_Data "C2"
#define CMD_Retain "C3"
#define CMD_Whether_Bluetooth_Calls_Back "C4"

// Music Function's
#define CMD_Play_Mode "AA"
#define CMD_Specify_physical_sequential_playback "AB"
#define CMD_Specify_playback_mode "AC"
#define CMD_Specified_Play_Device "AD"
#define CMD_Specifies_EQ_to_play "AE"
#define CMD_Specify_speed_playback "AS"
#define CMD_Specify_folder_to_play_circularly "AF"
#define CMD_Specify_folder_file_name_to_play_onc "AJ"
#define CMD_Specify_a_file_to_read_data_read_TXT "AR"
#define CMD_Specify_a_path_to_delete_files "AL"

// Bluetooth function's
#define CMD_Bluetooth_control "BA"
#define CMD_Setting_EDR_Bluetooth_Name "BD"
#define CMD_Setting_EDR_Connection_Password 'BE'
#define CMD_Setting_BLE_Bluetooth_Name "BM"
#define CMD_Setting_BLE_Connection_Password "BN"
#define CMD_Setting_MAC_address_of_EDR "BS"
#define CMD_Simple_Password_Settings "B1"
#define CMD_call_settings "B2"
#define CMD_Bluetooth_Audio_Settings "B3"
#define CMD_Control_opening_and_closing_of_BLE "B4"
#define CMD_Control_EDR_Open_and_Close "B5"
#define CMD_Designated_Number_Dialing "BT"
#define CMD_Specify_servic_UUID "U0"
#define CMD_Specified_signature_1 "U1"
#define CMD_Specified_signature_2 "U2"
#define CMD_Specified_signature_3 "U3"

// Query for Common Function's
#define CMD_Query_volume "QA"
#define CMD_Query_Baud_Rate "QT"
#define CMD_Query_working_mode "QM"
#define CMD_Query_for_prompt_sound "QN"

// Query for Music Function's
#define CMD_Query_Play_file_physical_number_WULIXUHAO_WULIXUHAO_of_current_device "M1"
#define CMD_Query_Total_number_of_files_for_current_devices "M2"
#define CMD_Query_Current_playback_mode "MC"
#define CMD_Query_Current_playback_device "MD"
#define CMD_Query_Long_File_Name_of_Currently_Played_Files "MF"
#define CMD_Query_Current_playing_status "MP"
#define CMD_Query_Total_time_for_current_file_playback "MT"
#define CMD_Query_Time_when_the_current_file_has_been_played "MK"
#define CMD_Query_Current_on_line_equipment "MV"
#define CMD_Query_Data_returned_after_the_current_playback "MO"
#define CMD_Query_Insert_and_unplug_device "MU"

// Query for Bluetooth Function's
#define CMD_Query_Bluetooth_Password "TE"
#define CMD_Query_Bluetooth_Name_EDR "TD"
#define CMD_Query_Bluetooth_Address_EDR "TA"
#define CMD_Query_Bluetooth_Name_BLE "TM"
#define CMD_Query_Bluetooth_Address_BLE "TB"
#define CMD_Query_Bluetooth_whether_to_connect_IOS "TI"
#define CMD_Query_Bluetooth_Current_Status "TS"
#define CMD_Query_Bluetooth_Look_up_number_of_call "TT"
#define CMD_Query_Bluetooth_for_Simple_Password "T1"
#define CMD_Query_Bluetooth_if_there_is_a_call "T2"
#define CMD_Query_Bluetooth_whether_to_bring_A2DP "T3"
#define CMD_Query_Bluetooth_whether_to_bring_BLE "T4"
#define CMD_Query_Bluetooth_EDR "T5"
#define CMD_Query_Service_UUID "T6"
#define CMD_Query_signature_1 "T7"
#define CMD_Query_signature_2 "T8"
#define CMD_Query_signature_3 "T9"

// Return of Error Information on Chip [ER]
// ER+1\r\n The received data frame is not correct
// ER+2\r\n The received command does not exist, that is, the AT + KK string you sent can not be found.
// ER+3\r\n When recording, the device is not online, or other errors
// ER+4\r\n The instructions sent are out of range, or the format of the instructions is incorrect.
// ER+5\r\n Specify the device [TF or U disk], and the device is not online or abnormal
// ER+6\r\n Specify the path of the device [TF or U disk], and the path does not have a return error
// ER+7\r\n undetermined
// ER+8\r\n undetermined
// Real-time feedback will be given to some wrong states within the chip.For details, please refer to the
// table above.

#define chip_receives_successful "OK\r\n"

#define cmd_Chip_reset "AT+CZ\r\n"
#define cmd_Restore_factory "AT+CW\r\n"

// 1. Play volume of specified chip [CA] [CB] [CC] [CD] [CE]
#define cmd_set_volume "AT+CA%02d\r\n"
#define cmd_play_pause "AT+CB\r\n"
#define cmd_Stop "AT+AA00\r\n"
#define cmd_Play "AT+AA01\r\n"
#define cmd_Pause "AT+AA02\r\n"
#define cmd_PP "AT+AA03\r\n"
#define cmd_Fast_forward "AT+AA04\r\n"
#define cmd_Fast_rewind "AT+AA05\r\n"
#define cmd_Next_folder "AT+AA06\r\n"
#define cmd_Last_folder "AT+AA07\r\n"
#define cmd_Delete_currently_playing_file "AT+AA08\r\n"
#define cmd_Play_file_number "AT+AB%d\r\n"

#define cmd_next_song "AT+CC\r\n"
#define cmd_last_song "AT+CD\r\n"
#define cmd_volume_UP "AT+CE\r\n"
#define cmd_volume_down "AT+CF\r\n"

// 2. Set serial baud rate
#define cmd_Baud_Rate_9600 "AT+CT01\r\n"
#define cmd_Baud_Rate_19200 "AT+CT02\r\n"
#define cmd_Baud_Rate_38400 "AT+CT03\r\n"
#define cmd_Baud_Rate_57600 "AT+CT04\r\n"
#define cmd_Baud_Rate_115200 "AT+CT05\r\n"
#define cmd_Baud_Rate_256000 "AT+CT06\r\n"

// 3. Chip mode [CM]
#define cmd_Next_chip_mode "AT+CM00\r\n"
#define cmd_Bluetooth_mode "AT+CM01\r\n"
#define cmd_U_disk_mode "AT+CM02\r\n"
#define cmd_TF_Card_mode "AT+CM03\r\n"
#define cmd_music_mode "AT+CM04\r\n"
#define cmd_Input_AUX_mode "AT+CM05\r\n"
#define cmd_Sound_card "AT+CM07\r\n"
#define cmd_idle_mode "AT+CM08\r\n"

// 4. Setting module silence and DAC closing and opening details [CU] [CS]
#define cmd_un_mute "AT+CU00\r\n"
#define cmd_mute "AT+CU01\r\n"
#define cmd_silent "AT+CU02\r\n"
#define cmd_Turn_off_DAC "AT+CS00\r\n"
#define cmd_Turn_on_DAC "AT+CS01\r\n"

// 5.  Mode for Setting Up Automatic Entry on Chip [CP]
#define cmd_Power_on_Automatically_Enter_Bluetooth "AT+CP00\r\n"
#define cmd_Power_on_enters_a_waiting_state "AT+CP01\r\n"
#define cmd_Power_on_to_make_judgments "AT+CP02\r\n"
// #define Reserve "AT+CP03\r\n"
// #define Reserve "AT+CP04\r\n"

// 6. Setting the function of chip auto-return data to turn off and turn on [CR]
#define cmd_Turn_on_auto_return_function "AT+CR01\r\n"
#define cmd_Turn_off_auto_return_function "AT+CR00\r\n"

// 7. Set TF Card U Disk Play Once Stop or Sequential Loop Play [CJ]
#define cmd_Open_Single_Trigger_Play "AT+CJ01\r\n"
#define cmd_Close_Loop_sequential_playback "AT+CJ00\r\n"

// 8.  Recording function - whether to turn on [RE]
#define cmd_Turn_on_Recording "AT+RE01\r\n"
#define cmd_Turn_off_Recording "AT+RE00\r\n"

// 9. Set whether to turn on the prompt  [CN]
#define cmd_Turn_on_prompt_sound "AT+CN01\r\n"
#define cmd_Turn_off_prompt_sound "AT+CN00\r\n"

// 10.  Setting EQ [CQ] - Audio is not supported for the time being
#define cmd_default_EQ "AT+CQ00\r\n"
#define cmd_ROCK_EQ "AT+CQ01\r\n"
#define cmd_POP_EQ "AT+CQ02\r\n"
#define cmd_CLASSIC_EQ "AT+CQ03\r\n"
#define cmd_JAZZ_EQ "AT+CQ04\r\n"
#define cmd_COUNTRY_EQ "AT+CQ05\r\n"

// 11. Set Bluetooth Auto Switch to Background
#define cmd_Turn_off_automatically_switch_to_Bluetooth "AT+CK00\r\n"
#define cmd_Turn_on_automatically_switch_to_Bluetooth "AT+CK01\r\n"

// 12. Set whether Bluetooth opens the background [CG]
#define cmd_Close_Bluetooth_background "AT+CG00\r\n"
#define cmd_Open_Bluetooth_background "AT+CG01\r\n"

// 13. Set whether the key function is turned off and turned on [C1] [C2] [C3] [C4]
#define cmd_Turn_off_AD_button "AT+C100\r\n"
#define cmd_Turn_on_AD_button "AT+C101\r\n"
#define cmd_Turn_off_return_info "AT+C200\r\n"
#define cmd_Turn_on_return_info "AT+C201\r\n"
// #define cmd_Retain "AT+C300\r\n"
// #define cmd_Retain "AT+C301\r\n"
#define cmd_turn_off_last_pair_of_device "AT+C400\r\n"
#define cmd_turn_on_last_pair_of_device "AT+C401\r\n"

// page 23 ...
// ...
//

// File Folder Loop Play in in the specified Path [AF]
#define cmd_Play_folder_loop "AT+AF/%s/%s\r\n" // *???

// Play a file in the specified path once [AJ]
#define cmd_Play_file_in_folder_once "AT+AJ/%s/%s\r\n"


// Setting Bluetooth
#define cmd_BLctrl_Call_back_phone_call "AT+BA00\r\n"
#define cmd_BLctrl_Disconnect "AT+BA01\r\n" // -> Disconnect This only works after the connection  is successfull
#define cmd_BLctrl_Refuse_to_accept "AT+BA02\r\n"
#define cmd_BLctrl_Hang_up "AT+BA03\r\n"
#define cmd_BLctrl_Answer_phone "AT+BA04\r\n" // -> If there is a telephone coming in at present, issue this command,
                                              // then answer it.In the process of receiving, the relay will hang up.
#define cmd_BLctrl_Scanning_Device "AT+BA05\r\n"
#define cmd_EDR_Name "AT+BD%s\r\n" // Bluetooth audio and SPP
#define cmd_EDR_Pass "AT+BE%s\r\n"
#define cmd_BLE_Name "AT+BM%s\r\n"
#define cmd_BLE_Pass "AT+BN%s\r\n"
#define cmd_Bluetooth_MAC "AT+BS%s\r\n"
#define cmd_close_Bluetooth_Pass "AT+B100\r\n"
#define cmd_open_Bluetooth_Pass "AT+B101\r\n"
#define cmd_close_Bluetooth_call "AT+B200\r\n"
#define cmd_open_Bluetooth_call "AT+B201\r\n"
#define cmd_turn_off_Bluetooth_audio "AT+B300\r\n"
#define cmd_turn_on_Bluetooth_audio "AT+B301\r\n"

#define cmd_turn_off_BLE "AT+B400\r\n" // -> The default is 0x01.
#define cmd_turn_on_BLE "AT+B401\r\n"
#define cmd_turn_off_EDR "AT+B500\r\n" // -> The default is 0x01.
#define cmd_turn_on_EDR "AT+B501\r\n"
#define cmd_Number_Dialing "AT+BT%s\r\n"
#define cmd_MAC_Address_for_EDR "AT+BS%s\r\n"

typedef enum
{
    baudRate_9600 = 1,
    baudRate_19200,
    baudRate_38400,
    baudRate_57600,
    baudRate_115200,
    baudRate_256000
} Baud_Rate_Select;

typedef enum
{
    Next_chip_mode = 0,
    Bluetooth_mode,
    U_disk_mode,
    TF_Card_mode,
    music_mode,
    Input_AUX_mode,
    Sound_card = 7,
    idle_mode
} Chip_Mode_Select;

typedef enum
{
    Call_back_phon_call = 0,
    Disconnect, // -> Disconnect This only works after the connection  is successfull
    Refuse_to_accept,
    Hang_up,
    Answer_phone, // -> If there is a telephone coming in at present, issue this command,
                  // then answer it.In the process of receiving, the relay will hang up.
    Scanning_Device
} Bluetooth_Audio_Control_cmd_Select;

typedef enum
{
    Automatically_Enter_Bluetooth = 0, // -> Power-on Automatically Enter Bluetooth.
    Enters_waiting_state,              // -> Power-on enters a waiting state, requiring users to send mode instructions.
    to_make_judgments                  // -> Power on to make judgments, play devices with devices, and enter Bluetooth without devices.
} Power_on_Mode_Select;

typedef enum
{
    Default = 0,
    ROCK,
    POP,
    CLASSIC,
    JAZZ,
    COUNTRY
} EQ_Select;

typedef enum{
    Loop_play =0,
    Once_play
} Playback_Mode_Select;

class BT201
{
    void wait_for_timeOut(int timeOut);
    String wait_for_get_response(int timeOut);
    bool Send_CMD(String CMD, int param);

public:
    HardwareSerial *BT201_Serial;
    int baud_rate = 115200;
    String response = "";
    int timeOut_for_response = 1000; // ms
    uint8_t max_Resend = 3;

    void begin(HardwareSerial &Serial, bool doReset = false);
    String get_response();
    bool volume_set(uint8_t vol);
    bool PlayPause();
    bool Stop();
    bool Play();
    bool Play(int file_number);
    bool Pause();
    bool PP();
    bool Fast_forward();
    bool Fast_rewind();
    bool Next_folder();
    bool Last_folder();
    bool Play_folder(String folder_name, String filter_fileType = "*.????");
    bool Play_file_in_folder(String file_name, String folder_name);
    bool Delete_currently_playing_file();
    bool Next_Song();
    bool Last_Song();
    bool Volume_UP();
    bool Volume_Down();
    bool Set_Baud_Rate(Baud_Rate_Select Baud_Rate = baudRate_115200);
    bool Chip_Reset();
    bool Chip_Mode(Chip_Mode_Select Chip_Mode);
    bool Mute(bool Mute = true);
    bool Silent();
    bool Turn_off_DAC(bool in = true);
    bool Restore_factory();
    bool Set_Power_on_Mode(Power_on_Mode_Select Power_on_Mode = Enters_waiting_state);
    bool Turn_on_auto_return_function(bool in = true);
    bool Turn_on_Loop_playback(bool in = true);
    bool Turn_on_recording_function(bool in = true);
    bool Turn_on_prompt_tone(bool in = true);
    bool Set_EQ(EQ_Select EQ = Default);
    bool Turn_on_Bluetooth_Auto_Switch_to_Background(bool in = true);
    bool Turn_off_AD_button(bool in = true);
    bool Turn_off_return_information(bool in = true);
    bool Turn_off_last_pair_of_device(bool in = true);

    bool open_Bluetooth_Pass(bool in = true);
    bool open_Bluetooth_call(bool in = true);
    bool Set_Name_for_EDR_Bluetooth(String Name);
    bool Set_Pass_for_EDR_Bluetooth(String Pass);
    bool Set_Name_for_BLE_Bluetooth(String Name);
    bool Set_Pass_for_BLE_Bluetooth(String Pass);
    bool Call_back_phone_call();
    bool Disconnect();
    bool Refuse_to_accept();
    bool Hang_up();
    bool Answer_phone();
    bool Scanning_Device();
    bool turn_off_BLE(bool in = true);
    bool turn_off_EDR(bool in = true);
    bool telephone_number_to_call(String telephone_number);
    bool Set_MAC_Address_for_EDR(String MAC_Address);
};

#endif
