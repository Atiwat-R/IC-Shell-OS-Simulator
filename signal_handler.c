#include <stdio.h>
#include <string.h>
#include <signal.h>
#define SIGTSTP 18


/* Signal Handler for SIGINT */
void sig_INT_Handler(int sig_num)
{
    /* Reset handler to catch SIGINT next time.
       Refer http://en.cppreference.com/w/c/program/signal */
    signal(SIGINT, sig_INT_Handler);
    printf("\n Foreground process stopped. Press Enter.\n");
    fflush(stdout);

    // pid_t pid;
    // kill(pid, 9);
}

/* Signal Handler for SIGTSTP */
// void sig_TSTP_Handler(int sig_num)
// {
//     signal(SIGTSTP, sig_TSTP_Handler);
//     printf("\n Foreground process paused. \n");
//     fflush(stdout);

//     // pid_t pid;
//     // kill(pid, SIGTSTP);
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