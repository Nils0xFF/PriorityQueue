#include <iostream>
#include "PriorityQueue.h"

using namespace std;

PriorityQueue::~PriorityQueue() {
	delete[] queue;
	delete[] ref;
}

PQElement& PriorityQueue::getMin(void) const {
	return this->queue[1];
}

PQElement PriorityQueue::extractMin(void) {
	if (this->amount == 0) return NULL;
	if (this->amount == 1) return queue[--this->amount];
	PQElement& min = this->queue[1];
	swap(min, this->queue[this->amount--]);
	this->heapDown(1);
	return min;
}

void PriorityQueue::insert(const PQElement& e) {
	if (this->amount < this->length) {
		amount++;
		this->queue[amount] = e;
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
		ref[e.getId()] = amount;
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
	if (this->amount <= 1) {
		return true;
	}
	for (int i = 1; i <= amount; i++) {
		if (queue[i] < queue[getParentIndex(i)] || i != ref[queue[i].getId()]) {
			return false;
		}
	}
	return true;
}

void PriorityQueue::heapDown(int i) const {
	int l = getLeftChildIndex(i);
	int r = getRightChildIndex(i);
	int smallest = i;
	if (l <= amount && queue[l] < queue[i])
		smallest = l;
	if (r <= amount && queue[r] < queue[smallest])
		smallest = r;
	if (smallest != i && smallest <= amount)
	{
		swap(queue[i], queue[smallest]);
		heapDown(smallest);
	}
}

void PriorityQueue::heapUp(int i) const {
	while (i > 1 && queue[getParentIndex(i)] > queue[i]) {
		int temp = ref[queue[i].getId()];
		swap(queue[i], queue[getParentIndex(i)]);
		i = getParentIndex(i);
	}
	return;
}

void PriorityQueue::increaseSearch(int id, int value) {
	if (value == 0 || id >= newID || id < 0) return;
	for (int i = 1; i <= amount; i++) {
		if (queue[i].getId() == id ) {
			queue[i].setPriority(queue[i].getPriority() + value);
			if (value > 0) heapDown(i);
			else heapUp(i);
			return;
		}
	}
}

void PriorityQueue::increase(int id, int value) {
	if (value == 0 || id >= newID || id < 0) return;
	queue[ref[id]].setPriority(queue[ref[id]].getPriority() + value);
	if (value > 0) heapDown(ref[id]);
	else heapUp(ref[id]);
}

void PriorityQueue::removeSearch(int id) {
	if (id >= newID || id < 0) return;
	for (int i = 1; i <= amount; i++) {
		if (queue[i].getId() == id) {
			swap(queue[i], queue[amount]);
			amount--;
			if (i > 1 && queue[i] < queue[getParentIndex(i)]) heapUp(i);
			else heapDown(i);
			return;
		}
	}
}

void PriorityQueue::remove(int id) {
	int swapPos = ref[id];
	swap(queue[ref[id]], queue[amount]);
	amount--;
	if(swapPos > 1 && queue[swapPos] < queue[getParentIndex(swapPos)]) heapUp(swapPos);
	else heapDown(swapPos);
	return;
}

void PriorityQueue::swap(PQElement& a, PQElement& b) const {
	int temp = ref[a.getId()];
	ref[a.getId()] = ref[b.getId()];
	ref[b.getId()] = temp;
	std::swap(a,b);
}
