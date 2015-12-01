/*
 * LinkedList.h
 *
 *  Created on: Oct 7, 2015
 *      Author: mrhs
 */

#ifndef TERM_H_
#define TERM_H_
#include "Occurance.h"
#include <string>
#include <vector>
#include <math.h>
#include <iostream>
using namespace std;

class Term {

private:
	string mTerm;
	vector<Occurance*>* mListPointer;

public:
	Term(string term)
	{
		mTerm = term;
		mListPointer = new vector<Occurance*>;
	}
	~Term()
	{
		for(int i=0;i<mListPointer->size();i++)
		{
			delete mListPointer->at(i);
		}
		delete mListPointer;
	}

	vector<int>* getDocAddrList(Document* doc){
		for(int i=0;i<mListPointer->size();i++){
			if(mListPointer->at(i)->getDoc() == doc){
				return mListPointer->at(i)->getAddrList();
			}
		}
	}
	void calculateTfidf(int docCount){
		float idf = log10f((float)(docCount)/mListPointer->size());
		for(int i=0;i<mListPointer->size();i++)
		{
			mListPointer->at(i)->setTfIdf(mListPointer->at(i)->getRepeat()*idf);
		}
	}
	void sortByTfidf(int docCount){
		calculateTfidf(docCount);
		//TODO for the sake of simplicity bubble sort is used but it has to be exchanged with merge sort
		//++++++++++++++++++
		for(int i=0;i<mListPointer->size()-1;i++)
		{
			for(int j=0;j<mListPointer->size()-1-i;j++)
			{
				if(mListPointer->at(i)->getTfIdf() < mListPointer->at(i+1)->getTfIdf()){
					swap(mListPointer->at(i),mListPointer->at(i+1));
				}
			}
		}
		//++++++++++++++++++
	}
	string getTerm(){return mTerm;}
	vector<Occurance*>* getPointer(){return mListPointer;}

};


#endif /* LINKEDLIST_H_ */
