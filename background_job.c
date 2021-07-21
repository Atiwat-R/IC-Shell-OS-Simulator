#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>


void execute_bg(char input[100]) {

    // input[strlen(input)-1] = '\0'; // Eliminate \n
    // input[strlen(input)-2] = '\0'; // Eliminate &
    char *all_words = strtok(input, " "); // Split by spaces

    //puts(input);

    //processInput(input);

    char extcom_path[100] = "/bin/"; // Path to external commands on device
    strcat(extcom_path, all_words);  // Specify the file on /bin/

    // // Create argv, an array of string, holding command arguments.  
    char *argv[100];
    int cntr = 0;
    while (all_words != NULL) {
        argv[cntr] = all_words;
        all_words = strtok(NULL, " ");
        cntr++;
    }
    argv[cntr] = NULL;

    execvp( extcom_path, argv ); // child: call execv with the path and the args




}





















