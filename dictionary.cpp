// Implementation of ADT Dictionary
//     data object: a bunch of texting abbreviations and their meanings 
//     operations: create, destroy
//                 search the dictionary for an item given its text
//                 insert a new item into the dictionary
//                 remove an item from the dictionary given its text
//   associated operations: input and output
// filename dictionary.cpp
//date September 25, 2018

#include "dictionary.h"
#include <iostream>


const int TABLESIZE = 11;

// displays a dictionary
// pre: output has been opened if it is a file
//      rightHandSideDictionary has been assigned items
// post: output contains each item on a separate line in the format with headings.
//       for example
//       address    text       meaning
//          0        lol       laugh out loud
//          1        ttyl      talk to you later
// usage: outfile << myDictionary;
ostream& operator<< (ostream& output, const Dictionary& rightHandSideDictionary)
{
	Item anItem;
	cout << "Address	Text	Meaning" <<endl;
	for (int i = 0 ; i < TABLESIZE; i++)
	{
		anItem = rightHandSideDictionary.dictionaryPtr->hashTablePtr[i];
		output << i << "	" << anItem << endl;
	}
	return output;
}

// inputs items into a dictionary
// pre: input has been opened if it is a file
//      items are arranged in the following format
//      2
//      lol
//      laugh out loud
//      ttyl
//      talk to you later
// post: if there is room, 
//       all items in the input have been stored in rightHandSideDictionary
// usage: infile >> myDictionary;
istream& operator>> (istream& input, Dictionary& rightHandSideDictionary)
{
	bool isFull = false;
	bool isAlreadyThere = false;
	int numberOfItems = 0;
	input >> numberOfItems;
	for (int i = 0 ; ((i < numberOfItems) && (!isFull)); i++)
	{
		Item anItem;
		input >> anItem;
		if (!(anItem.isEmpty()))
		{
			isAlreadyThere = false;
			rightHandSideDictionary.addNewEntry(anItem, isFull, isAlreadyThere);
		}
	}
	return input;
}

// creates a new dictionary
// post: Dictionary object exists but is empty
// usage: Dictionary myDictionary;	
Dictionary::Dictionary(){
	dictionaryPtr = new DictionaryRecord;
	dictionaryPtr->numberOfItems = 0; 
	dictionaryPtr->hashTablePtr = new Item[TABLESIZE];
}

// destroys a dictionary
// pre: Dictionary object exists
// post: all memory for Dictionary object has been freed
// usage: automatically done at the end of scope
Dictionary::~Dictionary()
{
}

// searchs for a meaning with a given text
// pre targetText has been assigned 
// post if an item with texting abbreviation the same as targetText is found then
//          isFound is true and theItem is that item
//       else isFound is false
// usage  myDictionary.searchForMeaning(targetText, anItem, isFound);
void Dictionary::searchForMeaning(const Key& targetText, Item& anItem, bool& isFound)
{
	int address;
	int hashIndex;
	int indexStop;
	bool isMarked = false;
	isFound = false;
	address = hashFunction(targetText);
	hashIndex = address;
	while (!(dictionaryPtr->hashTablePtr[hashIndex] == targetText))
	{
		hashIndex = (hashIndex + 1) % TABLESIZE;
	}
	if (dictionaryPtr->hashTablePtr[hashIndex] == targetText)
	{
		isFound = true;
		anItem = dictionaryPtr->hashTablePtr[hashIndex];
	}
}

// inserts a new text' item into the dictionary
// pre: newItem has been assigned
// post: if there is room in the Dictionary object and newItem's text
//            is not already there  isFull is false and isAlreadyThere is false
//            and newItem is appropriately added
//       else either isFull is true or isAlreadyThere is true, depending
// usage: myDictionary.addNewEntry(myItem, isFull, isAlreadyThere);
void Dictionary::addNewEntry(const Item& newItem, bool& isFull, bool& isAlreadyThere)
{
	int address;
	int hashIndex;
	bool isMarked = false;
	isFull = (dictionaryPtr->numberOfItems == TABLESIZE);
	if (!isFull)
	{
		address = hashFunction(newItem);
		hashIndex = address;
		//cout << newItem << "'s hash address is: " << address << endl;
		isAlreadyThere = (dictionaryPtr->hashTablePtr[hashIndex] == newItem);
		while (!(dictionaryPtr->hashTablePtr[hashIndex].isEmpty()) && !(isMarked) && !(isAlreadyThere))
		{
			isAlreadyThere = (dictionaryPtr->hashTablePtr[hashIndex] == newItem);
			isMarked = dictionaryPtr->hashTablePtr[hashIndex].hasBeenMarked();
			hashIndex = (hashIndex + 1) % TABLESIZE;
			//cout << "	changing address to: " << hashIndex << endl;
		}
		if(!isAlreadyThere)
		{
			dictionaryPtr->hashTablePtr[hashIndex] = newItem;
			dictionaryPtr->numberOfItems = dictionaryPtr->numberOfItems + 1;
			//cout <<"	new address: " << hashIndex << endl;
		}
	}
}

// removes the item associated with a given text from the dictionary
// pre: targetText is assigned
// post: if Dictionary object is not empty and 
//           targetText is found in Dictionary object, isFound is true
//           and the associated Item object (text and meaning) has been 
//           removed from the Dictionary object 
//       else isFound is false or isEmpty is true depending
// usage: myDictionary.deleteEntry(myText, isEmpty, isFound);
void Dictionary::deleteEntry(const Key& targetText, bool& isEmpty, bool& isFound)
{
	isFound = false;
	isEmpty = false;
	int address;
	int hashIndex;
	int stopHashIndex;
	address = hashFunction(targetText);
	hashIndex = address;
	stopHashIndex = (address - 1) % TABLESIZE;
	if (!dictionaryPtr)
	{
		isEmpty = true;
		cout << "Dictionary is empty" << endl;
		return;
	}
	while (!(dictionaryPtr->hashTablePtr[hashIndex] == targetText) && (hashIndex != stopHashIndex))
	{
		hashIndex = (hashIndex+1) % TABLESIZE;
	}
	if (dictionaryPtr->hashTablePtr[hashIndex] == targetText)
	{
		isFound = true;
		dictionaryPtr->hashTablePtr[hashIndex].markIt();
		dictionaryPtr->numberOfItems -= 1;
	}
}

//Hashes a key value
//
//pre	key value exists in an item object
//post	returns the key's integer value modulo(%) TABLESIZE to hash to an address
//usage	hashAddress = hashFunction(aKey);
int Dictionary::hashFunction(const Key& theKey)
{
	return (theKey.convertToInteger() % TABLESIZE);
}
