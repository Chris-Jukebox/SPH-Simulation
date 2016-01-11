#pragma once

#include <include\ISQpp.h>

struct Particle {
	si::mass mass;
	si::density mass_density;
	si::pressure pressure;
	si::temperature temperature;

	si::vec::position position;
	si::vec::velocity velocity;
	si::vec::velocity last_velocity;
	si::vec::acceleration acceleration;

	si::vec::force accumulated_force;

	si::length support_radius;

protected:
	unsigned int uid;
	friend bool operator==(const Particle&, const Particle&);
	friend class Simulation;
};

static bool operator==(const Particle& lhs, const Particle& rhs) {
	return lhs.uid == rhs.uid;
}
