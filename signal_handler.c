#include <stdio.h>
#include <string.h>
#include <signal.h>
#define SIGTSTP 18

// Initiate signal handlers.
void initiate_sigaction() {
        // signal(SIGINT, sig_INT_Handler);

    struct sigaction sigint, sigtstp;

    // Ctrl-C
    sigint.sa_handler = sig_INT_Handler;
    sigint.sa_flags = 0;
    sigemptyset(&sigint.sa_mask);

    if ( sigaction(SIGINT, &sigint, NULL) == -1 ) {
        perror("Couldn't set SIGINT handler");
        exit(EXIT_FAILURE);
    }

    // Ctrl-Z
    sigtstp.sa_handler = sig_TSTP_Handler;
    sigtstp.sa_flags = 0;
    sigemptyset(&sigtstp.sa_mask);

    if ( sigaction(SIGTSTP, &sigtstp, NULL) == -1 ) {
        perror("Couldn't set SIGTSTP handler");
        exit(EXIT_FAILURE);
    }

    // https://stackoverflow.com/questions/40098170/handling-sigtstp-signals-in-c
}


/* Signal Handler for SIGINT */
void sig_INT_Handler(int sig_num)
{
    /* Reset handler to catch SIGINT next time.
       Refer http://en.cppreference.com/w/c/program/signal */
    signal(SIGINT, sig_INT_Handler);
    printf("\n Foreground process stopped. Press Enter.\n");
    fflush(stdout);
    return;

    // pid_t pid;
    // kill(pid, 9);
}


void sig_TSTP_Handler(int n)
{
    signal(SIGTSTP, sig_TSTP_Handler);
    printf("\n Foreground process paused. \n");
    pause();
    fflush(stdout);
    return;
}


/* Signal Handler for SIGTSTP */
// void sig_TSTP_Handler(int sig_num)
// {
//     signal(SIGTSTP, sig_TSTP_Handler);
//     printf("\n Foreground process paused. \n");
//     fflush(stdout);

//     pid_t pid;
//     kill(pid, SIGTSTP);
// }


  
// int main ()
// {
//     /* Set the SIGINT (Ctrl-C) signal handler to sigintHandler 
//        Refer http://en.cppreference.com/w/c/program/signal */
//     signal(SIGINT, sigintHandler);
  
//     /* Infinite loop */
//     printf("Sleeping...\n");
//     sleep(100);
//     printf("Finished\n");
//     return 0;
// }