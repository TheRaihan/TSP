#include <bits/stdc++.h>
#define mem(a, b) memset(a, b, sizeof(a))
using namespace std;

int vertex, i1 = 0, i = 0, adj[100][100], mn = 999999;
bool mark[100];

list<int> sol[50];
int totalCost(int);
void input()
{
    // cout << "Input Number of vertex: ";
    int a, b, w, edge;
    cin >> vertex >> edge;
    while (edge--)
    {
        // cout << "Edge " << i << ": ";
        cin >> a >> b >> w;
        adj[a][b] = w;
        adj[b][a] = w;
        i++;
    }
    cout << endl;
    for (int i = 0; i < vertex; i++)
    {
        cout << "\t\t";
        for (int j = 0; j < vertex; j++)
            cout << adj[i][j] << "  ";
        cout << endl
             << endl;
        ;
    }
}

void ranSol()
{
    list<int>::iterator it;
    int flag = 1;
    while (flag)
    {
        int x = rand() % vertex;
        if (mark[x] == 0)
        {
            sol[i1].push_back(x);
            mark[x] = 1;
        }
        flag = 0;
        for (int i = 0; i < vertex; i++)
            if (mark[i] == 0)
                flag = 1;
    }
    cout << i1 << " : Random Chlid: ";

    for (it = sol[i1].begin(); it != sol[i1].end(); it++)
        cout << *it << " ";

    cout << endl;
    i1++;
    for (int i = 0; i < 50; i++)
        mark[i] = 0;
}

int totalCost(int a)
{
    if (a > i1)
    {
        cout << "Not Found" << endl;
        return 0;
    }

    list<int>::iterator it, it2;
    int cost = 0, x, x1;
    it = sol[a].begin();
    x = *it;
    x1 = x;
    it++;
    for (; it != sol[a].end(); it++)
    {
        cost += adj[x][*it];
        x = *it;
    }
    cost += adj[x][x1];
    return cost;
}

void cross(int a, int b)
{
    list<int>::iterator it;
    vector<int> v;
    if (a > i1 || b > i1 || a < 0 || b < 0)
    {
        cout << "No Parent Found" << endl;
        return;
    }
    int half = vertex / 2, j = 0;

    for (it = sol[a].begin(); j < half; it++)
    {
        v.push_back(*it);
        j++;
    }
    // for(int i =0;i<v.size();i++)
    //     cout << v[i] << " ";
    // cout << endl;
    sol[i1] = sol[b];
    for (it = sol[i1].begin(); it != sol[i1].end(); it++)
        for (int i = 0; i < v.size(); i++)
            if (*it == v[i])
                sol[i1].erase(it);

    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++)
        sol[i1].push_back(v[i]);

    cout << i1 << " : Cross of " << a << " & " << b << " : ";
    for (it = sol[i1].begin(); it != sol[i1].end(); it++)
        cout << *it << " ";
    cout << endl;
    i1++;
}

int main()
{
    int fitness, apprx, k;
    list<int>::iterator it;
    srand(time(0));
    freopen("input3.txt", "r", stdin);
    input();
    cout << "Enter The Value of K : ";
    cin >> k;
    cout << endl;

    for (int i = 0; i < k; i++)
        ranSol();

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < k; j++)
            cross(i1 - i - 1, i1 - j - 2);

    for (int i = 0; i < i1; i++)
    {
        fitness = totalCost(i);
        // cout << fitness << " ";
        if (fitness < mn)
        {
            mn = fitness;
            apprx = i;
        }
    }

    cout << "\nApprx ans: " << mn << " for this child: ";
    for (it = sol[apprx].begin(); it != sol[apprx].end(); it++)
        cout << *it << " ";
    cout << endl
         << endl;

    return 0;
}
