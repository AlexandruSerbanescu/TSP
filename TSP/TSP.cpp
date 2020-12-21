// TSP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <vector>

#include "TravelSalesman.h"
#include "assert.h"

class TestData
{
public:

	static vector<Event> DeliveryScenario_1()
	{
		vector<Event> deliveryScenario_1;
		deliveryScenario_1.emplace_back(3, 0, 1);
		deliveryScenario_1.emplace_back(2, 0, 10);
		deliveryScenario_1.emplace_back(3, 4, 1);
		deliveryScenario_1.emplace_back(4, 7, 1);
		deliveryScenario_1.emplace_back(1, 7, 0);

		return deliveryScenario_1;
	}

	static vector<Event> PickupScenario_1()
	{
		vector<Event> pickupScenario_1;
		pickupScenario_1.emplace_back(5, 1, 2);
		pickupScenario_1.emplace_back(2, 6, 2);
		pickupScenario_1.emplace_back(1, 10, 1);

		return pickupScenario_1;
	}

	static vector<Event> PickupScenario_2()
	{
		vector<Event> pickupScenario_2;
		pickupScenario_2.emplace_back(14, 1, 10);
		pickupScenario_2.emplace_back(14, 1, 2);
		pickupScenario_2.emplace_back(14, 1, -1);

		return pickupScenario_2;
	}
};

class TestTSP
{
public:

	static void GetShortestTSRoute_Regular()
	{
		int32_t vehicleCapacityLimit = 14;
		int32_t vehicleEventsLimit = 8;

		auto deliveryEvents = TestData::DeliveryScenario_1();

		auto pickupEvents = TestData::PickupScenario_1();

		auto updatedEvents = TravelSalesman::GetShortestTSRoute(deliveryEvents, pickupEvents, vehicleCapacityLimit, vehicleEventsLimit);

		assert((deliveryEvents.size() + 2) == updatedEvents.size());
		assert(updatedEvents[3] == pickupEvents[1]);
	}

	static void GetShortestTSRoute_NoPickUp()
	{
		int32_t vehicleCapacityLimit = 13;
		int32_t vehicleEventsLimit = 8;

		auto deliveryEvents = TestData::DeliveryScenario_1();

		auto pickupEvents = TestData::PickupScenario_2();

		auto updatedEvents = TravelSalesman::GetShortestTSRoute(deliveryEvents, pickupEvents, vehicleCapacityLimit, vehicleEventsLimit);

		assert((deliveryEvents.size() + 1) == updatedEvents.size());
	}
};


int main()
{
	TestTSP::GetShortestTSRoute_Regular();
	TestTSP::GetShortestTSRoute_NoPickUp();

    std::cout << "Hello World!\n";
}

