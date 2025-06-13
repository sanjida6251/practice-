#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define TRAINEE_COUNT 4
#define QUESTION_COUNT 10
#define QUIZ_QUESTIONS 5

struct Question {
    int id;
    char content[100];
    char correctAnswer[100];
};

struct Trainee {
    char name[30];
    char nickname[30];
    char nationality[20];
    int score;
    char passStatus;
};

struct QuizAnswer {
    int questionID;
    char correctness;
};

struct Question questionBank[QUESTION_COUNT] = {
    {1, "What is the Korean word for 'Hello'?", "안녕하세요"},
    {2, "What is the Korean word for 'Thank you'?", "감사합니다"},
    {3, "What is the Korean word for 'Yes'?", "네"},
    {4, "What is the Korean word for 'No'?", "아니요"},
    {5, "What is the Korean word for 'Love'?", "사랑"},
    {6, "What is the Korean word for 'Food'?", "음식"},
    {7, "What is the Korean word for 'Water'?", "물"},
    {8, "What is the Korean word for 'Friend'?", "친구"},
    {9, "What is the Korean word for 'Goodbye'?", "안녕히 가세요"},
    {10, "What is the Korean word for 'Family'?", "가족"}
};

struct Trainee trainees[TRAINEE_COUNT] = {
    {"Park Ji-yeon", "Jiyeon", "Korea", 0, 'N'},
    {"Alex Carter", "Alex", "USA", 0, 'N'},
    {"Hana Suzuki", "Hana", "Japan", 0, 'N'},
    {"Liam Chen", "Liam", "Taiwan", 0, 'N'}
};

int isAnswer(int qid, const char *input, struct QuizAnswer *record) {
    int i;
    for (i = 0; i < QUESTION_COUNT; i++) {
        if (questionBank[i].id == qid) {
            record->questionID = qid;
            if (strcmp(input, questionBank[i].correctAnswer) == 0) {
                record->correctness = 'O';
                return 20;
            } else {
                record->correctness = 'X';
                return 0;
            }
        }
    }
    return 0;
}

int selectRandomTakers() {
    int index;
    srand(time(NULL));
    while (1) {
        index = rand() % TRAINEE_COUNT;
        if (strcmp(trainees[index].nationality, "Korea") != 0) {
            printf("Welcome, %s, to the Korean quiz session!\n", trainees[index].name);
            return index;
        }
    }
}

void serveRandomQuiz(int traineeIndex) {
    int used[QUESTION_COUNT] = {0};
    int totalScore = 0;
    int i, qIndex;
    char userAnswer[100];
    struct QuizAnswer answerSheet[QUIZ_QUESTIONS];

    printf("The quiz will begin in 30 seconds. Please prepare...\n");
    sleep(30);

    srand(time(NULL));

    for (i = 0; i < QUIZ_QUESTIONS; i++) {
        do {
            qIndex = rand() % QUESTION_COUNT;
        } while (used[qIndex]);
        used[qIndex] = 1;
        printf("Q%d: %s\n", questionBank[qIndex].id, questionBank[qIndex].content);
        printf("Answer: ");
        scanf(" %[^\n]", userAnswer);
        totalScore += isAnswer(questionBank[qIndex].id, userAnswer, &answerSheet[i]);
    }

    trainees[traineeIndex].score = totalScore;
    trainees[traineeIndex].passStatus = (totalScore >= 80) ? 'Y' : 'N';

    printf("\n=== Quiz Result ===\n");
    for (i = 0; i < QUIZ_QUESTIONS; i++) {
        printf("Q%d: %c\n", answerSheet[i].questionID, answerSheet[i].correctness);
    }
    printf("Total Score: %d\n", totalScore);
    printf("Pass Status: %c\n", trainees[traineeIndex].passStatus);
}

void testKoreanLang() {
    int selectedIndex = selectRandomTakers();
    serveRandomQuiz(selectedIndex);
}
