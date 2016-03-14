#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void dummy_proc_0(){
    return;
}
void dummy_proc_1(int a0){
    return;
}
void dummy_proc_2(int a0, int a1){
    return;
}
void dummy_proc_3(int a0, int a1, int a2){
    return;
}
void dummy_proc_4(int a0, int a1, int a2, int a3){
    return;
}
void dummy_proc_5(int a0, int a1, int a2, int a3, int a4){
    return;
}
void dummy_proc_6(int a0, int a1, int a2, int a3, int a4, int a5){
    return;
}
void dummy_proc_7(int a0, int a1, int a2, int a3, int a4, int a5, int a6){
    return;
}

void prob2(float overhead){
    unsigned t, min, max;
    float avg, stddev;
    int num_iter = 100000;

    avg = 0.0;
    stddev = 0.0;
    min = 100000000;
    max = 0;
    for (int i = 1; i <= num_iter; i++){
        t = ccnt_read();
        dummy_proc_0();
        t = ccnt_read() - t;
        float prev_avg = avg;
        avg += (t - overhead - prev_avg) / i;
        stddev += (t - overhead - prev_avg) * (t - overhead - avg);
        if (t-overhead > max) max = t-overhead;
        if (t-overhead < min) min = t-overhead;
    }
    stddev = sqrt(stddev / (num_iter - 1));
    printf("0 variables procedure call : average = %f, std = %f, min = %d, max = %d\n", avg, stddev, min, max);    

    avg = 0.0;
    stddev = 0.0;
    min = 100000000;
    max = 0;
    for (int i = 1; i <= num_iter; i++){
        t = ccnt_read();
        dummy_proc_1(0);
        t = ccnt_read() - t;
        float prev_avg = avg;
        avg += (t - overhead - prev_avg) / i;
        stddev += (t - overhead - prev_avg) * (t - overhead - avg);
        if (t-overhead > max) max = t-overhead;
        if (t-overhead < min) min = t-overhead;
    }
    stddev = sqrt(stddev / (num_iter - 1));
    printf("1 variables procedure call : average = %f, std = %f, min = %d, max = %d\n", avg, stddev, min, max);

    avg = 0.0;
    stddev = 0.0;
    min = 100000000;
    max = 0;
    for (int i = 1; i <= num_iter; i++){
        t = ccnt_read();
        dummy_proc_2(0, 1);
        t = ccnt_read() - t;
        float prev_avg = avg;
        avg += (t - overhead - prev_avg) / i;
        stddev += (t - overhead - prev_avg) * (t - overhead - avg);
        if (t-overhead > max) max = t-overhead;
        if (t-overhead < min) min = t-overhead;
    }
    stddev = sqrt(stddev / (num_iter - 1));
    printf("2 variables procedure call : average = %f, std = %f, min = %d, max = %d\n", avg, stddev, min, max);

    avg = 0.0;
    stddev = 0.0;
    min = 100000000;
    max = 0;
    for (int i = 1; i <= num_iter; i++){
        t = ccnt_read();
        dummy_proc_3(0, 1, 2);
        t = ccnt_read() - t;
        float prev_avg = avg;
        avg += (t - overhead - prev_avg) / i;
        stddev += (t - overhead - prev_avg) * (t - overhead - avg);
        if (t-overhead > max) max = t-overhead;
        if (t-overhead < min) min = t-overhead;
    }
    stddev = sqrt(stddev / (num_iter - 1));
    printf("3 variables procedure call : average = %f, std = %f, min = %d, max = %d\n", avg, stddev, min, max);

    avg = 0.0;
    stddev = 0.0;
    min = 100000000;
    max = 0;
    for (int i = 1; i <= num_iter; i++){
        t = ccnt_read();
        dummy_proc_4(0, 1, 2, 3);
        t = ccnt_read() - t;
        float prev_avg = avg;
        avg += (t - overhead - prev_avg) / i;
        stddev += (t - overhead - prev_avg) * (t - overhead - avg);
        if (t-overhead > max) max = t-overhead;
        if (t-overhead < min) min = t-overhead;
    }
    stddev = sqrt(stddev / (num_iter - 1));
    printf("4 variables procedure call : average = %f, std = %f, min = %d, max = %d\n", avg, stddev, min, max);

    avg = 0.0;
    stddev = 0.0;
    min = 100000000;
    max = 0;
    for (int i = 1; i <= num_iter; i++){
        t = ccnt_read();
        dummy_proc_5(0, 1, 2, 3, 4);
        t = ccnt_read() - t;
        float prev_avg = avg;
        avg += (t - overhead - prev_avg) / i;
        stddev += (t - overhead - prev_avg) * (t - overhead - avg);
        if (t-overhead > max) max = t-overhead;
        if (t-overhead < min) min = t-overhead;
    }
    stddev = sqrt(stddev / (num_iter - 1));
    printf("5 variables procedure call : average = %f, std = %f, min = %d, max = %d\n", avg, stddev, min, max);

    avg = 0.0;
    stddev = 0.0;
    min = 100000000;
    max = 0;
    for (int i = 1; i <= num_iter; i++){
        t = ccnt_read();
        dummy_proc_6(0, 1, 2, 3, 4, 5);
        t = ccnt_read() - t;
        float prev_avg = avg;
        avg += (t - overhead - prev_avg) / i;
        stddev += (t - overhead - prev_avg) * (t - overhead - avg);
        if (t-overhead > max) max = t-overhead;
        if (t-overhead < min) min = t-overhead;
    }
    stddev = sqrt(stddev / (num_iter - 1));
    printf("6 variables procedure call : average = %f, std = %f, min = %d, max = %d\n", avg, stddev, min, max);

    avg = 0.0;
    stddev = 0.0;
    min = 100000000;
    max = 0;
    for (int i = 1; i <= num_iter; i++){
        t = ccnt_read();
        dummy_proc_7(0, 1, 2, 3, 4, 5, 6);
        t = ccnt_read() - t;
        float prev_avg = avg;
        avg += (t - overhead - prev_avg) / i;
        stddev += (t - overhead - prev_avg) * (t - overhead - avg);
        if (t-overhead > max) max = t-overhead;
        if (t-overhead < min) min = t-overhead;
    }
    stddev = sqrt(stddev / (num_iter - 1));
    printf("7 variables procedure call : average = %f, std = %f, min = %d, max = %d\n", avg, stddev, min, max);

    return;  
}

int main(){
    prob2(8);
    return 0;
}

