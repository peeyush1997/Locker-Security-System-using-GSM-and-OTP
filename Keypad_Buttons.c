#include<lpc214x.h>
#include"Keypad_Header.h"
#include"lcd_header.h"
	
void Keypad_Interface()
{	
   	int c;
	IODIR0 = LCD;
	lcd_init();
	countPressed=0;
	pressedDigit = 0;
	
 	while(1 && (countPressed < 4) )
 	{
		IODIR1 = Row_all;
		IOCLR1 = Row_all;
  	  	c = IOPIN1 & Col_all;
	  	if(c != Col_all)
	  	{
	  		if(c == 0x01c00000)
			{
			   delay(100);
				row1();
			}
			if(c == 0x01a00000)
			{
			    delay(100);
				row2();
			} 
		 	if(c == 0x01600000)
			{
				delay(100);
		 		row3();
			}
			if(c == 0x00e00000)
			{
				delay(100);
				row4();
			}
	  	} 
	}
}

void row1()
{
	int a;
	IODIR1 = Col_all;
	IOCLR1 = Col_all;	// columns awill be zero
	a = IOPIN1 & Row_all;
	if(a != Row_all)
	{
		if(a == 0x001c0000)
		{
			lcd_data('7');
			pressedDigit = pressedDigit*10 + 7;
			countPressed++;
		}	
		if(a == 0x001a0000)
		{
			lcd_data('4');	
			pressedDigit = pressedDigit*10 + 4;
			countPressed++;				
		}
		if(a == 0x00160000)
		{
			lcd_data('1');
			pressedDigit = pressedDigit*10 + 1;	
			countPressed++;			
		}
		if(a == 0x000e0000)
		{
			lcd_data('.');
		}
	}

}
void row2()
{
	int a;
	IODIR1 = Col_all;
	IOCLR1 = Col_all;
	a = IOPIN1 & Row_all;
	if(a != Row_all)
	{
		if(a == 0x001c0000)
		{
			lcd_data('8');
			pressedDigit = pressedDigit*10 + 8;
			countPressed++;
		}			 	
		if(a == 0x001a0000)
		{		
			lcd_data('5');
			pressedDigit = pressedDigit*10 + 5;
			countPressed++;
		}
		if(a == 0x00160000)
		{
			lcd_data('2');
			pressedDigit = pressedDigit*10 + 2;
			countPressed++;
		}
		if(a == 0x000e0000)
		{	
			lcd_data('0');
			pressedDigit = pressedDigit*10 + 0;
			countPressed++;
		}	
	}

}
void row3()
{
	int a;
	IODIR1 = Col_all;
	IOCLR1 = Col_all;
	a = IOPIN1 & Row_all;
	if(a != Row_all)
	{
		if(a == 0x001c0000)
		{
			lcd_data('9');
			pressedDigit = pressedDigit*10 + 9;
			countPressed++;
		}
					 	
		if(a == 0x001a0000)
		{
			lcd_data('6');
			pressedDigit = pressedDigit*10 + 6;
			countPressed++;
		}

		if(a == 0x00160000)
		{	
			lcd_data('3');
			pressedDigit = pressedDigit*10 + 3;
			countPressed++;
		}	

		if(a == 0x000e0000)
			lcd_data('=');
	}
}
void row4()
{
	int a;
	IODIR1 = Col_all;
	IOCLR1 = Col_all;
	a = IOPIN1 & Row_all;
	if(a != Row_all)
	{
		if(a == 0x001c0000)
			lcd_data('/');
					 	
		if(a == 0x001a0000)
			lcd_data('*');

		if(a == 0x00160000)	
			lcd_data('-');

		if(a == 0x000e0000)
			lcd_data('+');
			
	}
}
