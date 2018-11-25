#include "PQTest.h"
#include <time.h>
#include <iostream>

using namespace std;

void pqInsertExtractTest(PriorityQueue* queue, int size) {
	Random rand(size);
	PQElement* a = new PQElement[size];

	// Time for insertion
	clock_t start = clock();
	for (int i = 0; i < size; i++) {
		queue->insert(PQElement(i, rand.give()));
	}
	clock_t end = clock();

	if (queue->isValid()) {
		cout << "Insert valid for " << size << " elements" << endl << "Duration: " << ((end - start) * 1000) / CLOCKS_PER_SEC << endl;
	}
	else {
		cout << "Insert failed for " << size << " elements" << endl;
	}


	// Time for extraction
	start = clock();
	for (int i = 0; i < size; i++) {
		a[i] = queue->extractMin();
	}
	end = clock();

	if (queue->isValid()) {
		cout << "Extraction valid for " << size << " elements" << endl << "Duration: " << ((end - start) * 1000) / CLOCKS_PER_SEC << endl;
	}
	else {
		cout << "Extraction failed for " << size << " elements" << endl;
	}

	cout << endl;

	delete[] a;
}

void pqIncreaseRemoveSearchTest(PriorityQueue* queue, int size) {
	// filling the queue
	Random* rand = new Random(size);
	for (int i = 0; i < size; i++) {
		queue->insert(PQElement(i, rand->give()));
	}
	delete rand;
	rand = new Random(size);
	// Time for sequential search acces to the queue
	clock_t start = clock();
	for (int i = 0; i<size; i++) {
		if (i % 2 == 0) queue->removeSearch(i);
		else
			queue->increaseSearch(i, rand->give() / 2);
	}
	clock_t end = clock();
	if (queue->isValid())
		cout << "Sequential search duration: " << ((end - start) * 1000) / CLOCKS_PER_SEC << endl;
	
	cout << endl;

	delete rand;
}

void pqIncreaseRemoveTest(PriorityQueue* queue, int size) {
	// filling the queue
	Random* rand = new Random(size);
	for (int i = 0; i < size; i++) {
		queue->insert(PQElement(i, rand->give()));
	}
	delete rand;
	rand = new Random(size);
	// Time for the acces using the refArray
	clock_t start = clock();
	for (int i = 0; i<size; i++) {
		if (i % 2 == 0) queue->remove(i);
		else queue->increase(i, rand->give() / 2);
	}
	clock_t end = clock();
	if (queue->isValid())
		cout << "My Test Refarray Duration: " << ((end - start) * 1000) / CLOCKS_PER_SEC << endl;

	cout << endl;
	delete rand;
}