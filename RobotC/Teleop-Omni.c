#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     sensor_IR,      sensorI2CCustomFastSkipStates9V)
#pragma config(Sensor, S4,     sensor_gyro,    sensorI2CCustomFastSkipStates9V)
#pragma config(Motor,  mtr_S1_C1_1,     motor_FR,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motor_FL,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motor_BL,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     motor_BR,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motor_sweeper, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motor_lift,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     motor_flag,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motorK,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo_funnel_L,       tServoStandard)
#pragma config(Servo,  srvo_S2_C1_6,    servo_funnel_R,       tServoStandard)
#pragma config(Servo,  srvo_S2_C2_1,    servo_dump,           tServoStandard)
#pragma config(Servo,  srvo_S2_C2_2,    servo_flag,           tServoStandard)
#pragma config(Servo,  srvo_S2_C2_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S2_C2_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S2_C2_6,    servo12,              tServoNone)

#include "includes.h"



task main()
{
	// For the stweet streeper motor; controlled by BUTTON_A.
	// Currently not reversible--should it be?
	bool isSweeping = false;
	//float orientation = 0.0;
	float translation_x = 0.0;
	float translation_y = 0.0;
	float rotation = 0.0;
	float power_FR = 0.0;
	float power_FL = 0.0;
	float power_BL = 0.0;
	float power_BR = 0.0;
	float power_cap = 0.0;
	bool doNormalizePower = false;
	float power_lift = 0.0;
	bool isRaisingFlag = false;
	//HTGYROstartCal(sensor_gyro);
	Joystick_WaitForStart();

	Time_ClearTimer(T1);
	while (true)
	{
		//orientation += Time_GetTime(T1)*HTGYROreadRot(sensor_gyro);
		//Time_ClearTimer(T1);

		Joystick_UpdateData();
		translation_x = Math_Normalize(Math_TrimDeadband(Joystick_Joystick(JOYSTICK_R, AXIS_X), 10), 128, 100);
		translation_y = Math_Normalize(Math_TrimDeadband(Joystick_Joystick(JOYSTICK_R, AXIS_Y), 10), 128, 100);
		rotation = Math_Normalize(Math_TrimDeadband(Joystick_Joystick(JOYSTICK_L, AXIS_X), 10), 128, 100);

		//Math_RotateVector(translation_x, translation_y, -orientation);

		power_FR = translation_y-translation_x-rotation;
		power_FL = translation_y+translation_x+rotation;
		power_BL = translation_y-translation_x+rotation;
		power_BR = translation_y+translation_x-rotation;

		if (power_FR>g_FullPower) {
			power_cap = power_FR;
			doNormalizePower = true;
		}
		if ((power_FL>g_FullPower)&&(power_FL>power_cap)) {
			power_cap = power_FL;
			doNormalizePower = true;
		}
		if ((power_BL>g_FullPower)&&(power_BL>power_cap)) {
			power_cap = power_BL;
			doNormalizePower = true;
		}
		if ((power_BR>g_FullPower)&&(power_BR>power_cap)) {
			power_cap = power_BR;
			doNormalizePower = true;
		}
		if (doNormalizePower==true) {
			Math_Normalize(power_FR, power_cap, g_FullPower);
			Math_Normalize(power_FR, power_cap, g_FullPower);
			Math_Normalize(power_FR, power_cap, g_FullPower);
			Math_Normalize(power_FR, power_cap, g_FullPower);
			doNormalizePower = false;
		}

		if (Joystick_ButtonReleased(BUTTON_A)==true) {
			isSweeping = (!isSweeping);
		}

		power_lift = Math_Normalize(Math_TrimDeadband(Joystick_Joystick(JOYSTICK_R, AXIS_Y, CONTROLLER_2), 10), 128, 100);
		if (Joystick_Direction(DIRECTION_NONE)==false) {
			power_lift = 0;
			if (Joystick_Direction(DIRECTION_F)==true) {
				power_lift = 100;
			} else if (Joystick_Direction(DIRECTION_B)==true) {
				power_lift = -100;
			}
		}

		if (Joystick_Button(BUTTON_Y)==true) {
			isRaisingFlag = true;
		} else {
			isRaisingFlag = false;
		}

		Motor_SetPower(power_FR, motor_FR);
		Motor_SetPower(power_FL, motor_FL);
		Motor_SetPower(power_BL, motor_BL);
		Motor_SetPower(power_BR, motor_BR);
		if (isSweeping==true) {
			Motor_SetPower(100, motor_sweeper);
		} else {
			Motor_SetPower(0, motor_sweeper);
		}
		Motor_SetPower(power_lift, motor_lift);
		if (isRaisingFlag==true) {
			Motor_SetPower(100, motor_flag);
		} else {
			Motor_SetPower(0, motor_flag);
		}
	}
}
