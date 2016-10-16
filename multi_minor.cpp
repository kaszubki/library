//Karol Kaszuba

#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef long long int64;
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

struct Modular {
	static int64 MOD;
	
	int64 n;
	Modular() : n(0) {}
	Modular(int64 n_) : n(n_) {update();}
	
	void update() {
		n = n % MOD;
		if (n < 0) n += MOD;
	}
	
	static Modular qpot(Modular a, int64 b);
	
	Modular operator-() const {
		return Modular(-(this->n));
	}
	
	friend std::ostream& operator<< (std::ostream& stream, const Modular& a) {
		stream << a.n;
		return stream;
    }
};

int64 Modular::MOD;

bool is_zero(const Modular &a) {
	return (a.n == 0);
}

bool operator== (const Modular &a, const Modular &b) {
	return (a.n == b.n);
}

Modular operator+ (const Modular &a, const Modular &b) {
	return Modular(a.n + b.n);
}

Modular operator- (const Modular &a, const Modular &b) {
	return Modular(a.n - b.n);
}

Modular operator* (const Modular &a, const Modular &b) {
	return Modular(a.n * b.n);
}

Modular operator* (const Modular &a, int64 b) {
	return Modular(a.n * b);
}

Modular Modular::qpot(Modular a, int64 b) {
	Modular res = 1;
	while(b) {
		if(b & 1ll) res = res * a;
		a = a * a;
		b >>= 1ll;
	}
	return res;
}
	
Modular operator/ (const Modular &a, const Modular &b) {
	return a * Modular::qpot(b, Modular::MOD - 2LL);
}

template<typename T>
struct Matrix {
	// Type T needs to have standard arithmetic operators,
	// also there needs to be a function bool is_zero.
	vector<vector<T>> M;
	int n, m;
	T det_sign;
	
	Matrix(const vector<vector<T>> &M_) : M(M_), det_sign(T(1)) {
		n = SIZE(M);
		if (n == 0) {
			m = 0;
		} else {
			m = SIZE(M.front());
		}
	}
	
	Matrix(int n_, int m_) : n(n_), m(m_), det_sign(T(1)) {
		M.resize(n);
		REP(i, n) M[i].resize(m);
	}
	
	vector<T> diag() {
		assert(n == m);
		vector<T> d;
		REP(i, n) d.push_back(M[i][i]);
		return d;
	}
	
	vector<T> get_row(int nr) {
		assert(nr < n);
		return M[nr];
	}
	
	void swap_rows(int a, int b) {
		swap(M[a], M[b]);
	}
	
	void multiply_row(int i, T ile) {
		assert(i < n);
		REP(j, m) {
			M[i][j] = M[i][j] * ile;
		}
	}
	
	void single_gauss_operation(int row1, int row2, T ile) {
		if (is_zero(ile)) return;
		FOR(i, row2, m - 1) {
			M[row1][i] = M[row1][i] - (M[row2][i] * ile);
		}
	}
	
	void rotate_rows() {
		REP(i, n - 1) swap_rows(i, i + 1);
	}
	
	int find_suitable_row(int act_row, int col) {
		FOR(i, act_row, n - 2) {
			if (!is_zero(M[i][col])) return i;
		}
		return -1;
	}
	
	void make_suitable(int act_row, int col) {
		int to_swap = find_suitable_row(act_row, col);
		if (to_swap > act_row) {
			swap_rows(to_swap, act_row);
			det_sign = -det_sign;
		}
	}
	
	void bash_lower_gauss(int act_row) {
		make_suitable(act_row, act_row);
		if (!is_zero(M[act_row][act_row])) {
			FOR(i, act_row + 1, n - 1) {
				single_gauss_operation(
				    i, act_row, M[i][act_row] / M[act_row][act_row]);
			}
		}
	}
	
	void bash_upper_gauss(int act_row) {
		if (!is_zero(M[act_row][act_row])) {
			FORD(i, act_row - 1, 0) {
				single_gauss_operation(
				    i, act_row, M[i][act_row] / M[act_row][act_row]);
			}
		}
	}
	
	void one_way_gauss(function<void(int)> f) {
		REP(i, n) {
			f(i);
		}
	}
	
	void full_gauss() {
		one_way_gauss(
		    std::bind(&Matrix::bash_lower_gauss, this, std::placeholders::_1));
		one_way_gauss(
		    std::bind(&Matrix::bash_upper_gauss, this, std::placeholders::_1));
	}
	
	void zero_a_row(int nr) {
		REP(j, m) M[nr][j] = T(0);
	}
	
	vector<T> make_dp() {
		vector<T> dp(n + 1);
		dp[n] = T(1);
		dp[n - 1] = M[n - 2][n - 1];
		if (n > 2) {
			dp[n - 2] = (M[n - 2][n - 1] * M[n - 3][n - 2]) - 
						(M[n - 2][n - 2] * M[n - 3][n - 1]);
			int last_zero = (is_zero(M[n - 2][n - 2]) ? n - 2 : n - 1);
			T prod = (is_zero(M[n - 2][n - 2]) ? 1 : M[n - 2][n - 2]);
			FORD(i, n - 3, 1) {
				if (is_zero(M[i][i])) {
					dp[i] = dp[i + 1] * M[i - 1][i];
					last_zero = i;
					prod = T(1);
				} else {
					int l = last_zero - i;
					prod = prod * M[i][i];
					dp[i] = prod;
					dp[i] = dp[i] * M[i - 1][i + l];
					dp[i] = dp[i] * dp[i + l + 1];
					if (l & 1) dp[i] = -dp[i];
				}
			}
		}
		return dp;
	}
	
	vector<T> get_last_minors() {
		zero_a_row(n - 1);
		full_gauss();
		vector<T> pref, dp = make_dp(), minors;
		pref.push_back(T(1));
		FOR(i, 0, n - 1) {
			pref.push_back(pref.back() * M[i][i]);
		}
		REP(i, n) {
			T minor = det_sign * pref[i] * dp[i + 1];
			minors.push_back(minor);
		}
		return minors;
	}
	
	vector<vector<T>> get_all_minors() {
		vector<vector<T>> res;
		T signd(1);
		REP(i, n) {
			rotate_rows();
			Matrix oldM(*this);
			res.push_back(oldM.get_last_minors());
			if (n & 1) {
				REP(j, SIZE(res.back())) res.back()[j] = res.back()[j] * signd;
				signd = -signd;
			}
		}
		return res;
	}
	
	T get_det(const vector<vector<T>>& minors) {
		T res = 0;
		REP(i, n) {
			T tmp = minors[0][i] * M[0][i];
			if (i & 1) tmp = -tmp;
			res = res + tmp;
		}
		return res;
	}
	
	T det() {
		full_gauss();
		T d = det_sign;
		for(T el : diag()) d = d * el;
		return d;
	}
};
