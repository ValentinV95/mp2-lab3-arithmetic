#include "arithmetic.h"
#include "stack.h"
#define max_size 50

string TPostfix::ToPostfix()
{

    int  len = GetSizeInfix();
    char result[max_size];
    TStack<char> stack(len);
    int count = 0;
    int i = 0;
    int flag = 0;
    while (i < len)
    {
        if (infix[i] != '+' && infix[i] != '-' && infix[i] != '*' && infix[i] != '/' && infix[i] != '(' && infix[i] != ')')
        {
            flag = 0;
            while ((infix[i] != '+' && infix[i] != '-' && infix[i] != '*' && infix[i] != '/' && infix[i] != '(' && infix[i] != ')') && i<len)
            {
                if ((infix[i] >= 'a' && infix[i] <= 'z') || (infix[i] >= 'A' && infix[i] <= 'Z')) flag = 0;
                else flag = 1;
                result[count++] = infix[i++];
            }
            if( flag==1) result[count++] = ' ';
        }
            
        if (infix[i] == '(') stack.Push(infix[i]);
        if (infix[i] == ')')
        {
            while (stack.Top() != '(')
                result[count++] = stack.Pop();
            stack.Pop();
        }
        if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/')
        {
            if (infix[i] == '-' && (i == 0 || i > 0 && (infix[i - 1] < '0' || infix[i - 1] > '9'))) {
                result[count++] = '-';
                i++;
                continue;
            }
            if (stack.IsEmpty() || stack.Top() == '(') stack.Push(infix[i]);
            else if (Priort(infix[i]) > Priort(stack.Top())) stack.Push(infix[i]);
            else
            {
                while (!stack.IsEmpty() && Priort(infix[i]) <= Priort(stack.Top()))
                    result[count++] = stack.Pop();
                stack.Push(infix[i]);
            }
        }
        i++;
    }
    while (stack.IsEmpty() != true)
        result[count++] = stack.Pop();
    result[--count] = '\0';
    postfix = result;
    return postfix;
}

double TPostfix::Calculate()
{
    int len =postfix.length();

    TStack<double> stack(len);

    double c, c1;
    double k;

    double tmp[max_size];
    char tmp1[max_size];
    int flag;

    int i = 0;

    while(i<len)
    {
        if (postfix[i] != '+' && postfix[i] != '*' && postfix[i] != '/' && postfix[i] != '-')
        {
            if ((postfix[i] >= 'a' && postfix[i] <= 'z') || (postfix[i] >= 'A' && postfix[i] <= 'Z'))
            {
                flag = 0;
                tmp1[i] = postfix[i];
                for (int j = 0; j < i; j++)
                    if (postfix[i] == tmp1[j])
                    {
                        flag = 1;
                        stack.Push(tmp[j]);
                        throw "Error: not correct symbol int variety-parameter";
                        break;
                    }

                if (flag == 0)
                {
                    cout << postfix[i] << "=" << " ";
                    cin >> k;
                    tmp[i] = k;
                    stack.Push(k);
                }
            }
            else
            {
                bool isNeg = false;;
                if (i > 0 && (postfix[i - 1] == '-'))
                    isNeg = true;
                double tmp = 0;
                while (postfix[i] != ' ' && postfix[i] != '.')
                {
                    while (postfix[i] >= 0x30 && postfix[i] <= 0x39)
                    {
                        tmp = tmp + (postfix[i] & 0x0F);
                        tmp = tmp * 10;
                        i++;
                    }
                }
                if (postfix[i] == '.') {
                    //int exp1 = 1;
                    i++;
                    while (postfix[i] >= 0x30 && postfix[i] <= 0x39)
                    {
                        tmp = tmp + (postfix[i] & 0x0F);
                        tmp = tmp / 10;
                        i++;
                    }
                }
                else
                    tmp = tmp / 10;
                tmp *= isNeg ? -1 : 1;
                stack.Push(tmp);
            }
        }
        else
        {
            if (postfix[i] == '+')
            {
                c = stack.Pop();
                c1 = stack.Pop();
                stack.Push(c1 + c);
            }
            if (postfix[i] == '-')
            {
                if (i < postfix.length() - 1 && (postfix[i + 1] >= '0' && postfix[i + 1] <= '9')) {
                    i++;
                    continue;
                }
                c = stack.Pop();
                c1 = stack.Pop();
                stack.Push(c1 - c);
            }
            if (postfix[i] == '/')
            {
                c = stack.Pop();
                c1 = stack.Pop();
                stack.Push(c1 / c);
            }
            if (postfix[i] == '*')
            {
                c = stack.Pop();
                c1 = stack.Pop();
                stack.Push(c1*c);
            }
        }
            i++;
    }
    return stack.Pop();
}

int TPostfix::Priort(char c)
{
    if ((c == '/') || (c == '*')) return 2;
    if ((c == '+') || (c == '-')) return 1;
    if (c == '(') return 0;
    return -1;
}
