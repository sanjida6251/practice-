#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JUDGES 100
#define MAX_INFO_LEN 512
#define EXPECTED_INFO_ITEMS 7

char judges_array[MAX_JUDGES][MAX_INFO_LEN];

// Count number of commas to verify if the input has correct number of items
int count_commas(const char *str) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ',') count++;
    }
    return count;
}

int main() {
    char project_name[100];
    int total_judges, selected_members;

    printf("####################################\n");
    printf("#      Judge List Data Entry      #\n");
    printf("####################################\n");
    printf("Participating Project: ");
    fgets(project_name, sizeof(project_name), stdin);
    project_name[strcspn(project_name, "\n")] = '\0';

    printf("Total Number of Judges: ");
    scanf("%d", &total_judges);
    getchar();

    printf("Number of Selected Members: ");
    scanf("%d", &selected_members);
    getchar();

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Starting to input information for %d judges.\n", total_judges);
    printf("++++++++++++++++++++++++++++++++++++\n");

    int count = 0;
    while (count < total_judges) {
        printf("Judge %d: ", count + 1);
        fgets(judges_array[count], MAX_INFO_LEN, stdin);
        judges_array[count][strcspn(judges_array[count], "\n")] = '\0';

        if (count_commas(judges_array[count]) != EXPECTED_INFO_ITEMS - 1) {
            printf("The input items are incorrect. Please enter them again.\n");
            continue;
        }

        count++;
    }

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Judge information entry is complete.\n");
    printf("++++++++++++++++++++++++++++++++++++\n");

    char view_response;
    printf("\"Should we check the judge information?\" (Y/N): ");
    scanf(" %c", &view_response);

    if (view_response == 'N') {
        printf("Program terminated.\n");
        return 0;
    }

    printf("[%s] Should we check the judge information? %c\n", project_name, view_response);
    printf("####################################\n");
    printf("#        Display Judge Data        #\n");
    printf("####################################\n");

    for (int i = 0; i < total_judges; i++) {
        char *token;
        char info_copy[MAX_INFO_LEN];
        strcpy(info_copy, judges_array[i]);

        printf("[Judge %d]\n", i + 1);
        token = strtok(info_copy, ",");
        if (token) printf("Name: %s\n", token);
        token = strtok(NULL, ",");
        if (token) printf("Gender: %s\n", token);
        token = strtok(NULL, ",");
        if (token) printf("Affiliation: %s\n", token);
        token = strtok(NULL, ",");
        if (token) printf("Title: %s\n", token);
        token = strtok(NULL, ",");
        if (token) printf("Expertise: %s\n", token);
        token = strtok(NULL, ",");
        if (token) printf("Email: %s\n", token);
        token = strtok(NULL, ",");
        if (token) printf("Phone: %s\n", token);
        printf("-----------------------------------\n");
    }

    return 0;
}
