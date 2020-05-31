#pragma once
#include "utils.h"

class SubmodularFunction {

	bool g[n][n];

public:

	bool getG(int i, int j) {
		return g[i][j];
	}

	void init_f(const char* fileName = "graph.txt") {

		memset(g, 0, sizeof(g));
		ifstream fin(fileName);

		while (!fin.eof()) {
			int x, y;
			fin >> x >> y;
			g[x][y] = 1;
			g[y][x] = 1;
		}

	}

	int f(const set<int>& s) {
		int ans = 0;

		for (int i = 1; i < n; ++i)
			for (int j = 0; j < i; ++j)
				if (g[i][j])
					if (s.count(i) || s.count(j))
						++ans;

		return ans;
	}

	double F(const vector<double>& x) {
		double ans = 0.0;

		for (int sample = 0; sample < F_sample_size; ++sample) {
			set<int>s;

			for (int i = 0; i < n; ++i)
				if (rand01() < x[i])
					s.insert(i);

			ans += f(s);
		}

		ans /= (double)F_sample_size;

		return ans;
	}

	double F_grad(const vector<double>& x, int j) {
		double ans = 0.0;

		for (int sample = 0; sample < F_sample_size; ++sample) {
			set<int>s;

			for (int i = 0; i < n; ++i)
				if (rand01() < x[i])
					s.insert(i);

			s.insert(j);
			ans += f(s);

			s.erase(j);
			ans -= f(s);
		}

		ans /= (double)F_sample_size;

		return ans;
	}
}oracle;