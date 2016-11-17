//Karol Kaszuba

#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef vector<int> VI;
typedef pair<int, int> PII;
typedef double D;
typedef long double LD;
typedef vector<PII> VII;
typedef unordered_set<int> USI;
typedef unordered_set<LL> USLL;

#define FOR(i,x,y) for(auto i=(x);i<=(y);++i)
#define REP(i,x) FOR(i,0,(x)-1)
#define FORD(i,x,y) for(auto i=(x);i>=(y);--i)
#define VAR(i,c) __typeof(c) i=(c)
#define FORE(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define SIZE(c) (int)((c).size())
#define ALL(c) (c).begin(),(c).end()
#define PB push_back
#define EB emplace_back
#define IN insert
#define ER erase
#define MP make_pair
#define ST first
#define ND second
#define IOSYNC ios_base::sync_with_stdio(0)
#define FREOPEN(f) freopen(f, "r", stdin),freopen(f, "w", stdout)

const int N = 100005;

struct path
{
	static int PATH_ID;
	VI nodes;
	
	void add_node(int a)
	{
		nodes.PB(a);
	}
} paths[N];

int path::PATH_ID = 0;

struct node
{
	int dep;
	int subtree;
	int path_id;
	int pos_on_path;
	int parent;
	int heavy_son;
	VI v;
} tree[N];

void dfs(int a)
{
	//usun parenta z listy sasiadow
	for(int &b : tree[a].v)
	{
		if(b == tree[a].parent)
		{
			b = tree[a].v.back();
			tree[a].v[SIZE(tree[a].v) - 1] = -1;
		}
	}
	if(tree[a].v.back() == -1) tree[a].v.pop_back();
	
	tree[a].subtree = 1;
	
	if(!tree[a].v.empty())
	{	
		for(int b : tree[a].v)
		{
			tree[b].parent = a;
			tree[b].dep = tree[a].dep + 1;
			dfs(b);	
			tree[a].subtree += tree[b].subtree;
		}
		
		tree[a].heavy_son = tree[a].v[0];
		for(int b : tree[a].v)
			if(tree[b].subtree > tree[tree[a].heavy_son].subtree)
				tree[a].heavy_son = b;
	}
}

void dfs_bp(int a)
{
	for(int b : tree[a].v)
	{
		if(b == tree[a].heavy_son)
		{
			tree[b].path_id = tree[a].path_id;
			tree[b].pos_on_path = tree[a].pos_on_path + 1;
		}
		else
		{
			tree[b].path_id = ++path::PATH_ID;
			tree[b].pos_on_path = 0;
		}
		dfs_bp(b);
	}
}

void dfs_cp(int a)
{
	paths[tab[i].path_id].add_node(i);
	for(int b : tab[a].v)
		dfs_cp(b);
}

int read_tree()
{
	int n;
	cin >> n;
	REP(i, n)
	{
		int a, b;
		cin >> a >> b;
		//a++; b++; //ODKOMENTOWAC JESLI NUMEROWANE OD 0
		tree[a].v.PB(b);
		tree[b].v.PB(a);
	}
	return n;
}

void jebaj()
{
	int n = read_tree();
	dfs(1);
	dfs_bp(1);
	
	FOR(i, 1, n)
	{
		paths[tab[i].path_id].add_node(i);
	}
}

int main()
{
	IOSYNC;
	int t = 1;
	//cin >> t;
	
	REP(i, t)
	{
		jebaj();
	}
}
