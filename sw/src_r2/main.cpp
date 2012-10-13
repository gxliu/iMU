extern "C" {
	#include "stm32f4xx.h"
}

#include "tick.h"
#include "l3gd20.h"
//#include "lsm303.h"
//#include "sdio.h"
#include "spi_platform.h"
#include "l3gd20_platform.h"
#include "stdlib.h"

//! @defgroup util Utilities

//! @name LED macros
//! @{
#define LED_GPIO GPIOD
#define LED_PIN(x) (GPIO_Pin_12 << x)
#define LED_PIN_ALL (LED_PIN(0) | LED_PIN(1) | LED_PIN(2))

#define LED_SET(x)    (LED_GPIO->ODR |= LED_PIN(x))
#define LED_SET_ALL() (LED_GPIO->ODR |= LED_PIN_ALL)
#define LED_CLR(x)    (LED_GPIO->ODR &= ~LED_PIN(x))
#define LED_CLR_ALL() (LED_GPIO->ODR &= ~LED_PIN_ALL)
//! @}

int main(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// All GPIO clock enable
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA |
	                       RCC_AHB1Periph_GPIOB |
	                       RCC_AHB1Periph_GPIOC |
	                       RCC_AHB1Periph_GPIOD |
	                       RCC_AHB1Periph_GPIOE, ENABLE);

	// Configure LEDs in output pushpull mode
	GPIO_InitStructure.GPIO_Pin = LED_PIN_ALL;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(LED_GPIO, &GPIO_InitStructure);
	
	spi1.init();
	
	// Configure SysTick for 400ms period	
	if(!Tick::start(400.0)){
		
		while(1);
	}

	//l3gd20_init();
	gyro1.init();
	
	while (1){
		Tick::wait(1);
		//l3gd20_read_sync();
	}
}
