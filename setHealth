#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_MEMBERS 5
#define MAX_TESTS 7

// Member data (1D arrays)
char *milliways_names[MAX_MEMBERS] = {"Hyekyung", "Goeun", "Woncheol", "Youngjin", "Arthur"};
char *milliways_nicknames[MAX_MEMBERS] = {"Hye", "Goe", "Wonc", "YJ", "Art"};

// Fitness test names
char *fitness_tests[MAX_TESTS] = {
    "1-Mile Run (min)",
    "Speed Sprint (sec)",
    "Push-ups (min)",
    "Squats (min)",
    "Arm Strength (min)",
    "Swimming (min)",
    "Weightlifting (xBW)"
};

// Scores stored as flattened 2D array (1D)
float health_scores[MAX_MEMBERS * MAX_TESTS];

// Utility to get member index by nickname
int get_member_index_by_nickname(const char *nickname) {
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(milliways_nicknames[i], nickname) == 0) {
            return i;
        }
    }
    return -1;
}

// Set fitness data
void setHealth() {
    char input[256];
    printf("\n[Enter Fitness Data] Format: Nickname,Test1,...,Test7\n");

    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("Input for %s (%s): ", milliways_names[i], milliways_nicknames[i]);
        if (!fgets(input, sizeof(input), stdin)) return;
        input[strcspn(input, "\n")] = 0;

        char *token = strtok(input, ",");
        int index = get_member_index_by_nickname(token);
        if (index == -1) {
            printf("Invalid nickname. Try again.\n");
            i--;
            continue;
        }

        for (int j = 0; j < MAX_TESTS; j++) {
            token = strtok(NULL, ",");
            if (!token) {
                printf("Missing values. Try again.\n");
                i--;
                break;
            }
            health_scores[index * MAX_TESTS + j] = atof(token);
        }
    }

    printf("✅ Fitness data recorded.\n");
}

// View fitness data
void getHealth() {
    char input[64];
    printf("\n[View Fitness Data]\n");
    printf("1. View All\n2. View One Member\n3. View One Test\nSelect: ");

    if (!fgets(input, sizeof(input), stdin)) return;

    if (input[0] == '1') {
        for (int i = 0; i < MAX_MEMBERS; i++) {
            printf("\n%s (%s):\n", milliways_names[i], milliways_nicknames[i]);
            for (int j = 0; j < MAX_TESTS; j++) {
                printf("  %s: %.2f\n", fitness_tests[j], health_scores[i * MAX_TESTS + j]);
            }
        }

    } else if (input[0] == '2') {
        printf("Enter nickname: ");
        if (!fgets(input, sizeof(input), stdin)) return;
        input[strcspn(input, "\n")] = 0;

        int i = get_member_index_by_nickname(input);
        if (i == -1) {
            printf("Member not found.\n");
            return;
        }

        printf("\n%s (%s):\n", milliways_names[i], milliways_nicknames[i]);
        for (int j = 0; j < MAX_TESTS; j++) {
            printf("  %s: %.2f\n", fitness_tests[j], health_scores[i * MAX_TESTS + j]);
        }

    } else if (input[0] == '3') {
        printf("Enter nickname: ");
        if (!fgets(input, sizeof(input), stdin)) return;
        input[strcspn(input, "\n")] = 0;
        int i = get_member_index_by_nickname(input);
        if (i == -1) {
            printf("Member not found.\n");
            return;
        }

        printf("Enter test number (1-7): ");
        if (!fgets(input, sizeof(input), stdin)) return;
        int t = atoi(input) - 1;

        if (t < 0 || t >= MAX_TESTS) {
            printf("Invalid test number.\n");
            return;
        }

        printf("%s (%s) - %s: %.2f\n",
               milliways_names[i], milliways_nicknames[i], fitness_tests[t], health_scores[i * MAX_TESTS + t]);

    } else {
        printf("Invalid selection.\n");
    }
}

// Menu for Physical Strength & Knowledge
void physical_strength_menu() {
    char input[10];
    while (1) {
        printf("\n--- Stage 1: Physical Strength & Knowledge ---\n");
        printf("A. Enter Fitness Data\n");
        printf("B. View Fitness Data\n");
        printf("Q. Back to Training Menu\n");
        printf("Select option: ");

        if (!fgets(input, sizeof(input), stdin)) return;
        input[0] = toupper(input[0]);

        switch (input[0]) {
            case 'A': setHealth(); break;
            case 'B': getHealth(); break;
            case 'Q': return;
            default: printf("Invalid input.\n"); break;
        }
    }
}

// Main function for test
int main() {
    physical_strength_menu();  // For standalone test
    return 0;
}
