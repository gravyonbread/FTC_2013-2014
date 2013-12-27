// For communicating with the NXT (via the SuperPro board).
#ifndef COMM_CONTROLLER_H
#define COMM_CONTROLLER_H

#include <avr/io.h>
#include <avr/interrupt.h>	// Include <util/atomic.h> for proper use.
#include <util/atomic.h>	// For interrupts^.
#include <util/twi.h>
#ifndef F_CPU
#define F_CPU 1000000UL
#endif
#include <util/delay.h>
#include <math.h>

// Number of I/O lines.
#define NXT_LINE_NUM		6

// TODO: Enum this?
// Each NXT line.
#define NXT_LINE_A			PB6
#define NXT_LINE_B			PB7
#define NXT_LINE_C			PD5
#define NXT_LINE_D			PD6
#define NXT_LINE_E			PD7
#define NXT_LINE_F			PB0

// Ports of each NXT line.
#define NXT_LINE_A_PORT		PORTB
#define NXT_LINE_B_PORT		PORTB
#define NXT_LINE_C_PORT		PORTD
#define NXT_LINE_D_PORT		PORTD
#define NXT_LINE_E_PORT		PORTD
#define NXT_LINE_F_PORT		PORTB

// Clock counts for debounce to trigger.
// 9999 = 10 ms
#define DEBOUNCE_COUNTS		9999



void setupPins(void);

namespace TWI
{
	// Common uses:
	// start-write_address-write_data-stop
	// start-write_address-read_data_once-stop
	
	void setup(void);
	void start(void); // REPEATED START is same as START (according to datasheet).
	void stop(void);
	void write_address(uint8_t u8data);
	void write_data(uint8_t u8data);
	void read_data_once(uint8_t &u8data);
	
	//// TODO!
	//void read_data_cont(int size);
	
	void write_SLAW(uint8_t address);
	void write_SLAR(uint8_t address);
	
	uint8_t status(void);
}



#endif // COMM_CONTROLLER_H