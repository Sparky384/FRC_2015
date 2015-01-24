/*
 * ConfigReader.cpp
 *
 *  Singleton class for reading configuration file
 *
 */

#include "ConfigReader.h"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

ConfigReader* ConfigReader::instance = 0;

ConfigReader::ConfigReader() {
	ifstream inFile("config.txt");
	keyValueMap = new std::map<string, string>;

	string line;
	istringstream iss;
	string key, value;

	while(getline(inFile, line)){
	    iss.str(line);

	    if(!(iss >> key >> value)){
	    	break;
	    }

	    keyValueMap->insert(pair<string,string>(key, value));
	}
}

ConfigReader* ConfigReader::getInstance(){

	if(instance == 0){
		// create the singleton instance of this class
		instance = new ConfigReader();
	}

	return instance;
}

ConfigReader::~ConfigReader() {
	// delete the instance of the singleton
	delete instance;
	instance = 0;
}

int	ConfigReader::getIntValue(string key){
	float valueInt = 0;
	string valueString = getStringValue(key);

	if(valueString.size() > 0){
		valueInt = atoi(valueString.c_str());
	}

	return valueInt;
}

float ConfigReader::getFloatValue(string key){
	float valueFloat = 0.0;
	string valueString = getStringValue(key);

	if(valueString.size() > 0){
		valueFloat = atof(valueString.c_str());
	}

	return valueFloat;
}

string ConfigReader::getStringValue(string key){
	map<string, string>::iterator valueIterator;
	string valueString("");

	valueIterator = keyValueMap->find(key);

	if(valueIterator != keyValueMap->end()){
		valueString = valueIterator->second;
	}

	return valueString;
}



