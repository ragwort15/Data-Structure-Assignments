#include <stdio.h>
#include<string.h>
#include <stdlib.h>

//if total number of aruguments are missing(program name being the 1st argument, < or > 5) 
int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Use this format: %s -n 1,2,3,4,5 -f filename.txt\n", argv[0]);
        return 1;
    }
    // manually creating a my_numbers.txt file using file pointer
    FILE *file_pointer; 
    file_pointer = fopen("my_numbers.txt", "w");

    fprintf(file_pointer, "3 4 5 2 1\n");
    fprintf(file_pointer, "3 5 13 18 20\n");
    fprintf(file_pointer, "1 2 3 4 5\n");
    fclose(file_pointer);
    

    // declaring two strings to hold the number n arguments and the file name argument
    char *numbers_arg = NULL;
    char *file_arg = NULL;

    //loop is used for the command line argumemts and compares with -n and -f using strcmp()
    //if it finds -n it will store in the next argument (numbers_arg) and if it finds -f it will store in the next argument (file_arg)
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0) {
            numbers_arg = argv[i + 1];
        } else if (strcmp(argv[i], "-f") == 0) {
            file_arg = argv[i + 1];
        }
    }

    if (numbers_arg == NULL || file_arg == NULL) {
        printf("Either numbers argument or file name is missing\n");
        return 1;
    }
    // the given input as string is separated by , using strtok, converts string to ineteger
    int input[5];
    int i = 0;
    char *token = strtok(numbers_arg, ",");
    while (token != NULL && i < 5) {
        input[i] = atoi(token);
        token = strtok(NULL, ",");
        i++;
    }
    // check for error condition, whether the file is null 
    FILE *file = fopen(file_arg, "r");
    if (file == NULL) {
        printf("Could not open file.\n");
        return 1;
    }

    int matches[6] = {0}; // counts number of lines which have exactly 6 number of matches with the input 
    int lines[6][100]; // stores the line number which had 6 matches.
    int counts[6] = {0};// number of lines stored

    char line[100]; //stores one line from the file
    int line_num = 0; // counts on the line we are on.

    // reads each line from the file using fgets and extracts 5 integers, if not found then skip the line
    while (fgets(line, sizeof(line), file)) {
        int nums[5];
        int read = sscanf(line, "%d %d %d %d %d", &nums[0], &nums[1], &nums[2], &nums[3], &nums[4]);
        if (read != 5) continue;

        int match = 0;
        for (int a = 0; a < 5; a++) {
            for (int b = 0; b < 5; b++) {
                if (input[a] == nums[b]) {
                    match++;
                    break;
                }
            }
        }

        matches[match]++; // no.of numbers matched in the current line from the input
        lines[match][counts[match]] = line_num; //store the current line number in buffer, at the next position
        counts[match]++; //Updates the count of how many line numbers we’ve stored in this match group
        line_num++; // increment the line number for next iteration
    }

    fclose(file);

    for (int k = 5; k >= 0; k--) {
        if (matches[k] > 0) {
            printf("%d (", k);
            for (int j = 0; j < counts[k]; j++) {
                printf("%d", lines[k][j]);
                if (j < counts[k] - 1) printf(",");
            }
            printf(")\n");
        }
    }

    return 0;
}
