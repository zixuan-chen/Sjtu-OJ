#include <iostream>
#include <cstdio>
using namespace std;

const char null = '\n';
char tree[10000];
char preOrder[10000];
char midOrder[10000];
int len = 0;
char root;
void getTree(int level, int pl, int pr, int ml, int mr)
{
    if (pl > pr)
        return;
    //cout << "premeter: " << level << ' ' << pl << ' ' << pr << ' ' << ' ' << ml << ' ' << mr << endl;
    root = preOrder[pl];
    tree[level] = root;
    int l = 0;
    for (; midOrder[ml + l] != root; l++)
        ;
    //cout << "l = " << l << endl;
    getTree(2 * level + 1, pl + 1, pl + l, ml, ml + l - 1);
    getTree(2 * level + 2, pl + l + 1, pr, ml + l + 1, mr);
}
int main(int argc, char const *argv[])
{
    freopen("in", "r", stdin);
    cin.getline(preOrder, 1001, '\n');
    cin.getline(midOrder, 1001, '\n');
    for (len = 0; preOrder[len] != '\0'; len++)
        ;
    for (int i = 0; i < 1001; i++)
        tree[i] = null;

    getTree(0, 0, len - 1, 0, len - 1);

    for (int i = 0; len > 0; i++)
    {
        if (tree[i] == null)
            cout << "NULL ";
        else
        {
            cout << tree[i] << ' ';
            len--;
        }
    }

    fclose(stdin);
    return 0;
}