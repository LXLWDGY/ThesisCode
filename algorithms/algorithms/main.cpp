#include "utils.h"
#include "af.h"
#include "pg.h"
#include "fast.h"
#include "fun.h"

void init() {
	oracle.init_f();
	init_N();
}

int main() {

	cout << "Initializing...";

	init();

	cout << "Done." << endl;

	cout << "Guessing OPT...";
	vector<int>single_f;
	for (int i = 0; i <= n; ++i) {
		set<int>s;
		s.insert(i);
		single_f.push_back(oracle.f(s));
	}
	sort(single_f.begin(), single_f.end());

	double guess_low = single_f[n - 1], guess_high = 0.;
	for (int i = n - k; i < n; ++i)
		guess_high += single_f[i];

	vector<double>guess = geometric(guess_low, guess_high, 1. - eps);

	AmortizedFilter AF;
	ParallelGreedy PG;
	FASTAlgo FAST;

	BinarySearch bs(0, guess.size() - 1e-5, 1.);
	while (!bs.done()) {
		OPT = guess[bs.mid()];

		double SOL = oracle.f(FAST.FAST());
		if (SOL >= (1. - 1. / exp(1.)) * OPT)
			bs.larger();
		else
			bs.smaller();
	}
	
	cout << "Done." << endl;

	OPT = guess[bs.mid()];

	cout << "Testing Amortized Filtering..." << endl;

	using namespace std::chrono;

	steady_clock::time_point start, end;
	duration<double> time_span;
	double SOL;

	start = steady_clock::now();

	SOL = oracle.f(AF.Amortized_Filter());

	end = steady_clock::now();
	time_span = duration_cast<duration<double>>(end - start);

	cout << "Solution: " << SOL << endl;
	cout << "Time: " << time_span.count() << endl;

	cout << "Testing Parallel Greedy..." << endl;
	start = steady_clock::now();

	SOL = oracle.f(AF.Amortized_Filter());

	end = steady_clock::now();
	time_span = duration_cast<duration<double>>(end - start);

	cout << "Solution: " << SOL << endl;
	cout << "Time: " << time_span.count() << endl;

	cout << "Testing FAST..." << endl;
	start = steady_clock::now();

	SOL = oracle.f(AF.Amortized_Filter());

	end = steady_clock::now();
	time_span = duration_cast<duration<double>>(end - start);

	cout << "Solution: " << SOL << endl;
	cout << "Time: " << time_span.count() << endl;

	return 0;
}