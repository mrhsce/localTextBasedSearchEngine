#include <iostream>
#include "DocumentAnalyzer.h"
#include "FileNameManager.h"
#include <algorithm>
#include <iomanip>
#include <fstream>
#include "SimilarityMatrix.h"
using namespace std;


void printList(Hashmap* hash,ofstream &out,FileNameManager &fnMgr);
void printSimilarity(Hashmap* hash,ofstream &out,FileNameManager &fnMgr,int threshold);

string readFile(char* addr)
{
	string out = "";
	ifstream file;
	file.open(addr,ios::in);
	std::string temp;
	while(std::getline(file, temp)) {
		if(out != "")
			out += "\n";
		out += temp;
	}
	file.close();
	return out;

}

vector<string> tokenizer(string txt){
	vector<string> result;
	string tmpStr = "";
	for(int i = 0;i<txt.size();i++)
	{
		if(('a'<=txt.at(i) && txt.at(i)<='z') || ('A'<=txt.at(i) && txt.at(i)<='Z') || txt.at(i)=='\'')
		{
			tmpStr += txt.at(i);
		}
		else if(tmpStr!="")
		{
			result.push_back(tmpStr);
			tmpStr = "";
		}
	}
	result.push_back(tmpStr);
	return result;
}

void findMultiple(vector<string> termList,Hashmap* hash,FileNameManager &fnMgr){
	vector<Document *> documentList,sharedList;
	// In this section all documents having the desired terms are retrieved
	// in a sorted list with document repetition

	for(int i=0;i<termList.size();i++){
		vector<Occurance *>* tmpList = hash->getPointer(termList[i]);
		if(tmpList == NULL){
			cout<<"The word "<<termList[i]<<" does not exist in the documents"<<endl;
			break;
		}
		for(int j=0;j<tmpList->size();j++){
			documentList.push_back(tmpList->at(j)->getDoc());
		}
		sort(documentList.begin(),documentList.end());
	}
	// Here documents repeated with the number of the termList are put inside
	// sharedList meaning they have all the words in termList
	if(documentList.size()>0){
		Document* tmpDoc = NULL;
		int count=0;
		for(int i=0;i<documentList.size();i++){
			if(documentList[i] == tmpDoc || tmpDoc == NULL){
				tmpDoc = documentList[i];
				count++;
			}
			else{
				tmpDoc = documentList[i];
				count = 1;
			}
			if(count == termList.size()){
				sharedList.push_back(documentList[i]);
				tmpDoc = NULL;
				count = 0;
			}
		}
	}
	// Post process checks that the words in termList are in the desired order of the user
	vector<int> addrList,secAddrList;
	for(int i=0;i<sharedList.size();i++){
		addrList = *(hash->getTerm(termList[0])->getDocAddrList(sharedList[i]));
		// Takes the address of the places the first term occurred in the doc
		for(int j=1;j<termList.size();j++){
			secAddrList = *(hash->getTerm(termList[j])->getDocAddrList(sharedList[i]));
			// Takes the address of the places the j-th term occurred in the doc
			vector<int> tmpList; // holds the addresses that has passed
			//in each itearation checks the addresses that has passed the previous iteration
			// about the existance of the next word
			for(int k=0;k<addrList.size();k++){
				if(find(secAddrList.begin(),secAddrList.end(),addrList[k]+j) != secAddrList.end()){
					tmpList.push_back(addrList[k]);
				}
			}
			if(tmpList.size()==0) //It means no addresses has remained
				break;
			else{
				addrList = tmpList; //puts the remaining addresses in the tmpList for next level
			}
		}
		//The number of addresses that all the words has been found in desired order in
		// the sharedList[i]
		if(addrList.size() > 0){
			cout<<"In the document: "<<fnMgr.getFileName(sharedList[i]->getId())<<endl;
			cout<<addrList.size()<<" occurance has been found"<<endl;
		}
	}

}

void find(string term,Hashmap* hash,FileNameManager &fnMgr){
	vector<Occurance *>* mListPointer = hash->getPointer(term);
	if(mListPointer)
	{
		cout<<term<<" exists in ";
		for(int i=0;i<mListPointer->size();i++)
		{
			if(i != 0)
			{
				cout<<",";
			}

			cout<<fnMgr.getFileName(mListPointer->at(i)->getDoc()->getId())<<"("<<mListPointer->at(i)->getTfIdf()<<")";
		}
		cout<<endl;
	}
	else{
		cout<<"Not found"<<endl;
	}
}

int main(int argc, char* argv[])
{
	Hashmap* hash = new Hashmap();
	FileNameManager fNameMgr;

	ofstream out;
	out.open("result.xml",ios::out);

	cout<<"The number of documents are: "<<argc-1<<"\n"<<endl;
	for(int i=1;i<argc;i++)
	{
		cout<<argv[i]<<"\n"<<endl;
		documentAnalyzer(new Document(readFile(argv[i]),fNameMgr.addFileName(argv[i])),hash);

	}
	hash->postProcessTfIdf(argc-1);

	printSimilarity(hash,out,fNameMgr,10);

//	printList(hash,out,fNameMgr);
//	cout<<"\nOutput saved in result.txt\n"<<endl;
	out.close();
//	string input="";
//	while(true){
//		cout<<"please insert the token to be searched: ";
//		std::getline(cin,input);
//		//cin.get(input);
//		vector<string> list = tokenizer(input);
//		if(list.size() <= 1){
//			find(list[0],hash,fNameMgr);
//		}
//		else{
//			findMultiple(list,hash,fNameMgr);
//		}
//
//	}



	return 0;
}

void printSimilarity(Hashmap* hash,ofstream &out,FileNameManager &fnMgr,int threshold){
	SimilarityMatrix similMat(fnMgr.getFileCount(),threshold);
	similMat.processTermList(hash);
	cout<<endl<<"The similarity between files with "<<threshold<<" threshold:"<<endl;
	vector<int>* resulist;
	for(int i=0;i<fnMgr.getFileCount();i++){
		cout<<fnMgr.getFileName(i)<<" is similar with: "<<endl;
		resulist = similMat.getSimilarity(i);
		for(int j=0;j<resulist->size();j++){
			cout<< fnMgr.getFileName(resulist->at(j))<<", ";
		}
		cout<<endl;
	}
}

void printList(Hashmap* hash,ofstream &out,FileNameManager &fnMgr)
{
	vector<string>* termList = hash->getTermList();
		sort(termList->begin(),termList->end());

		vector<Occurance *>* mListPointer;
		//cout<<endl<<"INVERTED INDEX\nTERM DOCUMENT LIST"<<endl<<endl<<"-----------------------"<<endl;
		out<<endl<<"INVERTED INDEX\nTERM DOCUMENT LIST"<<endl<<endl<<"-----------------------"<<endl;
		for(int i =0;i<termList->size();i++)
		{
			mListPointer = hash->getPointer(termList->at(i));
			if(mListPointer)
			{
				//cout<<setw(15)<<termList->at(i)<<setw(10)<<"-->"<<left<<"[";
				out<<setw(15)<<termList->at(i)<<setw(10)<<"-->"<<left<<"[";
				for(int i=0;i<mListPointer->size();i++)
				{
					if(i != 0)
					{
						//cout<<",";
						out<<",";
					}
					//cout<<"{";
					out<<"{";
					//cout<<mListPointer->at(i)->getDoc()->getId()<<"->";
					out<<fnMgr.getFileName(mListPointer->at(i)->getDoc()->getId())<<"->";
					vector<int>* occuranceAddresses = mListPointer->at(i)->getAddrList();
					for(int i = 0;i<occuranceAddresses->size();i++){
						//cout<<occuranceAddresses->at(i);
						out<<occuranceAddresses->at(i);
						if(i != occuranceAddresses->size()-1)
						{
							//cout<<",";
							out<<",";
						}
					}

					//cout<<"}";
					out<<"}";
				}
				//cout<<"]"<<endl;
				out<<"]"<<endl;
			}
		}
}
