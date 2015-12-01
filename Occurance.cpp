/*
 * Occurance.cpp
 *
 *  Created on: Nov 6, 2015
 *      Author: mrhs
 */

#include "Occurance.h"

Occurance::Occurance(Document* docu) {
	// TODO Auto-generated constructor stub
	doc = docu;
	occuranceAddresses = new vector<int>;
	repeat = 0;
	tfIdf = 0;
}

Occurance::~Occurance() {
	// TODO Auto-generated destructor stub
}

void Occurance::pushAddr(int addr){
	occuranceAddresses->push_back(addr);
	repeat++;
}


