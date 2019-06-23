#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"
#include "pru_iep.h"

volatile register uint32_t __R30;
volatile register uint32_t __R31;

void reset_iep(void){
	CT_IEP.TMR_CNT = 0x0;
	CT_IEP.TMR_GLB_CFG = 0x11;
}

int read_iep(void){
	return CT_IEP.TMR_CNT;
}

void main(void)
{
	uint32_t gpio;

	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

	gpio = 0x0001;	// Select which pin to toggle.

	//int i;

	while (1) {

		reset_iep();

		//wile(read_iep()<100000000){}
		__R30 |= gpio;		// Set the GPIO pin to 1

		//while(read_iep()<100000000){}
		//__R30 &= ~gpio;		// Clearn the GPIO pin
	}
}

/*
inline void wait_for_pwm_timer(){
	while(!(__R31 & (1<<30))){}
	*PRU_INTC_SICR = 15;
	*ECAP_ECCLR = 0xff;
}
*/

