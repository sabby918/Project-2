#pragma once
#include <vector>
#include <list>


using namespace std;

class Elevator {
private:
	int ID, current, floornumber;
	bool up;
	bool exits = false;
	bool moving;
public:
	list<int> destinations;
	int direction = -1;
	void setExiting(bool yes_no) { exits = yes_no; }
	bool getExiting() { return exits; }
	void restart(int number) { current = number; }
	void addDestination(int floor);
	void moveUp() {if (current < floornumber) {++current; } };
	void moveDown() {if (current > 0) {--current; } };
	void checkDestinations();
	void changeDirection();
	void move();
	void setID(int id, int floor) { ID = id, floornumber = floor; };
	int getLevel() { return current; }

};

class building {
	friend class elevator;
private:
	struct call { int floor, goal, direction, waitingTime; bool pickedUP, arrived; };
	list<call> floorCall;
	vector<Elevator> elevators;
	int elevatorNumber;
	int floorNumbers;
	int completeCalls = 0;
public:
	list<call>::iterator location = floorCall.begin();
	void setLocation(list<call>::iterator here);
	int getComplete() { return completeCalls; }
	void generate();
	void setElevator(int number = 1);
	void setFloors(int floors = 10);
	void dropOff(list<call> requests);
	void moveCalls();
	int moveElevators();
	void simulate();
	void pickup();
	int dropoff( int num);
	int createCalls(int requests, int percentage, int possiblePeople);
};
