

/**
 * main.c
 */
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

uint32_t g_ui32SysClock;

void
InitConsole(void)
{
    //
    // Enable GPIO port A which is used for UART0 pins.
    // TODO: change this to whichever GPIO port you are using.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    //
    // Enable UART0 so that we can configure the clock.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Select the alternate (UART) function for these pins.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}

int main(void)
{
    volatile uint32_t ui32Loop;

    g_ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                             SYSCTL_OSC_MAIN |
                                             SYSCTL_USE_PLL |
                                             SYSCTL_CFG_VCO_480), 120000000);
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    SysCtlPWMClockSet(SYSCTL_PWMDIV_4);
    InitConsole();
    UARTprintf("PWM ->\n");
     UARTprintf("  Module: PWM0\n");
     UARTprintf("  Pin(s): PN0 and PF1\n");
     UARTprintf("  Features: Dead-band Generation\n");
     UARTprintf("  Duty Cycle: 25%% on PD0 and 75%% on PD1\n");
     UARTprintf("  Dead-band Length: 160 cycles on rising and falling edges\n\n");
     UARTprintf("Generating PWM on PWM0 (PD0) -> ");
     SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
     SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
     GPIOPinConfigure(GPIO_PF0_M0PWM0);
     GPIOPinConfigure(GPIO_PF1_M0PWM1);
     GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_0);
     GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1);

    //
    // Check if the peripheral access is enabled.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))
    {
    }
    PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN |
                        PWM_GEN_MODE_NO_SYNC);

    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, 1000);

    //
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0,99);

   // PWMDeadBandEnable(PWM0_BASE, PWM_GEN_0, 160, 160);

    //
    // Enable the PWM0 Bit 0 (PD0) and Bit 1 (PD1) output signals.
    //
    PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT | PWM_OUT_0_BIT, true);

    //
    // Enables the counter for a PWM generator block.
    //
    PWMGenEnable(PWM0_BASE, PWM_GEN_0);

    //
    // Enable the GPIO pin for the LED (PN0).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    //
    int x=0;

    while(1)
       {

        if(x>998)
        {
            x=0;
        }
        x=x+1;

        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, x);

         SysCtlDelay(1200000);


        /*
           //
           // Turn on the LED.
           //
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);
           GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);


           //
           // Delay for a bit.
           //
           for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++)
           {
           }

           //
           // Turn off the LED.
           //
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x0);
           GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0,0x0 );


           //
           // Delay for a bit.
           //
           for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++)
           {
           }
      */ }
}
