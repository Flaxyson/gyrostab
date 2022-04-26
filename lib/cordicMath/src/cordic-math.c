/* Copyright (c) 2022 Max Gulda, KTH

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

#include "cordic-math.h"

/* AngTable = 45, 26.565, 14.036, 7.125, 3.576, 1.790, 0.895, 0.448, 0.225, 0.112, 0.056, 0.028, 0.014, 0.007,  0.003 */
int LUT_CORDIC_ATAN[15] = {11520, 6801, 3593, 1824, 916, 458, 229, 115, 57, 28, 14, 7, 4, 2, 1}; /* Degree << 8 */

int32_t cordic_atan(int32_t y, int32_t x){
    int sumAngle = 0;
    int newX=x, newY=y;
    if(x<0 && y>0){              
        sumAngle = 180*256; 
        x = -x;
        y = -y;
    }else if(y < 0 && x>0){  
        sumAngle = 360*256;
    }
    for (int i = 0; i < 15; i++){
        if(y>0){
            /* Rotate clockwise */
            newX += (y>>i);
            newY -= (x>>i);
            sumAngle += LUT_CORDIC_ATAN[i];
        }else{
            /* Rotate counterclockwise */
            newX -= (y>>i);
            newY += (x>>i);
            sumAngle -= LUT_CORDIC_ATAN[i];
        }
        x = newX;
        y = newY;
    }
    /* If hypotenusa calculation is needed you will need to multiply 'x' by the cordic-gain which is cos(0.45)*cos(26.565)....
    The cordic gain for all 15 angles is 0.607252935 */
    return sumAngle;
}

int32_t cordic_cos(int32_t theta){
    int x = 156;
    int y = 0;
    int sumAngle = 0;
    int newX=x, newY=y;

    if(theta>(90*256)){
        sumAngle = 180*256;
    }
    if(theta>(270*256)){
        sumAngle = 360*256;
    }

    for(int i = 0; i < 15; i++){
        if(theta > sumAngle){
            /* Rotate counter clockwise */
            newX -= (y>>i);
            newY += (x>>i);
            sumAngle += LUT_CORDIC_ATAN[i];
        }else{
            /* Rotate clockwise */
            newX += (y>>i);
            newY -= (x>>i);
            sumAngle -= LUT_CORDIC_ATAN[i];
        }
        x = newX;
        y = newY;
    }
    if(theta > (180*256) && theta < (360*256)){
        x = -x;
    }
    return x;
}

int32_t cordic_sin(int32_t theta){
    int x = 156;
    int y = 0;
    int sumAngle = 0;
    int newX=x, newY=y;

    if(theta>(90*256)){
        sumAngle = 180*256;
    }
    if(theta>(270*256)){
        sumAngle = 360*256;
    }

    for(int i = 0; i < 15; i++){
        if(theta > sumAngle){
            /* Rotate counter clockwise */
            newX -= (y>>i);
            newY += (x>>i);
            sumAngle += LUT_CORDIC_ATAN[i];
        }else{
            /* Rotate clockwise */
            newX += (y>>i);
            newY -= (x>>i);
            sumAngle -= LUT_CORDIC_ATAN[i];
        }
        x = newX;
        y = newY;
    }
    if(theta > (90*256) && theta < (270*256)){
        y = -y;
    }
    return y;
}

int32_t cordic_asin(int32_t yInput){
    int x = 156;
    int y = 0;
    int sumAngle = 0;
    int newX=x, newY=y;

    for(int i = 0; i < 15; i++){
        if(y < yInput){
            /* Rotate counter clockwise */
            newX -= (y>>i);
            newY += (x>>i);
            sumAngle += LUT_CORDIC_ATAN[i];
        }else{
            /* Rotate clockwise */
            newX += (y>>i);
            newY -= (x>>i);
            sumAngle -= LUT_CORDIC_ATAN[i];
        }
        x = newX;
        y = newY;
    }

    return sumAngle;
}

int32_t cordic_acos(int32_t xInput){
    int x = 0;
    int y = 156;
    int sumAngle = 90*256;
    int newX=x, newY=y;

    for(int i = 0; i < 15; i++){
        if(x > xInput){
            /* Rotate counter clockwise */
            newX -= (y>>i);
            newY += (x>>i);
            sumAngle += LUT_CORDIC_ATAN[i];
        }else{
            /* Rotate clockwise */
            newX += (y>>i);
            newY -= (x>>i);
            sumAngle -= LUT_CORDIC_ATAN[i];
        }
        x = newX;
        y = newY;
    }

    return sumAngle;
}

int32_t cordic_tan(int32_t degree){
    return (cordic_sin(degree)/cordic_cos(degree));
}

int32_t ssqrt(int32_t n){
    n = n<<2;
    int64_t val = n << 10;
    unsigned long temp, g=0, b = 0x8000, bshft = 15;
    do {
        if (val >= (temp = (((g << 1) + b)<<bshft--))) {
           g += b;
           val -= temp;
        }
    } while (b >>= 1);
    return g>>2;
}

int power(int x, int y){

    if(y==0){
        return 256;
    }
    if(x==0){
        return 0;
    }
    if(/*y>0*/1){
        return (x * power(x,y-256))/256;
    }/* else{ //Funkar inte än
        return ((x * power(x,y+256))/256)*(1/256); 
    } */
}

int absolute(int input){
    if(input>0){
        return input;
    }else{
        return -input;
    }
}

int isEven(int input){
    if(input%2) return 0;
    return 1;
}

int isOdd(int input){
    if(input%2) return 1;
    return 0;
}

int to_degree(int input){
    return (input*14667>>8);
}

int to_radians(int input){
    return (input/14667)<<8;
}


/*E^*/
/*log*/
/*rad to degree*/
/*degree to rad*/

