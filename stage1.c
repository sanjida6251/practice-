#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function declarations
void show_main_menu();
void show_training_menu();
void audition_management();
void debut();
void training_stage(int stage_num, char *stage_name, char *stage_status);

// Constants
#define TOTAL_STAGES 8

// Global arrays
char *stage_names[TOTAL_STAGES] = {
    "Physical Strength & Knowledge",
    "Self-Management & Teamwork",
    "Language & Pronunciation",
    "Vocal",
    "Dance",
    "Visual & Image",
    "Acting & Stage Performance",
    "Fan Communication"
};

char stage_status[TOTAL_STAGES]; // P = Passed, F = Failed, ' ' = Not attempted

// Helper to flush input
void flush_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Main function
int main() {
    // Initialize stage_status with spaces
    for (int i = 0; i < TOTAL_STAGES; i++) {
        stage_status[i] = ' ';
    }

    show_main_menu();
    return 0;
}

void show_main_menu() {
    char input[10];

    while (1) {
        printf("\n=== Main Menu ===\n");
        printf("1. Audition Management\n");
        printf("2. Training\n");
        printf("3. Debut\n");
        printf("Enter option (0/Q to quit): ");

        if (!fgets(input, sizeof(input), stdin)) break;
        if (input[0] == '\n' || input[0] == '0' || tolower(input[0]) == 'q') {
            printf("Exiting program.\n");
            break;
        }

        switch (input[0]) {
            case '1':
                audition_management();
                break;
            case '2':
                show_training_menu();
                break;
            case '3':
                debut();
                break;
            default:
                printf("Invalid input. Try again.\n");
        }
    }
}

void show_training_menu() {
    char input[10];

    while (1) {
        printf("\n=== Training Menu ===\n");
        for (int i = 0; i < TOTAL_STAGES; i++) {
            printf("%d. %s [%c]\n", i + 1, stage_names[i], stage_status[i] == ' ' ? '-' : stage_status[i]);
        }
        printf("Enter stage number to proceed (0 to return): ");

        if (!fgets(input, sizeof(input), stdin)) break;
        if (input[0] == '0') return;

        int choice = atoi(input);
        if (choice < 1 || choice > TOTAL_STAGES) {
            printf("Invalid stage selection.\n");
            continue;
        }

        // Enforce training rules
        if (choice == 1 || choice == 2) {
            if (choice == 2 && stage_status[0] != 'P') {
                printf("You must pass Stage 1 before attempting Stage 2.\n");
                continue;
            }
        } else {
            if (stage_status[1] != 'P') {
                printf("You must pass Stages 1 and 2 before attempting other stages.\n");
                continue;
            }
        }

        if (stage_status[choice - 1] == 'P') {
            printf("Stage %d has already been passed.\n", choice);
            continue;
        }

        training_stage(choice, stage_names[choice - 1], &stage_status[choice - 1]);
    }
}

void training_stage(int stage_num, char *stage_name, char *status) {
    char input[10];

    printf("\n-- %s --\n", stage_name);
    printf("Would you like to enter the evaluation result? (Y/N): ");
    if (!fgets(input, sizeof(input), stdin)) return;
    if (toupper(input[0]) != 'Y') return;

    printf("Did you complete the training and pass the certification? (P/F): ");
    if (!fgets(input, sizeof(input), stdin)) return;
    char result = toupper(input[0]);

    if (result == 'P' || result == 'F') {
        *status = result;
        printf("Stage %d result recorded as '%c'.\n", stage_num, result);
    } else {
        printf("Invalid result. Only 'P' or 'F' are accepted.\n");
    }
}

void audition_management() {
    printf("\n[Audition Management Placeholder]\n");
    // Add real logic here
}

void debut() {
    printf("\n[Debut Placeholder]\n");
    // Add real logic here
}

