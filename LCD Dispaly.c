#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#include "stdint.h"
// Rs pin 5 , R/W PIN 6 , E PIN 7 PORT A
// data 8 bits in port B
void SystemInit(){}
void delay_ms(int x){
int i,j;
for( i =0 ; i<x ; i++){for( j=0 ; j<3180 ; j++){}}
}	
void LCD_Command(unsigned char com){
GPIO_PORTA_DATA_R &=0x1F; // Rs=0,R/W=0  (CONTROL)  
GPIO_PORTB_DATA_R	= com ;    //         (DATA)	
GPIO_PORTA_DATA_R |= 0x80;	 // E=1   PIN 7	
delay_ms(0);	
GPIO_PORTA_DATA_R &=0x1F; 	//E=0
delay_ms(2);	
}
void LCD_Data(unsigned char data){
GPIO_PORTA_DATA_R&=0x3F; //Rw,E =0
GPIO_PORTA_DATA_R |= 0x20; // Rs=1 pin 5,R/W=0  (CONTROL)  
GPIO_PORTB_DATA_R	= data ;    //         (DATA)
GPIO_PORTA_DATA_R |= 0x80;	 // E=1   PIN 7
delay_ms(0);	
GPIO_PORTA_DATA_R &=0x1F;    //E=0
delay_ms(2);		
}
void init(){
SYSCTL_RCGCGPIO_R=0x23;
while ((SYSCTL_PRGPIO_R&0x23)==0){}
//Activation for Port F
GPIO_PORTF_LOCK_R=0x4C4F434B;
GPIO_PORTF_CR_R =0x1F;
GPIO_PORTF_AFSEL_R=0;
GPIO_PORTF_PCTL_R=0;
GPIO_PORTF_AMSEL_R=0;
GPIO_PORTF_DIR_R=0x0E;
GPIO_PORTF_DEN_R=0x1F;
GPIO_PORTF_PUR_R=0x11;
//Activation for Port A
GPIO_PORTA_LOCK_R=0x4C4F434B;
GPIO_PORTA_CR_R =0xFF;
GPIO_PORTA_AMSEL_R &=~ 0xFF;
GPIO_PORTA_AFSEL_R &=~ 0xE0;
GPIO_PORTA_DEN_R |= 0xE0;
GPIO_PORTA_PCTL_R &= ~0xFFF00000;
GPIO_PORTA_DIR_R |= 0XE0;
//Activation for Port B
GPIO_PORTB_LOCK_R=0x4C4F434B;
GPIO_PORTB_CR_R =0xFF;
GPIO_PORTB_AMSEL_R &= ~0xFF;
GPIO_PORTB_AFSEL_R &= ~0xFF;
GPIO_PORTB_DEN_R |= 0xFF;
GPIO_PORTB_PCTL_R &= ~0xFFFFFFFF;
GPIO_PORTB_DIR_R |= 0XFF;
}
void LCD_init(){	
int i;	
char dist[14]={'T','o','t','a','l',' ','D','i','s','t','a','n','c','e'};		
LCD_Command(0x30); //Wake up
LCD_Command(0x38);	// select 8 bits mode	
LCD_Command(0x01);   //clear display
LCD_Command(0x0F); // display on , cursor blinking
LCD_Command(0x80);  //FORCE CURSOR TO BEGIN AT FIRST LINE
delay_ms(500);	
for(i=0;i<14;i++){
LCD_Data(dist[i]);
LCD_Command(0x06);
delay_ms(500);	
}
}
int main(){
init();	
while(1){
LCD_init();	
}	
}
