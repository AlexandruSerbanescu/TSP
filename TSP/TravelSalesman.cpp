#include "TravelSalesman.h"

#include <utility>
#include "assert.h"


std::pair<Event*, uint64_t> TravelSalesman::GetOptimalInsert(vector<Event>& cadidateEvents, vector<Event>::iterator from, vector<Event>::iterator to, uint32_t freeCapacity)
{
	auto insertEvent = cadidateEvents.end();
	double extraDistance = 0;
	double minExtraDistance = numeric_limits<double>::max();
	double currentDistance = from->DistanceToEvent(*to);

	for (auto it = cadidateEvents.begin(); it != cadidateEvents.end(); ++it)
	{
		extraDistance = from->DistanceToEvent(*it) + to->DistanceToEvent(*it) - currentDistance;

		if (extraDistance < minExtraDistance && it->Capacity() <= freeCapacity)
		{
			minExtraDistance = extraDistance;
			insertEvent = it;
		}
	}

	return move(make_pair(insertEvent != cadidateEvents.end() ? static_cast<Event*>(&(*insertEvent)) : nullptr, minExtraDistance));
}


vector<Event> TravelSalesman::InsertOptimalPickUpCandidate(const vector<Event>& deliveryEvents, const vector<Event>& pickUpEvents, uint32_t maxCapacity)
{
	vector<Event> updatedEvents = deliveryEvents;
	vector<Event> cadidateEvents = pickUpEvents;

	uint32_t totalCount = updatedEvents.size();


	if (cadidateEvents.size() == 0)
	{
		return updatedEvents;
	}

	if (totalCount == 0)
	{
		updatedEvents.push_back(cadidateEvents[0]);
		return updatedEvents;
	}

	sort(cadidateEvents.begin(), cadidateEvents.end(), CompareSmaller);

	uint64_t minDistance = numeric_limits<uint64_t>::max();
	Event* insertEvent = nullptr;
	auto insertLocation = updatedEvents.end();

	uint32_t capacity = 0;
	for (auto& event : updatedEvents)
	{
		capacity += event.Capacity();
	}

	assert(maxCapacity >= capacity);
	//ToDo throw exception 

	uint32_t freeCapacity = maxCapacity - capacity;

	auto from = updatedEvents.begin();
	auto to = next(updatedEvents.begin());
	pair<Event*, uint64_t> insertData;

	while (to != updatedEvents.end())
	{
		freeCapacity += from->Capacity();
		insertData = GetOptimalInsert(cadidateEvents, from, to, freeCapacity);
		if (insertData.first != nullptr && insertData.second < minDistance)
		{
			minDistance = insertData.second;
			insertEvent = insertData.first;
			insertLocation = to;
		}
		advance(from, 1);
		advance(to, 1);
	}

	freeCapacity += from->Capacity();
	insertData = GetOptimalInsert(cadidateEvents, from, updatedEvents.begin(), freeCapacity);
	if (insertData.first != nullptr && insertData.second < minDistance)
	{
		insertEvent = insertData.first;
		insertLocation = updatedEvents.end();
	}

	if (insertEvent != nullptr)
	{
		updatedEvents.insert(insertLocation, *insertEvent);
	}

	return updatedEvents;
}


vector<Event> TravelSalesman::GetMaxDelivery(const vector<Event>& deliveryEvents, uint32_t maxEvents, uint32_t maxCapacity)
{
	vector<Event> events = deliveryEvents;
	auto first = events.begin();
	auto last = events.begin();

	uint32_t capacity = 0;
	uint32_t count = 0;
	uint32_t totalCount = events.size();
	uint32_t totalMaxCount = min(totalCount, maxEvents);


	if (totalCount == 0)
	{
		return move(*(new vector<Event>()));
	}

	sort(events.begin(), events.end(), CompareSmaller);

	//Identify the larggest drop events collection 
	while (count < totalMaxCount)
	{
		if (capacity + last->Capacity() > maxCapacity)
		{
			break;
		}

		count++;
		capacity += last->Capacity();
		advance(last, 1);
	}

	vector<Event> selectedDelivery(first, last);

	return selectedDelivery;
}


vector<Event> TravelSalesman::TwoOpt(const vector<Event>& events)
{
	vector<Event> retVal = events;
	auto minLength = Round2(TotalCycleLength(retVal));
	double length = minLength;
	double deltaLength = 0;

	auto prevI = retVal.end();
	auto nextK = retVal.end();

	if (events.size() <= 2)
	{
		return retVal;
	}
		
	do
	{
		minLength = length;

		for (auto itI = next(retVal.begin()); itI != prev(retVal.end()); ++itI)
		{
			for (auto itK = next(itI); itK != retVal.end(); ++itK)
			{
				prevI = prev(itI);
				nextK = next(itK) != retVal.end() ? next(itK) : retVal.begin();
				deltaLength = Round2((prevI->DistanceToEvent(*itK) + nextK->DistanceToEvent(*itI)) -
					                 (prevI->DistanceToEvent(*itI) + nextK->DistanceToEvent(*itK)));
				
				//If the overall path length improves swap 
				if (deltaLength < 0)
				{
					length += deltaLength;
					reverse(itI, next(itK));
				}
			}
		}
	} while (minLength > length);

	return retVal;
}


vector<Event> TravelSalesman::GetShortestTSRoute(vector<Event>& deliveries, vector<Event>& pickUps, uint32_t maxCapacity, uint32_t maxEvents)
{
	if (maxEvents <= 2)	
	{
		throw std::invalid_argument("The maximum no of events during a trip, maxEvents, should be larger or equal than 2, counting for at least on delivery and one pickup");
	}

	// Select a maximum feasable set of deliveries counting for 1 pick-up
	// A feasable set should not exeed the vehicle capacity and the maximum no of events
	auto deliverySelection = GetMaxDelivery(deliveries, maxEvents - 1, maxCapacity);
	
	// Add the Depot
	// It is assumed that only the Depot is located in the Origin (0,0) and that it can be only one
	Event origin(0,0,0);
	deliverySelection.insert(deliverySelection.begin(), origin);

	//Optimise the path via the 2-Opt algorithm 
	//A path is a sequence of events starting with the Depot. The total length is the distance between the locations + the distance between the last event and the Depot 
	auto path = TwoOpt(deliverySelection);

	//Insert one pick-up by selecting the one that minimises the path observing the max capacity rule for the vehicle 
	auto updatedPath = InsertOptimalPickUpCandidate(path, pickUps, maxCapacity);

	//ToDo: if (updatedPath.size() != path.size() + 1) { // warning/notify }

	return updatedPath;
}

