/*
Written for ECS36A, Fall 2019

Eric Wang, October 19, 2019

Print and compare interesting rounding mechanisms in float pi additions
*/
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
    float pi = 3.141592653589793238462643383279502884197169399375105820;  /*Create pi value*/
    printf("%.11f\n",pi);  
    pi=pi+pi+pi+pi+pi+pi+pi+pi+pi+pi;  /*Add pi ten times*/
    printf("%.11f\n",pi);
    return 0;
}

/*From looking at the outputs of the print statements above, it seems that the original pi when printing 11 digits rounds the decimals up 
until the 7th decimal point, atfter which the digits stop rounding up.
A similar case for the pi added ten times, everything is rounded up until the 6th decimal digit, after which the rounding stops and the original digit orders can be seen.
This can be attributed to C's rounding mechanism for 4 byte floats. On the documentation, it is recorded that floats round up to 7 decimal places for its 
precision count. If one wants more precision for pi, using a double or long double can provide more precision, 15, and 19 digits respectively.
 */