#include "building.h"
#include <ctime>
#include <iostream>

void building::setElevator(int number) {
	for (int i = 0; i < number; i++) {
		Elevator elevator;
		elevator.setID(i);
		elevators.push_back(elevator);
	}
}

void building::setFloors(int floor) {
	floorNumbers = floor;
}

void building::moveCalls() {
	list<call>::iterator itr;

	for (itr = floorCall.begin(); itr != floorCall.end(); itr++) {
		int closest = 0; int diffrence = 100;
		for (int i = 0; i < elevators.size(); i++) {
			if (diffrence >(elevators[i].getLevel() - itr->floor)) {
				closest = i;
				diffrence = elevators[i].getLevel() - itr->floor;
			}
		}
		elevators[closest].addDestination(itr->floor);
	}
}

void building::moveElevators() {
	list<call>::iterator itr;
	for (int i = 0; i < elevators.size(); i++) {
		for (itr = floorCall.begin(); itr != floorCall.end(); itr++) {

			if (elevators[i].getLevel() == itr->floor && !itr->pickedUP ) {
				elevators[i].addDestination(itr->goal);
				itr->pickedUP = true;
				floorCall.erase(itr);
				if (floorCall.empty())
					return;
				itr = floorCall.begin();
			}
		}
	}
	for (int z = 0; z < elevators.size(); z++) {
		elevators[z].move();
	}
}
void building::simulate() {

	int count = 0;
	srand(time(NULL));

	int index = 0;
	while (index < 10) {

		int possiblePeople = rand() % 50;

		for (int z = 0; z < possiblePeople; z++) {

			bool TrueFalse = ((rand() % 100) < 10);
			if (TrueFalse) {
				generate();
			}
		}


		while (!floorCall.empty() || !elevators[0].destinations.empty()) {
			moveCalls();
			moveElevators();
			count++;
			cout << count << endl;
		}
		index++;
		
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