#ifndef SYSTEM_CONFIG
#define SYSTEM_CONFIG


#ifndef SERIAL_DEVICE_NAME_TR_MODEULE
#define SERIAL_DEVICE_NAME_TR_MODEULE "ttyUSB0"
#endif

#ifndef DB_PATH
#define DB_PATH "RadioManager.db"
#endif

#ifndef KEY_CODE_ENTER
#define KEY_CODE_ENTER 16777220
#endif

#ifndef KEY_CODE_ESC
#define KEY_CODE_ESC 16777216
#endif

#ifndef KEY_CODE_UP
#define KEY_CODE_UP 16777235
#endif

#ifndef KEY_CODE_DOWN
#define KEY_CODE_DOWN 16777237
#endif

#ifndef KEY_CODE_LEFT
#define KEY_CODE_LEFT 16777234
#endif

#ifndef KEY_CODE_RIGHT
#define KEY_CODE_RIGHT 16777236
#endif

#ifndef KEY_CODE_1
#define KEY_CODE_1 49
#endif

#ifndef KEY_CODE_2
#define KEY_CODE_2 50
#endif

#ifndef KEY_CODE_3
#define KEY_CODE_3 51
#endif

#ifndef KEY_CODE_4
#define KEY_CODE_4 52
#endif

#ifndef KEY_CODE_5
#define KEY_CODE_5 53
#endif

#ifndef KEY_CODE_6
#define KEY_CODE_6 54
#endif

#ifndef KEY_CODE_7
#define KEY_CODE_7 55
#endif

#ifndef KEY_CODE_8
#define KEY_CODE_8 56
#endif

#ifndef KEY_CODE_9
#define KEY_CODE_9 57
#endif

#ifndef KEY_CODE_0
#define KEY_CODE_0 48
#endif


extern bool global_b_serial_is_open;
extern bool global_b_tr_data_ctrl_interface_enabled;
extern int global_i_page_index;
extern bool global_b_channel_has_been_tune;



extern int global_i_current_channel_index;


#endif // SYSTEM_CONFIG

