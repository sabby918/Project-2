#pragma once
#include <vector>
#include <list>


using namespace std;

class Elevator {
private:
	int ID, current, direction, floornumber;
	bool up;
	bool moving;
	int floorNumber;
public:
	list<int> destinations;
	void addDestination(int floor);
	void moveUp() { ++current; checkDestinations(); };
	void moveDown() { --current; checkDestinations(); };
	void checkDestinations();
	void changeDirection();
	void move();
	void setID(int id) { ID = id; };
	int getLevel() { return current; }

};

class building {
	friend class elevator;
private:
	struct call { int floor, goal, direction; bool pickedUP; };
	list<call> floorCall;
	vector<Elevator> elevators;
	int elevatorNumber;
	int floorNumbers;
public:
	void generate();
	void setElevator(int number = 1);
	void setFloors(int floors = 10);
	void moveCalls();
	void moveElevators();
	void simulate();
};