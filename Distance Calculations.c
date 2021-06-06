#include <cmath>
#include <stdio.h>
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#define pi 3.14159265358979323846
void SystemInit(){}
double deg2rad(double deg) {
    return (deg * pi / 180);
}
double rad2deg(double rad) {
    return (rad * 180 / pi);
}

double distance(double lat1, double lon1, double lat2, double lon2, char unit) {
    double theta, dist;
    
    if ((lat1 == lat2) && (lon1 == lon2)) {
        return 0;
    }
    else {
        theta = lon1 - lon2;
        dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) * cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
        dist = acos(dist);
        dist = rad2deg(dist);
        dist = dist * 60 * 1.1515;
        dist = dist * 1.609344 *1000; 
         }
		return dist;
	}
   
    int main(){
    double x1=40.76532;
    double x2=20.867456;
    double y1=20.89123;
    double y2=20.980842;   
    double c=distance(x1,x2,y1,y2,0);
		printf("%1f",c);		
		}
		