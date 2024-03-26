#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h> 
#include <string.h>
#define SIZE 50

char stack[SIZE];		//decalred a char datatype of array
int top = -1;

//defining the Stack
void push(char item)	//declaring the push opeartion
{
    if (top >= SIZE - 1) {
        printf("\nStack Overflow.");
    }
    else {
        top = top + 1;
        stack[top] = item;
    }
}
char pop()				//declariing the pop opeartion
{
    char item;

    if (top < 0) {
        printf("stack under flow: invalid infix expression");
        getchar();
        exit(1);
    }
    else {
        item = stack[top];
        top = top - 1;
        return (item);
    }
}


int a_operator(char symbol)
{
    if (symbol == '^' || symbol == '*' || symbol == '/' || symbol == '+' || symbol == '-') {
        return 1;
    }
    else {
        return 0;
    }
}
int operator_precedence(char symbol)
{
    if (symbol == '^') 
    {
        return (3);
    }
    else if (symbol == '*' || symbol == '/') {
        return (2);
    }
    else if (symbol == '+' || symbol == '-') 
    {
        return (1);
    }
    else {
        return (0);
    }
}


void InfixToPostfix(char infix_exp[], char postfix_exp[])		//function to convert infix expression to postfix expression
{
    int i, j;
    char item;
    char c;
    push('('); 
    strcat(infix_exp, ")"); 
    i = 0;
    j = 0;
    item = infix_exp[i]; 
    while (item != '\0') 
    {
        if (item == '(') {
            push(item);
        }
        else if (isdigit(item) || isalpha(item)) {
            postfix_exp[j] = item; 
            j++;
        }
        else if (a_operator(item) == 1) 
        {
            c = pop();
            while (a_operator(c) == 1 && operator_precedence(c) >= operator_precedence(item)) {
                postfix_exp[j] = c; 
                j++;
                c = pop(); 
            }
            push(c);
            push(item); 
        }
        else if (item == ')') 
        {
            c = pop(); 
            while (c != '(') 
            {
                postfix_exp[j] = c;
                j++;
                c = pop();
            }
        }
        else { 
        
            printf("\nInvalid infix Expression.\n"); 
            getchar();
            exit(1);
        }
        i++;
        item = infix_exp[i]; 
    } 
    if (top > 0) {
        printf("\nInvalid infix Expression.\n"); 
        getchar();
        exit(1);
    }
    if (top > 0) {
        printf("\nInvalid infix Expression.\n");
        getchar();
        exit(1);
    }
    postfix_exp[j] = '\0'; 
}


int main()
{
    char infix[SIZE], postfix[SIZE]; 
    printf("Enter Infix expression : ");
    gets(infix);
    InfixToPostfix(infix, postfix); 
    printf("Postfix Expression: ");
    puts(postfix);
	return 0;
}

