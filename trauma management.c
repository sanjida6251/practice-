#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MEMBERS 8
#define MAX_TRAUMA_LEN 200
#define MAX_RESPONSE_LEN 101
#define MAX_QUESTIONS 5
#define MAX_SESSIONS 24

// Dummy structure from previous assignment
typedef struct {
    char nickname[20];
    int age;
} Trainee;

// Trauma Info
typedef struct {
    char nickname[20];
    int age;
    char trauma[MAX_TRAUMA_LEN];
} TraumaInfo;

// Counseling Questions (read-only)
typedef struct {
    int id;
    char content[100];
} CounselingQuestion;

// Counseling Session Responses
typedef struct {
    char nickname[20];
    char question[100];
    char response[MAX_RESPONSE_LEN];
} CounselingSession;

// Global Data Arrays
TraumaInfo traumaList[MAX_MEMBERS];
int traumaCount = 0;

const CounselingQuestion questionList[MAX_QUESTIONS] = {
    {1, "In what situations have you experienced this trauma?"},
    {2, "How has this situation affected your daily life and emotions?"},
    {3, "How have you tried to overcome this trauma?"},
    {4, "What emotions do you associate with this trauma?"},
    {5, "What kind of support do you think is necessary to overcome this trauma?"}
};

CounselingSession sessions[MAX_SESSIONS];
int sessionCount = 0;

void inputTrauma(Trainee members[], int memberCount) {
    char nickname[20];
    char trauma[MAX_TRAUMA_LEN];
    int found = 0;

    while (1) {
        printf("Enter nickname (or '0' to exit): ");
        scanf("%s", nickname);
        if (strcmp(nickname, "0") == 0) break;

        found = 0;
        for (int i = 0; i < memberCount; i++) {
            if (strcmp(members[i].nickname, nickname) == 0) {
                printf("Enter trauma description: ");
                getchar(); // clear newline
                fgets(trauma, MAX_TRAUMA_LEN, stdin);
                trauma[strcspn(trauma, "\n")] = '\0';

                strcpy(traumaList[traumaCount].nickname, nickname);
                traumaList[traumaCount].age = members[i].age;
                strcpy(traumaList[traumaCount].trauma, trauma);
                traumaCount++;
                found = 1;
                break;
            }
        }

        // Ternary operator usage
        found ? printf("Trauma saved.\n") : printf("Nickname not found.\n");
    }
}

void conductCounseling() {
    if (traumaCount == 0) {
        printf("No trauma records available.\n");
        return;
    }

    printf("Members with trauma:\n");
    for (int i = 0; i < traumaCount; i++) {
        printf("%d. %s\n", i + 1, traumaList[i].nickname);
    }

    int choice;
    printf("Select member (number): ");
    scanf("%d", &choice);
    if (choice < 1 || choice > traumaCount) return;

    TraumaInfo *selected = &traumaList[choice - 1];
    printf("Counseling session for %s\n", selected->nickname);

    int selectedQuestions[3];
    int count = 0;

    srand(time(NULL));
    while (count < 3) {
        int r = rand() % MAX_QUESTIONS;
        int duplicate = 0;
        for (int j = 0; j < count; j++)
            if (selectedQuestions[j] == r)
                duplicate = 1;
        if (!duplicate) selectedQuestions[count++] = r;
    }

    getchar(); // flush newline
    for (int i = 0; i < 3; i++) {
        char response[MAX_RESPONSE_LEN];
        int qid = selectedQuestions[i];

        while (1) {
            printf("Q%d: %s\n> ", i + 1, questionList[qid].content);
            fgets(response, MAX_RESPONSE_LEN, stdin);
            response[strcspn(response, "\n")] = '\0';
            if (strlen(response) == 0 || strlen(response) >= MAX_RESPONSE_LEN - 1)
                printf("Invalid input. Try again.\n");
            else break;
        }

        strcpy(sessions[sessionCount].nickname, selected->nickname);
        strcpy(sessions[sessionCount].question, questionList[qid].content);
        strcpy(sessions[sessionCount].response, response);
        sessionCount++;
    }

    printf("Counseling for %s completed.\n", selected->nickname);
}

void viewCounseling() {
    char nickname[20];
    printf("Enter nickname to view counseling: ");
    scanf("%s", nickname);

    int found = 0;
    for (int i = 0; i < traumaCount; i++) {
        if (strcmp(traumaList[i].nickname, nickname) == 0) {
            printf("Nickname: %s\n", nickname);
            printf("Trauma: %s\n", traumaList[i].trauma);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No such member found.\n");
        return;
    }

    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessions[i].nickname, nickname) == 0) {
            printf("\nQ: %s\nA: %s\n", sessions[i].question, sessions[i].response);
        }
    }
}

void overcomeTrauma(Trainee members[], int memberCount) {
    char choice;
    while (1) {
        printf("\n[Trauma Management Menu]\n");
        printf("A. Input Trauma\nB. Start Counseling\nC. View Counseling\n0. Back\n");
        printf("Select option: ");
        scanf(" %c", &choice);

        switch (toupper(choice)) {
            case 'A': inputTrauma(members, memberCount); break;
            case 'B': conductCounseling(); break;
            case 'C': viewCounseling(); break;
            case '0': return;
            default: printf("Invalid option.\n");
        }
    }
}

// Example usage in Stage 1 Menu
void stage1Menu(Trainee members[], int memberCount) {
    char choice;
    while (1) {
        printf("\n[Stage I: Training Menu]\n");
        printf("1. Fitness Tracking\n");
        printf("2. Basic Workout\n");
        printf("3. Trauma Management\n");
        printf("0. Back\n");
        printf("Select an option: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1': /* fitnessTracking(members, memberCount); */ break;
            case '2': /* basicWorkout(members, memberCount); */ break;
            case '3': overcomeTrauma(members, memberCount); break;
            case '0': return;
            default: printf("Invalid option.\n");
        }
    }
}
