/* Challenge Problem 2 - PartiallySorted ArrayList
* @authors: Mason Campbell & Rachel Schultz
* @version 3/7/23
* This is the Header class for PartiallySorted
* Included is PartiallySortedList class and PartiallySortedString class
*/

#pragma once 
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T>
class PartiallySortedList {
private:
	//Fields
	string* stringData;
	int size{ 0 }; //TODO maybe initialize
	int capacity{ 10 };

public:
	//Constructor
	PartiallySortedList() { //O(1)
		stringData = new string[capacity];
	}

	//Destructor
	~PartiallySortedList() { //O(1)
		delete[] stringData;
	}

	//Copy constructor
	PartiallySortedList(const PartiallySortedList<string>& other) { //O(N) ->for loop, rest goes away
		capacity = other.capacity;
		size = other.size;
		stringData = new string[capacity];
		//Go through
		for (int i = 0; i < size; i++) { //O(N)
			//Copy all the real items
			stringData[i] = other.stringData[i];
		}
	}

	//Copy assignment operator
	PartiallySortedList operator=(const PartiallySortedList<string>& other) { //O(N) ->for loop, rest goes away
		//Delete old stuff
		delete[] stringData;

		//Mimic the copy constructor
		capacity = other.capacity;
		size = other.size;
		stringData = new string[capacity];
		//Go through
		for (int i = 0; i < size; i++) {
			//Copy all the real items
			stringData[i] = other.stringData[i];
		}
	}
	void expand() { //O(N) -> for loop, rest goes away

		string* tmp = new string[capacity * 2];
		//Copy contents
		for (int i = 0; i < capacity; i++) { //O(N)
			tmp[i] = stringData[i];
		}
		//Delete the old data
		delete[] stringData;
		//Swap!
		stringData = tmp;
		tmp = nullptr;
		capacity *= 2;
	}

	/*
	* Either the value is going to be added before another string because
	* it has the same length or a larger length than value's length. Otherwise it should
	* be added at the end of the arraylist.
	*/
	char add(string value) { //O(N^2) -> two nested for loops O(N), expand method O(N) does not matter, rest goes away
		// Check if the capacity of the arraylist needs to be expanded
		if (size + 1 > capacity) { 
			this->expand(); //O(N)
		}

		// Check if size is equal to 0 and there is nothing to compare values length to
		if (size == 0) { 
			// insert value at the first slot in the arraylist since it is currently empty
			stringData[0] = value;
			// increment size since a new value was added
			size++;
			return 'a'; // return false because the loop isn't used
		}
		else {
			// Loop through stringData until a suitable spot is found
			for (int i = 0; i < size; i++) { //O(N)
				// Check if the value should be inserted at the given index or continue looping
				if (stringData[i].length() >= value.length()) { 
					// Loop to make room for the new value being inserted
					for (int j = size; j > i; j--) { //O(N)
						// Moves the current index back one slot in the array
						stringData[j] = stringData[j - 1];
					}
					// Enters in the new value at the available index
					stringData[i] = value;
					// Increment size since a new value was added
					size++;
					// use return to end the loop early since we only need to insert one value at a time
					return 'b'; // could be used to make the distinction of when only part of the loop was used
				}
			}

			/*
			* If the loop doesn't find a spot for value, then value must have a length
			* larger than the rest and should be put at the end.
			*/
			stringData[size] = value;
			// Increment size since a new value was added
			size++;
			return 'c'; // could be used to make a distinction of when the entire loop was used
		}
	}

	string get(int index) { //O(1)
		return stringData[index];
	}

	int getSize() { //O(1)
		return size;
	}

	int CountPermutations() {  //O(NlogN)
		int groupNum{ 0 };
		int numPerms{ 0 };
		vector<int> groupList;
		int current{ 0 };

		//Going through stringData
		for (int i = 0; i <= getSize(); i++) {  //O(N)
			// If the last index occurs add it to the group and stop.
			if (i == getSize()) {
				// Puts the number of people in a group into the vector
				groupList.push_back(groupNum);
			}
			else {
				//setting current to first index
				if (i == 0) {
					current = stringData[i].length();
					groupNum++;
				}
				else {
					//checks if current matchings the length, if so then it adds to the groupNum
					if (current == stringData[i].length()) {
						groupNum++;

						//once the lengths don't match it pushes the groupNum into a vector
					}
					else {
						// Puts the number of people in a group into the vector
						groupList.push_back(groupNum);
						//resets current for comparision
						current = stringData[i].length();
						//resets groupNum
						groupNum = 1;
					}
				}
			}

			
		}

		//If groupList is 0 returns 0
		if (groupList.size() == 0) {
			numPerms = 0;
			return numPerms;
		}
		//Calculates from groupList the number the of permutations 		
		//loops through groupList 
		for (int i = 0; i < groupList.size(); i++) { //O(N)
			if (i == 0) {
				numPerms = groupList.at(0);
			}
			int num = groupList.at(i);
			//calculates factorial of i
			numPerms *= factorial(num);
		}
		//Return number of permutations 
		return numPerms;
	}

	// calculates factorial using recursion
	int factorial(int val) { //O(logN)
		// base case - stopping point
		if (val == 1) {
			return val; // or return 1 it wouldn't matter since they are the same
		}
		// return the factorial times the current so it progressively gets smaller
		return val * factorial(val - 1);
	}
};

class PartiallySortedString {
private:
	// Fields
	string str;

public:
	// constructor
	PartiallySortedString(string str) { //O(1)
		this->str = str;
	}

	// getter
	string getStr() { //O(1)
		return str;
	}

	// setter
	void setStr(string str) { //O(1)
		this->str = str;
	}

	//== (two strings have exactly the same characters)
	bool operator==(const PartiallySortedString& other) { //O(N) -> for loop the rest doesn't matter
		if (str.length() == other.str.length()) {
			for (int i = 0; i < str.length(); i++) { // O(N)
				if (str[i] == other.str[i]) { 
					return true;
				}
			}
		}
		else {
			return false;
		}
	}

	//|= (incomparability)
	bool operator|=(const PartiallySortedString& other) { //0(1)
		if (str.length() == other.str.length()) { // 1 + (2 for body)
			return true;
			}
			else {
				return false;
			}
	}

	//>
	bool operator>(const PartiallySortedString& other) { //O(1)
		if (str.length() > other.str.length()) { // 1 + (2 for body)
			return true;
		}
		else {
			return false;
		}
	}

	//<
	bool operator<(const PartiallySortedString& other) { //O(1) 
		if (str.length() < other.str.length()) { //1 + (2 for body)
			return true;
		}
		else {
			return false;
		}
	}
};
;
