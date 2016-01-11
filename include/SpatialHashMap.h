/*
* Copyright © 2015 Jeremy T. Hatcher All Rights Reserved
*/

#pragma once

#include <utility>
#include <unordered_map>
#include <vector>
#include <functional>

namespace std {
	template <typename T, typename U>
	struct hash<std::pair<T, U>> {
		size_t operator()(const std::pair<T, U>& p) const {
			return hash<T>()(p.first) ^ hash<U>()(p.second);
		}
	};
}

enum class SpatialHashQueryMode {
	SingleCell,
	Neighborhood,
	Default = SingleCell
};

enum SpatialHashFlags : unsigned int {
	None			= 0x0,
	CountComplexity	= 0x1,
	CheckDuplicates = 0x2,
};

template<typename T> class SpatialHashMap
{
	double m_cellsize;
	SpatialHashQueryMode m_queryMode;
	SpatialHashFlags m_flags;

	int m_complexity;
	int m_reserve = 6;

	std::unordered_map<std::pair<int, int>, std::vector<T>>* m_buckets;

public:
	SpatialHashMap(double cellsize = 0.05, SpatialHashQueryMode mode = SpatialHashQueryMode::Default, SpatialHashFlags flags = SpatialHashFlags::None);
	~SpatialHashMap();

	void insert(double, double, T);

	size_t size();
	
	unsigned int bucket_count() const;

	void remove(std::pair<int, int>, T);
	void remove(double, double, T);
	void remove(T);

	void translate(double, double, double, double, T);

	std::vector<T> query(double, double);
	std::vector<T> query(std::pair<int, int>);

	std::vector<T> query_local(double, double);
	std::vector<T> query_local(std::pair<int, int>);

	std::vector<T> query_all();

	std::vector<std::vector<T>> buckets() const;

	std::vector<std::pair<int, int>> keys() const;

	double cell_size() const;

	void clear();

private:
	std::pair<int, int> make_key(double, double);
	bool is_intersecting_grid(std::pair<int, int>, std::pair<int, int>) const;
	std::vector<std::pair<int, int>> get_intersecting_cells(double, double, double, double);
};

template<typename T>
inline std::pair<int, int> SpatialHashMap<T>::make_key(double x, double y)
{
	return std::pair<int, int>(int(x / m_cellsize), int(y / m_cellsize));
}

template<typename T>
inline bool SpatialHashMap<T>::is_intersecting_grid(std::pair<int, int> key1, std::pair<int, int> key2) const
{
	return ((std::abs(key1.first - key2.first) > 2) || (std::abs(key1.second - key2.second) > 2));
}

template<typename T>
inline std::vector<std::pair<int, int>> SpatialHashMap<T>::get_intersecting_cells(double x1, double y1, double x2, double y2)
{
	throw "get_intersecting_cells() is an unfinished function";

	auto old_key = make_key(x1, y1);
	auto new_key = make_key(x2, y2);

	if (!is_intersecting_grid(old_key, new_key)) {
		return std::vector<std::pair<int, int>>(0);
	}

	std::vector<std::pair<int, int>> result;
	char field[7][7] = {0};
	memset(&field[2][2], 1, sizeof(char) * 3);
	memset(&field[3][2], 1, sizeof(char) * 3);
	memset(&field[4][2], 1, sizeof(char) * 3);

	return result;
}

template<typename T> inline SpatialHashMap<T>::SpatialHashMap(double cellsize, SpatialHashQueryMode mode, SpatialHashFlags flags)
	:m_cellsize((double)cellsize), m_queryMode(mode), m_flags(flags)
{
	m_buckets = new std::unordered_map<std::pair<int, int>, std::vector<T>>;
}

template<typename T>
inline SpatialHashMap<T>::~SpatialHashMap()
{
	delete m_buckets;
}

template<typename T>
inline void SpatialHashMap<T>::insert(double x, double y, T object)
{
	auto key = make_key(x, y);

	switch (m_queryMode)
	{

	case SpatialHashQueryMode::SingleCell:
	{
		if (m_buckets->count(key) > 0) {
			m_buckets->at(key).push_back(object);
		}
		else {
			std::vector<T> vec = { object };
			m_buckets->emplace(key, vec);
		}

		break;
	}
	case SpatialHashQueryMode::Neighborhood:
	{
		--key.first;
		--key.second;
		for (; key.first < key.first + 2; key.first++) {
			for (; key.second < key.second + 2; key.second++) {
				if (m_buckets->count(key) > 0) {
					if (m_flags & SpatialHashFlags::CheckDuplicates) {
						if (std::find(m_buckets->at(key).begin(), m_buckets->at(key).end(), object) != m_buckets->at(key).end()) {
							continue;
						}
					}
					m_buckets->at(key).push_back(object);
				}
				else {
					std::vector<T> vec;
					vec.push_back(object);
					m_buckets->emplace(key, vec);
				}
			}
		}
		break;
	}
	default:
		break;
	}
}

template<typename T>
inline size_t SpatialHashMap<T>::size()
{
	return query_all().size();
}

template<typename T>
inline unsigned int SpatialHashMap<T>::bucket_count() const
{
	return m_buckets->size();
}

template<typename T>
inline void SpatialHashMap<T>::remove(std::pair<int, int> key, T object)
{
	if (m_buckets->count(key) > 0) {
		std::vector<T>::iterator it = m_buckets->at(key).begin();
		while (it != m_buckets->at(key).end()) {

			if (*it == object) {
				it = m_buckets->at(key).erase(it);

				if (m_buckets->at(key).size() < 1) {
					m_buckets->erase(key);
				}
				return;
			}
			++it;
		}
	}
}

template<typename T>
inline void SpatialHashMap<T>::remove(double x, double y, T object)
{
	auto key = make_key(x, y);
	remove(key, object);
}

template<typename T>
inline void SpatialHashMap<T>::remove(T object)
{
	for (auto bucket : m_buckets) {
		remove(bucket.first, object);
	}
}

template<typename T>
inline void SpatialHashMap<T>::translate(double old_x, double old_y, double new_x, double new_y, T object)
{
	auto old_key = make_key(old_x, old_y);
	auto new_key = make_key(new_x, new_y);

	if (old_key != new_key) {
		remove(old_key, object);
		insert(new_x, new_y, object);
	}
}

template<typename T>
inline std::vector<T> SpatialHashMap<T>::query(double x, double y)
{
	return query(make_key(x, y));
}

template<typename T>
inline std::vector<T> SpatialHashMap<T>::query(std::pair<int, int> key)
{
	std::vector<T> result = m_buckets->at(key);

	switch (m_queryMode)
	{
	case SpatialHashQueryMode::SingleCell:
	{
		result.reserve(m_reserve * 8);

		for (int i = -1; i <= 1; i++) {
			for (int k = -1; k <= 1; k++) {
				if (i == 0 && k == 0) continue;
				std::pair<int, int> current_key(key.first + i, key.second + k);
				if (m_buckets->count(current_key) > 0) {
					result.insert(result.end(), m_buckets->at(current_key).begin(), m_buckets->at(current_key).end());
				}
			}
		}
		break;
	}
	default:
		break;
	}
	
	return result;
}

template<typename T>
inline typename std::vector<T> SpatialHashMap<T>::query_local(double x, double y)
{
	std::pair<int, int> key = make_key(x, y);
	return m_buckets->at(key);
}

template<typename T>
inline typename std::vector<T> SpatialHashMap<T>::query_local(std::pair<int, int> key)
{
	return m_buckets->at(key);
}

template<typename T>
inline std::vector<T> SpatialHashMap<T>::query_all()
{
	auto buckets = *m_buckets;
	std::vector<T> result;
	result.reserve(buckets.size() * m_reserve);
	for (auto bucket : buckets) {
		result.insert(result.end(), bucket.second.begin(), bucket.second.end());
	}
	return result;
}

template<typename T>
inline std::vector<std::vector<T>> SpatialHashMap<T>::buckets() const
{
	std::vector<std::vector<T>> result;
	for (auto bucket : *m_buckets) {
		result.push_back(bucket.second);
	}
	return result;
}

template<typename T>
inline std::vector<std::pair<int, int>> SpatialHashMap<T>::keys() const
{
	std::vector<std::pair<int, int>> result;
	for (auto bucket : *m_buckets) {
		result.push_back(bucket.first);
	}
	return result;
}

template<typename T>
inline double SpatialHashMap<T>::cell_size() const
{
	return m_cellsize;
}

template<typename T>
inline void SpatialHashMap<T>::clear()
{
	if(!m_buckets->empty())
		m_buckets->clear();
}
