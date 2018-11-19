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
	this->sortDown(1);
	return min;
}

void PriorityQueue::insert(const PQElement& e) {
	if (this->amount < this->length) {
		amount++;
		this->queue[amount] = e;
		this->queue[amount].setId(this->newID);
		if (this->newID > refLength) {
			cout << "Limit reached";
			refLength *= 2;
			ref = (int*) realloc(ref, refLength * sizeof(int));
		}
		ref[newID] = amount;
		newID++;
		sortUp(amount);
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

void PriorityQueue::sortDown(int i) const {
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
		sortDown(smallest);
	}
}

void PriorityQueue::sortUp(int i) const {
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
			if (value > 0) sortDown(i);
			else sortUp(i);
			return;
		}
	}
}

void PriorityQueue::increase(int id, int value) {
	if (value == 0 || id >= newID || id < 0) return;
	queue[ref[id]].setPriority(queue[ref[id]].getPriority() + value);
	if (value > 0) sortDown(ref[id]);
	else sortUp(ref[id]);
}

void PriorityQueue::removeSearch(int id) {
	if (id >= newID || id < 0) return;
	for (int i = 1; i <= amount; i++) {
		if (queue[i].getId() == id) {
			queue[i].setPriority(INT_MIN);
			sortUp(i);
			extractMin();
			return;
		}
	}
}

void PriorityQueue::remove(int id) {
	queue[ref[id]].setPriority(INT_MIN);
	sortUp(ref[id]);
	extractMin();
	return;
}

void PriorityQueue::swap(PQElement& a, PQElement& b) const {
	int temp = ref[a.getId()];
	ref[a.getId()] = ref[b.getId()];
	ref[b.getId()] = temp;
	std::swap(a,b);
}