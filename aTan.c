#include "aTan.h"

#define NINETY 23040
#define HUNDREDEIGHTY 46080

int arctan(int x, int y){

    /* AngTable = 45, 26.565, 14.036, 7.125, 3.576, 1.790, 0.895, 0.448 ... etc */

    int LUT_CORDIC_ATAN[8] = {11520, 6801, 3593, 1824, 916, 458, 229, 115, 57, 28, 14, 7, 4, 2, 1}; /* Degree << 8 */
    int sumAngle = 0;
    if(x<0){
        sumAngle = HUNDREDEIGHTY; /* 180 * 256 */
        x = -x;
        y = -y;
    }else if(y < 0){
        sumAngle = -NINETY; /* -90 * 256 */
    }
    for (int i = 0; i < 15; i++){
        if(y>0){
            /* Rotate clockwise */
            x += (y>>i);
            y -= (x>>i);
            sumAngle += LUT_CORDIC_ATAN[i];
        }else{
            /* Rotate counterclockwise */
            x -= (y>>i);
            y += (x>>i);
            sumAngle -= LUT_CORDIC_ATAN[i];
        }
    }
    return sumAngle;
}