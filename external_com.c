#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


// File that kept the list of external commands
char extcom_list[] = "all_external_com.txt";

// Check whether input is an external command or not. Return 1 if yes, 0 if no.
int is_external_com(char input[100]) {
    char *word = strtok(input, "\n"); // Clean out the "\n"
    FILE *file = fopen( extcom_list, "r" ); 
    int ans = 0;
    if ( file == 0 ) { 
        printf( "Cannot open %s\n", extcom_list ); 
    } 
    else  { 
        char line[100] = " ";
        while  ( fgets(line, 100, file ) != NULL ) { 
            // printf( "%s", line );  // print files in dir
            if (strcmp(word, strtok(line, "\n")) == 0) {  // Compare word and line, both had "\n" removed
                ans++;
                break;
            }
        } 
        fclose( file ); 
    } 
    return ans;
}



// Execute external command
void execute_external_com(char input[100]) {

    input[strlen(input)-1] = '\0'; // Eliminate \n
    char *all_words = strtok(input, " "); // Split by spaces

    char extcom_path[100] = "/bin/"; // Path to external commands on device
    strcat(extcom_path, all_words);  // Specify the file on /bin/

    // Create argv, an array of string, holding command arguments.  
    char *argv[100];
    int cntr = 0;
    while (all_words != NULL) {
        argv[cntr] = all_words;
        all_words = strtok(NULL, " ");
        cntr++;
    }
    argv[cntr] = NULL;

    // Fork and Execute
    int status;
    if ( fork() == 0 )
        execv( extcom_path, argv ); // child: call execv with the path and the args
    else
        wait( &status );        // parent: wait for the child (not really necessary)

}



    // char* arr[] = {"ls", "-l", "-a", "-i", NULL};
    // execv("/bin/ls", arr);






















