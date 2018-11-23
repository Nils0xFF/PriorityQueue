#include <iostream>
#include <time.h>
#include "PriorityQueue.h"
#include "Random.h"

int main() {
	PQElement feld[5000000];
	int n = 100000;
	Random *rand = new Random(n);
	PriorityQueue *queue = new PriorityQueue(n);
	PriorityQueue *queue2 = new PriorityQueue(5000000);

	clock_t start = clock();
	for (int i = 0; i < n; i++) {
		queue->insert(PQElement(i, rand->give()));
	}
	for (int i = 0; i < n; i++) {
		feld[i] = queue->extractMin();
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
		queue->insert(PQElement(i, rand->give()));
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
		queue->insert(PQElement(i, rand->give()));
	}
	for (int i = 0; i < n; i++) {
		feld[i] = queue->extractMin();
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
		queue->insert(PQElement(i, rand->give()));
	}
	for (int i = 0; i < n; i++) {
		feld[i] = queue->extractMin();
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