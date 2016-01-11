#pragma once

#include <include\ISQpp.h>
#include <include\SimulationParameters.h>
#include <include\SpatialHashMap.h>
#include <include\Particle.h>

class Simulation
{
	friend class Renderer;
public:
	void initialize(SimulationParameters, BulkSimData);
	si::time step();

protected:
	std::vector<Boundary> m_boundaries;
	SpatialHashMap<Particle*> m_particles;
	SimulationParameters m_parameters;

private:
	void do_discrete_step(si::time);
	void do_reverse_half_euler(si::time);

	si::vec::acceleration gravity();
};
