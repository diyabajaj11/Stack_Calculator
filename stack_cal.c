#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX 100
int stack[MAX];
int top = -1;

void push(char val)
{
    if (top == MAX - 1)
    {
        printf("Overflow");
    }
    else
    {
        top++;
        stack[top] = val;
    }
}

int pop()
{
    if (top == -1)
    {
        printf("Underflow");
    }
    else
    {
        return stack[top--];
    }
}

int operator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int evaluate(char c, int op1, int op2)
{
    switch (c)
    {
    case '+':
        return op1 + op2;
    case '-':
        return op1 - op2;
    case '*':
        return op1 * op2;
    case '/':
        return op1 / op2;
    case '^':
        return (int)pow((double)op1, (double)op2);
    }
}

int prefix(char *exp)
{
    top = -1;
    int len = strlen(exp);
    for (int i = len - 1; i >= 0; i--)
    {
        char c = exp[i];
        if (isspace(c))
        {
            continue;
        }

        if (isdigit(c))
        {
            push(c - '0');
        }
        else if (operator(c))
        {
            int op1 = pop();
            int op2 = pop();
            int res = evaluate(c, op1, op2);
            push(res);
        }
    }
    return pop();
}

int postfix(char *exp)
{
    top = -1;
    int len = strlen(exp);
    for (int i = 0; i <= len; i++)
    {
        char c = exp[i];
        if (isspace(c))
        {
            continue;
        }

        if (isdigit(c))
        {
            push(c - '0');
        }
        else if (operator(c))
        {
            int op1 = pop();
            int op2 = pop();
            int res = evaluate(c, op1, op2);
            push(res);
        }
    }
    return pop();
}

void reverse(char *str)
{
    int len = strlen(str);
    char temp;
    int i = 0, j = len - 1;
    while (i < j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

void swap(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '(')
        {
            str[i] = ')';
        }
        else if (str[i] == ')')
        {
            str[i] = '(';
        }
    }
}

int precedence(char c)
{
    if (c == '^')
    {
        return 3;
    }
    else if (c == '*' || c == '/')
    {
        return 2;
    }
    else if (c == '+' || c == '-')
    {
        return 1;
    }
    else
    {
        return -1;
    }
}
void infix_prefix(char *infix, char *prefix)
{
    char rev[MAX], stack[MAX], postfix[MAX];
    int i, j = 0, top = -1;
    strcpy(rev, infix);
    reverse(rev);
    swap(rev);
    for (int i = 0; rev[i] != '\0'; i++)
    {
        char c = rev[i];
        if (isalnum(c))
        {
            postfix[j++] = c;
        }
        else if (c == ')')
        {
            stack[++top] = c;
        }
        else if (c == '(')
        {
            while (top != -1 && stack[top] != ')')
            {
                postfix[j++] = stack[top--];
            }
            if (top != -1)
            {
                top--;
            }
        }
        else
        {
            while (top != -1 && precedence(c) < precedence(stack[top]))
            {
                postfix[j++] = stack[top--];
            }
            stack[++top] = c;
        }
    }
    while (top != -1)
    {
        postfix[j++] = stack[top--];
    }
    postfix[j] = '\0';
    reverse(postfix);
    strcpy(prefix, postfix);
}

int right_associativity(char c)
{
    return c == '^';
}

void infix_postfix(char *infix_2, char *postfix_1)
{
    char stack[MAX], postfix_exp[MAX];
    int i, j = 0, top = -1;
    for (i = 0; i < strlen(infix_2); i++)
    {
        char c = infix_2[i];
        if (isalnum(c))
        {
            postfix_exp[j++] = c;
        }
        else if (c == '(')
        {
            stack[++top] = c;
        }
        else if (c == ')')
        {
            while (top != -1 && stack[top] != '(')
            {
                postfix_exp[j++] = stack[top--];
            }
            if (top = -1)
            {
                top--;
            }
        }
        else
        {
            while (top != -1 && ((precedence(c) < precedence(stack[top])) || (precedence(c) == precedence(stack[top]) && !right_associativity(c))) && stack[top] != '(')
            {
                postfix_exp[j++] = stack[top--];
            }
            stack[++top] = c;
        }
    }
    while (top != -1)
    {
        postfix_exp[j++] = stack[top--];
    }
    postfix_exp[j] = '\0';
    strcpy(postfix_1, postfix_exp);
}

void prefix_infix(char *prefix, char *infix)
{
    char stack[MAX][MAX], exp[MAX];
    int top = -1;
    for (int i = strlen(prefix) - 1; i >= 0; i--)
    {
        char c = prefix[i];
        if (isalnum(c))
        {
            char operand[2] = {c, '\0'};
            strcpy(stack[++top], operand);
        }
        else if (operator(c))
        {
            char op1[MAX], op2[MAX];
            strcpy(op1, stack[top--]);
            strcpy(op2, stack[top--]);
            sprintf(exp, "(%s%c%s)", op1, c, op2);
            strcpy(stack[++top], exp);
        }
    }
    strcpy(infix, stack[top]);
}

void prefix_postfix(char *prefix, char *postfix)
{
    char stack[MAX][MAX], exp[MAX];
    int top = -1;
    for (int i = strlen(prefix) - 1; i >= 0; i--)
    {
        char c = prefix[i];
        if (isalnum(c))
        {
            char operand[2] = {c, '\0'};
            strcpy(stack[++top], operand);
        }
        else if (operator(c))
        {
            char op1[MAX], op2[MAX];
            strcpy(op1, stack[top--]);
            strcpy(op2, stack[top--]);
            sprintf(exp, "(%s%s%c)", op1, op2, c);
            strcpy(stack[++top], exp);
        }
    }
    strcpy(postfix, stack[top]);
}

void postfix_infix(char *postfix, char *infix)
{
    int top = -1;
    char stack[MAX][MAX], exp[MAX];
    for (int i = 0; i < strlen(postfix); i++)
    {
        char c = postfix[i];
        if (isalnum(c))
        {
            char operand[2] = {c, '\0'};
            strcpy(stack[++top], operand);
        }
        else if (operator(c))
        {
            char op1[MAX], op2[MAX];
            strcpy(op1, stack[top--]);
            strcpy(op2, stack[top--]);
            sprintf(exp, "(%s%c%s)", op2, c, op1);
            strcpy(stack[++top], exp);
        }
    }
    strcpy(infix, stack[top]);
}

void postfix_prefix(char *postfix, char *prefix)
{
    int top = -1;
    char stack[MAX][MAX], exp[MAX];
    for (int i = 0; i <= strlen(postfix) - 1; i++)
    {
        char c = postfix[i];
        if (isalnum(c))
        {
            char operand[2] = {c, '\0'};
            strcpy(stack[++top], operand);
        }
        else if (operator(c))
        {
            char op1[MAX], op2[MAX];
            strcpy(op1, stack[top--]);
            strcpy(op2, stack[top--]);
            sprintf(exp, "%c%s%s", c, op2, op1);
            strcpy(stack[++top], exp);
        }
    }
    strcpy(prefix, stack[top]);
}
int main()
{
    char exp[20];

    int choice;

    do
    {

        printf("\n--Menu--");
        printf("\n1.Infix expression");
        printf("\n2.Prefix expression");
        printf("\n3.Postfix expression");
        printf("\n4.Infix to prefix");
        printf("\n5.Infix to postfix");
        printf("\n6.Prefix to Infix");
        printf("\n7.Prefix to Postfix");
        printf("\n8.Postfix to Infix");
        printf("\n9.Postfix to Prefix");
        printf("\n10.Exit");

        printf("\nEnter choice:");
        scanf("%i", &choice);
        getchar();

        switch (choice)
        {
        case 1:
        {
            char postfix_1_[MAX];
            printf("Infix expression:");
            printf("\nEnter infix expression:");
            scanf("%s", &exp);
            infix_postfix(exp, postfix_1_);
            int final = postfix(postfix_1_);
            printf("\nResult is:%i", final);
            break;
        }
        case 2:
            printf("\nPrefix expression:");
            printf("\nenter prefix exp:");
            scanf("%s", exp);
            int final1 = prefix(exp);
            printf("\nResult is:%i", final1);
            break;

        case 3:
            printf("\nPostfix expression:");
            printf("\nEnter postfix exp:");
            scanf("%s", exp);
            int final2 = postfix(exp);
            printf("\nResult is:%i", final2);
            break;

        case 4:
        {
            printf("\nInfix to prefix");

            char infix_1[] = "p-q-r/a";
            char prefix_1[MAX] = {0};

            printf("\nInfix exp is:%s", infix_1);
            infix_prefix(infix_1, prefix_1);
            printf("\nPrefix exp is:%s", prefix_1);
            break;
        }
        case 5:
        {
            printf("Infix to postfix");
            char infix_2[] = "x+y*z-k";
            char postfix_1[MAX] = {0};
            printf("\nInfix exp is:%s", infix_2);
            infix_postfix(infix_2, postfix_1);
            printf("\nPostfix exp is:%s", postfix_1);
            break;
        }

        case 6:
        {
            printf("\nprefix to infix:");
            char prefix_2[] = "*+ab/ef";
            char infix_3[MAX];
            printf("\nPrefix is:%s", prefix_2);
            prefix_infix(prefix_2, infix_3);
            printf("\nInfix is:%s", infix_3);
            break;
        }

        case 7:
        {
            printf("Prefix to Postfix");
            char prefix_3[] = "*+ab-cd";
            char postfix_2[MAX];
            printf("\nPrefix is:%s", prefix_3);
            prefix_postfix(prefix_3, postfix_2);
            printf("\nPostfix is:%s", postfix_2);
            break;
        }

        case 8:
        {
            printf("Postfix to Infix");
            char postfix_3[] = "ab+ef/*";
            char infix_4[MAX];
            printf("\nPostfix is :%s", postfix_3);
            postfix_infix(postfix_3, infix_4);
            printf("\nInfix is:%s", infix_4);
            break;
        }

        case 9:
        {
            printf("Postfix to prefix");
            char postfix_4[] = "ab+cd-*";
            char prefix_4[MAX];
            printf("\nPostfix is:%s", postfix_4);
            postfix_prefix(postfix_4, prefix_4);
            printf("\nPrefix is:%s", prefix_4);
            break;
        }

        case 10:
        {
            printf("Exit");
            break;
        }
        default:
            printf("\nEnter valid choice!");
            break;
        }
    } while (choice != 10);

    return 0;
}
