/*
 * FileNameManager.h
 *
 *  Created on: Nov 7, 2015
 *      Author: mrhs
 */

#ifndef FILENAMEMANAGER_H_
#define FILENAMEMANAGER_H_
#include <vector>
#include <string>

using namespace std;

class FileNameManager {
public:
	FileNameManager();
	virtual ~FileNameManager();
	int addFileName(string name);
	int getFileId(string name);
	string getFileName(int id);

	int getFileCount(){return mainList.size();}
private:
	vector<string> mainList;


};


#endif /* FILENAMEMANAGER_H_ */
