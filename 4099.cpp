//KMP
#include <iostream>
#include <cstdio>
using namespace std;
void KMP(char *str, int *next, int len)
{
    next[0] = -1; //next[0]初始化为-1，-1表示不存在相同的最大前缀和最大后缀
    int k = -1;   //k初始化为-1
    for (int q = 1; q < len; q++)
    {
        while (k > -1 && str[k + 1] != str[q]) //如果下一个不同，那么k就变成next[k]，注意next[k]是小于k的，无论k取任何值。
        {
            k = next[k]; //往前回溯
        }
        if (str[k + 1] == str[q]) //如果相同，k++
        {
            ++k;
        }
        next[q] = k; //这个是把算的k的值（就是相同的最大前缀和最大后缀长）赋给next[q]
    }
}

char word[251], str[1000001];

int main(int argc, char const *argv[])
{
    freopen("in", "r", stdin);
    int len = 0;
    while ((word[len] = cin.get()) != '\n')
        len++;
    int strl = 1, wordNum;
    cin >> wordNum;
    cin.get();
    while ((str[0] = cin.get()) == ' ')
        ;
    if (str[0] == '\n')
    {
        cout << -1;
        return 0;
    }
    while ((str[strl] = cin.get()) != '\n')
    {
        if (str[strl] == ' ' && str[strl - 1] == ' ')
            continue;
        strl++;
    }

    for (int i = 0; i < len; i++)
        if (word[i] > 'A' && word[i] < 'Z')
            word[i] = 'a' + word[i] - 'A';
    for (int i = 0; i < strl; i++)
        if (str[i] > 'A' && str[i] < 'Z')
            str[i] = 'a' + str[i] - 'A';

    int *next = new int[len];
    KMP(word, next, len);
    int step = len - (next[len - 1] + 1);
    int first, num = 0, i, j, blanks = 0;

    cout << str << endl;

    for (i = 0; i < strl;)
    {
        if (str[i] == ' ')
        {
            i++;
            blanks++;
            continue;
        }
        for (j = 0; j < len && str[j] != ' '; j++, i++)
        {
            if (str[i] != word[j])
                break;
        }
        if (str[j] == ' ')
            blanks++;
        if (j == len && (str[j] == ' ' || str[j] == '\n'))
        {
            num++;
            if (num == 1)
                first = i - len - blanks;
        }
    }

    if (num == 0)
        cout << -1;
    else
        cout << num << ' ' << first;
    fclose(stdin);
    return 0;
}
