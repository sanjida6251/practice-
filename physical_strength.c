#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_MEMBERS 5
#define DAYS 6
#define EXERCISE_LEN 100

// Member info
char *milliways_names[MAX_MEMBERS] = {"Goeun", "Woncheol", "Youngjin", "Hyekyung", "Arthur"};
char *milliways_nicknames[MAX_MEMBERS] = {"G", "W", "Y", "H", "A"};

// Days of week
char *weekdays[DAYS] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Exercise categories
char *exercise_types[5] = {
    "Cardio: Running, Cycling, Fast Walking",
    "Full-body Strength: Push-ups, Squats",
    "Lower-body Strength: Leg Press, Leg Curl",
    "Upper-body Strength: Pull-ups, Chin-ups",
    "Core Strength: Plank, Crunches"
};

// Member workout routines (1D flattened: [member][day])
char member_routine[MAX_MEMBERS * DAYS][EXERCISE_LEN];

// Show members
void displayMemberList() {
    printf("\n-- Milliways Members --\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("%d. %s (%s)\n", i + 1, milliways_names[i], milliways_nicknames[i]);
    }
}

// Set basic workout routine
void setExerciseRoutine() {
    int member;
    displayMemberList();
    printf("Select a member (1-%d): ", MAX_MEMBERS);
    scanf("%d", &member);
    getchar();

    if (member < 1 || member > MAX_MEMBERS) {
        printf("Invalid member.\n");
        return;
    }
    member--;

    int core_used = 0;

    printf("\n-- Exercise Options --\n");
    for (int i = 0; i < 5; i++) {
        printf("%d. %s\n", i + 1, exercise_types[i]);
    }

    for (int d = 0; d < DAYS; d++) {
        printf("\n%s - Choose 2 exercises (e.g. 1,2):\n", weekdays[d]);
        char input[20];
        int e1 = 0, e2 = 0;
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d,%d", &e1, &e2);

        if (e1 < 1 || e1 > 5 || e2 < 1 || e2 > 5 || e1 == e2) {
            printf("Invalid selection. Try again.\n");
            d--;
            continue;
        }

        int has_cardio = (e1 == 1 || e2 == 1);
        int has_strength_or_core = (e1 > 1 || e2 > 1);
        int has_core = (e1 == 5 || e2 == 5);

        if (!has_cardio || !has_strength_or_core) {
            printf("Must include 1 cardio + 1 strength/core. Try again.\n");
            d--;
            continue;
        }

        if (has_core) {
            if (core_used) {
                printf("Core exercise already used once this week. Try again.\n");
                d--;
                continue;
            } else {
                core_used = 1;
            }
        }

        int idx = member * DAYS + d;
        snprintf(member_routine[idx], EXERCISE_LEN, "%s / %s", exercise_types[e1 - 1], exercise_types[e2 - 1]);
    }

    printf("\n✅ Routine saved for %s (%s)\n", milliways_names[member], milliways_nicknames[member]);
}

// View basic workout routine
void getExerciseRoutine() {
    int member;
    displayMemberList();
    printf("Select a member (1-%d): ", MAX_MEMBERS);
    scanf("%d", &member);
    getchar();

    if (member < 1 || member > MAX_MEMBERS) {
        printf("Invalid member.\n");
        return;
    }
    member--;

    printf("\n-- %s (%s)'s Workout Routine --\n", milliways_names[member], milliways_nicknames[member]);
    for (int d = 0; d < DAYS; d++) {
        int idx = member * DAYS + d;
        if (member_routine[idx][0] != '\0') {
            printf("%s: %s\n", weekdays[d], member_routine[idx]);
        } else {
            printf("%s: Not set\n", weekdays[d]);
        }
    }
}
