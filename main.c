#include <stdio.h>
#include <ctype.h>

typedef struct {
    double arr[50];
    int top;
} OperatorStack;

void init(OperatorStack* stack) {

    stack->top = -1;
}

int isEmpty(OperatorStack* stack) {

    return stack->top == -1;
}

void push(OperatorStack* stack, double value) {

    stack->arr[++stack->top] = value;
}

void pop(OperatorStack* stack) {

    if (isEmpty(stack)) {
        return ;
    }
    stack->top--;
}

double peek(OperatorStack* stack) {

    if (isEmpty(stack)) {
        return -1;
    }

    return stack->arr[stack->top];
}

void printStack(OperatorStack* stack) {
    if (isEmpty(stack))
        return ;
    printf("Printing stack: \n");
    int index = 0;
    while (index <= stack->top) {
        printf("%f\n", stack->arr[index]);
        index++;
    }
}

int isOperator(char c) {

    return c == '+' || c == '-' || c == '*' || c == '/'
        || c == '^';
}

int precedence(char op) {

    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

double applyOp(double a, double b, char op) {

    switch (op) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    default:
        return 0;

    }
}

int main()
{
    OperatorStack operators;
    OperatorStack operands;

    init(&operands);
    init(&operators);

    char expression[1500];
    
    //while (1) {

//        printf("Enter mathematical expression: \n");

        fgets(expression, sizeof(expression), stdin);
//        printf("Entered: %s", expression);

        for (int i = 0; expression[i] != 10; i++) {

            if (expression[i] == 32) //скип пробела
                continue;
            else if (isdigit(expression[i])) {
                double num = 0;
                while (expression[i] != 10 && isdigit(expression[i])) {
                    num = num * 10 + (expression[i] - '0');
                    i++;
                }
                i--;
                push(&operands, num);
            }

            else if (isOperator(expression[i])) {

                while (!isEmpty(&operators) && precedence(peek(&operators)) >= precedence(expression[i])) {

                    double firstOperand = peek(&operands);
                    pop(&operands);

                    double secondOperand = peek(&operands);
                    pop(&operands);

                    char op = (char)peek(&operators);
                    pop(&operators);

                    double result = applyOp(secondOperand, firstOperand, op);

                    push(&operands, result);
                }

                push(&operators, expression[i]);
                
            }

            else if (expression[i] == '(') {

                push(&operators, expression[i]);
            }

            else if (expression[i] == ')') {

                while (!isEmpty(&operators) && peek(&operators) != '(') {

                    double firstOperand = peek(&operands);
                    pop(&operands);

                    double secondOperand = peek(&operands);
                    pop(&operands);

                    char op = (char)peek(&operators);
                    pop(&operators);

                    double result = applyOp(secondOperand, firstOperand, op);

                    push(&operands, result);
                }

                pop(&operators);
              
            }

//            printf("Operators: \n");
//            printStack(&operators);
//
//            printf("Operands: \n");
//            printStack(&operands);
        }

//        printf("Operators final: \n");
//        printStack(&operators);
//
//        printf("Operands final: \n");
//        printStack(&operands);

        while (!isEmpty(&operators)) {

            double firstOperand = peek(&operands);
            pop(&operands);

            double secondOperand = peek(&operands);
            pop(&operands);

            char op = (char)peek(&operators);
            pop(&operators);

            double result = applyOp(secondOperand, firstOperand, op);

            

            push(&operands, result);;
        }

        

        printf("%g\n", peek(&operands));
    //}
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
