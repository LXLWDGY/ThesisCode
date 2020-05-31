#pragma once
#include "utils.h"
#include "fun.h"
#include "bs.h"

class ParallelGreedy {
	set<int> rounding(const vector<double>& x) {
		set<int>S;

		for (int i = 0; i < n; ++i)
			if (rand01() < x[i])
				S.insert(i);

		return S;
	}
public:
	set<int> parallel_greedy() {

		vector<double>x(n, 0.), ones(n, 1.);
		double lambda = OPT;

		while (in_prod(x, ones) <= k && lambda >= OPT / exp(1.)) {
			set<int>S;

			for (int j = 0; j < n; ++j)
				if (oracle.F_grad(x, j) >= (1. - eps) * lambda / (double)k)
					S.insert(j);

			while (!S.empty() && in_prod(x, ones) <= k) {
				double delta;
				BinarySearch bs(0., 1., 1e-5);

				while (!bs.done()) {
					delta = bs.mid();

					vector<double>newx(x);

					for (set<int>::iterator it = S.begin(); it != S.end(); ++it) {
						newx[*it] += delta;
					}

					double margin = oracle.F(newx) - oracle.F(x);
					if (margin >= (1. - eps) * (1. - eps) * lambda * delta * (double)S.size() / (double)k
						&& in_prod(newx, ones) <= k)
						bs.larger();
					else
						bs.smaller();
				}

				delta = bs.mid();

				for (set<int>::iterator it = S.begin(); it != S.end(); ++it) {
					x[*it] += delta;
				}

				S.clear();
				for (int j = 0; j < n; ++j)
					if (oracle.F_grad(x, j) >= (1. - eps) * lambda / (double)k)
						S.insert(j);

			}

			lambda = (1. - eps) * lambda;

		}

		set<int> S = rounding(x);
		return S;
	}
};