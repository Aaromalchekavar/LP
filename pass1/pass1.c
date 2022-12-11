#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Remove tabs and newlines from a line
void stripTabspacesAndNewLine(char *line) {
    int i = 0;
    while (line[i] != '\0') {
        // replace tab with space
        if (line[i] == '\t') {
            line[i] = ' ';
        }
        i++;
    }

    // remove new line
    if (line[i - 1] == '\n') {
        line[i - 1] = '\0';
    }
}

// To get words in a line "COPY START 1000" should give array [COPY,START,1000]
void getInstructions(char *line, char *instructions[], int *instructionCount) {
    stripTabspacesAndNewLine(line);
    int i = 0;
    // strtok splits the line into words by space
    char *token = strtok(line, " ");
    while (token != NULL) {
        // ommits empty spaces (string of length 0)
        if (strlen(token) > 0) {
            instructions[i] = token;
            i++; // increment word count
        }
        // get next token (word)
        token = strtok(NULL, " "); 
    }

    // set instruction count as word count
    *instructionCount = i;
}

// Write instructions to intermediate file
void writeToFile(char *instructions[], int instructionCount, int address, FILE *file) {
    if (instructionCount == 3) {
        fprintf(file, "%d %s %s %s\n",address, instructions[0], instructions[1], instructions[2]);
    } else if (instructionCount == 2) {
        fprintf(file, "%d %s %s\n",address, instructions[0], instructions[1]);
    } else if (instructionCount == 1) {
        fprintf(file, "%d %s\n",address, instructions[0]);
    } else {
        printf("Invalid instruction count: %d\n", instructionCount);
    }
}

int readOptab(FILE *file, char optab[20][10]) {
    int i = 0;
    char line[100];
    while (fgets(line, 100, file) != NULL) {
        stripTabspacesAndNewLine(line);

        int j = 0;
        while (line[j] != ' ') {
            optab[i][j] = line[j];
            j++;
        }
        optab[i][j] = '\0';
        i++;
    }

    return i;
}

int main() {
    FILE *inputFile, *outputFile, *symTabOutput, *lengthOutput, *optabInput;
    inputFile = fopen("input.txt", "r");
    optabInput = fopen("optab.txt", "r");
    symTabOutput = fopen("symtab.txt", "w");
    outputFile = fopen("output.txt", "w");
    lengthOutput = fopen("length.txt", "w");

    char opcodes[20][10];
    int opcodeCount = readOptab(optabInput, opcodes);

    char line[100];
    int instructionCount;

    char *instructions[3]; // array of instructions (words) in a line 
    fgets(line, 100, inputFile); // read first line
    getInstructions(line, instructions, &instructionCount);

    if (instructionCount != 3) {
        printf("Invalid instruction, START should have name and address\n");
        return 0;
    }

    // write first line to output file (program name and starting address)
    fprintf(outputFile, "%s %s %s\n", instructions[0], instructions[1], instructions[2]);

    int startingAddress = atoi(instructions[2]); // convert string to int
    int address = startingAddress; // get starting address as integer
    while (fgets(line, 100, inputFile)) {
        getInstructions(line, instructions, &instructionCount);
        writeToFile(instructions, instructionCount, address, outputFile);

        char *opCode = instructions[0];
        if (instructionCount > 2) {
            // if instruction is of type "LABEL LDA 1000" (3 words)
            // opcode is at second position
            opCode = instructions[1];

            // write label and address to symbol table
            char *symbol = instructions[0];
            fprintf(symTabOutput, "%d %s\n", address, symbol);
        }

        // increment address by opcode type
        if (strcmp(opCode, "WORD") == 0) {
            address += 3;
        } else if (strcmp(opCode, "RESW") == 0) {
            address += 3 * atoi(instructions[2]);
        } else if (strcmp(opCode, "RESB") == 0) {
            address += atoi(instructions[2]);
        } else if (strcmp(opCode, "BYTE") == 0) {
            address += strlen(instructions[2]) - 2;
        } else if (strcmp(opCode, "END") == 0) {
            break;
        } else {
            for (int i = 0; i < opcodeCount; i++) {
                if (strcmp(opCode, opcodes[i]) == 0) {
                    address += 3;
                    break;
                }
            }
        }
    }

    // write length to length.txt
    fprintf(lengthOutput, "%d", address - startingAddress);
    printf("Completed! symbol table written to symtab.txt, length to length.txt, and output to output.txt\n");
    return 0;
}