// Question Link: https://www.spoj.com/problems/KGSS/
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


class Node {
public: 
    int one, two;
    Node () {}
    Node(int one, int two){
        this->one = one, this->two = two;
    }
};
v<Node> tree;
Node merge(Node left, Node right){
    Node ans;
    v<int> temp = {left.one, left.two , right.one, right.two};
    sort(all(temp));
    ans.one = temp[3], ans.two = temp[2];
    return ans;
}

void built(int node, int start, int end, v<int> &nums){
    if (start == end){
        tree[node] = Node(nums[start], 0);
        return;
    }
    else {
        int mid = (start + end) / 2;
        built(node*2, start, mid, nums);
        built(node*2+1, mid+1, end, nums);
        tree[node] = merge(tree[node*2], tree[node*2+1]);
    }
}

Node query(int node, int start, int end, int left, int right){
    if (left > end or right < start)    return Node(INT_MIN, INT_MIN);
    if (left <= start and right >= end){
        return tree[node];
    }  
    else {
        int mid = (start + end) / 2;
        return merge(query(node*2, start, mid, left, right), query(node*2+1, mid+1, end, left, right));
    }
}

void update(int node, int start, int end, int id, int val){
    if (start == end){
        tree[node] = Node(val, 0);
        return;
    }
    else {
        int mid = (start + end) / 2;
        if (id >= start and id <= mid){
            update(node*2, start, mid, id, val);
        }
        else {
            update(node*2+1, mid+1, end, id, val);
        }
        tree[node] = merge(tree[node*2], tree[node*2+1]);
    }
}


int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin >> n;
    v<int> nums(n); cin >> nums;
    int m; cin >> m;
    tree.resize(4*n);
    built(1, 0, n-1, nums);
    while(m--){
        char ch;cin >> ch;
        if (ch == 'Q'){
            int x, y;cin >> x >> y;
            Node ans = query(1, 0, n-1, x-1, y-1);
            cout << (ans.one + ans.two) << "\n";
        }
        else {
            int id, val; cin >> id >> val;
            update(1, 0, n-1, id-1, val);
        }
    }
}






