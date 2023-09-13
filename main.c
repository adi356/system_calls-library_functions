/**
 * @file main.c
 * @author Andrew Irvine (adi356@umsystem.edu)
 * @brief main file to run application, contains logic for command line arguments & reversing input
 * @version 0.1
 * @date 2023-09-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "stack.h"

void check_filePrint(int);

int main(int argc, char **argv) {
    char *inputFile;
    char *outputFile;
    int x; //will be used to hold value of getopt
    int childCount; //corresponds to first line in input file (#number of sets/ child processes to be generated)

    char line[LINE_MAX];

    pid_t child_pid;

    //set names to default -> given in project requirements
    inputFile = "input.dat";
    outputFile = "output.dat";

    FILE *inputStream;
    FILE *outputStream;

    opterr = 0;

    //command line arguments logic
    //!TODO: getting weird output when calling -h
    while((x = getopt(argc, argv, "hi:o:")) != -1) {
        switch(x) {
            case 'h':
                printf("%s\n\t%s\n\t%s\n\t%s",
                    "The available options for this application include:",
                    "-h: Display help menu (this page)",
                    "i: Add input file -> 'reverse -i [file]'",
                    "-o: Add output file -> 'reverse -o [filename]'");
                break;

            case 'i':
                inputFile = optarg;
                break;

            case 'o':
                outputFile = optarg;
                break;
            
            case '?':
                if (optopt == 'i')
                    fprintf(stderr, "Option -i requires an argument");
                else if (optopt == 'o')
                    fprintf(stderr, "Option -o requires an argument");
                else if (isprint(optopt) == 1)
                    fprintf(stderr, "Unknown option `-%c'\n", optopt);
                else 
                    fprintf (stderr, "Unknown option character `\\x%x'\n", optopt);
                return 1;
            default: 
                fprintf(stderr, "Uknown argument error \n");
                printf("Argument error: Type 'reverse -h' for help");
                abort();
        }
    }

    //reading and writing logic for input and output
    inputStream = fopen(inputFile, "r");
    outputStream = fopen(outputFile, "w+");
    if(inputStream == NULL) {
        perror(inputFile);
        return -1;
    }

    if(fgets(line, LINE_MAX, inputStream) == NULL) {
        fprintf(stderr, "File %s contains no text", inputFile);
        fclose(inputStream);
        return 2;
    }



    childCount = atoi(line);

    int *pids = malloc(sizeof(int) * childCount);

    //Logic for the actual forking of processes and reversing of input
    for(int i = 0; i < childCount; i++) {
        fgets(line, LINE_MAX, inputStream);
        if(fork() == 0) {
            //create stack to hold variables that need to be reversed
            Stack stack = createStack(&stack, atoi(line));

            //sizeof gives us the expected string length
            fgets(line, sizeof(line), inputStream);

            char* token = strtok(line, " ");

            //!TODO: having problem here
            while(token != NULL) {
                stack.push(&stack, atoi(token));
                token = strtok(NULL, " ");
            }

            check_filePrint(fprintf(outputStream, "%d: ", getpid()));

            while(stack.size != -1) {
                check_filePrint(fprintf(outputStream, "%d ", stack.pop(&stack)));
            }

            check_filePrint(fprintf(outputStream, "\n"));

            exit(0);
        } else {
        //putting pids here so they can be displayed later
        pids[i] = wait(0);
    }
    fgets(line, LINE_MAX, inputStream);
    } 

    check_filePrint(fprintf(outputStream, "All childred were: "));

    //print child pids
    for(int x = 0; x < childCount; x++) {
        check_filePrint(fprintf(outputStream, "%d ", pids[x]));
    }
    check_filePrint(fprintf(outputStream, "\n"));
    fclose(outputStream);
    return (0);
}

void check_filePrint(int testInput) {
    if(testInput < 0) {
        perror("Failed to write to outputSream: ");
    }
}