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


// int main ( int argc, char *argv[] ) // argc is number of files, including this one.
// { 
//     if ( argc != 2 ) /* argc should be 2 for ./a.out and filename.txt */ 
//     { 
//         printf( "usage: %s is provided,filename is not provided", argv[0] ); 
//     } 
//     else  
//     { 
//         FILE *file = fopen( argv[1], "r" ); 
//         if ( file == 0 ) 
//         { 
//             printf( "Could not open file\n" ); 
//         } 
//         else  
//         { 
//             int x; 
//             while  ( ( x = fgetc( file ) ) != EOF ) 
//             { 
//                 printf( "%c", x ); 
//             } 
//             fclose( file ); 
//         } 
//     } 
// } 

