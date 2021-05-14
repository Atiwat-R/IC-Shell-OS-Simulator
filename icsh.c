#include <stdio.h>
#include <string.h>


char lastCommand[100] = "";

void echo(char word[100]) {
    word = strtok(NULL, " "); // Move away from first token "echo"
    // Prints the rest
    while (word != NULL) {
        printf("%s ", word);
        word = strtok(NULL, " ");
    }
}

void processInput(char input[100]) {
    char *all_words = strtok(input, " "); // Split String input by spaces
    /////////////////// printf("\n-%s-\n", all_words); // For testing

    // blank
    if (strcmp(all_words, "\n") == 0) 
    {
        return;
    } 
    // echo
    else if (strcmp(all_words, "echo") == 0) 
    {
        echo(all_words);
    } 
    // !! double bang, repeat last command.
    else if (strcmp(all_words, "!!\n") == 0) 
    {
        char comm[100];
        strcpy(comm, lastCommand); // Can't pass lastCommand straight in. Referencing means that lastCommand itself will be modified. Pass a clone instead. 
        printf("last input: %s", comm);
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



int start() {
    while (1) {
        char *input[100];
        printf("icsh $ ");
        fgets(input, sizeof(input), stdin); // Takes input
        if (strcmp(&input, "!!\n") != 0) strcpy(lastCommand, &input); // Updates lastCommand
        processInput(&input);

    }
    return 0;
}



int main() {

    char argv[100] = "!!";
    start();
    // printf("-%s-", strtok(argv, " "));
    // printf("\n- %d -\n", strcmp(argv, "!!"));
    return 0;
}



