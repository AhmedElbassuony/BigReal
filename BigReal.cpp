// File: task2.cpp
// Purpose: BIGCLASS
// Author: ahmed mohamed tolba
// Section: S7,8
// ID: 20220033
// TA: khaled ibrahem
// Date: 5 NOV 2023

#include "BigReal.h"
#include <iostream>
#include <deque>
using namespace std;

bool isValid(string s)
{
    int points = 0;
    bool valid = true;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '.')
        {
            points++;
            if (points > 1 or i == s.size() - 1)
            {
                valid = false;
                break;
            }
        }
        else if ((s[i] == '+' or s[i] == '-') and i == 0)
        {
            continue;
        }
        else if (s[i] < '0' or s[i] > '9')
        {
            valid = false;
            break;
        }
    }
    if (!valid)
    {
        cout << "ERROR the number is invalid\n";
    }
    return valid;
}

BigReal::BigReal()
{
    integer.push_back('0');
    fraction.push_back('0');
    decimal = true;
    postive = true;
}

BigReal::BigReal(string num)
{
    if (!isValid(num))
    {
        integer.push_back('0');
        fraction.push_back('0');
        decimal = true;
        postive = true;
        return;
    }
    int i = 0;
    postive = true;
    for (; i < num.size(); i++)
    {
        if (num[i] == '-' or num[i] == '+')
        {
            if (num[i] == '-')
            {
                postive = false;
            }
            continue;
        }
        if (num[i] == '.')
        {
            decimal = true;
            break;
        }
        integer.push_back(num[i]);
    }
    i++;
    for (; i < num.size(); i++)
    {
        fraction.push_back(num[i]);
    }

    while (integer.size() > 1 and integer.front() == '0')
    {
        integer.pop_front();
    }

    while (fraction.size() > 1 and fraction.back() == '0')
    {
        fraction.pop_back();
    }
    if (integer.empty()) //there is only fraction side
    {
        integer.push_back('0');
    }
}

void BigReal::operator=(string num)
{
    if (!isValid(num))
    {
        integer.push_back('0');
        fraction.push_back('0');
        decimal = true;
        postive = true;
        return;
    }

    integer.clear();
    fraction.clear();
    postive = true;
    decimal = false;

    int i = 0;
    postive = true;
    for (; i < num.size(); i++)
    {
        if (num[i] == '-' or num[i] == '+')
        {
            if (num[i] == '-')
            {
                postive = false;
            }
            continue;
        }
        if (num[i] == '.')
        {
            decimal = true;
            break;
        }
        integer.push_back(num[i]);
    }
    i++;
    for (; i < num.size(); i++)
    {
        fraction.push_back(num[i]);
    }

    while (integer.size() > 1 and integer.front() == '0')
    {
        integer.pop_front();
    }

    while (fraction.size() > 1 and fraction.back() == '0')
    {
        fraction.pop_back();
    }
    if (integer.empty())
    {
        integer.push_back('0');
    }
}

ostream &operator<<(ostream &out, BigReal num)
{
    if (!num.postive)
    {
        out << '-';
    }
    for (char x : num.integer)
    {
        out << x;
    }
    if (num.decimal)
    {
        out << ".";
        for (char x : num.fraction)
        {
            out << x;
        }
    }
    return out;
}

BigReal BigReal::operator+(BigReal &n)
{
    BigReal s1 = n;
    BigReal s2;
    BigReal sum;
    s2.decimal = decimal;
    s2.postive = postive;
    s2.integer = integer;
    s2.fraction = fraction;
    sum.fraction.pop_back();
    sum.integer.pop_back();

    if (s1.integer.size() != s2.integer.size())
    {
        if (s1.integer.size() < s2.integer.size())
        {
            while (s1.integer.size() != s2.integer.size())
            {
                s1.integer.push_front('0');
            }
        }
        else
        {
            while (s1.integer.size() != s2.integer.size())
            {
                s2.integer.push_front('0');
            }
        }
    }

    if ((s1.decimal or s2.decimal))
    {
        sum.decimal = true;
        if (s1.fraction.size() < s2.fraction.size())
        {
            while (s1.fraction.size() != s2.fraction.size())
            {
                s1.fraction.push_back('0');
            }
        }
        else
        {
            while (s1.fraction.size() != s2.fraction.size())
            {
                s2.fraction.push_back('0');
            }
        }
    }
    else
    {
        sum.decimal = false;
    }

    if (s1.postive == s2.postive)
    {
        sum.postive = postive;
        bool carry = false;
        if (sum.decimal)
        {
            int size = s1.fraction.size();
            for (int i = size - 1; i >= 0; i--)
            {
                char n1 = s1.fraction[i], n2 = s2.fraction[i];
                int out = (n1 - '0') + (n2 - '0');
                if (carry)
                {
                    out++;
                    carry = false;
                }
                if (out > 9)
                {
                    out -= 10;
                    carry = true;
                }
                sum.fraction.push_front('0' + out);
            }
        }

        int size = s1.integer.size();
        for (int i = size - 1; i >= 0; i--)
        {
            char n1 = s1.integer[i], n2 = s2.integer[i];
            int out = (n1 - '0') + (n2 - '0');
            if (carry)
            {
                out++;
                carry = false;
            }
            if (out > 9)
            {
                out -= 10;
                carry = true;
            }
            sum.integer.push_front('0' + out);
        }
        if (carry)
        {
            sum.integer.push_front('1');
        }
    }

    else
    {
        s1.postive = true;
        s2.postive = true;
        if (s1.integer == s2.integer and s1.fraction == s2.fraction)
        {
            sum.integer.push_back('0');
            return sum;
        }

        else if (s1 > s2)
        {
            sum.postive = n.postive;
            bool take_one = false;
            if (sum.decimal)
            {
                int size = s1.fraction.size();
                for (int i = size - 1; i >= 0; i--)
                {
                    char n1 = s1.fraction[i], n2 = s2.fraction[i];
                    int out = (n1 - '0') - (n2 - '0');
                    if (out < 0)
                    {
                        int j = i - 1;
                        while (j >= 0 and s1.fraction[j] == '0')
                        {
                            j--;
                        }
                        if (j >= 0)
                        {
                            s1.fraction[j] -= 1;
                        }
                        else
                        {
                            take_one = true;
                        }
                        j++;
                        while (j < i)
                        {
                            s1.fraction[j] = '9';
                            j++;
                        }
                        out += 10;
                    }
                    sum.fraction.push_front('0' + out);
                }
            }
            int size = s1.integer.size();
            for (int i = size - 1; i >= 0; i--)
            {
                char n1 = s1.integer[i], n2 = s2.integer[i];
                int out = (n1 - '0') - (n2 - '0');
                if (take_one)
                {
                    out--;
                    take_one = false;
                }
                if (out < 0)
                {
                    int j = i - 1;
                    while (j >= 0 and s1.integer[j] == '0')
                    {
                        j--;
                    }
                    s1.integer[j] -= 1;
                    j++;
                    while (j < i)
                    {
                        s1.integer[j] = '9';
                        j++;
                    }
                    out += 10;
                }
                sum.integer.push_front('0' + out);
            }
        }

        else
        {
            sum.postive = postive;
            bool take_one = false;
            if (sum.decimal)
            {
                int size = s1.fraction.size();
                for (int i = size - 1; i >= 0; i--)
                {
                    char n1 = s2.fraction[i], n2 = s1.fraction[i];
                    int out = (n1 - '0') - (n2 - '0');
                    if (out < 0)
                    {
                        int j = i - 1;
                        while (j >= 0 and s2.fraction[j] == '0')
                        {
                            j--;
                        }
                        if (j >= 0)
                        {
                            s2.fraction[j] -= 1;
                        }
                        else
                        {
                            take_one = true;
                        }
                        j++;
                        while (j < i)
                        {
                            s2.fraction[j] = '9';
                            j++;
                        }
                        out += 10;
                    }
                    sum.fraction.push_front('0' + out);
                }
            }
            int size = s1.integer.size();
            for (int i = size - 1; i >= 0; i--)
            {
                char n1 = s2.integer[i], n2 = s1.integer[i];
                int out = (n1 - '0') - (n2 - '0');
                if (take_one)
                {
                    out--;
                    take_one = false;
                }
                if (out < 0)
                {
                    int j = i - 1;
                    while (j >= 0 and s2.integer[j] == '0')
                    {
                        j--;
                    }
                    if (j >= 0)
                    {
                        s2.integer[j] -= 1;
                    }
                    j++;
                    while (j < i)
                    {
                        s2.integer[j] = '9';
                        j++;
                    }
                    out += 10;
                }
                sum.integer.push_front('0' + out);
            }
        }
    }

    while (sum.integer.size() > 1 and sum.integer.front() == '0')
    {
        sum.integer.pop_front();
    }

    while (sum.fraction.size() > 1 and sum.fraction.back() == '0')
    {
        sum.fraction.pop_back();
    }

    return sum;
}

BigReal BigReal::operator+(string n)
{
    BigReal s1(n);
    BigReal s2;
    s2.decimal = decimal;
    s2.postive = postive;
    s2.integer = integer;
    s2.fraction = fraction;
    return s2 + s1;
}

BigReal BigReal::operator-(BigReal &n)
{
    n.postive = !n.postive;
    BigReal s;
    s.decimal = decimal;
    s.fraction = fraction;
    s.integer = integer;
    s.postive = postive;
    return s + n;
}

bool BigReal::operator==(BigReal n)
{
    if (n.integer == integer && n.postive == postive && n.fraction == fraction)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool BigReal::operator<(BigReal n)
{
    if (postive != n.postive)
    {

        return n.postive;
    }

    if (integer.size() != n.integer.size())
    {
        if (postive)
        {
            return integer.size() < n.integer.size();
        }
        else
        {
            return integer.size() > n.integer.size();
        }
    }

    for (int i = 0; i < integer.size(); ++i)
    {
        if (integer[i] != n.integer[i])
        {
            if (postive)
            {
                return integer[i] < n.integer[i];
            }
            else
            {
                return integer[i] > n.integer[i];
            }
        }
    }

    if (decimal != n.decimal)
    {
        if (postive)
        {
            return !decimal;
        }
        else
        {
            return !n.decimal;
        }
    }
    if (fraction.size() != n.fraction.size())
    {
        if (postive)
        {
            return fraction.size() < n.fraction.size();
        }
        else
        {
            return fraction.size() > n.fraction.size();
        }
    }

    for (int i = 0; i < fraction.size(); ++i)
    {
        if (fraction[i] != n.fraction[i])
        {
            if (postive)
            {
                return fraction[i] < n.fraction[i];
            }
            else
            {
                return fraction[i] > n.fraction[i];
            }
        }
    }

    return false;
}

bool BigReal::operator>(BigReal n)
{
    if (postive != n.postive)
    {
        return postive;
    }

    if (integer.size() != n.integer.size())
    {
        if (postive)
        {
            return integer.size() > n.integer.size();
        }
        else
        {
            return integer.size() < n.integer.size();
        }
    }

    for (int i = 0; i < integer.size(); ++i)
    {
        if (integer[i] != n.integer[i])
        {
            if (postive)
            {
                return integer[i] > n.integer[i];
            }
            else
            {
                return integer[i] < n.integer[i];
            }
        }
    }

    if (decimal != n.decimal)
    {
        if (postive)
        {
            return decimal;
        }
        else
        {
            return n.decimal;
        }
    }

    if (fraction.size() != n.fraction.size())
    {
        if (postive)
        {
            return fraction.size() > n.fraction.size();
        }
        else
        {
            return fraction.size() < n.fraction.size();
        }
    }

    for (int i = 0; i < fraction.size(); ++i)
    {
        if (fraction[i] != n.fraction[i])
        {
            if (postive)
            {
                return fraction[i] > n.fraction[i];
            }
            else
            {
                return fraction[i] < n.fraction[i];
            }
        }
    }

    return false;
}
