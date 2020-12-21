# TSP

A Specific Travel Salesman Problem Implementation


Introduction 

The current Travel Salesman implementation receives:
-	a list of possible delivery locations and their capacities
-	a list of possible pickup locations and their capacities
-	the event and capacity limit of a vehicle
The aim is to visit as many drop locations as possible and 1 pick-up location. In this case a suitable pick-up location will be chosen that doesn’t violates the vehicle capacity constraint and minimises the optimised path created for the delivery locations.  

The problem is solved s following:
1)	Select the max number of delivery location that satisfies the constraints by sorting them on capacity and trying to fit as many as possible
2)	Insert the origin (the Depot). The current path will be a sequence of events that starts with the Depot. The full length of the circuit would be the sum of the distances between these locations plus the distance between the last location and the Depot. 
3)	Optimise the path by using the 2-Opt algorithm.
4)	Insert a pick-up location that minimises the additional driving distance without violating the constraints.  

Regarding the algorithm there are many heuristic algorithms to solve the Travel Salesman Problem. One of the popular algorithms written by Christofides and Serdyukov gives a path that is at most 1.5 times the optimal. The 2-opt heuristics gives on average solutions that are about 5% better than that. In principle other algorithms could be used in combination to generate the initial solution for 2-Opt, or more complex algorithms could be employed like V-opt methods.
However the good performance of the 2-Opt and the fact that it is quite strait, makes it a very good candidate in itself for this exercise.


The Code 

In order to calculate the Travel Salesman route it is enough to include the TravelSalesman.h and to call the GetShortestTSRoute with the parameters described above. The method is a static implementation and does not require any instantiation. The “TSP.cpp” contains an example.

