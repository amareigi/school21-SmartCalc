#ifndef S21_SMARTCALC_H
#define S21_SMARTCALC_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack {
  double number;
  int operation;
  int priority;
  struct stack *next;
} Stack;

typedef struct creditpay {
  double payment;
  double last_pay;
  double overpayment;
  double total;
} Creditpay;

// STACK
void Push(Stack **head, double number, int operation, int priority);
void Pop(Stack **head);
double parser(char *str, double x);
double calculate_bin(double a, double b, int op);
double calculate_trig(double a, int op);
int priorityCalc(int i);
double evaluete(Stack **stackNum, Stack **stackOp, int i);
void push_and_pop(Stack **stackNum, Stack **stackOp, double *res, int op);
int check_input(char *str);
int check_function(char *str, int *i);

// CREDIT
Creditpay Credit(double sum, int time, double perc);
Creditpay Credit2(double sum, int time, double perc);

#endif
