// Question Link: https://www.spoj.com/problems/ANDROUND/
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
v<int> tree;

void built(int node, int start, int end, v<int> &nums){
    if (start == end){
        tree[node] = nums[start];
    }
    else {
        int mid = (start + end) / 2;
        built(node*2, start, mid, nums);
        built(node*2+1, mid+1, end, nums);
        tree[node] = (tree[node*2] & tree[node*2+1]);
    }
}

int query(int node, int start, int end, int left, int right){
    if (left > end or right < start)    return ((1ll << 50) - 1);
    if (left <= start and right >= end){
        return tree[node];
    }
    int mid = (start + end) / 2;
    return (query(node*2, start, mid, left, right) & query(node*2+1, mid+1, end, left, right));
}

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    cin >> t;    
    while(t--){
        int n, k; cin >> n >> k;
        v<int> nums(n);
        cin >> nums;  
        if (k > n/2){
            int ans = 8589934591;
            for (int i = 0;i < n;i++){
                ans = (ans & nums[i]);
            }
            for (int i = 0;i < n;i++){
                cout << ans;
                if (i < n-1)    cout << ' ';
            }
            cout << "\n";
            continue;
        }
        // dbg(nums.size());
        nums.insert(nums.end(), all(nums));
        nums.insert(nums.end(), nums.begin(), nums.begin() + n);
        // dbg(nums);
        int nn = nums.size();
        tree.resize(4*nn);
        built(1, 0, nn-1, nums);

        v<int> ans;
        for (int i = n;i < 2*n;i++){
            ans.push_back(query(1, 0, nn-1, i-k, i+k));
        }

        for (int i = 0;i < ans.size();i++){
            cout << ans[i];
            if (i < n-1)    cout << ' ';
        }
        cout << "\n";
        // dbg(((1ll << 50) - 1));
    }
}






