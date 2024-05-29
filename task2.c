/*
 ============================================================================
 Задание 2. Обратная польская запись
 Написать алгоритм перевода из инфиксной записи в обратную польскую.
 Для его реализации нужны данные по приоритетам операций.
 Реализовать алгоритм, используя побитовые операции (&, |, ^).

 Пример №1
 Данные на вход: ( 3 & 5 ) ^ 4 | 9
 Данные на выход: 3 5 & 4 ^ 9 |

 Пример №2
 Данные на вход: 8 ^ 2 & 5 | ( 6 & 1 )
 Данные на выход: 8 2 5 & ^ 6 1 & |
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 255
#define STACK_SIZE 255

char oper[STACK_SIZE] = { 0 }; // стек для операций + - * / ( )
int oend = 0; // заполненность стека

void push(char v) {
	oper[oend++] = v;
}

char pop() {
	if (oend <= 0 || oend >= BUFFER_SIZE) {
		fprintf(stderr, "Stack overflow\n");
		exit(1);
	}
	return oper[--oend];
}

_Bool emptyStack() {
	return oend == 0;
}

_Bool isOperator(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/'
			|| c == '|' || c == '^' || c == '&';
}

int priority(char c) {
	if (c == '|')
		return 1;
	if (c == '^')
		return 2;
	if (c == '&')
		return 3;
	if (c == '+' || c == '-')
		return 5;
	if (c == '*' || c == '/' || c == '%')
		return 6;
	return 0;
}

void inputCharArray(char arr[], int len) {
	int i = 0;
	char c;
	while ((c = getchar()) != '\n')
		arr[i++] = c;
	arr[i] = '\0';
}

int main(void) {
	char c;
	int number, pos = 0;
	char answer[BUFFER_SIZE];
	char str[BUFFER_SIZE];
	printf("Input infix string: ");
	inputCharArray(str, BUFFER_SIZE);

	for (size_t i = 0; i < BUFFER_SIZE; ++i) {
		int p = 0;
		if (str[i] >= '0' && str[i] <= '9') {
			number = str[i] - 48;
			sprintf(answer + pos, "%d %n", number, &p);
			pos += p;
		} else {
			c = str[i];
			if (c == '\0')
				break;
			if (isOperator(c)) {
				while (!emptyStack()) {
					char top = pop();
					int p = 0;
					if (priority(top) >= priority(c)) {
						sprintf(answer + pos, "%c %n", top, &p);
						pos += p;
					} else { // isOperator(top) == false
						push(top);
						break;
					}
				}
				push(c);
			} else if (c == '(') {
				push(c);
			} else if (c == ')') {
				while ((c = pop()) != '(') {
					int p = 0;
					sprintf(answer + pos, "%c %n", c, &p);
					pos += p;
				}
			}
		}
	}
	while (!emptyStack()) {
		int p = 0;
		sprintf(answer + pos, "%c %n", pop(), &p);
		pos += p;
	}
	printf("Answer: %s\n", answer);
	return 0;
}
