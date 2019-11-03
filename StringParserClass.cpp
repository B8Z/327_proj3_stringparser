/*
 * StringParserClass.cpp
 *
 *  Created on: Nov 2, 2019
 *      Author: Adam Bates
 */

#include <string>
#include <string.h>
#include <vector>
#include <iostream>
#include "../327_proj3_test/includes/StringParserClass.h"
#include "../327_proj3_test/includes/constants.h"

using namespace std;
using namespace KP_StringParserClass;

//dont forget to initialize member variables
StringParserClass::StringParserClass(void) {
	//set tags to null and make boolean areTagsSet false
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
		areTagsSet = false;
	}
	//else make deepcopy of pStartTag and pEndTag
	else {
		//tags are set
		areTagsSet = true;

		//get length of pStart and pEnd
		int length_of_pStart = strlen(pStart);
		int length_of_pEnd = strlen(pEnd);

		//create new charArray with proper length
		pStartTag = new char[length_of_pStart];
		pEndTag = new char[length_of_pEnd];

		//create deepcopy of pStartTag and pEndTag
		strcpy(pStartTag, pStart);
		strcpy(pEndTag, pEnd);

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
	//if tags not set return tags_null constant
	if (!areTagsSet || pStartTag == NULL || pEndTag == NULL) {
		return ERROR_TAGS_NULL;
	}
	//if null data return data_null constant
	if (pDataToSearchThru == NULL) {
		return ERROR_DATA_NULL;
	}
	//clear vector
	myVector.clear();

	//declare int that holds size of pDataToSearchThru
	int data_length = strlen(pDataToSearchThru);
	//declare boolean that checks if looking for end
	bool end_of_tag = false;
	//declare string to hold values inbetween tags
	string string_to_append = "";
	//declare int to hold value returned from findTag method
	int find_tag;

	//loop through pDataToSearchThru
	for (int i = 0; i < data_length; i++) {

		//if end of tag add char to string
		if (end_of_tag) {
			string_to_append += pDataToSearchThru[i - 1];
		}

		//if pDataToSearchThru of current char is open bracket
		if (pDataToSearchThru[i] == '<') {
			//declare holder to pass to findTag method
			char *holder = &pDataToSearchThru[i];

			//if looking for pStartTag
			if (!end_of_tag) {
				find_tag = findTag(pStartTag, holder, holder);

				//if successful, add the length of pStartTag to index and begin looking for end
				if (find_tag == SUCCESS) {
					i += strlen(pStartTag);
					end_of_tag = true;
				}
				//if looking for pEndTag
			} else {
				find_tag = findTag(pEndTag, holder, holder);

				//if successful, push string to vector and update boolean
				if (find_tag == SUCCESS) {
					myVector.push_back(string_to_append);
					string_to_append = "";
					end_of_tag = false;
				}
			}
		}
	}

	//return success constant
	return SUCCESS;
}

void StringParserClass::cleanup() {
	//delete pStartTag
	if (pStartTag) {
		delete[] pStartTag;
		pStartTag = NULL;
	}
	//delete pEndTag
	if (pEndTag) {
		delete[] pEndTag;
		pEndTag = NULL;
	}
	//tags aren't set anymore so equals false
	areTagsSet = false;
}

//Searches a string starting at pStart for pTagToLookFor
//returns:
//SUCCESS  found pTagToLookFor, pStart points to beginning of tag and pEnd points to end of tag
//FAIL did not find pTagToLookFor and pEnd points to 0
//ERROR_TAGS_NULL if either pStart or pEnd is null
int StringParserClass::findTag(char *pTagToLookFor, char *&pStart,
		char *&pEnd) {
	//if tags null return tags_null constant
	if (!areTagsSet || pStartTag == NULL || pEndTag == NULL) {
		return ERROR_TAGS_NULL;
	}

	//declare int to hold pTagToLookFor size
	int tag_length = strlen(pTagToLookFor);

	//loop through pTagToLookFor
	for (int i = 0; i < tag_length; i++) {
		//if current char isn't equal to same char in startTag return FAIL constant
		if (pStart[i] != pTagToLookFor[i]) {
			return FAIL;
		}
	}
	//return success constant, tag found
	if (pEnd != 0) {
		return SUCCESS;
	}

	//return FAIL if pEnd is equal to 0
	return FAIL;
}
