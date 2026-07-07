#include <stdio.h>
#include <math.h>
#include <stdint.h>

/* メモ
    DMAでPWMモジュールに転送するSINのLUTを作製するコード
    分解能の部分は90°であるため，実際には4倍のデータ量になる
    PWMDCレジスタは2バイト長であるため，データ長はさらに2倍になる
    LUTはromに格納するため，自動でconst修飾子が付与される
    MAX_DUTY_CYCLEでデータの最大値を決定し，それに合うような形で出力する
    出力形式は，C言語の配列形式(uint16_t)でプリントするのでコピペして使用することができる
    定数配列名は"SIN_LUT_NAME"マクロにて定義する
*/


#define _USE_MATH_DEFINES

#define resolution 128// pi/2
#define start_angle 45//pi/4
#define MAX_DUTY_CYCLE 0x03FF
#define SIN_LUT_NAME "SIN_LUT"

#define PI 3.14159265358979323846

#define deg2rad(x) ((x) * (PI / 180.0))
#define get_lut_length() (resolution * 4)


int main() {
    printf("Generating sine LUT...\n\n");
    printf("/*\n");
    printf("LUT length: %d\n", get_lut_length());
    printf("LUT name: %s\n", SIN_LUT_NAME);
    printf("Resolution: %d\n", resolution);
    printf("MAX_DUTY_CYCLE: 0x%04X\n", MAX_DUTY_CYCLE);
    printf("Start angle: %.2f radians (%.2f degrees)\n", deg2rad(start_angle), (double)start_angle);
    printf("*/\n");
    printf("const uint16_t %s[%d] = {\n", SIN_LUT_NAME, get_lut_length());
    for(int i = 0; i < get_lut_length(); i++) {
        if (i % 16 == 0) {
            printf("    ");
        }
        double angle = deg2rad(start_angle) + (double)i * (PI / 2.0) / resolution;
        double sin_value = sin(angle);
        uint16_t duty_cycle_value = (uint16_t)(sin_value * (MAX_DUTY_CYCLE / 2.0) + (MAX_DUTY_CYCLE / 2.0));
        printf("0x%04X", duty_cycle_value);
        if (i < get_lut_length() - 1) {
            printf(", ");
        }
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
    if (get_lut_length() % 16 != 0) {
        printf("\n");
    }
    printf("};\n");
    printf("LUT generation complete.\n");

    return 0;
}