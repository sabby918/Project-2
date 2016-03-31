#include "building.h"


void Elevator::addDestination(int floor) {
	list<int>::iterator itr;
	moving = true;
	if (destinations.empty()) {
		destinations.push_back(floor);
		if ((current - floor) > 0) {
			up = false;
		}
		else
			up = true;

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

void Elevator::checkDestinations() {
	list<int>::iterator itr;
	if (destinations.empty())
		return;
	for (itr = destinations.begin(); itr != destinations.end(); itr++) {
		if (*itr == current) {
			destinations.remove(*itr);
			return;
		}
	}
}

void Elevator::move() {
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