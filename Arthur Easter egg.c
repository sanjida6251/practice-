#include <stdio.h>
#include <string.h>

/* Define Arthur's trauma struct */
struct ArthurTrauma {
    char keyword[8];
    char message[300];
};

/* Global instance of the trauma */
struct ArthurTrauma arthur = {
    "specter",
    "I confess. After graduating from university, I was blinded by the arrogance of starting a startup and recklessly blocked my friends' paths. "
    "I painfully learned that when I am the only one convinced by my idea, it leads to disastrous results. "
    "The past Arthur was a ghost of dogmatism and stubbornness."
};

/* Print binary of keyword characters in reverse order */
void printReversedBinary(const char *keyword) {
    int i, j;
    for (i = 6; i >= 0; i--) {
        unsigned char c = keyword[i];
        for (j = 7; j >= 0; j--) {
            putchar((c >> j) & 1 ? '1' : '0');
        }
        putchar('\n');
    }
}

/* Check if user entered characters match reversed keyword */
int isRightChar(const char *keyword, const char *input) {
    int i;
    for (i = 6; i >= 0; i--) {
        if (keyword[i] != input[6 - i]) {
            return 0;
        }
    }
    return 1;
}

/* Check if final word is the correct keyword */
int isEasterEgg(const char *input) {
    return strcmp(input, arthur.keyword) == 0;
}

/* Arthur's Easter Egg sequence */
void find_easter_egg() {
    char input_chars[8];
    char final_word[8];

    printf("<<Arthur's Easter Egg>>\n");
    printReversedBinary(arthur.keyword);

    while (1) {
        printf("Enter the 7 characters in reverse binary order: ");
        scanf("%7s", input_chars);

        if (isRightChar(arthur.keyword, input_chars)) {
            printf("Good! Now enter the combined word: ");
            scanf("%7s", final_word);

            if (isEasterEgg(final_word)) {
                printf("##Easter Egg Discovered!$$\n");
                printf("%s\n", arthur.message);
            } else {
                printf("Incorrect final word. Returning to menu.\n");
            }
            return;
        } else {
            printf("Incorrect characters. Try again.\n");
        }
    }
}

/* (Optional Bonus) Scramble keyword and print reversed binary */
void scramble_and_convert_keyword(const char *keyword) {
    char scrambled[8];
    int i, j = 0;

    // odd indices
    for (i = 1; i < 7; i += 2)
        scrambled[j++] = keyword[i];
    // even indices
    for (i = 0; i < 7; i += 2)
        scrambled[j++] = keyword[i];

    scrambled[7] = '\0';

    printf("Scrambled keyword: %s\n", scrambled);
    printReversedBinary(scrambled);
}

/* Integrate in Stage 2 menu */
void self_management_and_teamwork() {
    char name_input[20];

    printf("[II. Training > 2. Self-Management and Teamwork]\n");
    printf("Enter your name: ");
    scanf("%19s", name_input);

    if (strcmp(name_input, "Arthur") == 0) {
        find_easter_egg();
    } else {
        printf("Proceeding with regular Self-Management and Teamwork logic...\n");
        // Your regular stage 2 logic here
    }
}
