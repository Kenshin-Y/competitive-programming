
#include <bits/stdc++.h>
using namespace std;

vector<int> Kadena(vector<int> a){
    vector<int> ret(a.size()); //ret[j]:=max{a[i]+a[i+1]+...+a[j]} for i∈[1,j]
    ret[0]=max(a[0],0);
    for(int i=0;i<a.size()-1;i++){
        ret[i+1]=max(ret[i]+a[i+1],0);
    }
    return ret;
}
