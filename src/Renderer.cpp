#include <include\Simulation.h>
#include <include\Renderer.h>

#include <iostream>
#include <thread>

Renderer::Renderer()
{
	auto mode = sf::VideoMode(800, 600);
	auto style = sf::Style::Titlebar;
	auto settings = sf::ContextSettings();
	m_window.create(mode, "SPH", style, settings);

	m_view.setCenter(0.0, 0.0);
	m_view.setSize(800, 600);

	m_window.setView(m_view);
}

bool Renderer::is_open()
{
	return m_window.isOpen();
}

sf::Event Renderer::handle_events()
{
	sf::Event event;
	while (m_window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			m_window.close();
			return event;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Q && event.key.alt) {
				m_window.close();
			}

			if (event.key.code == sf::Keyboard::P && event.key.alt) {
				m_draw_particles = !m_draw_particles;
			}

			if (event.key.code == sf::Keyboard::V && event.key.alt) {
				m_draw_velocity = !m_draw_velocity;
			}

			if (event.key.code == sf::Keyboard::F && event.key.alt) {
				m_draw_force = !m_draw_force;
			}

			if (event.key.code == sf::Keyboard::G && event.key.alt) {
				m_draw_grid = !m_draw_grid;
			}

			if (event.key.code == sf::Keyboard::H) {
				if (event.key.alt) {
					m_draw_hash = !m_draw_hash;
				}
				else {
					m_view.setCenter(0, 0);
					m_window.setView(m_view);
				}
			}

			if (event.key.code == sf::Keyboard::B && event.key.alt) {
				m_draw_bounds = !m_draw_bounds;
			}
		}
		
		if (event.type == sf::Event::MouseWheelScrolled) {
			zoom = std::max<float>(110, std::min<float>(zoom + (event.mouseWheelScroll.delta * 10) * std::abs(std::pow(event.mouseWheelScroll.delta, 2)), 3000));
		}

		static sf::Vector2i mouse_starting_coords = {0, 0};
		static sf::Vector2f view_starting_coords = {0, 0};
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				mouse_starting_coords = sf::Mouse::getPosition();
				view_starting_coords = m_view.getCenter();
			}
		}
		else if(event.type == sf::Event::MouseButtonReleased) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2f diff = m_view.getCenter() - view_starting_coords;
				if (std::sqrt(diff.x * diff.x + diff.y * diff.y) > 800) {
					m_view.setCenter(view_starting_coords);
					m_window.setView(m_view);
				}
				mouse_starting_coords = sf::Vector2i(0, 0);
				view_starting_coords = sf::Vector2f(0, 0);
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			m_view.setCenter(view_starting_coords + sf::Vector2f((mouse_starting_coords - sf::Mouse::getPosition())));
			m_window.setView(m_view);
		}
	}
	return event;
}

si::time Renderer::render(Simulation* simulation)
{
	Simulation& sim = *simulation;
	if (!m_window.isOpen()) return 0;

	si::time start_time = get_running_time();
	m_window.clear(sf::Color::White);

	if (m_draw_hash)
	{
		sf::RectangleShape hash_cell_rect;
		hash_cell_rect.setFillColor(sf::Color(100, 100, 240, 100));
		for (auto key : sim.m_particles.keys()) {
			float cellsize = (float)sim.m_particles.cell_size();
			hash_cell_rect.setSize(sf::Vector2f(cellsize, cellsize));
			hash_cell_rect.setPosition((float)key.first * cellsize, (float)key.second * cellsize);

			m_window.draw(hash_cell_rect);
		}
	}

	if (m_draw_grid)
	{
		// Draw grid
		float grid_cell_size = 0.01f * 1.f;//sim.m_parameters.support_radius * 1.0;
		float window_frustum_x = 800 / zoom;
		float window_frustum_y = 600 / zoom;

		sf::Color grid_color = sf::Color(200, 200, 200, 100);

		float offset_x = m_view.getCenter().x - (m_view.getSize().x);
		float offset_y = m_view.getCenter().y - (m_view.getSize().y);

		offset_x = m_view.getCenter().x - fmod(m_view.getCenter().x, grid_cell_size * 10 * zoom) - (m_view.getSize().x / 2) - (grid_cell_size * 10 * zoom * 2);
		offset_y = m_view.getCenter().y - fmod(m_view.getCenter().y, grid_cell_size * 10 * zoom) - (m_view.getSize().y / 2) - (grid_cell_size * 10 * zoom * 2);

		for (int i = 1; i < (window_frustum_x / grid_cell_size)*1.5; i++) {
			sf::Color grid_color = sf::Color(200, 200, 200, 100);
			if (i % 10 == 0) grid_color = sf::Color(200, 200, 255, 255);

			sf::Vertex vertices[2] =
			{
				sf::Vertex(sf::Vector2f(offset_x + grid_cell_size * zoom * i, offset_y + 0), grid_color),
				sf::Vertex(sf::Vector2f(offset_x + grid_cell_size * zoom * i, offset_y + (window_frustum_x * zoom * 2.0)), grid_color)
			};
			m_window.draw(vertices, 2, sf::Lines);
		}

		for (int i = 1; i < (window_frustum_y / grid_cell_size)*1.5; i++) {
			sf::Color grid_color = sf::Color(200, 200, 200, 100);
			if (i % 10 == 0) grid_color = sf::Color(255, 200, 200, 255);

			sf::Vertex vertices[2] =
			{
				sf::Vertex(sf::Vector2f(offset_x + 0, offset_y + grid_cell_size * zoom * i), grid_color),
				sf::Vertex(sf::Vector2f(offset_x + (window_frustum_y * zoom * 2.0), offset_y + grid_cell_size * zoom * i), grid_color)
			};
			m_window.draw(vertices, 2, sf::Lines);
		}
	}

	if (m_draw_bounds) {
		for (auto boundary : sim.m_boundaries) {
			sf::Color boundary_color = sf::Color(0, 0, 0, 255);
			sf::Vertex vertices[2] =
			{
				sf::Vertex(sf::Vector2f(boundary.start.x * zoom, boundary.start.y * zoom), boundary_color),
				sf::Vertex(sf::Vector2f(boundary.end.x * zoom, boundary.end.y * zoom), boundary_color)
			};
			m_window.draw(vertices, 2, sf::Lines);
		}
	}

	if (m_draw_particles || m_draw_force || m_draw_velocity)
	{
		sf::CircleShape circle;
		sf::CircleShape point(1.0f, 5);

		for (auto particle : sim.m_particles.query_all()) {
			Particle p = *particle;

			// Particles
			if (m_draw_particles)
			{
				float circle_radius = (float)p.support_radius * zoom;
				float point_radius = 1.0f;

				point.setPosition((float)p.position.x * zoom, (float)p.position.y * zoom);
				circle.setPosition((float)p.position.x * zoom, (float)p.position.y * zoom);

				point.setFillColor(sf::Color::Black);
				circle.setFillColor(sf::Color(200, 30, 30, 50));

				point.setRadius(point_radius);
				circle.setRadius((float)p.support_radius * zoom);

				circle.setOrigin(circle_radius, circle_radius);
				point.setOrigin(point_radius, point_radius);

				m_window.draw(circle);
				m_window.draw(point);
			}

			// Velocity vectors
			if(m_draw_velocity)
			{
				//std::cout << particle->position.x << ", " << particle->position.y << std::endl;
			}

			// Force vectors
			if (m_draw_force)
			{

			}
		}
	}

	m_window.display();

	si::time end_time = get_running_time();
	return (end_time - start_time);
}

void Renderer::run_threaded(Simulation* sim)
{
	m_current_simulation = sim;
	
	m_window.setActive(false);
	std::thread thread(&Renderer::rendering_thread, this);

	thread.join();
}

void Renderer::deactivate_context()
{
	m_window.setActive(false);
}

void Renderer::rendering_thread()
{
	while (m_window.isOpen()) {
		render(m_current_simulation);
	}
}
