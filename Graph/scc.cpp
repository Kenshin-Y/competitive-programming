/*
    @created : 2020-9
    @updated : 2021-3
    @verifyed : ALPC-G
    @description:
        * Strongly connected component O(V+E)
        * Args : typename T SCC(T)
        * func : SCC.build(vector<vector<int>> v)

        * dfsでorderとって番号をつける。枝を逆にしてorderの降順にrdfs : 小さいorderには行けて、逆辺貼ってもいけるやろの気持ち
        * scc[i]でiが含まれる成分番号 scc[i]の昇順に塊としてトポロジカルソートされている
 */

#ifndef SCC_CPP
#define SCC_CPP
#include <bits/stdc++.h>
using namespace std;

// todo: verify
template<typename T>
struct SCC
{
    T &G;
    vector<vector<int>> Ngraph; // Normal graph
    vector<vector<int>> Rgraph; // Reversed graph
    vector<int> comp;           // 属する強連結成分のトポロジカル順序
    vector<int> order;          // 帰りがけ順の並び
    vector<bool> used;          // すでに調べたか

    SCC(T &g)
    {
        int sz = (int)g.size();
        G = g;
        Ngraph.resize(sz);
        Rgraph.resize(sz);
        comp.resize(sz);
        used.reszie(sz);
        // グラフの持ち方によってはここいじる. vector<vector<int>>想定.
        for(int i=0;sz;i++){
            for(auto u:g[i]){
                Ngraph[i].push_back((int)u);
                Rgraph[(int)u].push_back(i);
            }
        }
    }
    // idxが属する強連結成分のトポロジカル順序
    int operator[](int idx)
    {
        return comp[idx];
    }
    
    void dfs(int idx)
    {
        if(used[idx]) return;
        used[idx]=true;
        for(auto &to:Ngraph[idx]) dfs(to);
        order.push_back(idx);
    }

    void rdfs(int idx,int cnt)
    {
        if(comp[idx]!=-1) return;
        comp[idx]=cnt;
        for(auto &to:Rgraph[idx]) rdfs(to,cnt);
    }

    void build(vector<vector<int>> &ret)
    {
        for(int i=0;i<(int)Ngraph.size();i++) dfs(i);

        reverse(order.begin(),order.end());

        int group=0;
        for(auto i:order){
            if(comp[i]==-1){
                rdfs(i,group);
                group++;
            }
        }
        ret.resize(group);
        for(int i=0;i<(int)G.size();i++){
            for(auto &to:G[i]){
                int s=comp[i],t=comp[to];
                if(s!=t) ret[s].push_back(t);
            }
        }
    }
    
};
#endif // SCC_CPP