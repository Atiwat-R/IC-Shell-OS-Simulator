#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "script_mode.c"
#include "external_com.c"
#include "signal_handler.c"
#include "background_job.c"

// Prints out given string
void echo(char word[100]) {
    word = strtok(NULL, " "); // Move away from first token "echo"
    // Prints the rest
    while (word != NULL) {
        printf("%s ", word);
        word = strtok(NULL, " ");
    }
}

// --- UNNECESSARY ---
// // Check if it contains & at the back; indicates a background job
// int is_background_job(char input[100]) {
//     char *all_word = strtok(input, " "); // Split String input by spaces

//     char latest[100];
//     while (all_word != NULL) {
//         strcpy(latest, all_word);
//         // printf("%s\n", latest);
//         all_word = strtok(NULL, " ");
//     }
//     return strcmp(latest, "&");
// }


char lastCommand[100] = ""; // Contains latest commands, bar from keeping !! command.

// Take in a command and execute it. Also update lastCommand.
void processInput(char input[100]) {
    if (strncmp(input, "!!", 2) != 0) strcpy(lastCommand, input); // Updates lastCommand (strcmp(input, "!!\n")

    char input2[100]; // For secondary use
    strcpy(input2, input); 

    char *all_words = strtok(input, " "); // Split String input by spaces. Input is now altered.

    // printf("\n--%c--\n", input2[strlen(input2)-2]);

    // blank or header (starts with #)
    if (isspace(all_words[0]) != 0 || all_words[0] == '#') 
    {
        return; 
    } 

    // Background job
    if (input2[strlen(input2)-2] == '&')
    {
        input2[strlen(input2)-1] = '\0'; // Eliminate \n
        input2[strlen(input2)-2] = '\0'; // Eliminate &

        // char comm[100];
        // strcpy(comm, input2);

        // puts("reached!\n");
        //puts(input2);
        // puts("reached!\n");

        pid_t pid;
        pid = fork(); 
        
        if (pid == 0) execute_bg(input2);

        //kill(pid, SIGKILL);

        // if (pid) { exit(0); }


        // int status;
        // if ( fork() == 0 )
        //     execute_external_com(input2);
        //     return;
    }

    // echo
    else if (strcmp(all_words, "echo") == 0) 
    {
        echo(all_words);
    } 

    // !! double bang, repeat last command.
    else if (strncmp(all_words, "!!", 2) == 0) 
    {
        char comm[100];
        strcpy(comm, lastCommand); // Can't pass lastCommand straight in. Referencing means that lastCommand itself will be modified. Pass a clone instead. 
        printf("->last input: %s", comm);
        processInput(comm);
    }

    // exit with exitcode
    else if (strcmp(all_words, "exit\n") == 0 || strcmp(all_words, "exit") == 0) 
    {
        // int exitcode = atoi(strtok(NULL, " ")); // Turn second string to int
        // printf("\nexited\n");
        // exit(exitcode); // Exit program with given exit code. Use bash command echo $? immediately after termination to see the program's exit code.

        all_words = strtok(NULL, " ");
        printf("\nexited\n");
        if (all_words == NULL) { exit(0); }
        else { exit(atoi(all_words)); }
    }        

    // External commands
    else if (is_external_com(all_words))
    {
        char comm[100];
        strcpy(comm, lastCommand); // Pass in lastCommand, which is still complete, as input is compromised after split
        execute_external_com(comm);
    }
    
    // Bad Command
    else 
    {
        printf("Bad Command\n");
    }
}


// Launch the shell in an Interactive mode
int start() {
    while (1) {
        char *input[100];
        printf("icsh $ ");
        fgets(input, sizeof(input), stdin); // Takes input
        // if (strcmp(&input, "!!\n") != 0) strcpy(lastCommand, &input); // Updates lastCommand
        processInput(&input);
    }
    return 0;
}




int main(int argc, char *argv[]) {

    initiate_sigaction();

    if (argc != 2) { // See number of files: { $ ./icsh note.txt } will make argc = 2
        start(); // Go to interactive mode
    }
    else {
        process_script_mode(argv); // Script mode: read from script and process commands
        start(); // Go to interactive mode afterwards
    }

    return 0;
}



