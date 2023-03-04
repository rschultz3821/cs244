#pragma once
#include <iostream>
#include<string>
#include<vector>
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
	PartiallySortedList() {
		stringData = new string[capacity];
	}

	//Destructor
	~PartiallySortedList() {
		delete[] stringData;
	}

	//Copy constructor
	PartiallySortedList(const PartiallySortedList<string>& other) {
		capacity = other.capacity;
		size = other.size;
		stringData = new string[capacity];
		//Go through
		for (int i = 0; i < size; i++) {
			//Copy all the real items
			stringData[i] = other.stringData[i];
		}
	}

	//Copy assignment operator
	PartiallySortedList operator=(const PartiallySortedList<string>& other) {
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
	void expand() {

		string* tmp = new string[capacity * 2];
		//Copy contents
		for (int i = 0; i < capacity; i++) {
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
	char add(string value) {
		// Check if the capacity of the arraylist needs to be expanded
		if (size + 1 > capacity) {
			this->expand();
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
			for (int i = 0; i < size; i++) {
				// Check if the value should be inserted at the given index or continue looping
				if (stringData[i].length >= value.length) {
					// Loop to make room for the new value being inserted
					for (int j = size; j > i; j--) {
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

	string get(int index) {
		return stringData[index];
	}

	int getSize() {
		return size;
	}

	int CountPermutations() {
		int groupNum{ 0 };
		int numPerms{ 0 };
		vector<int> groupList;
		string* current;

		//Going through stringData
		for (int i = 0; i < size; i++) {

			//setting current to first index
			if (i == 0) {
				current = stringData[i].length;
			}
			else {
				//checks if current matchings the length, if so then it adds to the groupNum
				if (current == stringData[i].length) {
					groupNum++;

					//once the lengths don't match it pushes the groupNum into a vector
				}
				else {
					groupList.push_back(groupNum);

					//resets current for comparision
					current = stringData[i].length;
					//resets groupNum
					groupNum = 1;
				}
			}
		}

		//If groupList is 0 returns 0
		if (groupList.size == 0) {
			numPerms = 0;
			return numPerms;
		}
		//Calculates from groupList the number the of permutations 		
		//loops through groupList 
		for (int i = 0; i < groupList.size(); i++) {
			int num = groupList.at(i);
			//calculates factorial of i
			for (int j = num; j > 1; --j) {
				num *= j;
			}
			//Initializes numPerms starting value
			if (i == 0) {
				numPerms = num;
			}
			//multiples the num each time
			numPerms *= num;
		}
		//Return number of permutations 
		return numPerms;
	}
};

class PartiallySortedString {
private:
	// Fields
	string str;

private:
	// constructor
	PartiallySortedString(string str) {
		this->str = str;
	}

	// getter
	string getStr() {
		return str;
	}

	// setter
	void setStr(string str) {
		this->str = str;
	}

	//== (two strings have exactly the same characters)
	bool operator==(const PartiallySortedString& other) {
		if (str.length() == other.str.length()) {
			for (int i = 0; i < str.length(); i++) {
				if (str[i] == other.str[i]) {
					return true;
				}
			}
			return false;
		}
	}

	//|= (incomparability)
	bool operator|=(const PartiallySortedString& other) {
		if (str.length() == other.str.length()) {
			return true;
		}
		return false;
	}

	//>
	bool operator>(const PartiallySortedString& other) {
		if (str.length() > other.str.length()) {
			return true;
		}
		return false;
	}

	//<
	bool operator<(const PartiallySortedString& other) {
		if (str.length() < other.str.length()) {
			return true;
		}
		return false;
	}
};
