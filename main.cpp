
#include <vector>
#include <gtest/gtest.h>
#include <fstream>
#include "convert.cpp"
#include "../include/ver.hpp"
#include "MyPriorityQueue.hpp"

struct Word1{
	

	std::string word;
	size_t lcDistance = 0;
	size_t diffLetters = 0;
	size_t priority = 0;

	friend bool operator< (const Word1& w1, const Word1& w2){
		return w1.priority < w2.priority;
	}

	friend bool operator> (const Word1& w1, const Word1& w2){
		return w1.priority > w2.priority;
	}

	friend bool operator == (const Word1& w1, const Word1& w2){
		return w1.priority == w2.priority;
	}
};

int main()
{

	std::string WORD_ONE = "ant";
	std::string WORD_TWO = "eat";

	Word1 t1 = Word1();
	Word1 t2 = Word1();
	Word1 t3 = Word1();
	Word1 t4 = Word1();


	t1.word = "hello";
	t1.priority = 1;
	t2.word = "bye";
	t2.priority = 1;
	t3.word = "last";
	t3.priority = 3;
	t4.word = "yum";
	t4.priority = 1;

	MyPriorityQueue<Word1> test;

	test.insert(t1);
	test.insert(t2);
	test.insert(t3);
	test.insert(t4);

	test.extractMin();
	test.extractMin();
	
	std::cout << test.min().word;



	std::unordered_set<std::string> words;
	words.insert("ant");
	words.insert("bat");
	words.insert("cat");
	words.insert("aft");
	words.insert("act");
	words.insert("oft");
	words.insert("oat");
	words.insert("eat");

	
	
	return 0;
}

