/*
* Copyright © 2015 Jeremy T. Hatcher All Rights Reserved
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include <chrono>
#include <thread>

#include <include\Simulation.h>
#include <include\Renderer.h>

void sim_thread(Simulation* sim, Renderer* renderer) {
	while (renderer->is_open()) {
		sim->step();
	}
}

void render_thread(Simulation* sim, Renderer* renderer) {
	while (renderer->is_open()) {
		renderer->render(sim);
	}
}

//#define TEST

int main(int argc, char** argv)
{
	si::vec::position p1(0.0, 0.0);
	si::vec::position p2(1.0, 0.0);

	si::vec::position u1(0.5, 0.5);
	si::vec::position u2(0.5, -0.5);
	
	std::cout << "Intersects? " << test_line_intersection_2d(p1, p2, u1, u2);

#ifdef TEST
	Particle prototype;
	prototype.position = si::vec::position(0.0, 0.0);
	prototype.velocity = { 1.5, -1 };
	prototype.mass_density = 998.29;
	prototype.mass = 0.02;
	prototype.support_radius = 0.0427;
	prototype.temperature = 293;

	SimulationParameters params;
	params.gravity = si::vec::acceleration(0.0, 9.8);
	params.support_radius = 0.0457;
	params.time_step = 0.0001;
	params.gas_constant = 3;

	BulkSimData bulk;
	//bulk.add_particle(prototype);
	//bulk.add_particle(prototype, si::vec::position(0.08, 0.01));
	//bulk.add_particle(prototype, si::vec::position(0.08, -0.05));
	//bulk.add_particle(prototype, si::vec::position(0.03, -0.2));
	bulk.add_particle(prototype, si::vec::position(-0.1, -0.07));
	bulk.add_boundary(si::vec::position(-0.3, 0.1), si::vec::position(-0.4, -0.1));
	bulk.add_boundary(si::vec::position(-0.3, 0.1), si::vec::position(0.3, 0.1));
	bulk.add_boundary(si::vec::position(0.3, 0.1), si::vec::position(0.4, -0.1));

	Simulation sim;
	sim.initialize(params, bulk);

	Renderer renderer;

	renderer.deactivate_context();
	std::thread t_render(&render_thread, &sim, &renderer);
	std::thread t_sim(&sim_thread, &sim, &renderer);

	bool running = true;
	while (renderer.is_open()) {
		renderer.handle_events();
	}

	t_sim.join();
	t_render.join();
#endif // TEST

#ifdef _DEBUG
	std::cout << std::endl; system("pause");
#endif
	return 0;
}
