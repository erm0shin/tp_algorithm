#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct node {
    char symbol;
    node* next;
} Node;

class Stack {
public:
    Stack();
    ~Stack();
    void push(char input);
    char pop();
    bool is_empty();
    int get_size() {return size;}
private:
    Node *head;
    int size;
};

Stack::Stack() {
    head = NULL;
    size = 0;
}

Stack::~Stack() {
    Node *tmp = NULL;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        delete tmp;
    }
    size = 0;
}

bool Stack::is_empty() {
    return (size == 0);
}

void Stack::push(char input) {
    Node *tmp = new Node;
    tmp->symbol = input;
    tmp->next = head;
    head = tmp;
    size++;
}

char Stack::pop() {
    Node *tmp = head;
    char result = tmp->symbol;
    head = head->next;
    delete tmp;
    size--;
    return result;
}

void work(char *seq, int n, char * &result) {
    Stack open;
    Stack close;
    for (int i = 0; i < n; i++) {
        if ((seq[i] == '(') || (seq[i] == '[') || (seq[i] == '{'))
            open.push(seq[i]);
        if (seq[i] == ')' || seq[i] == ']' || seq[i] == '}')
            if (open.is_empty())
                close.push(seq[i]);
            else {
                char tmp = open.pop();
                if ((seq[i] == ')' && tmp != '(') || (seq[i] == ']' && tmp != '[') || (seq[i] == '}' && tmp != '{')) {
                    result = new char [11];
                    strcat(result, "IMPOSSIBLE");
                    return;
                }
            }
    }
    int new_size = close.get_size() + open.get_size() + n;
    result = new char[new_size];
    int i = 0;
    while (!close.is_empty()) {
        char tmp = close.pop();
        switch (tmp) {
            case ']': tmp = '['; break;
            case ')': tmp = '('; break;
            case '}': tmp = '{'; break;
        }
        result[i] = tmp;
        i++;
    }
    strcat(result, seq);
    i += strlen(seq);
    while (!open.is_empty()) {
        char tmp = open.pop();
        switch (tmp) {
            case '[': tmp = ']'; break;
            case '(': tmp = ')'; break;
            case '{': tmp = '}'; break;
        }
        result[i] = tmp;
        i++;
    }
    result[i] = '\0';
    return;
}

int main() {
    char *sequence = new char[200001];
    scanf("%s", sequence);
    int n = strlen(sequence) + 1;
    //realloc(sequence, n);
    char *result = NULL;
    work(sequence, n, result);
    printf("%s\n",result);
    delete [] sequence;
    delete [] result;
    return 0;
}