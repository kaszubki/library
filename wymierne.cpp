//Karol Kaszuba
//http://www.codeforces.com/problemset/problem/372/E

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
#define SQ(x) ((x)*(x))
#define IOSYNC ios_base::sync_with_stdio(0)
#define FREOPEN(f) freopen(f, "r", stdin),freopen(f, "w", stdout)

LL nwd(LL a, LL b)
{
	if(a > b) swap(a, b);
	if(!a) return b;
	return nwd(b % a, a);
}

struct wymierna
{
	LL a, b;
	
	wymierna(LL a, LL b) : a(a), b(b) {normuj();}
	wymierna(LL a) : a(a), b(1) {}
	
	wymierna(){}
	
	void normuj()
	{
		if(b < 0)
		{
			b = -b;
			a = -a;
		}
		if(b == 0)
		{
			//to nie powinno zajsc, ale przezorny zawsze ubezpieczony
			a = 0;
			b = 1;
		}
		else
		{
			LL d = nwd(abs(a), b);
			a /= d;
			b /= d;
		}
	}
	
	friend wymierna operator* (const wymierna &p, const wymierna &q)
	{
		return wymierna(p.a * q.a, p.b * q.b);
	}
	friend wymierna operator/ (const wymierna &p, const wymierna &q)
	{
		return wymierna(p.a * q.b, p.b * q.a);
	}
	friend wymierna operator+ (const wymierna &p, const wymierna &q)
	{
		return wymierna(p.a * q.b + p.b * q.a, p.b * q.b);
	}
	friend wymierna operator- (const wymierna &p, const wymierna &q)
	{
		return wymierna(p.a * q.b - p.b * q.a, p.b * q.b);
	}
	friend bool operator< (const wymierna &p, const wymierna &q)
	{
		if(p.b == 0) return false;
		if(q.b == 0) return true;
		return 0 < p.a * q.b - p.b * q.a;
	}
	friend bool operator== (const wymierna &p, const wymierna &q)
	{
		if(p.b == 0) return q.b == 0;
		return p.a * q.b == p.b * q.a;
	}
	friend ostream & operator<<(ostream &os, const wymierna& p) 
	{
		return os << p.a << "/" << p.b;
	}
};
wymierna odwroc(wymierna p)
{
	return wymierna(p.b, p.a);
}

int main()
{
	int n, m;
	cin >> n >> m;
	wymierna tab[n + 1][m + 1];
	REP(i, n + 1) tab[i][0] = tab[0][i] = 0;
	FOR(i, 1, n)
	{
		FOR(j, 1, m)
		{
			wymierna x = ((tab[i - 1][j - 1] + 1) * j) / (i + j - 1);
			wymierna y = ((i == 1) ? 0 : (tab[i - 2][j] * (i - 1)) / (i + j - 1));
			tab[i][j] = ((i + j) % 2) ? 0 : x + y;
		}
	}
	
	REP(i, n + 1)
	{
		REP(j, m + 1)
			cout << tab[i][j] << " ";
		cout << "\n";
	}
}
