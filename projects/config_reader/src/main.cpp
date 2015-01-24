/*
 * main.cpp
 *
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

#include "ConfigReader.h"

int main() {
	ConfigReader* configReader;

	configReader = ConfigReader::getInstance();

	cout << "First value: " << configReader->getStringValue("first_key") << endl;
	cout << "PID kI: " << configReader->getFloatValue("pid_controller_kI") << endl;
	cout << "key_integer: " << configReader->getIntValue("key_integer") << endl;

	return 0;
}


