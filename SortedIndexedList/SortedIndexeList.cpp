#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIndexedList::SortedIndexedList(Relation r) {
	this->nodes[0].elem = -1;
    this->nodes[0].left = 1;
    this->nodes[0].right = 2;
    this->nodes[0].leftchildren = 0;
    this->nodes[1].elem = -1;
    this->nodes[2].elem = -1;
    this->relation = r;
}
/*
* Best Case: Theta(1)
* Worst Case: Theta(log n)
* Average Case: Theta(log(n))
* Total case: O(log(n))
*/
int SortedIndexedList::size() const {
    if(this->isEmpty()) return 0;
    BSTNode node = this->nodes[0];
    int size =0;
    while(node.elem !=-1){
        size+= node.leftchildren+1;
        node = this->nodes[node.right];
    }

    return size;
}
/*
* Best Case: Theta(1)
* Worst Case: Theta(1)
* Average Case: Theta(1)
* Total case: Theta(1)
*/
bool SortedIndexedList::isEmpty() const {
	return this->nodes[0].elem== -1;
}

/*
* Best Case: Theta(1)
* Worst Case: Theta(1)
* Average Case: Theta(1)
* Total case: Theta(1)
*/
TComp SortedIndexedList::getElement(int i) {
    if(i<0 || i>this->size()-1)
        throw std::runtime_error("Invalid position");
    ListIterator it{*this};
    it.first();
    int in=0;
    while(it.valid() && in !=i){
        in++;
        it.next();
    }
    if(!it.valid()) return -1;
    return it.getCurrent();
}

/*
* Best Case: Theta(1)
* Worst Case: Theta(1)
* Average Case: Theta(1)
* Total case: Theta(1)
*/
TComp SortedIndexedList::remove(int i) {
    if(i<0 || i>this->size()-1)
        throw std::runtime_error("Invalid position");
    TComp n= this->getElement(i);


    BSTNode* node = &this->nodes[0];
    while(node->elem!=n){
        if (relation(node->elem, n)){
            node = &this->nodes[node->right];
        }
        else {
            node = &this->nodes[node->left];
        }
    }
    //Now the variable node is the node we want to delete
    std::stack<BSTNode> stack;
    calStack(node->right,stack);

    while(!stack.empty()){
        this->add(stack.top().elem);
        stack.pop();
    }

    return n;

}
/*
* Best Case: Theta(1)
* Worst Case: Theta(1)
* Average Case: Theta(1)
* Total case: Theta(1)
*/
int SortedIndexedList::search(TComp e) const {
    ListIterator it{*this};
    it.first();
    int i=0;
    while(it.valid() && it.getCurrent()!=e){
        i++;
        it.next();
    }
    if(!it.valid()) return -1;
    return i;
}
/*
* Best Case: Theta(1)
* Worst Case: Theta(n)
* Average Case: Theta(n)
* Total case: O(n)
*/
void SortedIndexedList::add(TComp e) {
    if(this->isEmpty())
    {
        this->nodes[0].elem = e;
    }
    else{
        BSTNode* node = &this->nodes[0];
        int index=0;
        while(node->elem!=-1){
            if (relation(node->elem, e)){
                index = node->right;
                node = &this->nodes[index];
            }
            else {
                node->leftchildren++;
                index = node->left;
                node = &this->nodes[index];
            }
        }
        node->elem = e;
        node->leftchildren =0;
        node->left = index*2+1;
        node->right = index*2+2;
        this->nodes[node->left].elem = -1;
        this->nodes[node->right].elem = -1;
    }
}
/*
* Best Case: Theta(1)
* Worst Case: Theta(1)
* Average Case: Theta(1)
* Total case: Theta(1)
*/
ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}

/*
* Best Case: Theta(1)
* Worst Case: Theta(1)
* Average Case: Theta(1)
* Total case: Theta(1)
*/
SortedIndexedList::~SortedIndexedList() {
}

/*
* Best Case: Theta(n)
* Worst Case: Theta(n)
* Average Case: Theta(n)
* Total case: Theta(n)
*/
void SortedIndexedList::calStack(BSTNode node,std::stack<BSTNode> stack) {
    if(this->nodes[node.left].elem ==-1 && this->nodes[node.right].elem ==-1){
        stack.push(node);
        node.elem = -1;
    }
    else if(this->nodes[node.left].elem ==-1 && this->nodes[node.right].elem !=-1){
        calStack(this->nodes[node.right],stack);
    }
    else if(this->nodes[node.left].elem !=-1 && this->nodes[node.right].elem ==-1){
        calStack(this->nodes[node.left],stack);
    } else{
        calStack(this->nodes[node.right],stack);
        calStack(this->nodes[node.left],stack);
    }
}
