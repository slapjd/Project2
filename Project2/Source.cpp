#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <fstream>
#include <ShlObj.h>
//Required include statements

using namespace std;
//Avoids me typing "std::" before everything

int main() {
	string sFileName, sSentence;
	vector<string> vsSentence, vsDictionary;
	vector<int> viPositions;
	//Global variable declarations which are named after their function

	{
		char cFileNameBuffer[MAX_PATH];
		SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, cFileNameBuffer);
		string sTempString(cFileNameBuffer);
		sTempString.append("\\A453.txt");
		sFileName = sTempString;
	}
	//Block of code which uses shell functions to get the documents directory

	cout << "Please enter a sentence without punctuation" << endl;
	getline(cin, sSentence);
	{
		stringstream issSentence(sSentence);
		string sTempString;
		while (issSentence >> sTempString) {
			vsSentence.push_back(sTempString);
		}
	}
	//Input block which automatically splits the sentence to words

	for each (auto aSentenceWord in vsSentence) {
		bool bFoundWord = false;
		for each (auto aDictionaryWord in vsDictionary) {
			if (aSentenceWord == aDictionaryWord) {
				bFoundWord = true;
				break;
			}
		}
		if (!bFoundWord) {
			vsDictionary.push_back(aSentenceWord);
		}
	}
	//Dictionary creation block which loops through the sentence looking for new words to add

	for each (auto aSentenceWord in vsSentence) {
		for (int iCounter = 0; iCounter < vsDictionary.size(); iCounter++) {
			if (aSentenceWord == vsDictionary[iCounter]) {
				viPositions.push_back(iCounter);
				break;
			}
		}
	}
	//Sentence indexer which finds the dictionary position of all words in the sentence

	ofstream ofFile(sFileName, ofstream::out);
	for each (auto aDictionaryWord in vsDictionary) {
		ofFile << aDictionaryWord << " ";
	}
	ofFile << endl;
	for each (auto aIndexPosition in viPositions) {
		ofFile << aIndexPosition << " ";
	}
	ofFile.close();
	//Block of code to create a file stream to write the output to

	cout << endl;
	system("pause");
	//Windows pause command to allow user to exit properly

	return 0;
}