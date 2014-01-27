#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  HTMotor,  none,     none)
#pragma config(Sensor, S3,     sensor_IR,      sensorI2CCustomFastSkipStates9V)
#pragma config(Sensor, S4,     sensor_protoboard, sensorI2CCustom9V)
#pragma config(Motor,  motorA,          motor_assist_L, tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          motor_assist_R, tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motor_flag,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motor_sweeper, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     motor_climb,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motor_lift,    tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     motor_BL,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     motor_FL,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S2_C2_1,     motor_BR,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S2_C2_2,     motor_FR,      tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C2_1,    servo_BL,             tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    servo_FL,             tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    servo_flip_L,         tServoStandard)
#pragma config(Servo,  srvo_S1_C2_4,    servo_dump,           tServoStandard)
#pragma config(Servo,  srvo_S1_C2_5,    servo_climb_L,        tServoStandard)
#pragma config(Servo,  srvo_S1_C2_6,    servo_auton,          tServoStandard)
#pragma config(Servo,  srvo_S2_C1_1,    servo_BR,             tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    servo_FR,             tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo_flip_R,         tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo_climb_R,        tServoStandard)
#pragma config(Servo,  srvo_S2_C1_6,    servo12,              tServoNone)

#include "includes.h"
#include "swerve-drive.h"

task main()
{
	initializeGlobalVariables();
	initializeRobotVariables();
	//Joystick_WaitForStart();
	while (true) {
		Servo_SetPosition(servo_auton, servo_auton_dumped);
		Time_Wait(1000);
		Servo_SetPosition(servo_auton, servo_auton_hold);
		Time_Wait(1000);
	}
}
