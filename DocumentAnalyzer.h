/*
 * DocumentAnalyzer.cpp
 *
 *  Created on: Oct 9, 2015
 *      Author: mrhs
 */

#ifndef DOCUMENTANALYZER_H_
#define DOCUMENTANALYZER_H_
#include "HashMap.h"
#include "cstring"

string toLower(string in);
void documentAnalyzer(Document* docPtr,Hashmap* hash)
{
	string txt = docPtr->getText();

	int counter = 0;

	string tmpStr = "";
	string escapechars = " ,.-\n\t?!'(){}[]/\\<>\":;*&%$#=+-—_0123456789";

	//cout<<"the size of the text is "<<txt.size()<<endl;
	for(int i = 0;i<txt.size();i++)
	{
		if(('a'<=txt.at(i) && txt.at(i)<='z') || ('A'<=txt.at(i) && txt.at(i)<='Z') || txt.at(i)=='\'')
			{
				tmpStr += txt.at(i);
			}
		else if(tmpStr!="")
		{
			//return;
			//cout<<"The counter is "<<counter<<endl;
			//cout<<"the term is "<<tmpStr<<endl;
			hash->addOccuranceAddr(toLower(tmpStr),docPtr,counter);
			//cout<<"hash has been added"<<endl;
			tmpStr = "";
			counter++;
		}
	}
	hash->addOccuranceAddr(toLower(tmpStr),docPtr,counter);
}

string toLower(string in)
{
	for (int i=0;i<in.size();i++)
	{
		if(in.at(i)<='Z' && in.at(i)>='A')
			in.at(i) = in.at(i)-('Z'-'z');
	}
	return in;
}

#endif


