#include <stdio.h> 


void process_script_mode(char *argv[]) {
    FILE *file = fopen( argv[1], "r" ); 
    if ( file == 0 ) { 
        printf( "Could not open file\n" ); 
    } 
    else  { 
        char line[100] = " ";
        while  ( line != NULL ) { 
            fgets(line, 100, file );
            // printf( "%s", line ); 
            processInput(line);
        } 
        fclose( file ); 
    } 
}




