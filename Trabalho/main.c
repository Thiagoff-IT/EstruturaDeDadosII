#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 128

struct word_count {
    char word[MAX_WORD_LENGTH];
    int count;
};

int compare_word_count(const void *a, const void *b) {
    struct word_count *wa = (struct word_count *)a;
    struct word_count *wb = (struct word_count *)b;
    return wb->count - wa->count;
}

void index_document(const char *filepath, struct word_count *word_counts, int *word_count_size) {
    FILE *file = fopen(filepath, "r");
    if (!file) {
        fprintf(stderr, "Failed to open file %s\n", filepath);
        return;
    }

    char word[MAX_WORD_LENGTH];
    int word_length = 0;
    int c;
    while ((c = fgetc(file)) != EOF) {
        if (isalpha(c)) {
            word[word_length++] = tolower(c);
        } else if (word_length > 0) {
            word[word_length] = '\0';
            word_length = 0;
            int i;
            for (i = 0; i < *word_count_size; i++) {
                if (strcmp(word_counts[i].word, word) == 0) {
                    word_counts[i].count++;
                    break;
                }
            }
            if (i == *word_count_size) {
                strcpy(word_counts[i].word, word);
                word_counts[i].count = 1;
                (*word_count_size)++;
            }
        }
    }

    fclose(file);
    qsort(word_counts, *word_count_size, sizeof(struct word_count), compare_word_count);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <command> <file> [<file>...]\n", argv[0]);
        return 1;
    }

    const char *command = argv[1];
    if (strcmp(command, "--freq") == 0) {
        int n = atoi(argv[2]);
        if (argc < 4) {
            fprintf(stderr, "Usage: %s %s <n> <file> [<file>...]\n", argv[0], command);
            return 1;
        }
        struct word_count word_counts[n];
        int word_count_size = 0;
        for (int i = 3; i < argc; i++) {
            index_document(argv[i], word_counts, &word_count_size);
        }
                int i = 0;
        while (i < n && i < word_count_size) {
            printf("%s: %d\n", word_counts[i].word, word_counts[i].count);
            i++;
        }
    } else if (strcmp(command, "--freq-word") == 0) {
        const char *word = argv[2];
        if (argc != 4) {
            fprintf(stderr, "Usage: %s %s <word> <file>\n", argv[0], command);
            return 1;
        }
        struct word_count word_counts[1];
        int word_count_size = 0;
        index_document(argv[3], word_counts, &word_count_size);
        for (int i = 0; i < word_count_size; i++) {
            if (strcmp(word_counts[i].word, word) == 0) {
                printf("%s: %d\n", word, word_counts[i].count);
                break;
            }
        }
    } else if (strcmp(command, "--search") == 0) {
        const char *term = argv[2];
        if (argc < 4) {
            fprintf(stderr, "Usage: %s %s <term> <file> [<file>...]\n", argv[0], command);
            return 1;
        }
        struct word_count *word_counts = malloc(sizeof(struct word_count) * argc);
        int *word_count_sizes = malloc(sizeof(int) * argc);
        int term_counts[argc];
        memset(term_counts, 0, sizeof(term_counts));
        for (int i = 3; i < argc; i++) {
            index_document(argv[i], &word_counts[i], &word_count_sizes[i]);
            for (int j = 0; j < word_count_sizes[i]; j++) {
                if (strcmp(word_counts[i][j].word, term) == 0) {
                    term_counts[i] = word_counts[i][j].count;
                    break;
                }
            }
        }
        for (int i = 3; i < argc; i++) {
            for (int j = i + 1; j < argc; j++) {
                if (term_counts[j] > term_counts[i]) {
                    int temp = term_counts[i];
                    term_counts[i] = term_counts[j];
                    term_counts[j] = temp;
                    char *temp_file = argv[i];
                    argv[i] = argv[j];
                    argv[j] = temp_file;
                }
            }
        }
        for (int i = 3; i < argc; i++) {
            if (term_counts[i] > 0) {
                printf("%s: %d\n", argv[i], term_counts[i]);
            }
        }
        free(word_counts);
        free(word_count_sizes);
    } else {
        fprintf(stderr, "Invalid command: %s\n", command);
        return 1;
    }

    return 0;
}

