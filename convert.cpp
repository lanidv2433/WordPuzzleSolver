#include "convert.hpp"
#include "MyPriorityQueue.hpp"
#include <string>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <algorithm>
struct Word{
	size_t findDiff(const std::string & s1, const std::string &s2) const{
		size_t distance = 0;
		for (size_t i = 0; i < s1.size(); i++){
			if (s1[i] != s2[i]){
				distance++;
			}
		}
		return distance;
	}

	std::string word;
	size_t lcDistance = 0;
	size_t diffLetters = 0;
	size_t priority = 0;

	friend bool operator< (const Word& w1, const Word& w2){
		return w1.priority < w2.priority;
	}

	friend bool operator> (const Word& w1, const Word& w2){
		return w1.priority > w2.priority;
	}

	friend bool operator == (const Word& w1, const Word& w2){
		return w1.priority == w2.priority;
	}
};

void loadWordsIntoTable(std::unordered_set<std::string> & words, std::istream & in)
{
	std::string line, word;
	std::stringstream ss;

	while(	getline(in, line) )
	{
		ss.clear();
		ss << line;
		while( ss >> word )
		{
			words.insert( word );
		}
	}

}



std::vector< std::string > convert(const std::string & s1, const std::string & s2, const std::unordered_set<std::string> & words)
{
	size_t LCdistance = 0;

	if (s1 == s2 || (words.count(s1) < 1 && words.count(s2) < 1) || s1.size() != s2.size()){
		return {};
	}

	std::vector<std::string> ret;
	std::unordered_map <std::string, std::string> path;
	MyPriorityQueue<Word> pq;
	std::string currentV;
	std::string prevV;
	std::unordered_set <std::string> discoveredSet;

	Word start = Word();
	start.word = s1;
	start.lcDistance = 0;
	start.diffLetters = start.findDiff(s1,s2);
	start.priority = start.lcDistance + start.diffLetters;

	pq.insert(start);

	discoveredSet.insert(s1);

	while(!pq.isEmpty()){
		currentV = pq.min().word;
		pq.extractMin();
		prevV = currentV;

		if(currentV == s2){
			ret.push_back(currentV);
			while(currentV != s1){
				ret.push_back(path[currentV]);
				currentV = path[currentV];
			}

			std::reverse(ret.begin(), ret.end());
			return ret;
		}

		for(size_t i = 0; i < s1.size(); i++){
			for (char c = 'a'; c <= 'z' ; c++){
				currentV = prevV;
				currentV[i] = c;
				if (words.count(currentV) > 0 && discoveredSet.count(currentV)==0){
					LCdistance++;
					Word current = Word();
					current.word = currentV;
					current.lcDistance = LCdistance;
					current.diffLetters = current.findDiff(currentV, s2);
					current.priority = current.lcDistance + current.diffLetters;
					pq.insert(current);
					discoveredSet.insert(currentV);
					path[currentV] = prevV;
				}
			}
		}
	}

	return {};
}

