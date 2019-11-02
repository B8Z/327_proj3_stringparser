/*
 * StringParserClass.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */

#include <string>
#include <string.h>
#include <vector>
#include "../327_proj3_test/includes/StringParserClass.h"
#include "../327_proj3_test/includes/constants.h"

using namespace std;
using namespace KP_StringParserClass;

//dont forget to initialize member variables
StringParserClass::StringParserClass(void) {
	pStartTag = NULL;
	pEndTag = NULL;
	areTagsSet = false;
}

//call cleanup to release any allocated memory
StringParserClass::~StringParserClass(void) {
	cleanup();
}

//these are the start tag and the end tags that we want to find,
//presumably the data of interest is between them, please make a
//COPY of what pStartTag and pEndTag point to.  In other words
//DO NOT SET pStartTag = pStart
//returns:
//SUCCESS
//ERROR_TAGS_NULL if either pStart or pEnd is null
int StringParserClass::setTags(const char *pStart, const char *pEnd) {
	//if pStart or pEnd is null return tags_null constant
	if (pStart == NULL || pEnd == NULL) {
		return ERROR_TAGS_NULL;
	}
	//else make deepcopy of pStartTag and pEndTag
	else {
		//tags are set
		areTagsSet = true;

		//get length of pStart and pEnd
		int length_of_pStart = strlen(pStart);
		int length_of_pEnd = strlen(pEnd);

		//create new charArray with proper length
		pStartTag = new char[1 + length_of_pStart];
		pEndTag = new char[1 + length_of_pEnd];

		//create deepcopy of pStartTag and pEndTag
		strncpy(pStartTag, pStart, length_of_pStart);
		strncpy(pEndTag, pEnd, length_of_pEnd);

		//return success constant
		return SUCCESS;
	}
}

//First clears myVector
//going to search thru pDataToSearchThru, looking for info bracketed by
//pStartTag and pEndTag, will add that info only to myVector
//returns
//SUCCESS  finished searching for data between tags, results in myVector (0 or more entries)
//ERROR_TAGS_NULL if either pStart or pEnd is null
//ERROR_DATA_NULL pDataToSearchThru is null
int StringParserClass::getDataBetweenTags(char *pDataToSearchThru,
		std::vector<std::string> &myVector) {

	if (!areTagsSet) {
		return ERROR_TAGS_NULL;
	}
	if (pDataToSearchThru == NULL) {
		return ERROR_DATA_NULL;
	}

	myVector.clear();

	string data = pDataToSearchThru;

	//FIXME

	return SUCCESS;

}

void StringParserClass::cleanup() {
	//delete pStartTag
	if (pStartTag) {
		delete[] pStartTag;
	}
	//delete pEndTag
	if (pEndTag) {
		delete[] pEndTag;
	}
}

//Searches a string starting at pStart for pTagToLookFor
//returns:
//SUCCESS  found pTagToLookFor, pStart points to beginning of tag and pEnd points to end of tag
//FAIL did not find pTagToLookFor and pEnd points to 0
//ERROR_TAGS_NULL if either pStart or pEnd is null
int StringParserClass::findTag(char *pTagToLookFor, char *&pStart,
		char *&pEnd) {
	//if tags aren't set return tags_null constant
	if (!areTagsSet) {
		return ERROR_TAGS_NULL;
	}
	//else return success constant
	return SUCCESS;
}

