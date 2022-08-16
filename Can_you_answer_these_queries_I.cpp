// Question Link: https://www.spoj.com/problems/GSS1/
#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define mod 1000000007
#define um unordered_map
#define us unordered_set
#define f first
#define s second
#define v vector
#define all(arr) arr.begin(), arr.end()
template <typename T> istream& operator>>(istream &istream, vector<T> &nums){ for(auto &val: nums) cin >> val; return istream;}
template <typename T1, typename T2> istream& operator>>(istream &istream, pair<T1, T2> &p){ return (istream >> p.f >> p.s);}
template<class Fun> class y_combinator_result {
    Fun fun_;
public:
    template<class T> explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
    template<class ...Args> decltype(auto) operator()(Args &&...args) { return fun_(std::ref(*this), std::forward<Args>(args)...);}
};
template<class Fun> decltype(auto) y_combinator(Fun &&fun) { return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun)); }template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')';}
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#ifdef NONI_DEBUG
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
class Node{
public:
    int sum, pre, suf, res;
    Node(){}
    Node(int val){
        this->sum = this->pre = this->suf = this->res = val;
    }
};
v<Node> tree;

Node merge(Node left, Node right){
    Node ans;
    ans.sum = left.sum + right.sum;
    ans.pre = max({left.pre, left.sum + right.pre});
    ans.suf = max({right.suf, left.suf + right.sum});
    ans.res = max({left.res, right.res, left.suf + right.pre});
    return ans;
}

void built(int node, int start, int end, v<int> &nums){
    if (start == end){
        tree[node] = Node(nums[start]);
        return;
    }
    else {
        int mid = (start + end) / 2;
        built(node*2, start, mid, nums);
        built(node*2+1, mid+1, end, nums);
        tree[node] = merge(tree[node*2], tree[node*2+1]);
    }
}

Node solve(int node, int start, int end, int left, int right){
    if (left > end or right < start){
        return Node(INT_MIN);
    }
    if (start >= left and end <= right){
        return tree[node];
    }
    int mid = (start + end) / 2;
    return merge(solve(node*2, start, mid, left, right), solve(node*2 + 1, mid+1, end, left, right));
}

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);    
    int n; cin >> n;
    v<int> nums(n);
    cin >> nums;
    tree.resize(4*n);
    built(1, 0, n-1, nums);
    int m;cin >> m;
    while(m--){
        int a, b;cin >> a >> b;
        cout << solve(1, 0, n-1, a-1, b-1).res << "\n";
    }  
}






