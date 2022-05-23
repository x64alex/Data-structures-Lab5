#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList &l):list(l) {
    BSTNode node=list.nodes[0];
    while (node.elem!= -1){
        this->stack.push(node);
        node=this->list.nodes[node.left];
    }
    if(!stack.empty())current = stack.top();
    else current.elem = -1;

    node.elem = 7;
}

/*
* Best Case: Theta(1)
* Worst Case: Theta(1)
* Average Case: Theta(1)
* Total case: Theta(1)
*/
void ListIterator::first() {
    while(!stack.empty())stack.pop();
    BSTNode node=list.nodes[0];
    while (node.elem!= -1){
        stack.push(node);
        node=this->list.nodes[node.left];
    }
    if(!stack.empty())current=stack.top();
    else current.elem = -1;
}

/*
* Best Case: Theta(1)
* Worst Case: Theta(1)
* Average Case: Theta(1)
* Total case: Theta(1)
*/
TComp ListIterator::getCurrent() {
    if(!valid())throw std::runtime_error("iterator not valid");
    return current.elem;
}

/*
* Best Case: Theta(1)
* Worst Case: Theta(1)
* Average Case: Theta(1)
* Total case: Theta(1)
*/
bool ListIterator::valid() {
    if(current.elem== -1)return false;
    return true;
}

/*
* Best Case: Theta(1)
* Worst Case: Theta(1)
* Average Case: Theta(1)
* Total case: Theta(1)
*/
void ListIterator::next() {
    if (!valid())
        throw std::invalid_argument("not valid");

    BSTNode node = this->stack.top();
    stack.pop();

    if (node.right != -1)
    {
        node = this->list.nodes[node.right];
        while (node.elem != -1)
        {
            stack.push(node);
            node = this->list.nodes[node.left];
        }
    }

    if (!stack.empty())
        current = stack.top();
    else
        current.elem = -1;
}


