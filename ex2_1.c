#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wave.h"
/*サイン波*/

int main(void)
{
    MONO_PCM pcm;
    int n;
    double a, f0;

    pcm.fs = 441000;    //標本化周波数
    pcm.bits = 16;      //量子化制度
    pcm.length = pcm.fs * 1;    //音データの長さ
    pcm.s =  calloc(pcm.length, sizeof(double));     //音データ

    a = 0.1;    //振幅
    f0 = 500.0; //周波数

    /*サイン波*/
    for (n = 0; n < pcm.length; n++)
    {
        pcm.s[n] = a * sin(2.0 * M_PI * f0 * n / pcm.fs);
    }

    wave_write_16bit_mono(&pcm, "ex2_1.wav");

    free(pcm.s);

    return 0;


}