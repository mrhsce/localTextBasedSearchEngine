/*
 * Occurance.h
 *
 *  Created on: Nov 6, 2015
 *      Author: mrhs
 */
#include "Document.h"
#include "Term.h"
#include <string>
#include <vector>

#ifndef OCCURANCE_H_
#define OCCURANCE_H_

using namespace std;

class Occurance {
public:
	Occurance(Document* doc);
	virtual ~Occurance();

	void pushAddr(int addr);
	Document* getDoc(){return doc;}
	vector<int>* getAddrList(){return occuranceAddresses;}
	int getRepeat(){return repeat;}
	float getTfIdf(){return tfIdf;}
	void setTfIdf(float value){tfIdf = value;}

private:
	vector<int>* occuranceAddresses;
	int repeat;
	float tfIdf;
	Document* doc;

};

#endif /* OCCURANCE_H_ */
