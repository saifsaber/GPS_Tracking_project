#include "stdint.h"
#include "C:/Keil/ARM/ARMCC/include/tm4c123gh6pm.h"
#include <stdint.h>
#include <cmath>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//Check if FIFO not empty to receive data from UART
while ((UART1_FR_R&	0x10) !=0);
return (char) UART1_DR_R;
}
char latitude[20];
char longtitude[20];
int Gpsdata;
	unsigned int loop;
	unsigned int comma=0;
	 unsigned int pos_string =0;
unsigned int longtitude_cnt=0;
	 
	unsigned int latitude_cnt=0;
void Receive_GPS_Data(){
	
	
				 
				 
    while(loop==0){
        Gpsdata = UART_receivechar();
       
       if( Gpsdata=='$' && pos_string == 0)   // finding GPRMC header
         pos_string=1;
       if( Gpsdata=='G' && pos_string == 1)
         pos_string=2;
       if( Gpsdata=='P' && pos_string == 2)
         pos_string=3;
       if( Gpsdata=='R' && pos_string == 3)
         pos_string=4;
       if( Gpsdata=='M' && pos_string == 4)
         pos_string=5;
       if( Gpsdata=='C' && pos_string==5 )
         pos_string=6;
       if( Gpsdata ==','&& pos_string==6){   // count commas in message
         
				 comma++;
         }

       while(comma==3 ){
        
				 latitude[latitude_cnt++] =  Gpsdata;         // latitude
        
       }

       while(comma==5 ){
        
				 longtitude[longtitude_cnt++] =  Gpsdata;         // Longitude
         
       }

       while( Gpsdata == '*' && comma >= 5){
				 latitude[latitude_cnt] ='\0';             // end of GPRMC message
         longtitude[longtitude_cnt]  = '\0';
         comma = 0;                      // end of GPRMC message
         latitude_cnt = 0;
         longtitude_cnt = 0;
         
         loop  = 1;

      }
    }
	
			loop = 0;
   pos_string = 0;
	}
