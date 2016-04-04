#include "building.h"
#include <ctime>
#include <iostream>

///////////
///////////  if two destinations on the same f
///////////
////////////
////////////
//////////////

void building::setElevator(int number) {
	for (int i = 0; i < number; i++) {
		Elevator elevator;
		elevator.setID(i,floorNumbers);
		elevators.push_back(elevator);
	}
}

void building::setFloors(int floor) {
	floorNumbers = floor;
}

void building::dropOff(list<call> request) {
	list<call>::iterator itr;

	vector<call> people;

	// push all the people that have arrived at there destination
	for (itr = request.begin(); itr != request.end(); itr++) {
		if (itr->arrived) {
			people.push_back(*itr);
		}
	}
	for (int i = 0; i < people.size(); i++) {
		cout << "Request went from floor " << people[i].floor << " to floor " << people[i].goal << endl;
	}

}

void building::moveCalls() {
	if (floorCall.size() == 0)
		return;

	if (location == floorCall.end()) {
		return;
	}
	list<call>::iterator floor;
	list<call>::iterator outside;
	list<int>::iterator inside;

	// go through all floor calls
	for (outside = floorCall.begin(); outside != floorCall.end(); outside++) {

		// if it is the first floor call there are no previous destinations
		if (elevators[0].destinations.empty()) {
			elevators[0].addDestination(location->floor);
			location++;
		}
		else {
			// going through the floor calls again
			for (floor = ++floorCall.begin(); floor != floorCall.end(); floor++) {
				// if there are multiple requests from the same floor -- do nothing
				for (inside = elevators[0].destinations.begin(); inside != elevators[0].destinations.end(); inside++) {
					if (floor->floor == *inside) {
						//return???
					}
					// if the goal is aready in the destination log
					else if (floor->goal == location->floor) {
						cout << "going there already" << endl;
						location++;
						return;
					}
				}
			}
		}
	}
}
void building::setLocation(list<call>::iterator here) {
	location = floorCall.begin();
}
int building::moveElevators() {
	bool leaving = false;
	elevators[0].setExiting(leaving);
	int done = getComplete();
	list<call>::iterator itr;
	for (itr = floorCall.begin(); itr != floorCall.end(); itr++) {

		if (elevators[0].getLevel() == itr->floor && !itr->pickedUP) {
			elevators[0].addDestination(itr->goal);
			itr->pickedUP = true;
		}
		else if (elevators[0].getLevel() == itr->goal && itr->pickedUP) {
			itr->arrived = true;
			/*
			floorCall.erase(itr);
			if (floorCall.empty())
				return;
			itr = floorCall.begin();*/
			++done;
			leaving = true;
		}
	}
	if (leaving) {
		elevators[0].setExiting(true);
	}

	elevators[0].move();

	/////////////////////////////////////////////////////
	list<call>::iterator Oitr;
	for (Oitr = floorCall.begin(); Oitr != floorCall.end(); Oitr++) {
		if(Oitr->arrived == false)
			Oitr->waitingTime++;
	}
	///////////////////////////////////////////////
	return done;
}
void building::simulate() {

	int count = 0;
	srand(time(NULL));
	
	int index = 0;
	while (index < 10) {
		elevators[0].restart(0);
		int requests = 0;
		int complete = 0;
		if (!floorCall.empty()) {
			floorCall.clear();
		}
		
		/*  
		int possiblePeople = rand() % 50;

		for (int z = 0; z < possiblePeople; z++) {

			bool TrueFalse = ((rand() % 100) < 10);
			if (TrueFalse) {
				generate();
				requests++;
			}
		}
		*/
		call newCall;
		newCall.floor = 0;
		newCall.goal = 4;
		newCall.pickedUP = false;
		newCall.arrived = false;
		newCall.direction = 1;
		newCall.waitingTime = 0;
		call newCall1;
		newCall1.floor = 0;
		newCall1.goal = 2;
		newCall1.pickedUP = false;
		newCall1.arrived = false;
		newCall1.direction = 1;
		newCall1.waitingTime = 0;
		floorCall.push_back(newCall);
		floorCall.push_back(newCall1);
		//generate();
		//generate();
		requests++;
		requests++;

		setLocation(location);

		while ( (complete < requests) ||!elevators[0].destinations.empty()) {
			moveCalls();
			complete += moveElevators();
			if  (elevators[0].destinations.size() == 0){}

			// (if the first floor was the first destination & there are still destinations) or if people were let off
			else if ((elevators[0].destinations.size() > 1 && elevators[0].destinations.front() < elevators[0].getLevel()) || elevators[0].getExiting())
				elevators[0].destinations.pop_front();

		}
		cout << "Round: " << index++ << " There were " << requests << " requests" << endl;
		dropOff(floorCall);
		cout <<  endl;

		list<call>::iterator itr;
		int i = 1;
		for (itr = floorCall.begin(); itr != floorCall.end(); itr++){
			cout << "The waiting time for floorcall [" << i << "] was " << itr->waitingTime << endl;
			i++;
		}

		cout << endl << endl;
		
		
	}
	
	
}

void building::generate() {

	int current_floor = rand() % 10;
	int desired_floor = rand() % 10;
	while (current_floor == desired_floor) {
		desired_floor = rand() % 10;
	}

	call newCall;
	newCall.floor = current_floor;
	newCall.goal = desired_floor;
	newCall.waitingTime = 0;
	newCall.pickedUP = false;
	newCall.arrived = false;
	if (current_floor < desired_floor) {
		newCall.direction = 1;
		floorCall.push_back(newCall);
		return;
	}
	else if (current_floor > desired_floor) {
		newCall.direction = 0;
		floorCall.push_back(newCall);
		return;
	}
	else {
		newCall.direction = -1;
		floorCall.push_back(newCall);
		return;
	}
}
