#include	<lpc214x.h>
#include  	"string.h"
#include	"gsm_header.h"
#include	"lcd_header.h"


char *AT = "AT\r\n"	;
char *AT_CMGF = "AT+CMGF=1\r\n";
char *AT_CMGS="AT+CMGS=\"+917276931096\"\r\n";

char *OK = "OK";
char temp[15];

/********************* UART1 Initialisation *********************/

void UART1_init(void)
{

	PINSEL0 |= ((1<<16)|(1<<18));	// FOR UART0 AND UART1
	U1LCR = 0X80;
	U1DLL = 97;
	U1LCR = 0X03;
}

/*------------------------------------------------------------------------------------------------
FUNCTION NAME : SENDING MESSAGE THROUGH GSM --> UART1
-------------------------------------------------------------------------------------------------*/

void string_uart_trns_gsm(char *str)
{
	while(*str)
	{
		put_char_gsm(*str);
		str++;
	}
}
void put_char_gsm(char c)
{
	while(!(U1LSR & (1 << 5)));
	U1THR = c;
}
 
char uart_recv_gsm(void)
{
	while(!(U1LSR & (1 << 0)));
	return(U1RBR);
}

/*-----------------------------------------------------------------------------------------------------
	FUNCTION DEFINITIONS --->GSM
--------------------------------------------------------------------------------------------------------*/

void gsm_response(char ca,int no)
{
	char c;
	int i = 0;
	do
	{
		//i = 0;
		c = uart_recv_gsm();
		temp[i] = c;

	}while((c != ca));

	do
	{
		i++;
		c=uart_recv_gsm();
		temp[i] = c;

	}while(i != no);

	delay(3000);
	delay(3000);
}
/*------------------------------------------------------------------------------------------------------*/


void gsm_init()
{
	do
	{
		delay(5000);
		string_uart_trns_gsm(AT);
		gsm_response('O',1);
		temp[2] = '\0';

	}while(strcmp(temp,OK) != 0);
	
	delay(5000);
	string_uart_trns_gsm(AT_CMGF);
	delay(6000);
}


void gsm_send_msg(char *otp, char *str)
{

	string_uart_trns_gsm(AT_CMGS);
   	delay(5000);
   	string_uart_trns_gsm(otp);
	put_char_gsm(0x0a);
	string_uart_trns_gsm(str);
	put_char_gsm(0x1a);
  	delay(3000);

}
