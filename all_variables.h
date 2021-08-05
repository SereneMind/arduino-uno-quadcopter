
/*-------------------------------------pid constants---------------------------------------------------*/
float p, i, d;
float pid_p_gain_roll = 2.0;              //Gain setting for the roll P-controller (1.3)0.625//2.00
float pid_i_gain_roll = 0.0010;              //Gain setting for the roll I-controller (0.3)0.00001//0.0015
float pid_d_gain_roll = 35;               //Gain setting for the roll D-controller (11-15)10//30//35
float pid_max_roll = 400;                    //Maximum output of the PID-controller (+/-)

float pid_p_gain_pitch = pid_p_gain_roll;  //Gain setting for the pitch P-controller.(0.605)
float pid_i_gain_pitch = 0.0001;// 0.0005; //Gain setting for the pitch I-controller.(0.00002)//0.0005
float pid_d_gain_pitch = pid_d_gain_roll;  //Gain setting for the pitch D-controller.(13)
float pid_max_pitch = pid_max_roll;          //Maximum output of the PID-controller (+/-)

float pid_p_gain_yaw = 00;                //Gain setting for the pitch P-controller. //4.0
float pid_i_gain_yaw = 0.0;               //Gain setting for the pitch I-controller. //0.02
float pid_d_gain_yaw = 0.0;                //Gain setting for the pitch D-controller.
float pid_max_yaw = 400;                     //Maximum output of the PID-controller (+/-)

float pid_error_temp_roll, pid_error_temp_pitch, pid_error_temp_yaw;

float pid_i_mem_roll, pid_roll_setpoint, gyro_roll_input, pid_output_roll, pid_last_roll_d_error;
float pid_i_mem_pitch, pid_pitch_setpoint, gyro_pitch_input, pid_output_pitch, pid_last_pitch_d_error;;
float pid_i_mem_yaw, pid_yaw_setpoint, gyro_yaw_input, pid_output_yaw, pid_last_yaw_d_error;


/*---------------------------------------Acc data --------------------------------------------------*/
#define DEVICE 0x53 // Device address as specified in data sheet 
byte _buff[6];

#define OFSTX  0x1E         //X_CALIB
#define OFSTY  0x1F         //Y_CALIB
#define OFSTZ  0x20         //Z_CALIB

char POWER_CTL = 0x2D;  //Power Control Register
char DATA_FORMAT = 0x31;//setting {(d7)SELF_TEST,(d6)SPI,(d5)INT_INVERT,(d4)0,(d3)FULL_RES,(d2)Justify,(d0,d1)Range} we need to change only range
char DATAX0 = 0x32; //X-Axis Data 0
char DATAX1 = 0x33; //X-Axis Data 1
char DATAY0 = 0x34; //Y-Axis Data 0
char DATAY1 = 0x35; //Y-Axis Data 1
char DATAZ0 = 0x36; //Z-Axis Data 0
char DATAZ1 = 0x37; //Z-Axis Data 1

double accelero_roll_cal;//calibration offsets
double accelero_pitch_cal;//calibration offsets
double accelero_yaw_cal;//calibration offsets

double xacc ;//raw value
double yacc ;//raw value
double zacc;//raw value

double vect_x;//gravity vector
double vect_y;//gravity vector
double vect_z;//gravity vector

double fXg, vect_x_f;
double fYg, vect_y_f;
double fZg, vect_z_f;

double accPitch;//angle in reference to z axis
double accRoll;//angle in reference to z axis

float alpha;//constant used in low pass filter
float  lpf_alpha;

double lastPitch;
double lastRoll;

/*------------------------------------Gyro Data---------------------------------------------*/
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24

int L3G4200D_Address = 105; //I2C address of the L3G4200D

double gyroRawx;
double gyroRawy;
double gyroRawz;

double gyroVectx, gyroVectx_f, gyroVectx_previous ;
double gyroVecty, gyroVecty_f, gyroVecty_previous  ;
double gyroVectz, gyroVectz_f, gyroVectz_previous  ;

double gyro_roll_cal  ;
double gyro_pitch_cal ;
double gyro_yaw_cal ;

double hpx, hpy, hpz; //highpass filter output
float hpf_alpha;

unsigned long start_time, loop_time;
float graph_time;
float Comp_pitch, Comp_roll, Comp_pitch1, Comp_roll1;
double errorPitch, errorRoll;
/*-------------------------------Mag Data-----------------------------------------------*/
int Mag_address = 0x1E;
double xMagRaw, yMagRaw, zMagRaw;//raw values of mag
double cos_roll, sin_roll, cos_pitch, sin_pitch;
double xMagF, yMagF, zMagF;
double xMagVect, yMagVect, zMagVect;
double MAG_X, MAG_Y;
double magHeading, headingDiff;
double yaw;
float alpha_m;
/*---------------------------mag calibration--------------------------------*/

#define compass_XY_excitation 1160 // The magnetic field excitation in X and Y direction during Self Test (Calibration)
#define compass_Z_excitation 1080  // The magnetic field excitation in Z direction during Self Test (Calibration)

float compass_gain_fact = 0.92; //Setting the gain
double compass_x_scalled, compass_y_scalled, compass_z_scalled;

// These values will be set from the calibration
double compass_x_gainError = 1.79, compass_y_gainError = 1.04, compass_z_gainError = 0.96;
double compass_x_offset = -341.40, compass_y_offset = -2.87, compass_z_offset = 106.85;
/*
  x_gain_offset = 1.79
  y_gain_offset = 1.04
  z_gain_offset = 0.96

  Offset x  = -341.40 mG
  Offset y  = -2.87 mG
  Offset z  = 106.85 mG
*/

/*----------------------------------ESC Data-------------------------------------------------*/
unsigned long timer_channel_1, timer_channel_2, timer_channel_3, timer_channel_4, esc_timer, esc_loop_timer;
double esc_1, esc_2, esc_3, esc_4;

float throttle;
float timeStep;
int start = 0, restart_no = 0;
unsigned long restart_time = 0, restart_time1 = 0;

int incomingByte;
/*------------------------------Receiver Data-------------------------------------------------*/
float receiver_input_channel_1, last_channel_1;
float receiver_input_channel_2, last_channel_2;
float receiver_input_channel_3, last_channel_3;
float receiver_input_channel_4, last_channel_4;

unsigned long current_time, timer_1, timer_2, timer_3, timer_4;
float battery_voltage;
/*-----------------------------------USS------------------------------------------------------*/
unsigned long uss_current_time, uss_last_channel, uss_timer;
float altitude, duration;

/*-----------------------------------Misc------------------------------------------------------*/
bool i_am_up, start_descend;
int throttle_ctrl;
unsigned long count = 0;
