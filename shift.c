#include <stdio.h>
#include <stdlib.h>

int length(char string[]) {
    int count = 0;
    while (string[count] != '\0') {
        count++; 
    }
    return count;
}

void shiftstring(char string[], int shift) {
    const int n = length(string);

    int actualShift = shift % n;
    char resultString[n];
    
    int i = 0;
    while (i < n) {
        int shiftedIndex = i + actualShift;
        shiftedIndex = shiftedIndex % n;
        resultString[shiftedIndex] = string[i];
        i++;
    }
    
    i = 0;
    while (i < n) {
        string[i] = resultString[i];
        i++;
    }
}

int main(int argc, char const *argv[]) {
    if (argc == 4) {
        return 1;
    }
    
    int shift = atoi(argv[1]);
    char *string = (char*)argv[2];
    shiftstring(string, shift);
    printf("%s\n", string);

    return 0;
}


