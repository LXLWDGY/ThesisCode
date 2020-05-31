#pragma once
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <chrono>
#include <iostream>
#include <fstream>
using namespace std;

const int n = 500;
const int k = 10;
set<int>N;

const double eps = 0.1;
const double delta = 0.1;

double OPT;

double rand01() {
	return (double)(rand() % 10000) / 10000.;
}

set<int> random_set(set<int> s, int size) {
	set<int>R;

	for (int sample = 0; sample < size; ++sample) {
		int e = s.size() * rand01();

		set<int>::iterator it = s.begin();
		for (int i = 0; i < e; ++i)
			++it;

		R.insert(*it);
		s.erase(it);
	}

	return R;
}

vector<int> random_sequence(set<int> s, int size) {
	vector<int>R;

	for (int sample = 0; sample < size; ++sample) {
		int e = s.size() * rand01();

		set<int>::iterator it = s.begin();
		for (int i = 0; i < e; ++i)
			++it;

		R.push_back(*it);
		s.erase(it);
	}

	return R;
}

void join(set<int>& A, const set<int>& B) {

	for (set<int>::iterator it = B.begin(); it != B.end(); ++it) {
		int element = *it;
		A.insert(element);
	}

}

void subtract(set<int>& A, const set<int>& B) {

	for (set<int>::iterator it = B.begin(); it != B.end(); ++it) {
		int element = *it;

		if (A.count(element)) {
			A.erase(element);
		}

	}

}

vector<double>geometric(double start, double end, double ratio) {
	vector<double>ans;
	for (double x = start; x < end; x *= ratio)
		ans.push_back(x);
	return ans;
}

double in_prod(const vector<double>& A, const vector<double>& B) {
	double ans = 0.0;

	for (int i = 0; i < n; ++i) ans += A[i] * B[i];
	
	return ans;
}

void init_N() {
	for (int i = 0; i < n; ++i)
		N.insert(i);
}

const int FILTER_sample_size = 100;
const int F_sample_size = 100;