//Karol Kaszuba

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,x,y) for(auto i=(x);i<=(y);++i)
#define REP(i,x) FOR(i,0,(x)-1)
#define ALL(c) (c).begin(),(c).end()
#define PB push_back

struct Node
{
	vector<int> neigh; //wektor z sasiadami
	unordered_set<int> s_neigh; //modyfikowalny kontener z sasiadami
	vector<int> roots; //wektor z kolejnymi korzeniami drzew
	int vis; //zmienna pomocnicza
	int subtree; //zmienna pomocnicza
};

struct Tree
{
	vector<Node> v;
	int n;
	
	Tree() {}
	
	int read_input()
	{
		cin >> n;
		v.resize(n);
		
		REP(i, n - 1)
		{
			int a, b;
			cin >> a >> b;
			a--; b--; //zakomentowac jesli numery sa od 0 do n-1
			v[a].neigh.PB(b);
			v[b].neigh.PB(a);
		}
		
		REP(i, n)
			v[i].s_neigh = unordered_set<int>(ALL(v[i].neigh));
		
		return n;
	}
	
	void dfs_subtree(int start, int vis)
	{
		v[start].subtree = 1;
		v[start].vis = vis;
		
		for(auto nast : v[start].s_neigh)
		{
			if(v[nast].vis != vis)
			{
				dfs_subtree(nast, vis);
				v[start].subtree += v[nast].subtree;
			}
		}
	}
	
	void dfs_centroid(int start, int vis, int &centroid, int r)
	{
		v[start].vis = vis;
		bool not_a_centroid = false;
		
		for(auto nast : v[start].s_neigh)
		{
			if(v[nast].vis != vis)
			{
				dfs_centroid(nast, vis, centroid, r);
				if(v[nast].subtree * 2 > r)
					not_a_centroid = true;
			}
		}
		
		if(not_a_centroid || (v[start].subtree * 2 < r))
			return;
		
		centroid = start;
	}
	
	void dfs_push_root(int start, int vis, int root)
	{
		v[start].vis = vis;
		v[start].roots.PB(root);
		
		for(auto nast : v[start].s_neigh)
			if(v[nast].vis != vis)
				dfs_push_root(nast, vis, root);
	}
	
	int get_centroid(int start)
	{
		int vis = (int)v[start].roots.size() + 1;
		v[start].vis = vis;
		int centroid = -1;
		dfs_subtree(start, vis);
		dfs_centroid(start, 0, centroid, v[start].subtree);
		return centroid;
	}
	
	void decomposition(int start=0)
	{
		int centroid = get_centroid(start);
		dfs_push_root(centroid, -1, centroid);
		for(auto p : v[centroid].s_neigh)
		{
			v[p].s_neigh.erase(centroid);
			decomposition(p);
		}
	}
};

int main()
{
	Tree t;
	int n = t.read_input();
	t.decomposition();
	
	REP(i, n)
	{
		cout << i << " : ";
		for(auto r : t.v[i].roots)
			cout << r << " ";
		cout << "\n";
	}
}
