#include "building.h"
#include <ctime>
#include <iomanip> 
#include <iostream>
#include <fstream>



int timeCoversion(int time, ostream& file) {

	time *= 10;
	int minutes = time / 60;
	int seconds = time % 60;
	if (minutes == 1) {
		file << minutes << " Min "
			<< seconds << " Secs";
	}
	else {
		file << minutes << " Mins "
			<< seconds << " Secs";
	}

	return time / 10;
}


void building::setElevator(int number) {

	theElevator.setNumFloor(floorNumbers);

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
	roundTime += 1;
}

void building::setFloors(int floor) {
	floorNumbers = floor;
}

void building::dropOff(list<call> request, ostream& file) {
	list<call>::iterator itr;

	vector<call> people;

	// push all the people that have arrived at there destination
	for (itr = request.begin(); itr != request.end(); itr++) {
		if (itr->arrived) {
			people.push_back(*itr);
		}
	}
	for (int i = 0; i < people.size(); i++) {
		file << "Request went from floor " << people[i].floor << " to floor " << people[i].goal << endl;
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

void building::pickup() {
	list<call>::iterator floor;
	for (floor = floorCall.begin(); floor != floorCall.end(); floor++) {
		if (floor->floor == theElevator.getLevel() && !floor->pickedUP) {
			if (!searchDest(floor->goal, theElevator.destinations)) {
				theElevator.addDestination(floor->goal);
			}
			floor->pickedUP = true;
		}
	}
}

int building::dropoff(int num) {
	list<call>::iterator floor;
	list<int>::iterator dest;
	dest = theElevator.destinations.begin();
	while (dest != theElevator.destinations.end()) {
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
	return num;
}
int building::moveElevators() {
	int num = 0;
	bool leaving;
	pickup();

	num = dropoff(num);

	theElevator.move();


	if (theElevator.isMoving()) {
		calcWaitingTime();
	}

	return num;
}

void building::simulate() {
	int index = 0;
	int count = 0;
	srand(time(NULL));
	ofstream fout;
	fout.open("example.txt");
	while (index < 10) {
		roundTime = 0;
		theElevator.restart(0);
		int requests = 0;
		int complete = 0;
		if (!floorCall.empty()) {
			floorCall.clear();
		}

		int possiblePeople = rand() % 50;
		int percentage = 50;
		requests = createCalls(requests, traffic, 10);
		setLocation(location);
		while (requests > complete) {
			moveCalls();
			while (!theElevator.destinations.empty()) {
				complete += moveElevators();
			}
			if (roundTime < 360) {
				requests = createCalls(requests, traffic, 5);
			}

		}

		ofstream myfile;
		myfile.open("elevator.txt", ofstream::app);

		myfile << "\t     Round: " << ++index << " There were " << requests << " requests" << endl << endl;
		myfile << "Request		Start		Goal		Time		Approx." << endl;
		for (int i = 0; i < 50; i++) {
			myfile << "__";
		}
		myfile << endl << endl;

		list<call>::iterator itr;
		int i = 1;
		int averageTime = 0;
		for (itr = floorCall.begin(); itr != floorCall.end(); itr++) {
			myfile << i << "\t|\t" << itr->floor << "\t|\t" << itr->goal << "\t|\t" << itr->waitingTime << "\t|\t";
			averageTime += timeCoversion(itr->waitingTime, myfile);
			myfile << endl;
			i++;
		}
		averageTime = averageTime / requests;
		myfile << endl;
		myfile << "Average Time: "; timeCoversion(averageTime, myfile);
		myfile << endl;
		//timeCoversion(roundTime, myfile);
		cout << roundTime << endl;
		int temp = roundTime;
		temp = temp * 10;
		int minutes = temp / 60;
		int seconds = temp % 30;
		myfile << "RoundTime: " << minutes <<" Mins " << seconds << " Secs";
		myfile << endl << endl;

		for (int i = 0; i < 30; i++) {
			myfile << "+-";
		}
		myfile << endl;
		myfile.close();
	}

	cout << "Simulation Complete.  Go to elevator.txt for results" << endl << endl;
}

void building::generate() {

	int current_floor = rand() % floorNumbers;
	int desired_floor = rand() % floorNumbers;
	while (current_floor == desired_floor) {
		desired_floor = rand() % floorNumbers;
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

