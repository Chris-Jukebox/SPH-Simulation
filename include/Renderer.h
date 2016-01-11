#pragma once

#include <SFML\Graphics.hpp>
#include <include\ISQpp.h>
#include <include\Utility.h>

class Simulation;

class Renderer
{
	sf::RenderWindow m_window;
	sf::View m_view;

	float zoom = 1000;

	bool m_draw_particles = true;
	bool m_draw_velocity = true;
	bool m_draw_force;
	bool m_draw_grid = true;
	bool m_draw_hash = true;
	bool m_draw_bounds = true;

	Simulation* m_current_simulation;

public:
	Renderer();

	bool is_open();

	sf::Event handle_events();
	si::time render(Simulation*);
	void run_threaded(Simulation*);
	void deactivate_context();

private:
	void rendering_thread();
};
