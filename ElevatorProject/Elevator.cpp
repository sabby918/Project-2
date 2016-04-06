#include "building.h"
#include <ctime>
#include <iostream>


void building::setElevator(int number) {
	theElevator.setNumFloors(number);
}

void building::setFloors(int floor) {
	floorNumbers = floor;
}


// determine where the request began, and where it was dropped off at
void building::dropOff(list<call> request) {
	list<call>::iterator itr;

	vector<call> people;

	for (itr = request.begin(); itr != request.end(); itr++) {
		if (itr->arrived) {
			people.push_back(*itr);
		}
	}
	for (int i = 0; i < people.size(); i++) {
		cout << "Request ["<< i+1 << "] went from floor " << people[i].floor << " to floor " << people[i].goal << endl;
	}

}

//add call to destination log
void building::moveCalls() {
	if (floorCall.size() == 0)
		return;

	if (location == floorCall.end()) {
		return;
	}
	list<call>::iterator itr;
	itr = floorCall.begin();
	while (itr != floorCall.end()) {
		if (theElevator.destinations.empty() && !itr->pickedUP) {
			theElevator.addDestination(itr->floor);
			return;
		}
		itr++;
	}
}


void building::setLocation(list<call>::iterator here) {
	location = floorCall.begin();
}

// return true if target was found
bool building::searchDest(int target, list<int> theList) {
	list<int>::iterator itr;
	for (itr = theList.begin(); itr != theList.end(); itr++) {
		if (target == *itr)
			return true;
	}
	return false;
}

//return true if target was found
bool building::searchCall(int target, list<call> theList) {
	list<call>::iterator itr;
	for (itr = theList.begin(); itr != theList.end(); itr++) {
		if (target == itr->floor)
			return true;
	}
	return false;
}

//increase time if call has not arrived
void building::calcWaitingTime() {
	list <call> ::iterator itr;
	for (itr = floorCall.begin(); itr != floorCall.end(); itr++) {
		if (itr->arrived == false)
			itr->waitingTime++;
	}
}

// moves elevator up and down && checks to see if there is a request entering and leaving the floor
int building::moveElevators() {
	int num = 0;
	bool leaving;
	list<call>::iterator floor;
	for (floor = floorCall.begin(); floor != floorCall.end(); floor++) {
		if (floor->floor == theElevator.getLevel() && !floor->pickedUP) {
			floor->pickedUP = true;
			if (!searchDest(floor->goal, theElevator.destinations)) {
				theElevator.addDestination(floor->goal);
			}
		}
	}

	list<int>::iterator dest;
	dest = theElevator.destinations.begin();
	while(dest != theElevator.destinations.end()) {
		if (*dest == theElevator.getLevel()) {
			for (floor = floorCall.begin(); floor != floorCall.end(); floor++) {
				if (floor->goal == theElevator.getLevel() && floor->pickedUP && !floor->arrived) {
					floor->arrived = true;
					num++;
				}
			}
			theElevator.destinations.erase(dest);
			break;
		}
		dest++;
	}
	

	theElevator.move();
	if (theElevator.isMoving()) {
		calcWaitingTime();
	}
	// the number of people that have arrived
	return num;
}


void building::simulate() {
	int index = 0;
	int count = 0;
	srand(time(NULL));

	while (index < 10) {
		theElevator.restart(0);
		int requests = 0;
		int complete = 0;
		if (!floorCall.empty()) {
			floorCall.clear();
		}
		
		int possiblePeople = rand() % 50;

		for (int z = 0; z < possiblePeople; z++) {

			bool TrueFalse = ((rand() % 100) < 50);
			if (TrueFalse) {
				generate();
				requests++;
			}
		} 

		setLocation(location);
		while (requests > complete) {
			moveCalls();
			while (!theElevator.destinations.empty()) {
				complete += moveElevators();
			}
		}
		cout << "Round: " << index++ << " There were " << requests << " requests" << endl;
		dropOff(floorCall);
		cout << endl;

		list<call>::iterator itr;
		int total = 0;
		int i = 1;
		for (itr = floorCall.begin(); itr != floorCall.end(); itr++) {
			cout << "The waiting time for floorcall [" << i << "] was " << itr->waitingTime << endl;
			i++;
			total += itr->waitingTime;

		}
		
		cout << endl;

		if (requests > 0) {
			cout << "There was a total of " << total << " seconds" << endl
				<< "There was an average of " << total / requests << " seconds per request" << endl;
			cout << endl << endl;
		}
	}
}

// creates a random request
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
