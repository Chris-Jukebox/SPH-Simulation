#pragma

#include <include\ISQpp.h>
#include <chrono>

inline si::time get_running_time() {
	using namespace std::chrono;
	high_resolution_clock::time_point tp = high_resolution_clock::now();
	auto as_micro = duration_cast<microseconds>(tp.time_since_epoch());
	return si::time(double(as_micro.count() / 1000000.0f));
}

namespace impl
{
	inline unsigned short lfsr_16() {
		static unsigned short state = 0xACE4;
		unsigned short feedback = 1 & ((state >> 0) ^ (state >> 2) ^ (state >> 3) ^ (state >> 5));
		state >>= 1;
		state |= (feedback << 15);
		return state;
	}

	inline unsigned int lfsr_32() {
		static unsigned int state = 0xCC31F1A7;
		unsigned int feedback = 1 & ((state >> 0) ^ (state >> 2) ^ (state >> 6) ^ (state >> 7));
		state >>= 1;
		state |= (feedback << 31);
		return state;
	}
}

inline unsigned int next_unique_id() {
	return impl::lfsr_32();
}

inline si::length projection_distance_2d(si::vec::position point, si::vec::position start, si::vec::position end)
{
	double u = ((point.x - start.x)*(end.x - start.x) + (point.y - start.y)*(end.y - start.y)) / (std::pow((std::sqrt(std::pow((start - end).x, 2) + std::pow((start - end).y, 2))), 2));
	si::vec::position incidence = si::vec::position(start.x + u*(end.x - start.x), start.y + u*(end.y - start.y));
	return si::length(incidence, point);
}

inline si::vec::position nearest_line_position_2d(si::vec::position point, si::vec::position start, si::vec::position end)
{
	double u = ((point.x - start.x)*(end.x - start.x) + (point.y - start.y)*(end.y - start.y)) / (std::pow((std::sqrt(std::pow((start - end).x, 2) + std::pow((start - end).y, 2))), 2));
	return si::vec::position(start.x + u*(end.x - start.x), start.y + u*(end.y - start.y));
}

template<typename T>
inline T normal_2d(T start, T end)
{
	T dxdy(end.x - start.x, end.y - start.y);
	return T(dxdy.y * -1.0, dxdy.x);
}

template<typename T>
inline T normal_2d_unit(T start, T end)
{
	T dxdy(end.x - start.x, end.y - start.y);
	double len = std::sqrt(std::pow((end.x - start.x), 2) + std::pow(end.y - start.y, 2));
	return T((dxdy.y * -1.0)/len, (dxdy.x)/len);
}

template<typename T>
inline double dot_2d( T first, T second) {
	return double(first.x * second.x + first.y * second.y);
}

template<typename T, typename U>
inline bool test_line_intersection_2d(T start_A, T end_A, U start_B, U end_B) {
	return
	(
		((start_B.x - start_A.x) * (end_A.y - start_A.y) - (start_B.y - start_A.y) * (end_A.x - start_A.x)) *
		((end_B.x - start_A.x)*(end_A.y - start_A.y) - (end_B.y - start_A.y)*(end_A.x - start_A.x)) < 0 && 
		((start_A.x - start_B.x)*(end_B.y - start_B.y) - (start_A.y - start_B.y)*(end_B.x - start_B.x)) *
		((end_A.x - start_B.x)*(end_B.y - start_B.y) - (end_A.y - start_B.y)*(end_B.x - start_B.x)) < 0
	);
}

template<typename T>
inline T line_intersection_2d(T first, T second) {

}
