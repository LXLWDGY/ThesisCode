#pragma once
#include "utils.h"
#include "bs.h"
#include "fun.h"

class FASTAlgo {
	double t;
	double m;
public:
	set<int> FAST() {
		t = log(log(k)) - log(eps);
		m = (2. + eps) / eps / eps / (1. - 3. * eps) * log(4. * t * log(n) / eps / eps);
		set<int>S;

		for (int rounds = 0; rounds < 1. / eps && S.size() < k; ++rounds) {
			set<int>X(N);
			double t = (1. - eps) * (OPT - oracle.f(S)) / (double)k;
			while (!X.empty() && S.size() < k) {
				vector<int>a = random_sequence(X, X.size());

				vector<set<int> > SA;
				set<int>A = S;
				for (int i = 0; i < a.size(); ++i) {

					SA.push_back(A);

					A.insert(a[i]);
					double margin = oracle.f(A);

					A.erase(a[i]);
					margin -= oracle.f(A);

					if (margin >= t) S.insert(a[i]);
				}

				set<int>X0;
				for (set<int>::iterator it = X.begin(); it != X.end(); ++it) {
					int a = *it;

					A.insert(a);
					double margin = oracle.f(A);
					A.erase(a);
					margin -= oracle.f(A);

					if (margin >= t) X0.insert(a);
				}

				if (X0.size() <= (1. - eps) * X.size()) {
					X0 = X;
					continue;
				}
				
				set<int>R = random_set(X, m);

				vector<double>I = geometric(1., k - S.size(), 1. - eps);

				double i_star;
				BinarySearch bs(0, I.size() - 1e-5, 1.);

				while (!bs.done()) {
					i_star = bs.mid();
					set<int>A = SA[i_star];

					int cnt = 0;
					for (set<int>::iterator it = R.begin(); it != R.end(); ++it) {

						A.insert(*it);
						double margin = oracle.f(A);

						A.erase(*it);
						margin -= oracle.f(A);

						if (margin >= t) ++cnt;
					}

					if ((double)cnt >= (1. - 2. * eps) * (double)R.size())
						bs.larger();
					else
						bs.smaller();

				}

				i_star = bs.mid();
				join(S, SA[i_star + 1]);
			}
		}

		return S;
	}
};