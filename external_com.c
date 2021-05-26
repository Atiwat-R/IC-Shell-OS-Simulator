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

    input[strlen(input)-1] = '\0'; // Eliminate \n and leave placeholder for NULL
    char extcom_path[100] = "/bin/ls"; // Path to external commands on device
    // strcat(input, " NULLPH"); 

    char *all_words = strtok(input, " "); // Split by spaces

    char *cmd[100];
    int cntr = 0;
    while (all_words != NULL) {
        cmd[cntr] = all_words;
        all_words = strtok(NULL, " ");
        cntr++;
    }
    cmd[cntr] = NULL;

    // size_t n = sizeof(all_words) / sizeof(all_words[0]); // Get array size
    // all_words[n-1] = NULL; // Use n to set last index to NULL


    // // Concat to extcom_path
    // char comm[100];
    // strcpy(comm, all_words);
    // strcat(extcom_path, all_words); 


    int status;
    // char *args[100];

    // args[0] = all_words;        // first arg is the full path to the executable
    // all_words = strtok(NULL, " ");

    // args[1] = all_words; // Rest of the argument, if any
    // args[2] = NULL; // list of args must be NULL terminated

    // while (all_words != NULL) {
    //     printf("->%s\n", all_words);
    //     all_words = strtok(NULL, " ");
    // }
      

    // Fork and Execute external files
    if ( fork() == 0 )
        execv( extcom_path, cmd ); // child: call execv with the path and the args
    else
        wait( &status );        // parent: wait for the child (not really neces>

}

















// int main( void )
// {
//     int status;
//     char *args[3];

//     args[0] = "/bin/ls";        // first arg is the full path to the executable
//     args[1] = "-l";
//     args[2] = NULL; // list of args must be NULL terminated

//     if ( fork() == 0 )
//         execv( args[0], args ); // child: call execv with the path and the args
//     else
//         wait( &status );        // parent: wait for the child (not really neces>

//     return 0;
// }



























