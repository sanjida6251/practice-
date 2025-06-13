#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define STAGES 8

// Training stage names
const char *training_stages[STAGES] = {
    "1. Physical Strength & Knowledge",
    "2. Self-Management & Teamwork",
    "3. Language & Pronunciation",
    "4. Vocal",
    "5. Dance",
    "6. Visual & Image",
    "7. Acting & Stage Performance",
    "8. Fan Communication"
};

char training_results[STAGES] = {0}; // 0 = not attempted, 'P' = pass, 'F' = fail

void audition_management() {
    printf("[Audition Management Selected]\n");
    // Placeholder for future functionality
}

void debut() {
    printf("[Debut Selected]\n");
    // Placeholder for future functionality
}

int is_stage_available(int stage) {
    if (training_results[stage] != 0) return 0; // already attempted
    if (stage >= 2) {
        return training_results[0] == 'P' && training_results[1] == 'P';
    }
    return 1;
}

void training() {
    while (1) {
        printf("\n--- Training Menu ---\n");
        for (int i = 0; i < STAGES; i++) {
            printf("%s [%c]\n", training_stages[i], training_results[i] ? training_results[i] : ' ');
        }
        printf("Select training stage (1-8) or Q to return: ");

        char input[10];
        fgets(input, sizeof(input), stdin);

        if (input[0] == 'Q' || input[0] == 'q' || input[0] == '0' || input[0] == '\n') {
            return;
        }

        int stage = input[0] - '1';
        if (stage < 0 || stage >= STAGES) {
            printf("Invalid input. Try again.\n");
            continue;
        }

        if (!is_stage_available(stage)) {
            printf("Stage not available (either already completed or prerequisites not met).\n");
            continue;
        }

        printf("Would you like to enter the evaluation result? (Y/N): ");
        fgets(input, sizeof(input), stdin);
        if (toupper(input[0]) != 'Y') continue;

        printf("Did you complete the training and pass the certification? (Y/N): ");
        fgets(input, sizeof(input), stdin);
        training_results[stage] = (toupper(input[0]) == 'Y') ? 'P' : 'F';
    }
}

void main_menu() {
    while (1) {
        printf("\n=== Magrathea System Main Menu ===\n");
        printf("I. Audition Management\n");
        printf("II. Training\n");
        printf("III. Debut\n");
        printf("Enter your choice (1-3), or Q/0 to quit: ");

        char input[10];
        fgets(input, sizeof(input), stdin);

        if (input[0] == 'Q' || input[0] == 'q' || input[0] == '0' || input[0] == '\n') {
            printf("Exiting...\n");
            break;
        }

        switch (input[0]) {
            case '1':
                audition_management();
                break;
            case '2':
                training();
                break;
            case '3':
                debut();
                break;
            default:
                printf("Invalid selection. Try again.\n");
        }
    }
}

int main() {
    main_menu();
    return 0;
}
