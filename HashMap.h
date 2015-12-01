/*
 * HashMap.h
 *
 *  Created on: Oct 7, 2015
 *      Author: mrhs
 */

#ifndef HASHMAP_H_
#define HASHMAP_H_
#define LIST_SIZE 100

#include "Document.h"
#include "Occurance.h"
#include "Term.h"
#include <string>
#include <vector>
#include <list>

using namespace std;

class Hashmap {
private:
	list<Term*>* mPointer[LIST_SIZE];

	int hashmethod(string term);

public:
	Hashmap();
	~Hashmap();

	bool isExist(string term);
	bool addOccuranceAddr(string term,Document* doc,int addr);
	bool isOccuranceExist(string term,Document* doc);
	Occurance* addOccurance(string term,Document* doc);
	Term* getTerm(string Term);
	vector<Occurance*>* getPointer(string term,bool addIfNotExist = false);
	vector<string>* getTermList();

	void postProcessTfIdf(int docCount);

};


#endif /* HASHMAP_H_ */
