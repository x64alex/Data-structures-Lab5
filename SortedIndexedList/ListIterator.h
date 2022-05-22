#pragma once
#include "SortedIndexedList.h"
#include <stack>

//DO NOT CHANGE THIS PART
class ListIterator{
	friend class SortedIndexedList;
private:
    BSTNode current;
    std::stack<BSTNode> stack;
	const SortedIndexedList& list;
	ListIterator(const SortedIndexedList& list);
public:
	void first();
	void next();
	bool valid();
    TComp getCurrent();
};


