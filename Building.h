#pragma once
#include <vector>
#include <list>


using namespace std;

class elevator {
private:
	int current, floornumber;
	bool up;
	bool moving;
public:
	// log of where the elevator will go
	list<int> destinations;
	int direction = -1;
	void restart(int number) { current = number; }
	void setMoving(bool yes_no) { moving = yes_no; }
	bool isMoving() { return moving; }
	void addDestination(int floor);
	void moveUp() {if (current < floornumber) {++current; } };
	void moveDown() {if (current > 0) {--current; } };
	void checkDestinations();
	void changeDirection();
	void move();
	void setNumFloor(int floor) {floornumber = floor; };
	int getLevel() { return current; }

};

class building {
	friend class elevator;
private:

	struct call { int floor, goal, direction, waitingTime; bool pickedUP, arrived; };

	// list of all the calls that are generated for that round
	list<call> floorCall;
	elevator theElevator;
	int elevatorNumber;

	//total number of floors in the building
	int floorNumbers;
	int completeCalls = 0;
	int roundTime = 0;
public:
	//where are we in the floorCall list
	list<call>::iterator location = floorCall.begin();
	void setLocation(list<call>::iterator here);
	int getComplete() { return completeCalls; }
	void calcWaitingTime();

	//creates a random call
	void generate();
	void generate(int numfloors);
	bool searchDest(int target, list<int> theList);
	bool searchCall(int target, list<call> theList);
	void setElevator(int number = 1);
	void setFloors(int floors = 10);
	void dropOff(list<call> requests,ostream& file);
	void moveCalls();
	int moveElevators();
	void simulate();
	void pickup();
	int dropoff(int num);
	int createCalls(int requests, int percentage, int possiblePeople);
};
