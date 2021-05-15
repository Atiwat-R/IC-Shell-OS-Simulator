#include <stdio.h>
#include <string.h>
#include "script_mode.c"

// Prints out given string
void echo(char word[100]) {
    word = strtok(NULL, " "); // Move away from first token "echo"
    // Prints the rest
    while (word != NULL) {
        printf("%s ", word);
        word = strtok(NULL, " ");
    }
}


char lastCommand[100] = ""; // Contains latest commands, bar from keeping !! command.

// Take in a command and execute it. Also update lastCommand.
void processInput(char input[100]) {
    if (strncmp(input, "!!", 2) != 0) strcpy(lastCommand, input); // Updates lastCommand (strcmp(input, "!!\n")
    char *all_words = strtok(input, " "); // Split String input by spaces

    // printf("\n--%s--\n", all_words);

    // blank or header (starts with #)
    if (isspace(all_words[0]) != 0 || all_words[0] == '#') 
    {
        return;
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
        int exitcode = atoi(strtok(NULL, " ")); // Turn second string to int
        printf("\nexited\n");
        exit(exitcode); // Exit program with given exit code. Use bash command echo $? immediately after termination to see the program's exit code.
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

    if (argc != 2) { // See number of files: { $ ./icsh note.txt } will make argc = 2
        start(); // Go to interactive mode
    }
    else {
        process_script_mode(argv); // Read from script and process commands
        start(); // Go to interactive mode afterwards
    }

    return 0;
}



