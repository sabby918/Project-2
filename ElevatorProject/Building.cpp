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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////





void building::dropOff(list<call> request) {
	list<call>::iterator itr;

	vector<call> people;

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
	list<int>::iterator floor;
	
	if (elevators[0].destinations.empty()) {
		elevators[0].addDestination(location->floor);
		location++;
	}
	else {
		for (floor = elevators[0].destinations.begin(); floor != elevators[0].destinations.end(); floor++) {
			if (*floor == location->floor) {
				cout << "we are already going there" << endl;
				location++;
				return;
			}
		}
		elevators[0].addDestination(location->floor);
		location++;
	}
}
void building::setLocation(list<call>::iterator here) {
	location = floorCall.begin();
}
int building::moveElevators() {
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
		}
	}
	for (int z = 0; z < elevators.size(); z++) {
		elevators[z].move();
	}
	return done;
}

void building::simulate() {

	
	int count = 0;
	srand(time(NULL));
	
	int index = 0;
	while (index < 10) {
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

		generate();
		requests++;

		setLocation(location);

		while ( (complete < requests) ||!elevators[0].destinations.empty()) {
			moveCalls();
			complete = moveElevators();

		}
		cout << "Round: " << index++ << " There were " << requests << " requests" << endl;
		dropOff(floorCall);
		
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
