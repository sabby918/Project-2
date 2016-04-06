#include "building.h"
#include <ctime>
#include <iostream>

/////////////////// MOST UPDATED

///////////
///////////  if two destinations on the same f
///////////
////////////
////////////
//////////////
void timeCoversion(int time) {

	time *= 30;
	int minutes = time / 60;
	int seconds = time % 60;
	cout << minutes << " Minutes " 
		<< seconds << " Seconds";
}

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
	list<call>::iterator itr;
	itr = floorCall.begin();
	while (itr != floorCall.end()) {
		if (elevators[0].destinations.empty() && !itr->pickedUP) {
			elevators[0].addDestination(itr->floor);
			return;
		}
		itr++;
	}
	
	// go through all floor calls
}

void building::setLocation(list<call>::iterator here) {
	location = floorCall.begin();
}

int building::moveElevators() {
	int num = 0;
	bool leaving;
	list<call>::iterator floor;
	for (floor = floorCall.begin(); floor != floorCall.end(); floor++) {
		if (floor->floor == elevators[0].getLevel() && !floor->pickedUP) {
			elevators[0].addDestination(floor->goal);
			floor->pickedUP = true;
		}
	}
	list<int>::iterator dest;
	dest = elevators[0].destinations.begin();
	while(dest != elevators[0].destinations.end()) {
		if (*dest == elevators[0].getLevel()) {
			for (floor = floorCall.begin(); floor != floorCall.end(); floor++) {
				if (floor->goal == elevators[0].getLevel() && floor->pickedUP && !floor->arrived) {
					floor->arrived = true;
					num++;
				}
			}
			elevators[0].destinations.erase(dest);
			break;
		}
		dest++;
	}
	if (!elevators[0].destinations.empty()) {
		list<call>::iterator Oitr;
		for (Oitr = floorCall.begin(); Oitr != floorCall.end(); Oitr++) {
			if (Oitr->arrived == false)
				Oitr->waitingTime++;
		}
	}
	elevators[0].move();
	return num;
}

void building::simulate() {
	int index = 0;
	int count = 0;
	srand(time(NULL));

	while (index < 24) {
		elevators[0].restart(0);
		int requests = 0;
		int complete = 0;
		if (!floorCall.empty()) {
			floorCall.clear();
		}
		/*call newCall;
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
	
		requests++;
		requests++;
		call newCall2;
		newCall2.floor = 6;
		newCall2.goal = 0;
		newCall2.pickedUP = false;
		newCall2.arrived = false;
		newCall2.direction = 0;
		newCall2.waitingTime = 0;
		floorCall.push_back(newCall2);
		requests++;
		call newCall3;
		newCall3.floor = 5;
		newCall3.goal = 6;
		newCall3.pickedUP = false;
		newCall3.arrived = false;
		newCall3.direction = 0;
		newCall3.waitingTime = 0;
		floorCall.push_back(newCall3);
		requests++;
		*/
		int possiblePeople = rand() % 50;
		int percentage = 50;
		requests = createCalls(requests, 75, 100);
		setLocation(location);
		while (requests > complete) {
			moveCalls();
			while (!elevators[0].destinations.empty()) {
				complete += moveElevators();
			}
		}
		cout << "Round: " << index++ << " There were " << requests << " requests" << endl;
		dropOff(floorCall);
		cout << endl;

		list<call>::iterator itr;
		int i = 1;
		for (itr = floorCall.begin(); itr != floorCall.end(); itr++) {
			cout << "The waiting time for floorcall [" << i << "] was "; timeCoversion(itr->waitingTime);
				cout << endl;
			i++;
		}

		cout << endl << endl;

	}
}
/*void building::simulate() {

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
		call newCall2;
		newCall2.floor = 6;
		newCall2.goal = 0;
		newCall2.pickedUP = false;
		newCall2.arrived = false;
		newCall2.direction = 0;
		newCall2.waitingTime = 0;
		floorCall.push_back(newCall2);
		requests++;
		call newCall3;
		newCall3.floor = 5;
		newCall3.goal = 6;
		newCall3.pickedUP = false;
		newCall3.arrived = false;
		newCall3.direction = 0;
		newCall3.waitingTime = 0;
		floorCall.push_back(newCall3);
		requests++;
		setLocation(location);

		while ( (complete < requests) || !floorCall.empty()) {
			moveCalls();
			complete += moveElevators();
			if (elevators[0].destinations.size() == 1 && elevators[0].destinations.front() == elevators[0].getLevel()) {
				elevators[0].destinations.pop_front();
			}
			// (if the first floor was the first destination & there are still destinations) or if people were let off
			else if (elevators[0].destinations.size() > 1 && ((elevators[0].destinations.front() < elevators[0].getLevel() && elevators[0].direction == 1)||( elevators[0].destinations.front() > elevators[0].getLevel() && elevators[0].direction == 0)) || elevators[0].getExiting())
				if (!elevators[0].destinations.empty()) {
					elevators[0].destinations.pop_front();
				}
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
*/
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
int building::createCalls(int requests, int percentage, int possiblePeople) {

	for (int z = 0; z < possiblePeople; z++) {

		bool TrueFalse = ((rand() % 100) < percentage);
		if (TrueFalse) {
			generate();
			requests++;
		}
	}
	return requests;
}

