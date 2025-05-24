#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CANDIDATE_COUNT 6
#define STRING_SIZE 100

// Structure to store each candidate's info
struct member_info {
    char name[STRING_SIZE];
    char dob[11];  // Format: YYYY/MM/DD
    char gender;
    char email[STRING_SIZE];
    char nationality[STRING_SIZE];
    float bmi;
    char primary_skill[STRING_SIZE];
    char secondary_skill[STRING_SIZE];
    int topik_level;
    char mbti[5];
    char introduction[256];
};

// Function to calculate age from birthdate string
int calculate_age(const char *dob) {
    int year, month, day;
    sscanf(dob, "%d/%d/%d", &year, &month, &day);

    time_t t = time(NULL);
    struct tm *now = localtime(&t);
    int age = now->tm_year + 1900 - year;
    if (now->tm_mon + 1 < month || (now->tm_mon + 1 == month && now->tm_mday < day)) {
        age--;
    }
    return age;
}

int main() {
    struct member_info candidate01, candidate02, candidate03, candidate04, candidate05, candidate06;
    struct member_info *candidates[CANDIDATE_COUNT] = {
        &candidate01, &candidate02, &candidate03, &candidate04, &candidate05, &candidate06
    };

    char group_name[STRING_SIZE];

    printf("####################################\n");
    printf("     Audition Candidate Data Entry\n");
    printf("####################################\n");
    printf("Enter Audition Group Name: ");
    fgets(group_name, STRING_SIZE, stdin);
    group_name[strcspn(group_name, "\n")] = '\0'; // Remove newline

    int i = 0;
    while (i < CANDIDATE_COUNT) {
        printf("\nEntering information for candidate %d in group %s.\n", i + 1, group_name);
        printf("---------------------------------\n");

        printf("1. Name: ");
        fgets(candidates[i]->name, STRING_SIZE, stdin);
        candidates[i]->name[strcspn(candidates[i]->name, "\n")] = '\0';

        printf("2. Date of Birth (YYYY/MM/DD): ");
        fgets(candidates[i]->dob, 11, stdin);
        getchar(); // Consume newline left over from input

        printf("3. Gender (F/M): ");
        scanf(" %c", &candidates[i]->gender);
        getchar();

        printf("4. Email: ");
        fgets(candidates[i]->email, STRING_SIZE, stdin);
        candidates[i]->email[strcspn(candidates[i]->email, "\n")] = '\0';

        printf("5. Nationality: ");
        fgets(candidates[i]->nationality, STRING_SIZE, stdin);
        candidates[i]->nationality[strcspn(candidates[i]->nationality, "\n")] = '\0';

        printf("6. BMI: ");
        scanf("%f", &candidates[i]->bmi);
        getchar();

        printf("7. Primary Skill: ");
        fgets(candidates[i]->primary_skill, STRING_SIZE, stdin);
        candidates[i]->primary_skill[strcspn(candidates[i]->primary_skill, "\n")] = '\0';

        printf("8. Secondary Skill: ");
        fgets(candidates[i]->secondary_skill, STRING_SIZE, stdin);
        candidates[i]->secondary_skill[strcspn(candidates[i]->secondary_skill, "\n")] = '\0';

        printf("9. Korean Proficiency Level (TOPIK): ");
        scanf("%d", &candidates[i]->topik_level);
        getchar();

        printf("10. MBTI: ");
        fgets(candidates[i]->mbti, 5, stdin);
        candidates[i]->mbti[strcspn(candidates[i]->mbti, "\n")] = '\0';
        getchar();

        printf("11. Introduction: ");
        fgets(candidates[i]->introduction, 256, stdin);
        candidates[i]->introduction[strcspn(candidates[i]->introduction, "\n")] = '\0';

        i++;
    }

    printf("\n####################################\n");
    printf("     Audition Candidate Data Review\n");
    printf("####################################\n");
    printf("Group: %s\n", group_name);
    printf("=============================================================================================\n");
    printf("Name (Age)     | DOB       | Gender | Email                 | Nationality | BMI  | Primary Skill | Secondary Skill      | TOPIK     | MBTI |\n");
    printf("=============================================================================================\n");

    for (int j = 0; j < CANDIDATE_COUNT; j++) {
        int age = calculate_age(candidates[j]->dob);
        printf("%-13s (%2d) | %8s |   %c    | %-21s | %-11s | %-4.1f | %-13s | %-20s | %-9s | %-4s |\n",
               candidates[j]->name,
               age,
               candidates[j]->dob,
               candidates[j]->gender,
               candidates[j]->email,
               candidates[j]->nationality,
               candidates[j]->bmi,
               candidates[j]->primary_skill,
               candidates[j]->secondary_skill,
               candidates[j]->topik_level == 0 ? "Native" : (candidates[j]->topik_level == 1 ? "Beginner" : (candidates[j]->topik_level == 2 ? "Elementary" : (candidates[j]->topik_level == 3 ? "Intermediate" : "Advanced"))),
               candidates[j]->mbti);

        printf("---------------------------------------------------------------------------------------------\n");
        printf("%s\n", candidates[j]->introduction);
        printf("---------------------------------------------------------------------------------------------\n");
    }

    return 0;
}
