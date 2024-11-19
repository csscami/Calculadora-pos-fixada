#include "expressao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_STACK 100
#define PI 3.14159265358979323846

typedef struct {
    float items[MAX_STACK];
    int top;
} FloatStack;

typedef struct {
    char items[MAX_STACK][512];
    int top;
} StringStack;

void initFloatStack(FloatStack *s) {
    s->top = -1;
}

void initStringStack(StringStack *s) {
    s->top = -1;
}

void pushFloat(FloatStack *s, float value) {
    if (s->top < MAX_STACK - 1) {
        s->items[++(s->top)] = value;
    }
}

float popFloat(FloatStack *s) {
    if (s->top >= 0) {
        return s->items[(s->top)--];
    }
    return 0.0f;
}

void pushString(StringStack *s, char *value) {
    if (s->top < MAX_STACK - 1) {
        strcpy(s->items[++(s->top)], value);
    }
}

char* popString(StringStack *s) {
    if (s->top >= 0) {
        return s->items[(s->top)--];
    }
    return "";
}

int isOperator(char *token) {
    return (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
            strcmp(token, "*") == 0 || strcmp(token, "/") == 0 ||
            strcmp(token, "^") == 0 || strcmp(token, "raiz") == 0 ||
            strcmp(token, "sen") == 0 || strcmp(token, "cos") == 0 ||
            strcmp(token, "tg") == 0 || strcmp(token, "log") == 0);
}

float applyOperator(float a, float b, char *op) {
    if (strcmp(op, "+") == 0) return a + b;
    if (strcmp(op, "-") == 0) return a - b;
    if (strcmp(op, "*") == 0) return a * b;
    if (strcmp(op, "/") == 0) return a / b;
    if (strcmp(op, "^") == 0) return powf(a, b);
    return 0.0f;
}

float applyFunction(float a, char *func) {
    if (strcmp(func, "raiz") == 0) return sqrtf(a);
    if (strcmp(func, "sen") == 0) return sinf(a * PI / 180.0f);
    if (strcmp(func, "cos") == 0) return cosf(a * PI / 180.0f);
    if (strcmp(func, "tg") == 0) return tanf(a * PI / 180.0f);
    if (strcmp(func, "log") == 0) return log10f(a);
    return 0.0f;
}

float getValor(char *Str) {
    FloatStack stack;
    initFloatStack(&stack);
    
    char *token = strtok(Str, " ");
    while (token != NULL) {
        if (isOperator(token)) {
            if (strcmp(token, "raiz") == 0 || strcmp(token, "sen") == 0 ||
                strcmp(token, "cos") == 0 || strcmp(token, "tg") == 0 ||
                strcmp(token, "log") == 0) {
                float a = popFloat(&stack);
                pushFloat(&stack, applyFunction(a, token));
            } else {
                float b = popFloat(&stack);
                float a = popFloat(&stack);
                pushFloat(&stack, applyOperator(a, b, token));
            }
        } else {
            pushFloat(&stack, atof(token));
        }
        token = strtok(NULL, " ");
    }
    
    return popFloat(&stack);
}

char* getFormaInFixa(char *Str) {
    static char result[512];
    StringStack operandStack;
    initStringStack(&operandStack);

    char *token = strtok(Str, " ");
    while (token != NULL) {
        if (isOperator(token)) {
            char operand1[512], operand2[512], temp[512];
            strcpy(operand2, popString(&operandStack));
            strcpy(operand1, popString(&operandStack));
            
            if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
                strcmp(token, "*") == 0 || strcmp(token, "/") == 0 || 
                strcmp(token, "^") == 0) {
                sprintf(temp, "(%s %s %s)", operand1, token, operand2);
            } else {
                sprintf(temp, "%s(%s)", token, operand2);
            }
            
            pushString(&operandStack, temp);
        } else {
            pushString(&operandStack, token);
        }
        
        token = strtok(NULL, " ");
    }
    
    strcpy(result, popString(&operandStack));
    return result;
}