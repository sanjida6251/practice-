#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRAINEES 16
#define MAX_MENTORS 8
#define NAME_LENGTH 50

// Trainee list (Millieway)
const char *trainees[MAX_TRAINEES] = {
    "Eunbi", "Jisoo", "Minho", "Yuna", "Taemin", "Sana", "Doyoung", "Irene",
    "Seungmin", "Nayeon", "Mark", "Hyunjin", "Joy", "Haechan", "Ryujin", "Felix"
};

// Mentor structure
typedef struct {
    int id;
    char name[NAME_LENGTH];
    int traineeIndex;
} Mentor;

// Global arrays
Mentor mentors[MAX_MENTORS];
int traineeScore[MAX_TRAINEES];
int traineeCode[MAX_TRAINEES];

// === Helper Functions ===

// Convert name to ASCII sum
int getAsciiSum(const char *name) {
    int sum = 0;
    while (*name) {
        sum += *name;
        name++;
    }
    return sum;
}

// Get random ability score
int getRandomScore() {
    return rand() % 901 + 100; // 100 to 1000
}

// Initialize trainee data
void setupTrainees() {
    for (int i = 0; i < MAX_TRAINEES; i++) {
        traineeCode[i] = getAsciiSum(trainees[i]);
        traineeScore[i] = getRandomScore();
    }
}

// Input mentor names
void registerMentors() {
    printf("\n[ Mentor Registration ]\n");
    for (int i = 0; i < MAX_MENTORS; i++) {
        printf("Enter name for Mentor %d: ", i + 1);
        fgets(mentors[i].name, NAME_LENGTH, stdin);
        mentors[i].name[strcspn(mentors[i].name, "\n")] = '\0'; // remove newline
        mentors[i].id = i + 1;
        mentors[i].traineeIndex = -1;
    }
}

// Assign trainees to mentors using modulo logic
void assignMentors() {
    for (int i = 0; i < MAX_TRAINEES; i++) {
        int slot = i % MAX_MENTORS;

        // Ensure 1:1 (bonus)
        while (mentors[slot].traineeIndex != -1) {
            slot = (slot + 1) % MAX_MENTORS;
        }

        mentors[slot].traineeIndex = i;
    }
}

// Show all mentor-mentee pairs
void showMatches() {
    printf("\n[ Mentor-Trainee Matching Result ]\n");
    for (int i = 0; i < MAX_MENTORS; i++) {
        if (mentors[i].traineeIndex != -1) {
            int t = mentors[i].traineeIndex;
            printf("Mentor %d (%s) -> Trainee %d (%s)\n",
                   mentors[i].id, mentors[i].name, t + 1, trainees[t]);
        }
    }
}

// Main menu entry for Stage 2 mentoring
void runStage2Mentoring() {
    srand(time(NULL));
    setupTrainees();
    registerMentors();
    assignMentors();
    showMatches();
}
