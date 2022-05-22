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

bool SortedIndexedList::isEmpty() const {
	return this->nodes[0].elem== -1;
}

TComp SortedIndexedList::getElement(int i) const{
	//TODO - Implementation get element
	return NULL_TCOMP;
}

TComp SortedIndexedList::remove(int i) {
	//TODO - Implementation remove
	return NULL_TCOMP;
}

int SortedIndexedList::search(TComp e) const {
    BSTNode node=this->nodes[0];
    int index = 0;
    while(node.elem!= -1){
        if(node.elem==e){
            return index;
        }
        if (relation(node.elem, e)){
            index = node.right;
            node = this->nodes[index];
        }
        else {
            index = node.left;
            node = this->nodes[index];
        }
    }
    return -1;
}

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

ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
}
