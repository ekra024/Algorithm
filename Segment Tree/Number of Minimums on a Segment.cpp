#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define gcd(a,b)  __gcd(a,b)
#define lcm(a,b) a/(b/__gcd(a,b))
#define optimize() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

const int N = 1e5+123;

pair<int,int> tree[4*N];
int a[N];

void build(int node, int st, int en)
{
    if(st == en) {
        tree[node].first = a[st];
        tree[node].second = 1;
        return;
    }

    int mid = (st+en)/2;
    build(2*node, st, mid);
    build(2*node+1, mid+1, en);

    if(tree[2*node].first < tree[2*node+1].first) {
        tree[node].first = tree[2*node].first;
        tree[node].second = tree[2*node].second;
    }
    else if(tree[2*node].first > tree[2*node+1].first){
        tree[node].first = tree[2*node+1].first;
        tree[node].second = tree[2*node+1].second;
    }
    else {
        tree[node].first = tree[2*node].first;
        tree[node].second = tree[2*node].second + tree[2*node+1].second;
    }


}

pair<int,int> MinVal(int node, int st, int en, int l, int r)
{
    if(st > r || en < l) {
        return {INT_MAX, -1};
    }

    if(l <= st && en <= r) return tree[node];

    int mid = (st + en)/2;
    pair<int,int> q1 = MinVal(2*node, st, mid, l, r);
    pair<int,int> q2 = MinVal(2*node+1,mid+1, en, l, r);

    pair<int,int> q;
    if(q1.first < q2.first) {
        q = q1;
    }
    else if(q2.first < q1.first) {
        q = q2;
    }
    else {
        q.first = q1.first;
        q.second = q1.second+q2.second;
    }

    return q;
}

void update(int node, int st, int en, int idx, int val)
{
    if(st == en) {
        a[st] = val;
        tree[node].first = val;
        tree[node].second = 1;
        return;
    }

    int mid = (st+en)/2;
    if(idx <= mid) {
        update(2*node, st, mid, idx, val);
    }
    else {
        update(2*node+1, mid+1, en, idx, val);
    }

    if(tree[2*node].first < tree[2*node+1].first) {
        tree[node].first = tree[2*node].first;
        tree[node].second = tree[2*node].second;
    }
    else if(tree[2*node].first > tree[2*node+1].first){
        tree[node].first = tree[2*node+1].first;
        tree[node].second = tree[2*node+1].second;
    }
    else {
        tree[node].first = tree[2*node].first;
        tree[node].second = tree[2*node].second + tree[2*node+1].second;
    }

}

int main()
{
    optimize();
    int n, q; cin >> n >> q;

    for(int i = 0; i < n; i++) cin >> a[i];
    build(1, 0, n-1);

    while(q--) {
        int type; cin >> type;
        if(type == 2) {
            int l, r; cin >> l >> r;
            pair<int,int> ans = MinVal(1, 0, n-1, l, r-1);
            cout << ans.first <<' '<< ans.second<<'\n';
        }
        else {
            int idx, val;
            cin >> idx >> val;
            update(1, 0, n-1, idx, val);
        }
    }
}



