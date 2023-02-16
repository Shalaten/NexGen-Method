#include "ChargeWeightsMethod.h"


int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru");

	ChargeWeightsMethod method(4);


	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "               BROOD FORCE    " << std::endl;
	method.PrintBroodForceMethodWay();

	return 0;
}