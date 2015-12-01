/*
 * FileNameManager.cpp
 *
 *  Created on: Nov 7, 2015
 *      Author: mrhs
 */

#include "FileNameManager.h"


FileNameManager::FileNameManager() {
	// TODO Auto-generated constructor stub

}

int FileNameManager::addFileName(string name){
	for(int i = 0;i<mainList.size();i++){
		if(mainList[i] == name){
			return i;
		}
	}
	mainList.push_back(name);
	return mainList.size()-1;
}

int FileNameManager::getFileId(string name){
	for(int i = 0;i<mainList.size();i++){
		if(mainList[i] == name){
			return i;
		}
	}
	return -1;
}

string FileNameManager::getFileName(int id){
	if(mainList.size()>id)
		return mainList[id];
	else
		return NULL;
}

FileNameManager::~FileNameManager() {
	// TODO Auto-generated destructor stub
}
