#include <iostream>
#include <time.h>
#include "PriorityQueue.h"
#include "Random.h"

int main() {
	int n = 100000;
	Random *rand = new Random(n);
	PriorityQueue *queue = new PriorityQueue(n);

	clock_t start = clock();
	for (int i = 0; i < n; i++) {
		queue->insert(PQElement(rand->give()));
	}
	clock_t end = clock();

	if (queue->isValid()) {
		cout << "TestDone for " << n << " Duration: " << ((end - start) * 1000) / CLOCKS_PER_SEC << endl;
	}
	else {
		cout << "TestFailed" << endl;
	}
	
	delete rand;
	rand = new Random(n);

	start = clock();
	for (int i = 0; i<n; i++) {
		if (i % 2 == 0) queue->removeSearch(i);
	else 
		queue->increaseSearch(i, rand->give() / 2);
	}
	end = clock();
	if (queue->isValid())
	cout << "My Test Search Duration: " << ((end - start) * 1000) / CLOCKS_PER_SEC << endl;

	delete rand;
	delete queue;

	rand = new Random(n);
	queue = new PriorityQueue(n);

	for (int i = 0; i < n; i++) {
		queue->insert(PQElement(rand->give()));
	}

	delete rand;
	rand = new Random(n);
	start = clock();
	for (int i = 0; i<n; i++) {
		if (i % 2 == 0) queue->remove(i);
		else queue->increase(i, rand->give() / 2);
	}
	end = clock();
	if (queue->isValid())
	cout << "My Test Refarray Duration: " << ((end - start) * 1000) / CLOCKS_PER_SEC << endl;
	
	delete rand;
	delete queue;
	
	n = 1000000;
	rand = new Random(n);
	queue = new PriorityQueue(n);

	start = clock();
	for (int i = 0; i < n; i++) {
		queue->insert(PQElement(rand->give()));
	}
	end = clock();

	// cout << queue->toStringDebug();

	if (queue->isValid()) {
		cout << "TestDone for " << n << " Duration: " << ((end - start) * 1000) / CLOCKS_PER_SEC << endl;
	}
	else {
		cout << "TestFailed" << endl;
	}

	delete rand;
	delete queue;

	n = 5000000;
	rand = new Random(n);
	queue = new PriorityQueue(n);

	start = clock();
	for (int i = 0; i < n; i++) {
		queue->insert(PQElement(rand->give()));
	}
	end = clock();


	if (queue->isValid()) {
		cout << "TestDone for " << n << " Duration: " << ((end - start) * 1000) / CLOCKS_PER_SEC << endl;
	}
	else {
		cout << "TestFailed" << endl;
	}

	delete rand;
	delete queue;

	return 0;
}