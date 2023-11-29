#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define gcd(a,b)  __gcd(a,b)
#define lcm(a,b) a/(b/__gcd(a,b))
#define optimize() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
//#include<ext/pb_ds/assoc_container.hpp>
//#include<ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;
//template <typename T> using pbds = tree<T, null_type, less<T>,rb_tree_tag, tree_order_statistics_node_update>;
int mod = 1e9 + 7;
const int N = 1e7 + 123;
int a[N], tree[4*N];

void build(int node, int st, int en)
{
    if(st == en) {
        tree[node] = a[st];
        return;
    }

    int mid = (st + en)/2;
    build(2*node, st, mid);
    build(2*node+1, mid+1, en);

    tree[node] = tree[2*node] + tree[2*node+1];
}

int query(int node, int st, int en, int l, int r)
{
    if(st > r || en < l) {
        return 0;
    }

    if(l <= st && en <= r) {
        return tree[node];
    }

    int mid = (st+en)/2;
    int q1 = query(2*node, st, mid, l, r);
    int q2 = query(2*node+1, mid+1, en, l, r);

    return q1+q2;
}

int main()
{
    optimize();
    int n; cin >> n;

    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    build(1, 0, n-1);

    while(1) {
        int type; cin >> type;
        if(type == -1) break;
        if(type == 1) {
            int l, r; cin >> l >> r;
            int ans = query(1, 0, n-1, l, r);
            cout << ans << ' ';
        }
    }
}



