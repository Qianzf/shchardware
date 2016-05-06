
#include "utils.h"
#include "gpio_init.h"

void startinfo()
	{
		sendString(DEBUG,"+------------------------------------------+\n\r");
		sendString(DEBUG,"|                                          |\n\r");
		sendString(DEBUG,"|                  Hello!                  |\n\r");
		sendString(DEBUG,"|                                          |\n\r");
		sendString(DEBUG,"|         CHIP:STM32F407VG                 |\n\r");
		sendString(DEBUG,"|         RAM:192KB                        |\n\r");
		sendString(DEBUG,"|         FLASH:1MB                        |\n\r");
		sendString(DEBUG,"|         SYSTEM:uCOSII                    |\n\r");
		sendString(DEBUG,"|         BOARD:DISCOVERY                  |\n\r");
		sendString(DEBUG,"|         AUTHOR:Qianzf                    |\n\r");
		sendString(DEBUG,"|         BUILD-DATE:2016-03-27            |\n\r");
		sendString(DEBUG,"|                                          |\n\r");
		sendString(DEBUG,"+------------------------------------------+\n\r");
		sendString(DEBUG,"\n\r");
		
	}
	
	

























