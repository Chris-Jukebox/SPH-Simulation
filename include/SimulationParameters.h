#pragma once

#include <vector>
#include <include\ISQpp.h>
#include <include\Particle.h>

struct Boundary {
	si::vec::position start;
	si::vec::position end;
};

struct SimulationParameters {
	si::time time_step;
	si::length support_radius;
	si::vec::acceleration gravity;
	si::dimensionless gas_constant;
};

struct BulkSimData {
	std::vector<Particle> particles;
	std::vector<Boundary> boundaries;

	void add_particle(Particle p, si::vec::position pos) {
		p.position = pos;
		add_particle(p);
	}

	void add_particle(Particle p) {
		particles.push_back(p);
	}

	void add_boundary(si::vec::position start, si::vec::position end) {
		add_boundary(Boundary{ start, end });
	}

	void add_boundary(Boundary b) {
		boundaries.push_back(b);
	}
};
