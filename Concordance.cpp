//Caleb Catt 5/14/2019
// This program creates an enhanced concordance by using a map of maps to get line numbers and occurrences for words
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
using namespace std;


int main()
{

	ifstream inFile("graveyardblues.txt");

	string oneLine;
	std::map<string, map<int, int> > concordance;

	// Read the words; add them to wordMap
	for (int lineNum = 1; getline(inFile, oneLine); lineNum++)
	{
		istringstream st(oneLine);
		string word;
		while (st >> word)
		{
			//To lower case
			std::transform(word.begin(), word.end(), word.begin(), ::tolower);
			// Remove Punctuation
			for (int i = 0, len = word.size(); i < len; i++)
			{
				if (ispunct(word[i]))
				{
					word.erase(i--, 1);
					len = word.size();
				}
			}
			if (concordance.find(word) == concordance.end()) // if word does not exist
				concordance[word] = map<int, int>();
			if (concordance[word].find(lineNum) == concordance[word].end()) // if lineNum does not exist
				concordance[word][lineNum] = 1;
			else // lineNum exists, enter map and increment occurrence
				concordance[word][lineNum]++;
		}
	}


		for (auto outItr = concordance.begin(); outItr != concordance.end(); outItr++)
		{
			cout << setw(5) << outItr->first;
			cout <<  "[" <<
				std::accumulate(outItr->second.begin(), outItr->second.end(), 0, [](int value, const std::map<int, int>::value_type & p)
					{ return value + p.second; }) << "]" << "\t";

			for (auto innerItr = outItr->second.begin(); innerItr != outItr->second.end(); innerItr++)
			{
				

				cout << innerItr->second << "\t" << "(" << innerItr->first << ")" << "\t";
			}
			cout << endl;
		}
		return 0;
	}

