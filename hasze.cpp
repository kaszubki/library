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

LL qpot(LL a, LL b, LL p)
{
	LL res = 1;
	if(a == 0) return 0;
	while(b)
	{
		if(b % 2)
		{
			res = (res * a) % p;
		}
		a = (a * a) % p;
		b /= 2;
	}
	return res;
}

LL odwroc(LL a, LL p)
{
	return qpot(a, p - 2, p); 
}

struct hasz
{
	static const LL MOD1, MOD2, P1, P2;
	static vector<LL> pot1, pot2;
	static void initialize(int);
	
	LL ST, ND;
	void przesun(int ile = 1)
	{
		ST = (ST * pot1[ile]) % MOD1;
		ND = (ND * pot2[ile]) % MOD2;
	}
	
	hasz(LL a, LL b) : ST(a), ND(b) {}
	hasz(int c = 0) : ST(c), ND(c) {}
	hasz(string s) : ST(0), ND(0)
	{
		FORD(i, SIZE(s) - 1, 0)
		{
			przesun(1);
			ST += (LL)(s[i] - 'a'); ST %= MOD1;
			ND += (LL)(s[i] - 'a'); ND %= MOD2;
		}
	}
};

const LL hasz::MOD1 = 1000000007, 
         hasz::MOD2 = 1000000009, 
		 hasz::P1 = 121211, 
		 hasz::P2 = 54637;

vector<LL> hasz::pot1 = vector<LL>(), 
           hasz::pot2 = vector<LL>();
		 
void hasz::initialize(int n = N)
{	
	pot1.resize(2 * n + 1);
	pot2.resize(2 * n + 1);
	pot1[0] = 1;
	pot2[0] = 1;
	FOR(i, 1, 2 * n)
	{
		pot1[i] = (pot1[i - 1] * P1) % MOD1;
		pot2[i] = (pot2[i - 1] * P2) % MOD2;
	}
}

hasz operator+ (const hasz &a, const hasz &b)
{
	return hasz((a.ST + b.ST) % hasz::MOD1, 
	            (a.ND + b.ND) % hasz::MOD2); 
}

hasz operator+ (const hasz &a, const LL &b)
{
	return hasz((a.ST + b) % hasz::MOD1, 
	            (a.ND + b) % hasz::MOD2); 
}

hasz operator- (const hasz &a, const hasz &b)
{
	return hasz((a.ST - b.ST + hasz::MOD1) % hasz::MOD1, 
	            (a.ND - b.ND + hasz::MOD2) % hasz::MOD2); 
}

hasz operator- (const hasz &a, const LL &b)
{
	return hasz((a.ST - b + hasz::MOD1) % hasz::MOD1, 
	            (a.ND - b + hasz::MOD2) % hasz::MOD2); 
}

hasz operator* (const hasz &a, const hasz &b)
{
	return hasz((a.ST * b.ST) % hasz::MOD1, 
	            (a.ND * b.ND) % hasz::MOD2);
}

hasz operator* (const hasz &a, const LL &b)
{
	return hasz((a.ST * b) % hasz::MOD1, 
	            (a.ND * b) % hasz::MOD2);
}

hasz operator/ (const hasz &a, const LL &b)
{
	return hasz((a.ST * odwroc(b, hasz::MOD1)) % hasz::MOD1, 
				(a.ND * odwroc(b, hasz::MOD2)) % hasz::MOD2);
}

bool operator== (const hasz &a, const hasz &b)
{
	return (a.ST == b.ST && a.ND == b.ND);
}

hasz przesun(hasz h, int a)
{
	return (h * hasz(hasz::pot1[a], hasz::pot2[a]));
}

int main()
{
	hasz::initialize(5);
	
	string s = "abba";
	string t = "baab";
	string u = "abba";
	
	hasz h[] = {hasz(s), hasz(t), hasz(u)};
	
	cout << (h[0] == h[1]) << "\n";
	cout << (h[1] == h[2]) << "\n";
	cout << (h[2] == h[0]) << "\n";
	
}
