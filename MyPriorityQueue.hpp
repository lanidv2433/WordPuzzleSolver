#ifndef __PROJ5_PRIORITY_QUEUE_HPP
#define __PROJ5_PRIORITY_QUEUE_HPP

#include "runtimeexcept.hpp"
#include <vector>


class PriorityQueueEmptyException : public RuntimeException 
{
public:
	PriorityQueueEmptyException(const std::string & err) : RuntimeException(err) {}
};




template<typename Object>
class MyPriorityQueue
{
private:
	size_t sizeN;
	std::vector<Object> heap;

public:

	
	MyPriorityQueue();
	~MyPriorityQueue();

 	size_t size() const noexcept;
	bool isEmpty() const noexcept;

	void percolateUp(size_t index);
	void percolateDown(size_t index);

	void insert(const Object & elem);


	const Object & min() const; 

	void extractMin(); 

};


template<typename Object>
MyPriorityQueue<Object>::MyPriorityQueue()
{
	sizeN = 0;
	heap = {};

}


template<typename Object>
MyPriorityQueue<Object>::~MyPriorityQueue()
{
	
}

template<typename Object>
size_t MyPriorityQueue<Object>::size() const noexcept
{
	return sizeN;

}

template<typename Object>
bool MyPriorityQueue<Object>::isEmpty() const noexcept
{
	return sizeN == 0; 
}

template<typename Object>
void MyPriorityQueue<Object>::percolateUp(size_t index){
	while (index > 0){
		size_t parentIndex = (index-1) / 2;
		if (heap[index] < heap[parentIndex]){
			std::swap(heap[index], heap[parentIndex]);
			index = parentIndex;
		} else{
			return;
			
		}
	}
}
template<typename Object>
void MyPriorityQueue<Object>::insert(const Object & elem) 
{
	heap.push_back(elem);
	sizeN++;
	percolateUp(sizeN-1);
}




template<typename Object>
const Object & MyPriorityQueue<Object>::min() const
{
	
	if (sizeN == 0){
		throw PriorityQueueEmptyException("empty");
	}
	const Object &o = heap[0];
	return o;
}

template<typename Object>
void MyPriorityQueue<Object>::percolateDown(size_t index){
	size_t childIndex = 2 * index + 1;
	Object value = heap[index];
	Object maxValue;
	int maxIndex;
	while (childIndex < sizeN){
		maxValue = value;
		maxIndex = -1;
		for (size_t i = 0; i < 2 && i + childIndex < sizeN; i++){
			if (heap[i + childIndex] < maxValue){
				maxValue = heap[i + childIndex];
				maxIndex = i + childIndex;
			}
		}
		if (maxValue == value){
			return;
		} else{
			std::swap(heap[index], heap[maxIndex]);
			index = maxIndex;
			childIndex = 2 * index + 1;
		}
	}


	
}

template<typename Object>
void MyPriorityQueue<Object>::extractMin() 
{
	if (sizeN == 0){
		throw PriorityQueueEmptyException("empty");
	}
	
	heap.erase(heap.begin());
	sizeN--;

	if (sizeN > 0){
		percolateDown(0);
	}
 }


#endif 
