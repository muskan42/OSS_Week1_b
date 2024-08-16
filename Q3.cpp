#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 1000
#define MAX_WORDS 100

typedef struct {
    char word[100];
    int count;
} WordCount;

void toLowerCase(char *str);
void countWordFrequencies(char *paragraph, WordCount *wordCounts, int *wordCount);
void printFrequencies(WordCount *wordCounts, int wordCount);

int main() {
    char paragraph[MAX_LEN];
    WordCount wordCounts[MAX_WORDS];
    int wordCount = 0;

    printf("Enter a paragraph (end with a single '.' on a new line):\n");

    char buffer[MAX_LEN];
    while (fgets(buffer, sizeof(buffer), stdin)) {
        if (strcmp(buffer, ".\n") == 0) break;
        strcat(paragraph, buffer);
    }
    
    toLowerCase(paragraph);
    countWordFrequencies(paragraph, wordCounts, &wordCount);
    printFrequencies(wordCounts, wordCount);

    return 0;
}

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void countWordFrequencies(char *paragraph, WordCount *wordCounts, int *wordCount) {
    char *token = strtok(paragraph, " \t\n.,;:!?");
    
    while (token != NULL) {
        int found = 0;
        for (int i = 0; i < *wordCount; i++) {
            if (strcmp(wordCounts[i].word, token) == 0) {
                wordCounts[i].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(wordCounts[*wordCount].word, token);
            wordCounts[*wordCount].count = 1;
            (*wordCount)++;
        }
        token = strtok(NULL, " \t\n.,;:!?");
    }
}

void printFrequencies(WordCount *wordCounts, int wordCount) {
    printf("Word frequencies:\n");
    for (int i = 0; i < wordCount; i++) {
        printf("%s: %d\n", wordCounts[i].word, wordCounts[i].count);
    }
}
