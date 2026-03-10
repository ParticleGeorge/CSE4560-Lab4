/*
 *
 */

#include <lab4.h>                              // Lab specific defines/declarations

/* Global variables */
volatile bool button1Flag;                     // Flag to indicate that button S1 has been pressed
volatile bool button2Flag;                     // Flag to indicate that button S2 has been pressed
volatile uint32_t count1 = 0;                  // Variable to count interrupts produced by S1
volatile uint32_t count2 = 0;                  // Variable to count interrupts produced by S2

void task1(void)
{
  /* Setup UART */
  uart_init(UART_BAUDRATE);

  //// Placeholder 1 /////////////////////////////////////////////////////////
  /* Configuring P2.1 (LED2 green) and P2.2 (LED2 blue) as output */
  GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN1);
  GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN2);
  ////////////////////////////////////////////////////////////////////////////

  //// Placeholder 2 /////////////////////////////////////////////////////////
  /* Configuring P1.1 (Button S1) and P1.4 (Button S2) as an input */
  GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1,GPIO_PIN1);
  GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1,GPIO_PIN4);
  ////////////////////////////////////////////////////////////////////////////

  //// Placeholder 3 /////////////////////////////////////////////////////////
  /* Configure interrupts for buttons S1 and S2 */
  GPIO_interruptEdgeSelect(GPIO_PORT_P1, GPIO_PIN1, GPIO_LOW_TO_HIGH_TRANSITION);
  GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);

  GPIO_interruptEdgeSelect(GPIO_PORT_P1, GPIO_PIN4, GPIO_LOW_TO_HIGH_TRANSITION);
  GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN4);
  ////////////////////////////////////////////////////////////////////////////

  //// Placeholder 4 /////////////////////////////////////////////////////////
  /* Enable interrupts for both GPIO pins */
  /* Enable interrupts on Port 1 */
  /* Enable interrupts globally */
  GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);
  GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);

  Interrupt_enableInterrupt(INT_PORT1);

  Interrupt_enableMaster();
  ////////////////////////////////////////////////////////////////////////////

  //// Placeholder 5 /////////////////////////////////////////////////////////
  /* Initially turn LEDs off */
  GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN1);
  GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN2);
  ////////////////////////////////////////////////////////////////////////////

  /* Code that is executed when processor is not busy with handling an interrupt */
  while (1)
  {
    // Sleep while waiting for an interrupt
    PCM_gotoLPM3();
    // After interrupt occurred
    if (button1Flag)
    {
      /* Increase and send counter for button S1 via UART */
      count1 += 1;
      uart_println("S1: %d", count1);
      button1Flag = false;
    }
    if (button2Flag)
    {
      /* Increase and send counter for button S2 via UART */
      count2 += 1;
      uart_println("S2: %d", count2);
      button2Flag = false;
    }
  }
}

/*
 * PORT 1 interrupt service routine
 */
void PORT1_IRQHandler(void)
{
  uint32_t status;

  /* Get the content of the interrupt status register of port 1 */
  status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);

  //// Pseudocode 1 (Task 1.1) ///////////////////////////////////////////////
  //
  // if (buttonS1WasPressed()) {
  //     toggleGreenLED();
  //     setFlagForButton1();
  //     clearInterruptFlag();
  // }
  if (status & GPIO_PIN1)
  {
      GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN1);
      button1Flag = true;
      GPIO_clearInterruptFlag(GPIO_PORT_P1, status);

  }
  // else if (buttonS2WasPressed()) {
  //     toggleBlueLED();
  //     setFlagForButton2();
  //     clearInterruptFlag();
  // }
  if (status & GPIO_PIN4)
  {
      GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN2);
      button2Flag = true;
      GPIO_clearInterruptFlag(GPIO_PORT_P1, status);

  }
  //
  // Hint: Use the provided status variable and the bit masks GPIO_PIN1 and
  //       GPIO_PIN4 to figure out if button S1 or S2 have been pressed.
  ////////////////////////////////////////////////////////////////////////////
}
