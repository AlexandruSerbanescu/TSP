#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include "TravelSalesman.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

class TravelSalesmanTesting : public TravelSalesman
{
public:
	static vector<Event> InsertOptimalPickUpCandidateTest(vector<Event>& events, vector<Event>& cadidateEvents, uint32_t maxCapacity)
	{
		return TravelSalesman::InsertOptimalPickUpCandidate(events, cadidateEvents, maxCapacity);
	}

	static vector<Event> GetMaxDeliveryTest(vector<Event>& events, uint32_t maxEvents, uint32_t maxCapacity)
	{
		return TravelSalesman::GetMaxDelivery(events, maxEvents, maxCapacity);
	}

	static vector<Event> TwoOptTest(const vector<Event>& events)
	{
		return TravelSalesman::TwoOpt(events);
	}
};

class TestData
{
public:
	static vector<Event> DeliveryScenario_1()
	{
		vector<Event> deliveryScenario_1;
		deliveryScenario_1.emplace_back(3, 0, 1);
		deliveryScenario_1.emplace_back(4, 7, 1);
		deliveryScenario_1.emplace_back(3, 4, 1);
		deliveryScenario_1.emplace_back(4, 7, 0);

		return deliveryScenario_1;
	}

	static vector<Event> DeliveryScenario_2()
	{
		vector<Event> deliveryScenario_2;
		deliveryScenario_2.emplace_back(3, 0, 1);
		deliveryScenario_2.emplace_back(2, 0, 10);
		deliveryScenario_2.emplace_back(3, 4, 1);
		deliveryScenario_2.emplace_back(4, 7, 1);
		deliveryScenario_2.emplace_back(1, 7, 0);

		return deliveryScenario_2;
	}

	// Capacity orders the optimal path in the scenario 
	static vector<Event> DeliveryScenario_3()
	{
		vector<Event> deliveryScenario_3;
		deliveryScenario_3.emplace_back(4, 4, 2);
		deliveryScenario_3.emplace_back(1, 0, 2);
		deliveryScenario_3.emplace_back(5, 4, 0);
		deliveryScenario_3.emplace_back(2, 2, 1);
		deliveryScenario_3.emplace_back(3, 3, 1);

		return deliveryScenario_3;
	}

	// Capacity orders the optimal path in the scenario 
	static vector<Event> DeliveryScenario_4()
	{
		vector<Event> deliveryScenario_3;
		deliveryScenario_3.emplace_back(1, 0, 2);
		deliveryScenario_3.emplace_back(4, -1, -5);
		deliveryScenario_3.emplace_back(3, 1, -5);
		deliveryScenario_3.emplace_back(2, 1, 1);

		return deliveryScenario_3;
	}

	// Capacity orders the optimal path in the scenario 
	static vector<Event> DeliveryScenario_5()
	{
		vector<Event> deliveryScenario_3;
		deliveryScenario_3.emplace_back(1, 1, 1);
		deliveryScenario_3.emplace_back(3, -1, -1);
		deliveryScenario_3.emplace_back(2, 1, 1);

		return deliveryScenario_3;
	}

	// Capacity orders the optimal path in the scenario 
	static vector<Event> DeliveryScenario_6()
	{
		vector<Event> deliveryScenario_3;
		deliveryScenario_3.emplace_back(1, 1, 1);

		return deliveryScenario_3;
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
		pickupScenario_2.emplace_back(1, 0, 10);
		pickupScenario_2.emplace_back(14, 1, 2);
		pickupScenario_2.emplace_back(14, 1, -1);

		return pickupScenario_2;
	}

	static vector<Event> PickupScenario_3()
	{
		vector<Event> pickupScenario_3;
		pickupScenario_3.emplace_back(12, 1, 3);
		pickupScenario_3.emplace_back(12, 1, 2);
		pickupScenario_3.emplace_back(1, 1, -1);

		return pickupScenario_3;
	}

	static vector<Event> PickupScenario_4()
	{
		vector<Event> pickupScenario_4;
		pickupScenario_4.emplace_back(14, 1, 10);
		pickupScenario_4.emplace_back(14, 1, 2);
		pickupScenario_4.emplace_back(13, 1, -1);

		return pickupScenario_4;
	}

	static vector<Event> PickupScenario_5()
	{
		vector<Event> pickupScenario_5;
		pickupScenario_5.emplace_back(14, 1, 10);
		pickupScenario_5.emplace_back(14, 1, 2);
		pickupScenario_5.emplace_back(14, 1, -1);

		return pickupScenario_5;
	}
};


namespace TestTravelSalesman 
{
	TEST_CLASS(TestTSP)
	{
	public:
		TEST_METHOD(GetMaxDelivery_CapacityLimit_Grater)
		{
			int32_t vehicleCapacityLimit = 11;
			int32_t vehicleEventLimit = 4;

			auto deliveryEvents = TestData::DeliveryScenario_1();
			size_t selectedEventsCount = TravelSalesmanTesting::GetMaxDeliveryTest(deliveryEvents, vehicleEventLimit, vehicleCapacityLimit).size();
			size_t expected = 3;

			Assert::AreEqual(expected, selectedEventsCount);
		}

		TEST_METHOD(GetMaxDelivery_CapacityLimit_Grater_LargeEventLimit)
		{
			int32_t vehicleCapacityLimit = 11;
			int32_t vehicleEventLimit = 10;

			auto deliveryEvents = TestData::DeliveryScenario_1();
			size_t selectedEventsCount = TravelSalesmanTesting::GetMaxDeliveryTest(deliveryEvents, vehicleEventLimit, vehicleCapacityLimit).size();
			size_t expected = 3;

			Assert::AreEqual(expected, selectedEventsCount);
		}
		
		TEST_METHOD(GetMaxDelivery_CapacityLimit_Equal)
		{
			int32_t vehicleCapacityLimit = 10;
			int32_t vehicleEventLimit = 4;

			auto deliveryEvents = TestData::DeliveryScenario_1();
			size_t selectedEventsCount = TravelSalesmanTesting::GetMaxDeliveryTest(deliveryEvents, vehicleEventLimit, vehicleCapacityLimit).size();
			size_t expected = 3;

			Assert::AreEqual(expected, selectedEventsCount);
		}
		
		TEST_METHOD(GetMaxDelivery_CapacityLimit_AND_EventLimit_Values)
		{
			int32_t vehicleCapacityLimit = 10;
			int32_t vehicleEventLimit = 3;
			auto deliveryEvents = TestData::DeliveryScenario_1();
			auto selectedEvents = TravelSalesmanTesting::GetMaxDeliveryTest(deliveryEvents, vehicleEventLimit, vehicleCapacityLimit);

			sort(deliveryEvents.begin(), deliveryEvents.end(), CompareSmaller);

			size_t expected = 3;

			Assert::AreEqual(expected, selectedEvents.size());

			for (size_t index = 0; index < expected; ++index)
			{
				Assert::IsTrue(deliveryEvents[index] == selectedEvents[index]);
			}
		}

		TEST_METHOD(GetMaxDelivery_EventLimit)
		{
			int32_t vehicleCapacityLimit = 10;
			int32_t vehicleEventLimit = 2;
			auto deliveryEvents = TestData::DeliveryScenario_1();
			size_t selectedEventsCount = TravelSalesmanTesting::GetMaxDeliveryTest(deliveryEvents, vehicleEventLimit, vehicleCapacityLimit).size();
			size_t expected = 2;

			Assert::AreEqual(expected, selectedEventsCount);
		}

		TEST_METHOD(GetMaxDelivery_CapacityLimit_TooLow)
		{
			int32_t vehicleCapacityLimit = 1;
			int32_t vehicleEventLimit = 3;
			auto deliveryEvents = TestData::DeliveryScenario_1();
			size_t selectedEventsCount = TravelSalesmanTesting::GetMaxDeliveryTest(deliveryEvents, vehicleEventLimit, vehicleCapacityLimit).size();
			size_t expected = 0;

			Assert::AreEqual(expected, selectedEventsCount);
		}

		TEST_METHOD(GetMaxDelivery_EventLimit_TooLow)
		{
			int32_t vehicleCapacityLimit = 10;
			int32_t vehicleEventLimit = 0;
			auto deliveryEvents = TestData::DeliveryScenario_1();
			size_t selectedEventsCount = TravelSalesmanTesting::GetMaxDeliveryTest(deliveryEvents, vehicleEventLimit, vehicleCapacityLimit).size();
			size_t expected = 0;

			Assert::AreEqual(expected, selectedEventsCount);
		}

		TEST_METHOD(GetMaxDelivery_All)
		{
			int32_t vehicleCapacityLimit = 100;
			int32_t vehicleEventLimit = 5;
			auto deliveryEvents = TestData::DeliveryScenario_1();
			size_t selectedEventsCount = TravelSalesmanTesting::GetMaxDeliveryTest(deliveryEvents, vehicleEventLimit, vehicleCapacityLimit).size();
			size_t expected = 4;

			Assert::AreEqual(expected, selectedEventsCount);
		}

		TEST_METHOD(InsertOptimalComplementCandidate_Capacity_Check)
		{
			int32_t vehicleCapacityLimit = 14;

			auto deliveryEvents = TestData::DeliveryScenario_2();
			deliveryEvents.emplace(deliveryEvents.begin(), 0, 0, 0);

			auto pickupEvents = TestData::PickupScenario_1();

			auto updatedEvents = TravelSalesmanTesting::InsertOptimalPickUpCandidateTest(deliveryEvents, pickupEvents, vehicleCapacityLimit);

			Assert::AreEqual((deliveryEvents.size() + 1) , updatedEvents.size());
			Assert::IsTrue(updatedEvents[4] == pickupEvents[1]);
		}

		TEST_METHOD(InsertOptimalComplementCandidate_Insert_Far)
		{
			int32_t vehicleCapacityLimit = 13;

			auto deliveryEvents = TestData::DeliveryScenario_2();
			deliveryEvents.emplace(deliveryEvents.begin(), 0, 0, 0);

			auto pickupEvents = TestData::PickupScenario_2();

			auto updatedEvents = TravelSalesmanTesting::InsertOptimalPickUpCandidateTest(deliveryEvents, pickupEvents, vehicleCapacityLimit);

			Assert::AreEqual((deliveryEvents.size() + 1), updatedEvents.size());
			Assert::IsTrue(updatedEvents[2] == pickupEvents[0]);
		}

		TEST_METHOD(InsertOptimalComplementCandidate_Insert_Last)
		{
			int32_t vehicleCapacityLimit = 13;

			auto deliveryEvents = TestData::DeliveryScenario_2();
			deliveryEvents.emplace(deliveryEvents.begin(), 0, 0, 0);

			auto pickupEvents = TestData::PickupScenario_3();

			auto updatedEvents = TravelSalesmanTesting::InsertOptimalPickUpCandidateTest(deliveryEvents, pickupEvents, vehicleCapacityLimit);

			Assert::AreEqual((deliveryEvents.size() + 1), updatedEvents.size());
			Assert::IsTrue(updatedEvents[6] == pickupEvents[2]);
		}

		TEST_METHOD(InsertOptimalComplementCandidate_Depot_Only_CapacityCheck_Equal_Last)
		{
			int32_t vehicleCapacityLimit = 13;

			auto deliveryEvents = TestData::DeliveryScenario_2();
			deliveryEvents.emplace(deliveryEvents.begin(), 0, 0, 0);

			auto pickupEvents = TestData::PickupScenario_4();

			auto updatedEvents = TravelSalesmanTesting::InsertOptimalPickUpCandidateTest(deliveryEvents, pickupEvents, vehicleCapacityLimit);

			Assert::AreEqual((deliveryEvents.size() + 1), updatedEvents.size());
			Assert::IsTrue(updatedEvents[6] == pickupEvents[2]);
		}

		TEST_METHOD(InsertOptimalComplementCandidate_Depot_Only_CapacityCheck_Equal_Over)
		{
			int32_t vehicleCapacityLimit = 13;

			auto deliveryEvents = TestData::DeliveryScenario_2();
			deliveryEvents.emplace(deliveryEvents.begin(), 0, 0, 0);

			auto pickupEvents = TestData::PickupScenario_5();

			auto updatedEvents = TravelSalesmanTesting::InsertOptimalPickUpCandidateTest(deliveryEvents, pickupEvents, vehicleCapacityLimit);

			Assert::AreEqual(deliveryEvents.size() , updatedEvents.size());
		}

		TEST_METHOD(InsertOptimalComplementCandidate_Depot_Only_Capacity_Under)
		{
			int32_t vehicleCapacityLimit = 13;

			vector<Event> deliveryEvents;
			deliveryEvents.emplace(deliveryEvents.begin(), 0, 0, 0);

			auto pickupEvents = TestData::PickupScenario_4();

			auto updatedEvents = TravelSalesmanTesting::InsertOptimalPickUpCandidateTest(deliveryEvents, pickupEvents, vehicleCapacityLimit);

			Assert::AreEqual((deliveryEvents.size() + 1), updatedEvents.size());
			Assert::IsTrue(updatedEvents[1] == pickupEvents[2]);
		}
		
		TEST_METHOD(InsertOptimalComplementCandidate_Depot_Only_Capacity_Over)
		{
			int32_t vehicleCapacityLimit = 13;

			vector<Event> deliveryEvents;
			deliveryEvents.emplace(deliveryEvents.begin(), 0, 0, 0);

			auto pickupEvents = TestData::PickupScenario_5();

			auto updatedEvents = TravelSalesmanTesting::InsertOptimalPickUpCandidateTest(deliveryEvents, pickupEvents, vehicleCapacityLimit);

			Assert::AreEqual(deliveryEvents.size(), updatedEvents.size());
		}

		TEST_METHOD(TwoOpt_Scenario_Complex_1)
		{
			auto deliveryEvents = TestData::DeliveryScenario_3();
			deliveryEvents.emplace(deliveryEvents.begin(), 0, 0, 0);

			auto path = TravelSalesmanTesting::TwoOptTest(deliveryEvents);

			sort(deliveryEvents.begin(), deliveryEvents.end(), CompareSmaller); // Capacity orders the optimal path in the scenario 

			Assert::AreEqual(Round2(TotalCycleLength(deliveryEvents)), Round2(TotalCycleLength(path)));
		}

		TEST_METHOD(TwoOpt_Scenario_Complex_2)
		{
			auto deliveryEvents = TestData::DeliveryScenario_4();
			deliveryEvents.emplace(deliveryEvents.begin(), 0, 0, 0);

			auto path = TravelSalesmanTesting::TwoOptTest(deliveryEvents);

			sort(deliveryEvents.begin(), deliveryEvents.end(), CompareSmaller); // Capacity orders the optimal path in the scenario 

			Assert::AreEqual(Round2(TotalCycleLength(deliveryEvents)), Round2(TotalCycleLength(path)));
		}

		TEST_METHOD(TwoOpt_Scenario_Multiple_Delivery_In_Same_Location)
		{
			auto deliveryEvents = TestData::DeliveryScenario_5();
			deliveryEvents.emplace(deliveryEvents.begin(), 0, 0, 0);

			auto path = TravelSalesmanTesting::TwoOptTest(deliveryEvents);

			sort(deliveryEvents.begin(), deliveryEvents.end(), CompareSmaller); // Capacity orders the optimal path in the scenario 

			Assert::AreEqual(Round2(TotalCycleLength(deliveryEvents)), Round2(TotalCycleLength(path)));
		}

		TEST_METHOD(TwoOpt_Scenario_DepotOnly)
		{
			vector<Event> deliveryEvents;
			deliveryEvents.emplace(deliveryEvents.begin(), 0, 0, 0);

			auto path = TravelSalesmanTesting::TwoOptTest(deliveryEvents);

			Assert::IsTrue(deliveryEvents[0] == path[0]);
		}

		TEST_METHOD(TwoOpt_Scenario_Simple_Delivery)
		{
			auto deliveryEvents = TestData::DeliveryScenario_6();
			deliveryEvents.emplace(deliveryEvents.begin(), 0, 0, 0);

			auto path = TravelSalesmanTesting::TwoOptTest(deliveryEvents);

			sort(deliveryEvents.begin(), deliveryEvents.end(), CompareSmaller); // Capacity orders the optimal path in the scenario 

			Assert::AreEqual(Round2(TotalCycleLength(deliveryEvents)), Round2(TotalCycleLength(path)));
		}
		
		TEST_METHOD(TwoOpt_Scenario_Complex_Preordered)
		{
			auto deliveryEvents = TestData::DeliveryScenario_3();
			deliveryEvents.emplace(deliveryEvents.begin(), 0, 0, 0);
			sort(deliveryEvents.begin(), deliveryEvents.end(), CompareSmaller); // Capacity orders the optimal path in the scenario 

			auto path = TravelSalesmanTesting::TwoOptTest(deliveryEvents);

			Assert::AreEqual(Round2(TotalCycleLength(deliveryEvents)), Round2(TotalCycleLength(path)));
		}

		TEST_METHOD(GetShortestTSRoute_Regular)
		{
			int32_t vehicleCapacityLimit = 14;
			int32_t vehicleEventsLimit = 8;

			auto deliveryEvents = TestData::DeliveryScenario_2();

			auto pickupEvents = TestData::PickupScenario_1();

			auto updatedEvents = TravelSalesmanTesting::GetShortestTSRoute(deliveryEvents, pickupEvents, vehicleCapacityLimit, vehicleEventsLimit);

			Assert::AreEqual((deliveryEvents.size() + 2), updatedEvents.size());
			Assert::IsTrue(updatedEvents[3] == pickupEvents[1]);
		}

		TEST_METHOD(GetShortestTSRoute_NoPickUp)
		{
			int32_t vehicleCapacityLimit = 13;
			int32_t vehicleEventsLimit = 8;

			auto deliveryEvents = TestData::DeliveryScenario_2();

			auto pickupEvents = TestData::PickupScenario_5();

			auto updatedEvents = TravelSalesmanTesting::GetShortestTSRoute(deliveryEvents, pickupEvents, vehicleCapacityLimit, vehicleEventsLimit);

			Assert::AreEqual((deliveryEvents.size() + 1), updatedEvents.size());
		}
	};
}
