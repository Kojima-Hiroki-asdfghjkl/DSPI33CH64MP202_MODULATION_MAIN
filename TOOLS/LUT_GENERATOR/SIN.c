#include <stdio.h>
#include <math.h>

#define _USE_MATH_DEFINES

#define resolution 128// pi/2


#define PI 3.14159265358979323846

#define deg2rad(x) ((x) * (PI / 180.0))


int main() {
    double angle, result;

    printf("Enter an angle in degrees: ");
    scanf("%lf", &angle);

    angle = deg2rad(angle);
    result = sin(angle);
    printf("The sine of %.2f degrees is %.4f\n", angle * (180.0 / PI), result);

    return 0;
}