#include <stdio.h>
#include <stdlib.h>
#include "wave.h"
//PSG(Programmable Sound Generator)
//サイン波を重ねるのではなく、直線を組み合わせて近似させる

int main(void)
{
    MONO_PCM pcm;
    int n, m, t0;
    double f0, gain;

    pcm.fs = 44100; /*標本化周波数*/
    pcm.bits = 16;  /*量子化精度*/
    pcm.length = pcm.fs * 1;    /*音データの長さ*/
    pcm.s = calloc(pcm.length, sizeof(double)); /*音データ*/

    f0 = 500.0; /*基本周波数*/

    /*ノコギリ波*/
    t0 = pcm.fs / f0;   /*基本周期*/
    m = 0;
    for (n = 0; n < pcm.length; n++)
    {
        pcm.s[n] = 1.0 - 2.0 * m / t0;  //近似

        m++;
        if (m >= t0)
        {
            m = 0;
        }
    }

    gain = 0.1; /*ゲイン*/

    for (n = 0; n < pcm.length; n++)
    {
        pcm.s[n] *= gain;
    }

    wave_write_16bit_mono(&pcm, "ex8_1.wav");

    free(pcm.s);

    return 0;
}