#pragma once

#include <include\ISQpp.h>

namespace kconsts {
	const double pi = 3.14159265359;
}

static double cubic_spline_2d(si::vec::position r, si::length h) {
	double Ch = 1 / (h * 6);
	//double Ch = 15 / (14 * 3.1415959 * std::pow(h, 2));
	//double Ch = 1.0 / (4 * 3.1415959 * std::pow(h, 2));

	double q = std::sqrt(r.x * r.x + r.y * r.y) / h;
	if (q >= 0 && q < 1) return Ch * (   std::pow((2 - q), 3) - (4 * (std::pow((1 - q), 3)))   );
	if (q >= 1 && q < 2) return Ch * (   std::pow( (2 - q), 3)   );
	else return 0.0;
}

static double cubic_spline_2d_gradient(si::vec::position r, si::length h) {
	return 0.0;
}

static double poly6_2d(si::vec::position r, si::length h) {
	static si::length sh;
	static double sCh = 0.0;
	if (sh != h || sCh == 0.0) { // avoid recalculating constant unless h changes
		sh = h;
		sCh = 315.0 / (64.0 * kconsts::pi * std::pow(h, 9));
	}
	double q = std::sqrt(r.x * r.x + r.y * r.y);
	if (q >= 0 && q <= h) return sCh * std::pow(((h*h) - (q*q)), 3);
	else return 0.0;
}

static si::vec::field poly6_2d_gradient(si::vec::position r, si::length h) {
	static si::length sh;
	static double sCh = 0.0;
	if (sh != h || sCh == 0.0) {
		sh = h;
		sCh = -1.0 * (945.0 / (32.0 * kconsts::pi * std::pow(h, 9)));
	}
	double q = std::sqrt(r.x * r.x + r.y * r.y);
	return si::vec::field(r.x, r.y) * sCh * std::pow(((h*h) - (q*q)), 2);
}

static double poly6_2d_laplace(si::vec::position r, si::length h) {
	static si::length sh;
	static double sCh = 0.0;
	if (sh != h || sCh == 0.0) {
		sh = h;
		sCh = -1.0 * (945.0 / (32.0 * kconsts::pi * std::pow(h, 9)));
	}
	double q = std::sqrt(r.x * r.x + r.y * r.y);
	return sCh * ((  (h*h) - (q*q)  ) * (  (3*(q*q)) - (7 * (q*q))  ));
}

static double spikey_2d(si::vec::position r, si::length h) {
	static si::length sh;
	static double sCh = 0.0;
	if (sh != h || sCh == 0.0) {
		sh = h;
		sCh = (15.0 / (kconsts::pi * std::pow(h, 6)));
	}
	double q = std::sqrt(r.x * r.x + r.y * r.y);
	if (q >= 0 && q <= h) return sCh * std::pow(h - q, 3);
	else return 0.0;
}

static si::vec::field spikey_2d_gradient(si::vec::position r, si::length h) {
	static si::length sh;
	static double sCh = 0.0;
	if (sh != h || sCh == 0.0) {
		sh = h;
		sCh = (45.0 / (kconsts::pi * std::pow(h, 6)));
	}
	double q = std::sqrt(r.x * r.x + r.y * r.y);
	return (si::vec::field(r.x, r.y) / q) * sCh * std::pow(h - q, 2);
}

static double spikey_2d_laplacian(si::vec::position r, si::length h) {
	static si::length sh;
	static double sCh = 0.0;
	if (sh != h || sCh == 0.0) {
		sh = h;
		sCh = (90.0 / (kconsts::pi * std::pow(h, 6)));
	}
	double q = std::sqrt(r.x * r.x + r.y * r.y);
	return sCh * (1 / q) * (h - q) * (h - (2 * q));
}
