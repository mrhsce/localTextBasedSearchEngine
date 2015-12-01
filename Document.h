/*
 * Document.h
 *
 *  Created on: Oct 7, 2015
 *      Author: mrhs
 */

#ifndef DOCUMENT_H_
#define DOCUMENT_H_
#include <string>
class Document {

public:
	Document(std::string text,int id){mText = text;mId = id;}
	~Document(){};

	std::string getText(){return mText;};
	int getId(){return mId;};

private:
	std::string mText;
	int mId;
};

#endif /* DOCUMENT_H_ */
