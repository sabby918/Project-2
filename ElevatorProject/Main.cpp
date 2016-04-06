
#include "Building.h"
#include <iostream>
#include <fstream>

	using namespace std;

void main() {
	bool reloop = true;
	while (reloop) {
		int choice;
		cout << "Welcome to the Elevator Simulator!!!!" << endl << "what would you like to do today?" << endl << "1. Simulate the defult elevator case?" << endl << "2. Simulate Custom elevator Case?" << endl << "3. Quit?" << endl << ">>";
		cin >> choice;
		switch (choice) {

		case 1:
			if (true) {
			building Building;
			Building.setFloors(10);
			Building.setElevator(10);
			Building.simulate();
			break;
		}
		case 2:
			if (true) {
				building Building;
				int floorNumber;
				int typeOfTraffic;
				int NumberElevators;
				cout << "specify the Number of floors" << endl << ">>";
				cin >> floorNumber;
				Building.setFloors(floorNumber);
				Building.setElevator(floorNumber);
				cout << "specify the type of traffic?" << endl << "1. low " << endl << "2. medium" << endl << "3. high" << endl << ">>";
				cin >> typeOfTraffic;
				if (typeOfTraffic == 1)
				{
					Building.traffic = 25;
				}
				else if (typeOfTraffic == 2) {
					Building.traffic = 50;
				}
				else if (typeOfTraffic == 3) {
					Building.traffic = 75;
				}
				else {
					cout << "Incorrect Choice was made so medium traffic wil be used" << endl;
					Building.traffic = 50;
				}
				Building.simulate();
			}
			break;
		case 3:
			reloop = false;
			break;
		default:
			cout << "Please Enter a valid Option";
			break;
		}
	}
}
