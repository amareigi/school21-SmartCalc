#include "s21_smartcalc.h"

void Push(Stack **head, double number, int operation, int priority) {
  Stack *tmp = ((Stack *)calloc(255, sizeof(Stack)));
  tmp->number = number;
  tmp->operation = operation;
  tmp->priority = priority;
  tmp->next = *head;
  *head = tmp;
}

void Pop(Stack **head) {
  if (*head != NULL) {
    Stack *tmp = *head;
    *head = (*head)->next;
    free(tmp);
    tmp = NULL;
  }
}

double calculate_bin(double a, double b, int op) {
  double result = 0;
  switch (op) {
    case 1:
      result = a + b;
      break;
    case 2:
      result = a - b;
      break;
    case 3:
      result = a * b;
      break;
    case 4:
      result = a / b;
      break;
    case 5:
      result = fmod(a, b);
      break;
    case 6:
      result = pow(a, b);
      break;
  }
  return result;
}

double calculate_trig(double a, int op) {
  double result = 0;
  switch (op) {
    case 7:
      result = cos(a);
      break;
    case 8:
      result = sin(a);
      break;
    case 9:
      result = tan(a);
      break;
    case 10:
      result = acos(a);
      break;
    case 11:
      result = asin(a);
      break;
    case 12:
      result = atan(a);
      break;
    case 13:
      result = sqrt(a);
      break;
    case 14:
      result = log(a);
      break;
    case 15:
      result = log10(a);
      break;
  }
  return result;
}

double parser(char *str, double x) {
  const char *operations[15] = {"+",    "-",    "*",    "/",   "mod",
                                "^",    "cos",  "sin",  "tan", "acos",
                                "asin", "atan", "sqrt", "ln",  "log"};
  double res = 0;
  Stack *stackNum = NULL;
  Stack *stackOp = NULL;
  int unary = 1;
  while (*str) {
    if (isdigit(*str)) {
      double num = strtod(str, &str);
      Push(&stackNum, num, 0, 0);
      res = stackNum->number;
      unary = 0;

    } else if (*str == ' ' || *str == '\t' || *str == '\n') {
      str++;
    } else if (*str == '(') {
      Push(&stackOp, 0, 16, 0);
      str++;

      if (*str == '-' || *str == '+') {
        unary = 1;
      }
    } else if (*str == ')') {
      while (stackOp->operation != 16) {
        if (stackOp->operation <= 6) {
          res = calculate_bin((stackNum)->next->number, (stackNum)->number,
                              (stackOp)->operation);
          Pop(&stackNum);
          Pop(&stackNum);
          Pop(&stackOp);
          Push(&stackNum, res, 0, 0);
        } else if (stackOp->operation > 6 && stackOp->operation <= 15) {
          res = calculate_trig((stackNum)->number, (stackOp)->operation);
          Pop(&stackNum);
          Pop(&stackOp);
          Push(&stackNum, res, 0, 0);
        }
      }
      Pop(&stackOp);
      str++;
    } else if (*str == 'x') {
      Push(&stackNum, x, 0, 0);
      res = stackNum->number;
      str++;
      unary = 0;
    } else {
      for (int i = 0; i < 15; i++) {
        if (!strncmp(str, operations[i], strlen(operations[i]))) {
          if (unary && (i <= 1)) {
            Push(&stackNum, 0, 0, 0);
            unary = 0;
          }
          res = evaluete(&stackNum, &stackOp, i + 1);
          str += strlen(operations[i]);
          break;
        }
      }
    }

    // if(test) {
    // unary--;
    // test--;
    // }
  }

  while (stackOp) {
    push_and_pop(&stackNum, &stackOp, &res, stackOp->operation);
  }
  Pop(&stackNum);
  return res;
}

void push_and_pop(Stack **stackNum, Stack **stackOp, double *res, int op) {
  if (*stackNum != NULL && *stackOp != NULL) {
    if (op >= 1 && op < 7 && (*stackNum)->next != NULL) {
      *res = calculate_bin((*stackNum)->next->number, (*stackNum)->number,
                           (*stackOp)->operation);
      Pop(stackNum);
      Pop(stackNum);
      Pop(stackOp);
      Push(stackNum, *res, 0, 0);
    } else if (op >= 7 && op <= 15) {
      *res = calculate_trig((*stackNum)->number, (*stackOp)->operation);
      Pop(stackNum);
      Pop(stackOp);
      Push(stackNum, *res, 0, 0);
    }
  }
}

double evaluete(Stack **stackNum, Stack **stackOp,
                int i) {  // обработка приоритетов
  double res = 0;
  if ((*stackOp) == NULL) {
    Push(stackOp, 0, i, priorityCalc(i));
  } else if ((*stackOp)->priority < priorityCalc(i) ||
             (*stackOp)->operation == 6) {
    Push(stackOp, 0, i, priorityCalc(i));
  } else if ((*stackOp)->priority >= priorityCalc(i)) {
    if (((*stackOp)->operation < 7 && (*stackNum)->next != NULL) ||
        (*stackOp)->operation > 6) {
      while ((*stackOp) != NULL && (priorityCalc(i) <= (*stackOp)->priority)) {
        push_and_pop(stackNum, stackOp, &res, (*stackOp)->operation);
      }
    }
    Push(stackOp, 0, i, priorityCalc(i));
  }
  return res;
}

int priorityCalc(int i) {
  return ((i == 1 || i == 2)             ? 1
          : (i == 3 || i == 4 || i == 5) ? 2
          : (i == 6)                     ? 3
                                         : 4);
}

int check_function(char *str, int *i) {
  int r = 0;
  if (strstr(str + *i, "ln")) {
    r = str[*i + 1];
    *i += 1;
  } else if (strstr(str + *i, "acos") || strstr(str + *i, "asin") ||
             strstr(str + *i, "atan") || strstr(str + *i, "sqrt")) {
    r = str[*i + 2];
    *i += 3;
  } else if (strstr(str + *i, "mod") || strstr(str + *i, "cos") ||
             strstr(str + *i, "tan") || strstr(str + *i, "sin") ||
             strstr(str + *i, "log")) {
    r = str[*i];
    *i += 2;
  } else {
    *i = -2;
  }
  return r;
}

int check_input(char *str) {
  int err = 0;
  int bracket_check = 0;
  if (strlen(str) == 0 || strchr(")*/^.", str[0]) ||
      strchr("(+-*/^", str[strlen(str) - 1])) {
    err = 1;
  } else {
    for (int i = 0; str[i] != '\0' && i >= 0; i++) {
      if (!strchr("1234567890()+-*/^mcstalx.", str[i])) {
        i = -2;
      } else {
        if (strchr(".", str[i])) {
          if ((!strchr("1234567890", str[i - 1]) ||
               !strchr("1234567890", str[i + 1]) || !str[i + 1] ||
               !str[i - 1])) {
            i = -2;
          } else {
            int count = 0;
            for (int k = i + 1; strchr("1234567890.", str[k]); k++) {
              if (str[k] == '.') count++;
            }
            if (count > 0) i = -2;
          }
        }
        if (strchr("-+*/^", str[i]) &&
            (!strchr("1234567890(cstalx", str[i + 1]) || !str[i + 1] ||
             !str[i - 1])) {
          i = -2;
        }
        if (strchr("x", str[i]) && !strchr("+-*/^)", str[i + 1])) {
          i = -2;
        }
        if (strchr("m", str[i])) {
          check_function(str, &i);
          if (!strchr("1234567890(x", str[i + 1]) || !str[i + 1] ||
              (!strchr("1234567890)x", str[i - 3]) || !str[i - 3]))
            i = -2;
        }
        if (strchr("cstal", str[i])) {
          check_function(str, &i);
          if (!strchr("1234567890(x", str[i + 1]) || !str[i + 1]) i = -2;
        }
        if (str[i] == '(') {
          if (str[i + 1] == ')' || strchr("^/*.", str[i + 1])) {
            i = -2;
          }
          bracket_check++;
        }
        if (str[i] == ')') bracket_check--;
      }
      if (i < 0) {
        err = 1;
      }
    }
    if (bracket_check != 0) err = 1;
  }
  return err;
}
