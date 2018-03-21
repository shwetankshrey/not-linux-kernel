#include <stdio.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>

void timetakingfunction() {
    int t = 100000;
    int a = 100;
    while(t-->0) {
        a--;
        a++;
        a--;
        a++;
    }
}

int main() {
    pid_t pid = getpid();
    struct timeval stop, start;
    if(fork() == 0) {
        long int am = syscall(546, pid, 100);
        gettimeofday(&start, NULL);
        timetakingfunction();
        gettimeofday(&stop, NULL);
        printf("With soft realtime (x = 100) scheduling %lu\n", stop.tv_usec - start.tv_usec);
    }
    else {
        if(fork() == 0) {
            long int am = syscall(546, pid, 10);
            gettimeofday(&start, NULL);
            timetakingfunction();
            gettimeofday(&stop, NULL);
            printf("With soft realtime (x = 10) scheduling %lu\n", stop.tv_usec - start.tv_usec);
        }
        else {
            if(fork() == 0) {
                long int am = syscall(546, pid, 20);
                gettimeofday(&start, NULL);
                timetakingfunction();
                gettimeofday(&stop, NULL);
                printf("With soft realtime (x = 20) scheduling %lu\n", stop.tv_usec - start.tv_usec);
            }
            else {
                if(fork() == 0) {
                    long int am = syscall(546, pid, 50);
                    gettimeofday(&start, NULL);
                    timetakingfunction();
                    gettimeofday(&stop, NULL);
                    printf("With soft realtime (x = 50) scheduling %lu\n", stop.tv_usec - start.tv_usec);
                }
                else {
                    gettimeofday(&start, NULL);
                    timetakingfunction();
                    gettimeofday(&stop, NULL);
                    printf("Without soft realtime scheduling %lu\n", stop.tv_usec - start.tv_usec);
                }
            }
        }
    }   
}
