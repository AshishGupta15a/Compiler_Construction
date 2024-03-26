#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASH_SIZE 100

typedef struct Node {
    char* key;
    struct Node* next;
} Node;

typedef struct {
    Node* table[HASH_SIZE];
} HashSet;

unsigned long hash(char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % HASH_SIZE;
}

void insertHashSet(HashSet* set, char* key) {
    unsigned long index = hash(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->next = set->table[index];
    set->table[index] = newNode;
}

int containsHashSet(HashSet* set, char* key) {
    unsigned long index = hash(key);
    Node* list = set->table[index];
    while (list) {
        if (strcmp(list->key, key) == 0) {
            return 1;
        }
        list = list->next;
    }
    return 0;
}

void initHashSet(HashSet* set) {
    for (int i = 0; i < HASH_SIZE; i++) {
        set->table[i] = NULL;
    }
}

char* trim(char* str) {
    char* end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return str;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = 0;
    return str;
}

char* generate_temp(int* temp_count) {
    char* temp_var = (char*)malloc(sizeof(char) * 20);
    sprintf(temp_var, "t%d", (*temp_count)++);
    return temp_var;
}

void compile(char* cpp_code, char** three_address_code, int* code_index, int* temp_count) {
    char* line = strtok(cpp_code, "\n");
    while (line != NULL) {
        line = trim(line);
        if (strlen(line) > 0) {
            if (strstr(line, "asm") != NULL) {
                char* asm_content = strstr(line, "\"") + 1;
                *(strrchr(asm_content, '"')) = 0;
                three_address_code[(*code_index)++] = strdup(asm_content);
            } else if (strstr(line, "FPOS") != NULL) {
                char* var = line + 5;
                char* temp_var = generate_temp(temp_count);
                char* new_line = (char*)malloc(sizeof(char) * 100);
                sprintf(new_line, "%s = -%s", temp_var, var);
                three_address_code[(*code_index)++] = new_line;
            } else if (strstr(line, "FNEN") != NULL) {
                char* var = line + 5;
                char* temp_var = generate_temp(temp_count);
                char* new_line = (char*)malloc(sizeof(char) * 100);
                sprintf(new_line, "%s = %s", temp_var, var);
                three_address_code[(*code_index)++] = new_line;
            } else if (strstr(line, "exit") != NULL) {
                three_address_code[(*code_index)++] = strdup("goto EXIT");
            } else if (strstr(line, "mem_addr") != NULL) {
                char* var = line + 9;
                char* temp_var = generate_temp(temp_count);
                char* new_line = (char*)malloc(sizeof(char) * 100);
                sprintf(new_line, "%s = %p", temp_var, (void*)&var);
                three_address_code[(*code_index)++] = new_line;
            } else {
                three_address_code[(*code_index)++] = strdup(line);
            }
        }
        line = strtok(NULL, "\n");
    }
}

int main() {
    char cpp_code[] = "int a, b, c;\nc = a + b;\nFPOS a;\nexit;\nFNEN -b;\nasm(\"mov $0x1, %eax\");\nmem_addr a;";
    char* three_address_code[100];
    int code_index = 0;
    int temp_count = 0;
    HashSet keywords;
    initHashSet(&keywords);
    insertHashSet(&keywords, "asm");
    insertHashSet(&keywords, "FPOS");
    insertHashSet(&keywords, "FNEN");
    insertHashSet(&keywords, "exit");
    insertHashSet(&keywords, "mem_addr");

    compile(cpp_code, three_address_code, &code_index, &temp_count);

    printf("Three-address code:\n");
    printf("START\n");
    for (int i = 0; i < code_index; i++) {
        printf("%s\n", three_address_code[i]);
    }
    printf("EXIT: \n");

    return 0;
}



