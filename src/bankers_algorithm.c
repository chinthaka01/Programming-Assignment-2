// bankers_algorithm.c
// Banker's algorithm implementation (C). Reads input from a input file.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NUM_PROCESSES 5
#define NUM_RESOURCES 3

// Function prototypes
void read_input(const char* filename, int available[], int max[][NUM_RESOURCES], 
                int allocation[][NUM_RESOURCES], int need[][NUM_RESOURCES]);
bool is_safe_state(int available[], int max[][NUM_RESOURCES], 
                   int allocation[][NUM_RESOURCES], int need[][NUM_RESOURCES], 
                   int safe_sequence[]);
void print_matrix(const char* name, int matrix[][NUM_RESOURCES], int rows);
void print_array(const char* name, int array[], int size);
void print_usage(const char* program_name);

int main(int argc, char* argv[]) {
    // Check command line arguments
    if (argc != 2) {
        printf("Error: Please provide an input file name.\n\n");
        print_usage(argv[0]);
        return 1;
    }
    
    const char* input_filename = argv[1];
    
    int available[NUM_RESOURCES];
    int max[NUM_PROCESSES][NUM_RESOURCES];
    int allocation[NUM_PROCESSES][NUM_RESOURCES];
    int need[NUM_PROCESSES][NUM_RESOURCES];
    int safe_sequence[NUM_PROCESSES];
    
    // Read input from file
    printf("Reading input from: %s\n", input_filename);
    read_input(input_filename, available, max, allocation, need);
    
    printf("\n=== Banker's Algorithm Implementation ===\n");
    printf("Input File: %s\n\n", input_filename);
    
    // Display the system state
    printf("System State:\n");
    printf("Available resources: ");
    print_array("Available", available, NUM_RESOURCES);
    
    printf("\nMaximum Resource Matrix:\n");
    print_matrix("Max", max, NUM_PROCESSES);
    
    printf("\nAllocation Matrix:\n");
    print_matrix("Allocation", allocation, NUM_PROCESSES);
    
    printf("\nNeed Matrix:\n");
    print_matrix("Need", need, NUM_PROCESSES);
    
    // Check if system is in safe state
    printf("\nChecking system safety...\n");
    if (is_safe_state(available, max, allocation, need, safe_sequence)) {
        printf("\n******************************\n");
        printf("\nThe system is in a SAFE state.\n");
        printf("\nSafe sequence: ");
        for (int i = 0; i < NUM_PROCESSES; i++) {
            printf("P%d", safe_sequence[i]);
            if (i < NUM_PROCESSES - 1) printf(" → ");
        }
        printf("\n");
        printf("\n******************************\n");
        printf("\n");
    } else {
        printf("\n The system is in an UNSAFE state (deadlock possible).\n");
    }
    
    return 0;
}

void read_input(const char* filename, int available[], int max[][NUM_RESOURCES], 
                int allocation[][NUM_RESOURCES], int need[][NUM_RESOURCES]) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open input file '%s'\n", filename);
        printf("Please make sure the file exists in the input/ directory\n");
        exit(1);
    }
    
    // Read available resources
    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (fscanf(file, "%d", &available[i]) != 1) {
            printf("Error: Invalid format in available resources\n");
            fclose(file);
            exit(1);
        }
    }
    
    // Read max matrix
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            if (fscanf(file, "%d", &max[i][j]) != 1) {
                printf("Error: Invalid format in max matrix at P%d\n", i);
                fclose(file);
                exit(1);
            }
        }
    }
    
    // Read allocation matrix
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            if (fscanf(file, "%d", &allocation[i][j]) != 1) {
                printf("Error: Invalid format in allocation matrix at P%d\n", i);
                fclose(file);
                exit(1);
            }
        }
    }
    
    // Calculate need matrix (Need = Max - Allocation)
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    
    fclose(file);
    printf("Successfully read input file: %s\n", filename);
}

bool is_safe_state(int available[], int max[][NUM_RESOURCES], 
                   int allocation[][NUM_RESOURCES], int need[][NUM_RESOURCES], 
                   int safe_sequence[]) {
    int work[NUM_RESOURCES];
    bool finish[NUM_PROCESSES] = {false};
    int safe_count = 0;
    
    // Initialize work = available
    for (int i = 0; i < NUM_RESOURCES; i++) {
        work[i] = available[i];
    }
    
    printf("\nSafety Algorithm Execution:\n");
    printf("Initial Work: ");
    print_array("Work", work, NUM_RESOURCES);
    
    bool found;
    int iterations = 0;
    do {
        found = false;
        for (int i = 0; i < NUM_PROCESSES; i++) {
            if (!finish[i]) {
                // Check if Need[i] <= Work
                bool can_allocate = true;
                for (int j = 0; j < NUM_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                
                if (can_allocate) {
                    printf("P%d can be executed (Need <= Work)\n", i);
                    
                    // Simulate process execution: Work = Work + Allocation[i]
                    for (int j = 0; j < NUM_RESOURCES; j++) {
                        work[j] += allocation[i][j];
                    }
                    
                    finish[i] = true;
                    safe_sequence[safe_count++] = i;
                    found = true;
                    
                    printf("Updated Work: ");
                    print_array("Work", work, NUM_RESOURCES);
                    break;
                }
            }
        }
        iterations++;
        
        // Safety check to prevent infinite loop
        if (iterations > NUM_PROCESSES * 2) {
            printf("Warning: Maximum iterations reached, breaking loop\n");
            break;
        }
    } while (found);
    
    // Check if all processes finished
    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (!finish[i]) {
            return false;
        }
    }
    return true;
}

void print_matrix(const char* name, int matrix[][NUM_RESOURCES], int rows) {
    printf("    A  B  C\n");
    for (int i = 0; i < rows; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < NUM_RESOURCES; j++) {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_array(const char* name, int array[], int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", array[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

void print_usage(const char* program_name) {
    printf("Usage: %s <input_file>\n", program_name);
    printf("\nExamples:\n");
    printf("  %s input/system_state1.txt\n", program_name);
    printf("  %s input/system_state2.txt\n", program_name);
    printf("\nAvailable input files:\n");
    printf("  input/system_state1.txt - Original assignment system state\n");
    printf("  input/system_state2.txt - Alternative system state for testing\n");
}