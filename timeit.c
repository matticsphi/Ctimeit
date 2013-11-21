/*
 *  timeit.c
 *  
 *
 *  Created by Mattics on 5/9/11.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

void handle(int num);

int main(int argc, char *argv[])
{
    int i, num;
    struct sigaction sig;
    struct itimerval interval;
    
    /* Checks for correct input */
    if (argc != 2) {
        fprintf(stderr, "usage: timeit <seconds>\n");
        return 1;
    }
    
    for (i = 0; i < strlen(argv[1]); i++) {
        if (!(isdigit(*(argv[1] + i)))) {
            fprintf(stderr, "%s: malformed time\n", argv[1]);
            fprintf(stderr, "usage: timeit <seconds>\n");
            return 1;
        }
    }
    
    /* Converts the string to integer */
    num = atoi(argv[1]);
    
    /* Set the handler */
    sig.sa_handler = handle;
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sigaction(SIGALRM, &sig, NULL);
    
    /* Set the timer */
    interval.it_interval.tv_sec = 0;
    interval.it_interval.tv_usec = 500000;
    interval.it_value.tv_sec = 0;
    interval.it_value.tv_usec = 500000;
    setitimer(ITIMER_REAL, &interval, NULL);
    
    /* Loops */
    for (i = 0; i < 2 * num; i++) {
        pause();
    }
    
    printf("Time's Up!\n");
    
    return 0;
}

/* Function that prints out "Tick...Tock" */
void handle(int num)
{
    static int check = 1;
    
    if (check) {
        printf("Tick...");
    } else {
        printf("Tock\n");
    }
    fflush(NULL);

    check = !check;
}