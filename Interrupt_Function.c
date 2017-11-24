#include	<lpc214x.h>
#include	"Keypad_Header.h"
#include	"gsm_header.h"
#include	"lcd_header.h"
#include	<stdlib.h>
#include	"Interrupt_Header.h"

char *str = "Enter OTP for Unlock the Locker ";


void Interrupt_Function()
{

	PINSEL0 |= (1 << 29);
	PINSEL0 &= (1 << 28);	// Selecting EINT-1 funcationality on P0.14

	VICIntSelect &= (1 << 15); 	// Select as IRQ  ( Mannual Page 54 )
	VICIntEnable = (1 << 15);	// enable 15 bit is enable interrupt

	VICVectCntl0 = 15 | (1 << 5);// Bit 5 set is control reg
	VICVectAddr0 = (long)isr_otpfun;

	EXTMODE = (1 << 1);		// Edge Sens   ( MAnual page 29/30 )
	EXTPOLAR = (1 << 1);		// Rising Edge

	while(1)
	{
	}
}

void isr_otpfun(void)__irq
{
	int x,d, j = 0;
	char *c , arr[5];

    x = (rand() % 9000) + 1000;
	
	while(x != 0)
	{
		d = x % 10;
		arr[j] = d + 48;
		j++;
		x = x / 10;
	}
	arr[j] = '\0';
	c = String_rev(arr , j-1);
	
	gsm_send_msg(c,str);			// str = " Enter OTP for Unlock the Locker "
				   	
	lcd_clr();
	lcd_str("OTP Send...");	
	delay(400);
	lcd_str("Enter The OTP");
	Keypad_Interface();
	
	if( pressedDigit == x )
		lcd_str("Code Correct");
	else
		lcd_str("Code incorrect");

	EXTINT = (1 << 1);		   //After the ISQ Execute the Pin is Clear or Set to Zero the Bit
	VICVectAddr = 0;	// Every ISR Routine always fix to the Zero.
}

char *String_rev(char *p , int j)
{
	int i = 0;
	while(i < j)
	{
		char temp = p[i];
		p[i] = p[j];
		p[j] = temp; 
		i++;
		j--;
	}
	return p;
}
