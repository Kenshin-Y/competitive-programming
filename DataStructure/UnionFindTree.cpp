/*
    @created: 2019-12
    @verified: ATC001-B
    @description:
        * UnionFind
        * 最小全域木にも使える
        * data[x]= par, rootならsizeになっていて、符号で判定
 */
#ifndef UNIONFIND
#define UNIONFIND
#include <bits/stdc++.h>
using namespace std;

struct Unionfind
{
    vector<int> data;
    Unionfind(int size):data(size, -1) {}

    bool unite(int x, int y)
    {
        x=root(x);
        y=root(y);
        if(x!=y){
            if(data[y] < data[x]) swap(x, y);
            data[x] += data[y];
            data[y] = x;
        }
        return x!=y;
    }

    bool same(int x, int y)
    {
        return root(x) == root(y);
    }

    int root(int x)
    {
        return (data[x] < 0) ? x : data[x]=root(data[x]);
    }

    int size(int x)
    {
        return -data[root(x)];
    }

};
#endif // UNIONFIND
