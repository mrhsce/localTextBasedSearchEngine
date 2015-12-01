/*
 * HashMap.cpp
 *
 *  Created on: Oct 9, 2015
 *      Author: mrhs
 */
#include "HashMap.h"
#include <iostream>

using namespace std;

int Hashmap::hashmethod(string term)
{
	int value = 0;
	for ( int i = 0; i < term.length(); i++ )
		value += term[i];
	return value % LIST_SIZE;
}

void Hashmap::postProcessTfIdf(int docCount){
	cout<<"The post process has been called"<<endl;
	for(int i=0;i<LIST_SIZE;i++){
		for(std::list<Term*>::const_iterator iterator = mPointer[i]->begin(),end = mPointer[i]->end();iterator != end;++iterator)
		{
			(*iterator)->sortByTfidf(docCount);
		}
	}
}

Hashmap::Hashmap()
{
	for(int i=0;i<LIST_SIZE;i++)
	{
		mPointer[i] = NULL;
	}
}
Hashmap::~Hashmap()
{
	for(int i=0;i<LIST_SIZE;i++)
	{
		if(mPointer[i]){
			for(std::list<Term*>::const_iterator iterator = mPointer[i]->begin(),end = mPointer[i]->end();iterator != end;++iterator)
			{
				delete *iterator;
			}
			delete mPointer[i];
		}
	}
}

bool Hashmap::isExist(string term)
{
	if(getPointer(term))
		return true;
	else
		return false;
}

bool Hashmap::isOccuranceExist(string term,Document* doc){
	if(!Hashmap::getPointer(term,false)->empty()){
		for(int i=0;i<Hashmap::getPointer(term,false)->size();i++){
			if(Hashmap::getPointer(term,false)->at(i)->getDoc() == doc)
				return true;
		}
		return false;
	}
	else{
		return false;
	}
}

Occurance* Hashmap::addOccurance(string term,Document* doc){
	Occurance* occur = new Occurance(doc);
	Hashmap::getPointer(term,false)->insert(Hashmap::getPointer(term,false)->begin(),occur);
	return occur;
}
bool Hashmap::addOccuranceAddr(string term,Document* doc,int addr){


	if(!Hashmap::isExist(term)){
		Hashmap::getPointer(term,true);
		//cout<<"the term has been initialized"<<endl;
	}
	//cout<<"before check"<<endl;
	if(!Hashmap::isOccuranceExist(term,doc)){
		//cout<<"the occurance list for doc initialized"<<endl;
		Hashmap::addOccurance(term,doc);
	}
	//cout<<"before adding occur"<<endl;
	Hashmap::getPointer(term,false)->front()->pushAddr(addr);
	//cout<<"after adding occur"<<endl;
	return true;
}

Term* Hashmap::getTerm(string term){
	int index = hashmethod(term);
	if( mPointer[index])
	{
		list<Term*>* list = mPointer[index];
		for(std::list<Term*>::const_iterator iterator = list->begin(),end = list->end();iterator != end;++iterator)
		{
			Term * pntr = *iterator;
			if(pntr->getTerm() == term)
			{
				return pntr;
			}
		}
	}
	return NULL;
}

vector<Occurance *>* Hashmap::getPointer(string term,bool addIfNotExist)
{
	int index = hashmethod(term);
	if( mPointer[index])
	{
		list<Term*>* list = mPointer[index];
		for(std::list<Term*>::const_iterator iterator = list->begin(),end = list->end();iterator != end;++iterator)
		{
			Term * pntr = *iterator;
			if(pntr->getTerm() == term)
			{
				return pntr->getPointer();
			}
		}
		if(addIfNotExist)
		{
			Term* pntr = new Term(term);
			list->push_front(pntr);
			return pntr->getPointer();
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		if(addIfNotExist)
		{
			mPointer[index] = new list<Term*>;
			Term* pntr = new Term(term);
			mPointer[index]->push_front(pntr);
			return pntr->getPointer();

		}
		else
		{
			return NULL;
		}
	}
}
vector<string>* Hashmap::getTermList()
	{
		vector<string>* vecy = new vector<string>;
		string tmp = "";
		for(int i=0;i<LIST_SIZE;i++)
		{
			if(mPointer[i])
			{
				for(std::list<Term*>::const_iterator iterator = mPointer[i]->begin(),end = mPointer[i]->end();iterator != end;++iterator)
				{
					vecy->push_back((*iterator)->getTerm());
				}
			}
		}
		return vecy;
	}


