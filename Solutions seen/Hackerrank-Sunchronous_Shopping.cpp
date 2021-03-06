#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>
#include <functional> // for less
using namespace __gnu_pbds;
using namespace std;
 
typedef vector< int > vi;
typedef vector< vi > vvi;
typedef pair< int,int > ii;
 
#define sz(a) int((a).size())
#define pb push_back
#define mp make_pair
#define all(c) (c).begin(),(c).end()
#define tr(c,i) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define present(c,x) ((c).find(x) != (c).end())
#define cpresent(c,x) (find(all(c),x) != (c).end())
#define input(v,n) for(ll i=0; i<n; i++) cin>>v[i]
#define output(v,n) for(ll i=0; i<n; i++) cout<<v[i]<<" "
#define ll long long
// a new data structure defined. Please refer below
// GNU link : https://goo.gl/WVDL6g
typedef tree<ll, null_type, less<ll>, rb_tree_tag,
             tree_order_statistics_node_update>
    new_data_set;
 
// Driver function to sort the vector elements
// by second element of pairs
bool sortbysec(const pair<int,int> &a,
              const pair<int,int> &b)
{
    return (a.second < b.second);
}
 
// Driver function to sort the vector elements by
// first element of pair in descending order
bool sortinrev(const pair<int,int> &a,
               const pair<int,int> &b)
{
       return (a.first > b.first);
}
 
// Driver function to sort the vector elements by
// second element of pair in descending order
bool sortbysecdesc(const pair<int,int> &a,
                   const pair<int,int> &b)
{
       return a.second>b.second;
}
 
 
ll gcd(ll a, ll b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
 
}

ll exp(ll x, ll p){
  if(p==0)
    return 1;
  else if(p%2==0)
    return exp(x, p/2)*exp(x, p/2);
  else
    return x*exp(x, p/2)*exp(x, p/2);
}

// /* Iterative Function to calculate (x^y)%p in O(log y) */
// ll power(ll x, ll y, ll p)
// {
//     ll res = 1;      // Initialize result
 
//     x = x % p;  // Update x if it is more than or 
//     // equal to p
//     while (y > 0){
//         // If y is odd, multiply x with result
//         if (y & 1)
//             res = (res*x) % p;
 
//         // y must be even now
//         y = y>>1; // y = y/2
//         x = (x*x) % p;
//     }
//     return res;
// }

#define INF 1000000000
#define ff first
#define ss second
ll dist[1005][1050];
ll fish[1050];
vector<pair<ll, ll> > adj[1005];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n, m, k;
    cin >> n >> m >> k;
    for(ll i= 1; i<=n; i++){
        ll fishes, type;
        cin >> fishes;
        for(ll j=1; j<=fishes; j++){
            cin >> type;
            // fish[i] stores type of fishes available
            fish[i]=(fish[i] | (1<<(type-1)) );
        }
    }
    
    ll p1, p2, weight; 
    for(ll i=1; i<=m; i++){
        cin >> p1 >> p2 >> weight;
        adj[p1].pb(mp(p2, weight));
        adj[p2].pb(mp(p1, weight));
    }

    for(int i=1; i<=n; i++){
        for(int j=0; j<(1<<k); j++){
            dist[i][j]=INF;
        }
    }

    // Dijkstra's Shortest Path Algorithm
    set< pair<ll , pair<ll, ll> > > s;
    // set stores {dist, node, cpat} 
    dist[1][fish[1]]=0;
    s.insert(mp(0, mp(1, fish[1])));
    while(s.size()>0){

        pair<ll, pair<ll, ll>> tmp=*(s.begin());
        s.erase(s.begin());

        ll vn=tmp.second.first;
        ll cpat=tmp.second.second;

        for(ll i=0; i<adj[vn].size(); i++){
            ll v=adj[vn][i].first;
            ll wgt=adj[vn][i].second;
            ll cpat1=(cpat|fish[v]);
            
            // if there is shorter path to v, cpat1 through vn, cpat
            if(dist[vn][cpat] + wgt < dist[v][ cpat1 ] ){
                
                // if already large dist is present
                if(dist[v][cpat1]!=INF){
                    s.erase( s.find( mp(dist[v][cpat1],mp(v, cpat1)) ) );
                }
                
                // update dist[v][ cpat1 ]
                dist[v][ cpat1 ] = (dist[vn][cpat] + wgt);
                s.insert(mp(dist[v][ cpat1 ], mp(v, cpat1)));
            }
        }
    }
    
    ll ans=INF;
    for(ll i=0; i<(1<<k); i++){
        for(ll j=0; j<(1<<k); j++){
            if((i|j)==exp(2, k)-1 ){
                ans=min(ans, max(dist[n][i], dist[n][j]));
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
