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
	list<call> floorCall;
	elevator theElevator;
	int elevatorNumber;
	int floorNumbers;
	int completeCalls = 0;
public:
	list<call>::iterator location = floorCall.begin();
	void setLocation(list<call>::iterator here);
	int getComplete() { return completeCalls; }
	void calcWaitingTime();
	void generate();
	bool searchDest(int target, list<int> theList);
	bool searchCall(int target, list<call> theList);
	void setElevator(int number = 1);
	void setFloors(int floors = 10);
	void dropOff(list<call> requests);
	void moveCalls();
	int moveElevators();
	void simulate();
	void pickup();
	int dropoff(int num);
	int createCalls(int requests, int percentage, int possiblePeople);
};
