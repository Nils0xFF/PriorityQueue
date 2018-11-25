#include <iostream>
#include "PriorityQueue.h"

using namespace std;

PriorityQueue::~PriorityQueue() {
	// free the allocated memory
	delete[] queue;
	delete[] ref;
}

PQElement& PriorityQueue::getMin(void) const {
	// return a reference to the smallest element
	return this->queue[1];
}

PQElement PriorityQueue::extractMin(void) {
	// if there is no element return NULL
	if (this->amount == 0) return NULL;
	// if there is only 1 element delete it by setting the amount to 0 and return a copy
	if (this->amount == 1) {
		amount = 0;
		return this->queue[1];
	}
	// swap the smallest element with the last
	PQElement& min = this->queue[1];
	swap(this->queue[1], this->queue[this->amount]);
	// "delete" it by decreasing the amount
	amount--;
	// restore the heap
	this->heapDown(1);
	// return a copy
	return min;
}

void PriorityQueue::insert(const PQElement& e) {
	// if there is still room for more elements
	if (this->amount < this->size) {
		// place it at the ende
		this->queue[++amount] = e;
		// increase the size of the refArray if needed
		if (e.getId() >= refLength) {
			int newLength = refLength + 100;
			int* newArr = new int[newLength];
			for (int i = 0; i < refLength; i++) {
				newArr[i] = ref[i];
			}
			delete[] ref;
			ref = newArr;
			refLength = newLength;
		}
		// set the position in the refArray
		ref[e.getId()] = amount;
		// restore the heap
		heapUp(amount);
	}
	else {
		cout << "Error: queue is full!" << endl;
	}
}

int PriorityQueue::getParentIndex(int i) const {
	return i / 2;
}

int PriorityQueue::getRightChildIndex(int i) const {
	return 2 * i + 1;
}

int PriorityQueue::getLeftChildIndex(int i) const {
	return 2 * i ;
}

string PriorityQueue::toStringDebug() const {
	stringstream str;
	str << "queue: " << endl;
	str << "[" << 1 << " - " << ref[queue[1].getId()] << "] " << this->queue[1].getId() << ": " << this->queue[1].getPriority() << endl;
	for (int i = 2; i <= this->amount; i++) {
		str << "[" << i << " - " << ref[this->queue[i].getId()] << "] " << this->queue[i].getId() << ": " << this->queue[i].getPriority() << " parent: " << this->queue[getParentIndex(i)].getPriority() << endl;
	}
	return str.str();
}

string PriorityQueue::toString() const {
	return (string)*this;
}

PriorityQueue::operator string() const {
	stringstream str;
	str << "queue: " << endl;
	for (int i = 1; i <= this->amount; i++) {
		str << "[" << i << "] " << this->queue[i].getPriority() << endl;
	}
	return str.str();
}

bool PriorityQueue::isValid() const {
	// always valid when there are less then 2 elements
	if (this->amount <= 1) {
		return true;
	}
	// iterate over the heap and check the MinHeapCondidion for every element
	for (int i = 1; i <= amount; i++) {
		if (queue[i] < queue[getParentIndex(i)] || i != ref[queue[i].getId()]) {
			return false;
		}
	}
	return true;
}

void PriorityQueue::heapDown(int i) const {
	// left and right child index
	int l = getLeftChildIndex(i);
	int r = getRightChildIndex(i);
	// index of the smallest element
	int smallest = i;
	// check if one of the childs is smaller then the parent
	if (l <= amount && queue[l] < queue[i])
		smallest = l;
	if (r <= amount && queue[r] < queue[smallest])
		smallest = r;
	// if there is a smaller child
	if (smallest != i && smallest <= amount)
	{
		// swap the elements
		swap(queue[i], queue[smallest]);
		// restore the changed subtree
		heapDown(smallest);
	}
}

void PriorityQueue::heapUp(int i) const {
	// while the current index is smallet then the root index 
	// and the current element is smaller then its parent
	while (i > 1 && queue[getParentIndex(i)] > queue[i]) {
		// swap the element with its parent
		swap(queue[i], queue[getParentIndex(i)]);
		i = getParentIndex(i);
	}
	return;
}

void PriorityQueue::increaseSearch(int id, int value) {
	if (value == 0 || id < 0) return;
	// search for the id and update the prio
	for (int i = 1; i <= amount; i++) {
		if (queue[i].getId() == id ) {
			queue[i].setPriority(queue[i].getPriority() + value);
			// restore the heap
			// downwards if the prio was increased
			// upwards if the prio was reduced
			if (value > 0) heapDown(i);
			else heapUp(i);
			return;
		}
	}
}

void PriorityQueue::increase(int id, int value) {
	if (value == 0 || id < 0 || id > refLength) return;
	// use the subtree to update the prio
	queue[ref[id]].setPriority(queue[ref[id]].getPriority() + value);
	// restore the heap
	// downwards if the prio was increased
	// upwards if the prio was reduced
	if (value > 0) heapDown(ref[id]);
	else heapUp(ref[id]);
}

void PriorityQueue::removeSearch(int id) {
	if (id < 0) return;
	// search for the id
	for (int i = 1; i <= amount; i++) {
		if (queue[i].getId() == id) {
			// swap with the last element
			swap(queue[i], queue[amount--]);
			// restore the Heap
			// heapUp if we havent swapped the root
			// heapDown if we swapped the root
			if (i > 1 && queue[i] < queue[getParentIndex(i)]) heapUp(i);
			else heapDown(i);
			return;
		}
	}
}

void PriorityQueue::remove(int id) {
	int swapPos = ref[id];
	swap(queue[swapPos], queue[amount--]);
	// restore the Heap
	// heapUp if we havent swapped the root
	// heapDown if we swapped the root
	if(swapPos > 1 && queue[swapPos] < queue[getParentIndex(swapPos)]) heapUp(swapPos);
	else heapDown(swapPos);
	return;
}

void PriorityQueue::swap(PQElement& a, PQElement& b) const {
	// swap the positions in the refArray
	int temp = ref[a.getId()];
	ref[a.getId()] = ref[b.getId()];
	ref[b.getId()] = temp;
	// swap the PQElements
	std::swap(a,b);
}
