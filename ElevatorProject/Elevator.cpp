#include "building.h"


void elevator::addDestination(int floor) {
	list<int>::iterator itr;
	moving = true;
	if (destinations.empty()) {
		destinations.push_back(floor);
		if ((current - floor) > 0) {
			up = false;
			direction = 0;
		}
		else {
			up = true;
			direction = 1;
		}


		return;
	}
	for (itr = destinations.begin(); itr != destinations.end(); itr++) {
		if (floor < *itr) {
			destinations.insert(itr, floor);
			return;
		}
	}
	destinations.push_back(floor);
	return;
}

void elevator::checkDestinations() {
	list<int>::iterator itr;
	if (destinations.empty())
		return;
	for (itr = destinations.begin(); itr != destinations.end(); itr++) {
		if (*itr == current) {
	
			return;
		}
	}
}

void elevator::move() {

	changeDirection();

	
	
	if (destinations.empty()) {
		moving = false;
		up = false;
	}
	if (moving && up) {
		moveUp();
		return;
	}
	if (moving && !up) {
		moveDown();
		return;
	}
	else {
		return;
	}
}


void elevator::changeDirection() {
	list<int>::iterator itr;
	if (up) {
		bool greater = false;
		for (itr = destinations.begin(); itr != destinations.end(); itr++) {
			if (current > *itr) {
				greater = true;
				up = false;
			}
			else {
				greater = false;
				up = true;
				return;
			}
		}
		return;
	}
	else {
		bool greater = true;
		for (itr = destinations.begin(); itr != destinations.end(); itr++) {
			if (current < *itr) {
				greater = false;
				up = true;
			}
			else {
				greater = true;
				up = false;
				return;
			}
		}
		return;
	}
}
