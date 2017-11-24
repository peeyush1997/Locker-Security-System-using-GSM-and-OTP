#include	<lpc214x.h>
#include	"Keypad_Header.h"
#include	"gsm_header.h"
#include	"lcd_header.h"
#include	"Interrupt_Header.h"

int main ()
{
/**************	Initilization **************/
	
	lcd_init();
	
	lcd_str("Wlcm to Locker");
	lcd_cmd(0xC0);				// For Next Line
	lcd_str("Security System");
	
	UART1_init();
	gsm_init();
	Interrupt_Function();
	
	while(1);
}
