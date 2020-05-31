#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#define w 1000
#define n 100
#define scale 0.45
const double pi = acos(-1.0);
using namespace cv;
using namespace std;

void DrawER() {
	double px[n], py[n];
	srand((int)time(0));
	Mat img(w, w, CV_8UC3, Scalar(255, 255, 255));
	for (int i = 0; i < n; ++i) {
		double x = w * (0.5 + scale * sin(2.0 * pi / (double)n * (double)i)), y = w * (0.5 + scale * cos(2.0 * pi / (double)n * (double)i));
		px[i] = x; py[i] = y;
	}
	ofstream fout("ER.txt");
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (rand() % 50 == 0) {
				line(img, Point(px[i], py[i]), Point(px[j], py[j]), Scalar(100, 100, 100));
				fout << i << ' ' << j << endl;
			}
		}
	}
	fout.close();
	for (int i = 0; i < n; ++i) {
		double x = px[i], y = py[i];
		circle(img, Point(x, y), 4, Scalar(100, 150, 200), FILLED, LINE_8);
	}
	imwrite("ER.jpg", img);
}

void DrawBA() {
	double px[n], py[n];
	int deg[n], totdeg = 0, f[n][n];
	memset(f, 0, sizeof(f));
	srand((int)time(0));
	Mat img(w, w, CV_8UC3, Scalar(255, 255, 255));
	for (int i = 0; i < n; ++i) {
		double x = w * (0.5 + scale * sin(2.0 * pi / (double)n * (double)i)), y = w * (0.5 + scale * cos(2.0 * pi / (double)n * (double)i));
		px[i] = x; py[i] = y;
	}
	ofstream fout("BA.txt");
	for (int i = 0; i < n; ++i) {
		deg[i] = 0; totdeg = 0;
		for (int j = 0; j < i; ++j) totdeg += deg[j];
		for (int e = 0; e < 1; ++e) {
			double p = (double)(rand() % 10000) / 10000. * (double)totdeg;
			for (int j = 0; j < i; ++j) {
				p -= (double)deg[j];
				if (p < 1e-5) {
					line(img, Point(px[i], py[i]), Point(px[j], py[j]), Scalar(100, 100, 100));
					fout << i << ' ' << j << endl;
					++deg[i];
					++deg[j];
					break;
				}
			}
		}
	}
	fout.close();
	for (int i = 0; i < n; ++i) {
		double x = px[i], y = py[i];
		circle(img, Point(x, y), 4, Scalar(200, 100, 150), FILLED, LINE_8);
	}
	imwrite("BA.jpg", img);
}

void DrawFB() {
	double px[n], py[n];
	int deg[n], totdeg = 0, f[n][n];
	memset(f, 0, sizeof(f));
	srand((int)time(0));
	Mat img(w, w, CV_8UC3, Scalar(255, 255, 255));
	for (int i = 0; i < n; ++i) {
		double x = w * (0.5 + scale * sin(2.0 * pi / (double)n * (double)i)), y = w * (0.5 + scale * cos(2.0 * pi / (double)n * (double)i));
		px[i] = x; py[i] = y;
	}
	ifstream fin("FB.txt");
	while (!fin.eof()) {
		int x, y;
		fin >> x >> y;
		x -= 1000; y -= 1000;
		if (x < n && y < n && x >= 0 && y >= 0) {
			f[x][y] = 1;
			line(img, Point(px[x], py[x]), Point(px[y], py[y]), Scalar(100, 100, 100));
		}
	}
	fin.close();
	for (int i = 0; i < n; ++i) {
		double x = px[i], y = py[i];
		circle(img, Point(x, y), 4, Scalar(150, 200, 100), FILLED, LINE_8);
	}
	imwrite("FB.jpg", img);
}