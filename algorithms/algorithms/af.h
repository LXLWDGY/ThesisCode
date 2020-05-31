#pragma once
#include "utils.h"
#include "fun.h"

class AmortizedFilter {
	int r;

	double get_marginal_contribution(set<int>& X, set<int>& S) {
		double ans = 0.0;

		for (int sample = 0; sample < FILTER_sample_size; ++sample) {
			set<int>R = random_set(X, k / r);
			
			ans += oracle.f(S);
			join(R, S);
			ans -= oracle.f(R);
		}

		ans /= (double)FILTER_sample_size;
		return ans;
	}

	double get_marginal_contribution_without_element(set<int>& X, set<int>& S, int a) {
		double ans = 0.0;

		for (int sample = 0; sample < FILTER_sample_size; ++sample) {
			set<int>R = random_set(X, k / r);

			if (R.count(a)) R.erase(a);

			ans += oracle.f(S);
			join(R, S);
			ans -= oracle.f(R);
		}

		ans /= (double)FILTER_sample_size;
		return ans;
	}

	void Filter(set<int>& X, set<int> S) {

		while (1) {
			double mc = get_marginal_contribution(X, S);
			if (mc > (1. - eps) * (OPT - oracle.f(S))) break;

			set<int>remove;

			for (set<int>::iterator it = X.begin(); it != X.end(); ++it) {
				int element = *it;
				double mc = get_marginal_contribution_without_element(X, S, element);
				if (mc < (1. + eps / 2.) * (1. - eps) * (OPT - oracle.f(S)) / (double)k)
					remove.insert(element);
			}

			subtract(X, remove);
		}

	}

public:
	set<int> Amortized_Filter() {
		set<int>S;

		r = 20. * log(n) / log(1. + eps / 2.) / eps;

		for (int epoch = 0; epoch < 20. / eps; ++epoch) {
			set<int>X = N, T;

			while (1) {
				set<int>SplusT = S;
				join(SplusT, T);

				double margin = oracle.f(SplusT) - oracle.f(S);
				if (margin > eps / 20. * (OPT - oracle.f(S)))
					break;
				if (SplusT.size() < k)
					break;

				Filter(X, SplusT);
				set<int>R = random_set(X, k / r);
				join(T, R);
			}

			join(S, T);
		}

		return S;
	}
};
