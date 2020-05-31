#pragma once
#include "utils.h"

class BinarySearch {
	double lower_bound, upper_bound, min_gap;
public:
	void set(double l, double u, double mg) {

		lower_bound = l;
		upper_bound = u;
		min_gap = mg;

	}
	BinarySearch(double l, double u, double mg): lower_bound(l), upper_bound(u), min_gap(mg) {}

	double mid() {
		return (lower_bound + upper_bound) / 2.;
	}

	double gap() {
		return upper_bound - lower_bound;
	}

	bool done() {
		return gap() < min_gap;
	}

	void larger() {
		lower_bound = (lower_bound + upper_bound) / 2.;
	}

	void smaller() {
		upper_bound = (lower_bound + upper_bound) / 2.;
	}
};
