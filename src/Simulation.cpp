#include <include\Simulation.h>
#include <include\Utility.h>
#include <include\Kernels.h>

#include <iostream>

static si::density calculate_particle_density(Particle* particle, std::vector<Particle*>& others) {
	si::density sum;
	for (auto elem : others) {
		sum += elem->mass * poly6_2d(particle->position - elem->position, particle->support_radius);
	}
	return sum;
}

void Simulation::initialize(SimulationParameters params, BulkSimData data)
{
	//m_particles = SpatialHashMap<Particle*>(params.support_radius * 3, SpatialHashQueryMode::SingleCell, SpatialHashFlags::None);
	m_particles.clear();
	m_parameters = params;

	for (auto boundary : data.boundaries) {
		m_boundaries.push_back(boundary);
	}

	for (auto particle : data.particles) {
		particle.uid = next_unique_id();
		particle.acceleration = si::vec::acceleration(0.0, 0.0);
		m_particles.insert(particle.position.x, particle.position.y, new Particle(particle));
	}

	do_reverse_half_euler(m_parameters.time_step);
}

si::time Simulation::step()
{
	si::time start_time = get_running_time();

	do_discrete_step(m_parameters.time_step);

	si::time end_time = get_running_time();
	return (end_time - start_time);
}

void Simulation::do_discrete_step(si::time dt)
{
	auto vec = m_particles.query_all();

	si::density rho;
	for (auto particle : vec) {
		auto locals = m_particles.query(particle->position.x, particle->position.y);

		rho = particle->mass_density;

		rho = calculate_particle_density(particle, locals);
		
		particle->accumulated_force = si::vec::force(0.0, 0.0);

		particle->pressure = (rho * m_parameters.gas_constant);
	}

	for (auto particle : vec) {
		auto locals = m_particles.query(particle->position.x, particle->position.y);
		for (auto other : locals) {
			if (particle == other) continue;

			si::pressure pressure = (particle->pressure / (std::pow(rho, 2))) + (other->pressure / (std::pow(rho, 2)));
			si::vec::field gradient = poly6_2d_gradient(particle->position - other->position, m_parameters.support_radius);
			si::vec::force fpressure = (gradient * pressure) * -1.0;
			particle->accumulated_force += fpressure * -1.0;
			other->accumulated_force += fpressure * 1.0;
		}

		// Leapfrog integration
		si::vec::position last_position = particle->position;

		particle->last_velocity = particle->velocity;
		particle->velocity += (particle->accumulated_force / particle->mass + gravity()) * dt;
		particle->position += (particle->velocity) * dt;

		// Boundary collision
		for (auto boundary : m_boundaries) {
			//if((particle->position + particle->velocity * dt))
			
		}

		// Update our spatial hash with new particle coordinates
		m_particles.translate(last_position.x, last_position.y, particle->position.x, particle->position.y, particle);
	}
}

void Simulation::do_reverse_half_euler(si::time dt)
{
	auto vec = m_particles.query_all();
	for (auto particle : vec) {
		particle->last_velocity = particle->velocity - 0.5 * dt * particle->acceleration;
	}
}

si::vec::acceleration Simulation::gravity()
{
	return m_parameters.gravity;
}

