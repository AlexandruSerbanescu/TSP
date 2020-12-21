#pragma once
#include "Event.h"

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class TravelSalesman
{
public:

    /**
     * Get a Travel Salesmen route, with maximum deliveries and one pickup selected to minimise the distance.
     *
     * @param[in] deliveries, potential delivery events, containing the location and the delivery capacity
     * @param[in] pickUps, potential pick-up events, containing the location and the delivery capacity
     * @param[in] maxCapacity, vehicle max capacity
     * @param[in] maxEvents, vehicle max number of events per trip
     * @return the Travel Salesman path as a sequence of events starting with the Depot (the last link is assumed between the last event and the Depot).
     */
    static vector<Event> GetShortestTSRoute(vector<Event>& delivery, vector<Event>& pickUp, uint32_t maxCapacity, uint32_t maxEvents);

protected:

    /**
     * Insert one pick-up by selecting the one that minimises the path observing the max capacity rule for the vehicle.
     *
     * @param[in] deliveryEvents, delivery events
     * @param[in] pickUpEvents, pick-up events to select from
     * @param[in] maxCapacity, vehicle max capacity
     * @return the updated path
     */
    static vector<Event> InsertOptimalPickUpCandidate(const vector<Event>& deliveryEvents, const vector<Event>& pickUpEvents, uint32_t maxCapacity);
    

    /**
     * Select a maximum feasable set of deliveries. A feasable set should not exeed the vehicle capacity and the maximum no of events
     *
     * @param[in] deliveryEvents, the delivery events
     * @param[in] maxEvents, vehicle max number of events per trip
     * @param[in] maxCapacity, vehicle max capacity
     * @return the selected set of events
     */
    static vector<Event> GetMaxDelivery(const vector<Event>& deliveryEvents, uint32_t maxEvents, uint32_t maxCapacity);


    /**
     * Optimise the path via the 2-Opt algorithm.
     *
     * @param[in] events, unoptimised path of events starting with the Depot (the last link is assumed between the last event and the Depot)
     * @return the calculated Travel Salesman path
     */
    static vector<Event> TwoOpt(const vector<Event>& events);

private:

    /**
     * For a sequence of 2 delivery events find the pick-up event that minimises the total travel length
     *
     * @param[in] cadidateEvents, pick-up events to select from
     * @param[in] from, from delivery event
     * @param[in] to, to delivery event
     * @param[in] freeCapacity, vehicle free capacity
     * @return the event and the extra travel distance
     */
	static std::pair<Event *, uint64_t> GetOptimalInsert(vector<Event>& cadidateEvents, vector<Event>::iterator from, vector<Event>::iterator to, uint32_t freeCapacity);
};
