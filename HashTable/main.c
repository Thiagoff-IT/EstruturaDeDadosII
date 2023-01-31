#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct Node {
  char *key;
  int value;
  struct Node *next;
} Node;

Node *hash_table[TABLE_SIZE];

unsigned long hash(char *str) {
  unsigned long hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;

  return hash % TABLE_SIZE;
}

void insert(char *key, int value) {
  unsigned long index = hash(key);
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->key = strdup(key);
  new_node->value = value;
  new_node->next = hash_table[index];
  hash_table[index] = new_node;
}

int search(char *key) {
  unsigned long index = hash(key);
  Node *node = hash_table[index];

  while (node) {
    if (strcmp(node->key, key) == 0)
      return node->value;
    node = node->next;
  }

  return -1;
}

void remove_key(char *key) {
  unsigned long index = hash(key);
  Node *node = hash_table[index];
  Node *prev = NULL;

  while (node) {
    if (strcmp(node->key, key) == 0) {
      if (prev)
        prev->next = node->next;
      else
        hash_table[index] = node->next;
      free(node->key);
      free(node);
      break;
    }
    prev = node;
    node = node->next;
  }
}
