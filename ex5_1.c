#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wave.h"
//Amplitude Envelope
/*サイン波の重ね合わせ*/
int main(void)
{
    MONO_PCM pcm;
    int n;
    double *a0, f0;

    pcm.fs = 44100;     /*標本化周波数*/
    pcm.bits = 16;      /*量子化精度*/
    pcm.length = pcm.fs * 4;    /*音データの長さ*/
    pcm.s = calloc(pcm.length, sizeof(double));     /*音データ*/

    a0 = calloc(pcm.length, sizeof(double));

    /*振幅の時間エンベロープ*/
    a0[0] = 0.5;
    a0[pcm.length - 1] = 0.0;
    for (n = 0; n < pcm.length; n++) 
    {
        a0[n] = a0[n] + (a0[pcm.length - 1] - a0[0]) * n / (pcm.length - 1);
    }  

    f0 = 500.0;     /*周波数*/

    for (n = 0; n < pcm.length; n++)
    {
        pcm.s[n] = a0[n] * sin(2.0 * M_PI * f0 * n / pcm.fs);
    }

    wave_write_16bit_mono(&pcm, "ex5_1.wav");

    free(pcm.s);
    free(a0);

    return 0;    
}