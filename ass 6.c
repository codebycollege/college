#include <stdio.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

/* Push into stack */
void push(char ch)
{
    stack[++top] = ch;
}

/* Pop from stack */
char pop()
{
    return stack[top--];
}

/* Precedence of operators */
int precedence(char ch)
{
    if (ch == '^')
        return 3;
    else if (ch == '*' || ch == '/')
        return 2;
    else if (ch == '+' || ch == '-')
        return 1;
    else
        return 0;
}

/* Infix to Postfix Conversion */
void infixToPostfix(char infix[], char postfix[])
{
    int i, j = 0;
    char ch;

    top = -1;

    for (i = 0; infix[i] != '\0'; i++)
    {
        ch = infix[i];

        /* Operand */
        if (isalnum(ch))
        {
            postfix[j++] = ch;
        }

        /* Opening bracket */
        else if (ch == '(')
        {
            push(ch);
        }

        /* Closing bracket */
        else if (ch == ')')
        {
            while (top != -1 && stack[top] != '(')
            {
                postfix[j++] = pop();
            }

            if (top != -1)
                pop();
        }

        /* Operator */
        else
        {
            while (top != -1 &&
                   stack[top] != '(' &&
                   (precedence(stack[top]) > precedence(ch) ||
                   (precedence(stack[top]) == precedence(ch) && ch != '^')))
            {
                postfix[j++] = pop();
            }

            push(ch);
        }
    }

    /* Pop remaining operators */
    while (top != -1)
    {
        postfix[j++] = pop();
    }

    postfix[j] = '\0';
}

/* Calculate power */
int power(int a, int b)
{
    int result = 1;

    while (b > 0)
    {
        result = result * a;
        b--;
    }

    return result;
}

/* Evaluate Postfix Expression */
int evaluatePostfix(char postfix[])
{
    int value[MAX];
    int vtop = -1;

    int i, a, b;
    char ch;

    int values[26] = {0};
    int entered[26] = {0};

    /* Get values of operands */
    for (i = 0; postfix[i] != '\0'; i++)
    {
        ch = postfix[i];

        if (islower(ch))
        {
            if (!entered[ch - 'a'])
            {
                printf("Enter value of %c: ", ch);
                scanf("%d", &values[ch - 'a']);

                entered[ch - 'a'] = 1;
            }
        }
    }

    /* Evaluate postfix */
    for (i = 0; postfix[i] != '\0'; i++)
    {
        ch = postfix[i];

        /* Operand */
        if (islower(ch))
        {
            value[++vtop] = values[ch - 'a'];
        }

        /* Operator */
        else
        {
            b = value[vtop--];
            a = value[vtop--];

            switch (ch)
            {
                case '+':
                    value[++vtop] = a + b;
                    break;

                case '-':
                    value[++vtop] = a - b;
                    break;

                case '*':
                    value[++vtop] = a * b;
                    break;

                case '/':
                    if (b == 0)
                    {
                        printf("Error: Division by zero!\n");
                        return 0;
                    }

                    value[++vtop] = a / b;
                    break;

                case '^':
                    value[++vtop] = power(a, b);
                    break;
            }
        }
    }

    return value[vtop];
}

/* Main Function */
int main()
{
    char infix[MAX];
    char postfix[MAX];

    int result;

    printf("Enter infix expression: ");
    scanf("%99s", infix);

    infixToPostfix(infix, postfix);

    printf("\nPostfix expression: %s", postfix);

    result = evaluatePostfix(postfix);

    printf("\nResult = %d\n", result);

    return 0;
}