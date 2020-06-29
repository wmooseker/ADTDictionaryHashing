//Client test program for ADT Dictionary
//     data object: a bunch of texting abbreviations and their meanings 
//    
// filename client.cpp
//date September 25, 2018


#include "dictionary.h"

#include <iostream>
#include <fstream>
using namespace std;

//opens the input file for the client test items and keys
//
//pre	inputFile exists but is not opened
//post	inputFile opened
//usage	closeTheFile(inFile);
void openTheFile(ifstream& inFile)
{
	inFile.open("in.dat");
}
	
//closes the input file for the client test items and keys
//
//pre	inputFile exists and is open
//post	inputFile closed
//usage closeTheFile(inFile);
void closeTheFile(ifstream& inFile)
{
	inFile.close();
}

//inputs 4 items into the dictionary hash table, then displays the dictionary
//
//pre	inFile is open and has 4 items to be read from the first section for entry
//post	4 items read from the inFile and hashed to unique addresses, then output the dictionary
//usage	taskA(inFile, theDictionary);
void taskA(ifstream& inFile ,Dictionary& theDictionary)
{
	cout << "---------------------------------------------------------------------" << endl;
	cout << "	TASK A: input 4 Items to a unique hash address" << endl;
	cout << "---------------------------------------------------------------------" << endl;
	inFile >> theDictionary;//read first 4 Items from file
	cout << theDictionary << endl; // print Dictionary
}

//reads three fake texting abbreviations and their meanings to ONE address entered to in taskA
//
//pre	3 more items ready to be input from inFile that hash to the same address
//post	the 3 items are read to different addresses(address+1), proving linear probing
//usage	taskB(inFile, theDictionary);
void taskB(ifstream& inFile ,Dictionary& theDictionary)
{
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "	TASK B: Read 3 fake Items to ONE address(ttyl) to prove \n		linear probing works correctly" << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	inFile >> theDictionary; //read next 3 fake text items
	cout << theDictionary << endl; // print dictionary to show successful linear probing
}

//reads two keys from a file, searches for them in the dictionary (one that takes one look,
//		one that uses linear probing, then displays the Items found
//pre	two keys exist in the inFile to be searched
//post	two keys read into key objects, key objects searched in dictionary
//			by calling .searchForMeaning() and printed the Items found in the searches
//usage	taskC(inFile, theDictionary);
void taskC(ifstream& inFile ,Dictionary& theDictionary)
{
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "	TASK C: Searching for two keys(in one look & w/linear probing)" << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	bool isFound = false;
	Key searchKeyOne, searchKeyTwo;
	cout << "Searching for the key 'rofl' and made up key 'tlyt'..." << endl;
	inFile >> searchKeyOne >> searchKeyTwo;
	Item searchedResultItemOne, searchedResultItemTwo;
	theDictionary.searchForMeaning(searchKeyOne, searchedResultItemOne, isFound);
	cout <<"	Item found by first search: " << searchedResultItemOne << endl;
	theDictionary.searchForMeaning(searchKeyTwo, searchedResultItemTwo, isFound);
	cout <<"	Item found by second search: " << searchedResultItemTwo << endl;
}

//deletes(marks) middle key from task B to put a gap in the hash table for linear probing
//
//pre	key exists in inFile and is the same as second item read in taskB
//post	key read from inFile and after search, replaced/marked with a '$' character
//		to mark as deleted. the dictionary is printed
//usage	taskD(inFile, theDictionary);
void taskD(ifstream& inFile, Dictionary& theDictionary)
{
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "	TASK D: Deleting key to show marker '$' and gap in lin. probing" << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	bool isEmpty;
	bool isFound;
	Key keyToBeDeleted;
	inFile >> keyToBeDeleted;
	theDictionary.deleteEntry(keyToBeDeleted, isEmpty, isFound);
	cout << theDictionary << endl;	
}	

//searches for the last key read in task B to show that linear probing moves past delete marker '$'
//		after an item has been deleted
//pre	key exists and can be read from inFile, same key as last read in task B
//post	key in inFile read into key object, then searched for past '$' sign to prove linear
//		probing treats marked as empty locations as if they were empty
void taskE(ifstream& inFile, Dictionary& theDictionary)
{	
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "	TASK E: Searching for last key of taskB to show linear \n 		probing moves across delete marker ('$')" << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	bool isFound;
	Key searchKeyThree;
	inFile >> searchKeyThree;
	Item searchedResultItemThree;
	cout << "Searching for made up key 'tlyt' to prove moving past delete marker '$'..." << endl;
	theDictionary.searchForMeaning(searchKeyThree, searchedResultItemThree, isFound);
	cout << "	Item found by third search: " << searchedResultItemThree << endl;
	cout << "-----------------------------------------------------------------------------" << endl;		
}

//main function for running the testing client
int main() 
{
	ifstream inFile;
	Dictionary theDictionary;
	openTheFile(inFile);
	taskA(inFile, theDictionary);
	taskB(inFile, theDictionary);
	taskC(inFile, theDictionary);
	taskD(inFile, theDictionary);
	taskE(inFile, theDictionary);
	closeTheFile(inFile);
	return 0;
}
	