#pragma once
#include <vector>
#include <list>


using namespace std;

class Elevator {
public:
	void connect(list<int> list) { elevator = list.begin(); };
	void addDestination(int floor);
	void moveUp() { ++elevator; current = *elevator; checkDestinations(); };
	void moveDown() { --elevator; current = *elevator; checkDestinations(); };
	void checkDestinations();
	void move();
	void setID(int id) { ID = id; };
	int getLevel() { return current; }
private:
	int ID, current, direction;
	list<int>::iterator elevator;
	list<int> destinations;
	bool up;
	bool moving;
};

class building {
	friend class elevator;
public:
	void generate();
	void setElevator(int number = 1);
	void setFloors(int floors = 10);
	void moveCalls();
	void moveElevators();
	void simulate();
private:
	struct call { int floor, goal, direction; };
	list<call> floorCall;
	list<int> frame;
	vector<Elevator> elevators;
	int elevatorNumber;
	int floorNumbers;

};