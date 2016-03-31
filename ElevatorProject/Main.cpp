#include "Building.h"
#include <iostream>
using namespace std;

void main(){

	building one;

	

	one.setFloors(10);
	one.setElevator(1);
	one.generate();
	one.simulate();

	system("pause");
}