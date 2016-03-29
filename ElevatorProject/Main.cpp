#include "Building.h"
using namespace std;

void main(){

	building one;

	one.generate();

	one.setFloors(10);
	one.setElevator(1);
	one.simulate();

	system("pause");
}