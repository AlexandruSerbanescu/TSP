#include "Event.h"
#include <iostream>


Event& Event::operator = (const Event& other)
{
	if (this != &other)
	{
		m_capacity = other.m_capacity;
		m_x = other.m_x;
		m_y = other.m_y;
	}

    return *this;
}

Event& Event::operator = (Event&& other) noexcept
{
	if (this != &other)
	{
		m_capacity = exchange(other.m_capacity, 0);
		m_x = exchange(other.m_x, 0);
		m_y = exchange(other.m_y, 0);
	}

    return *this;
}

double Event::DistanceToEvent(const Event& event) const
{ 
    return sqrt(pow(static_cast<int64_t>(event.X()) - static_cast<int64_t>(m_x), 2) + pow(static_cast<int64_t>(event.Y()) - static_cast<int64_t>(m_y), 2)); 
}

string Event::ToString() const
{
	return "Capacity: " + to_string(m_capacity) + "X: " + to_string(m_x) + "Y: " + to_string(m_x);
}

uint32_t Event::Capacity() const { return m_capacity; }
int32_t Event::X() const { return m_x; }
int32_t Event::Y() const { return m_y; }
