#pragma once

#include <iostream>
#include <vector>
#include <string> 

using namespace std;

//Round to 2 decimals 
inline double Round2(double value)
{
	return round(value * 100.0) / 100.0;
}

class Event
{
public:
    Event(uint32_t capacity, int32_t x, int32_t y) : m_capacity(capacity), m_x(x), m_y(y) {}

    Event(const Event& other) : m_capacity(other.m_capacity), m_x(other.m_x), m_y(other.m_y) {}
    Event(Event&& other) noexcept : m_capacity(exchange(other.m_capacity, 0)), m_x(exchange(other.m_x, 0)), m_y(exchange(other.m_y, 0)) {}

    Event& operator = (const Event& other);
    Event& operator = (Event&& other) noexcept;

    double DistanceToEvent(const Event& event) const;

    uint32_t Capacity() const;
    int32_t X() const;
    int32_t Y() const;

	string ToString() const;

private:
    uint32_t m_capacity;
    int32_t m_x;
    int32_t m_y;
};

inline bool CompareSmaller(const Event& left, const Event& right)
{
	if (left.Capacity() < right.Capacity())
	{
		return true;
	}

	return false;
}

inline double TotalCycleLength(vector<Event> events)
{
	double length = 0;

	if (events.size() <= 1)
	{
		return length;
	}

	for (auto it = events.begin(); it != prev(events.end()); ++it)
	{
		length += it->DistanceToEvent(*next(it));
	}

	length += events.begin()->DistanceToEvent(*prev(events.end()));

	return length;
}

inline bool operator == (const Event& left, const Event& right)
{
	return ((left.Capacity() == right.Capacity()) && (left.X() == right.X()) && (left.Y() == left.Y()));
}