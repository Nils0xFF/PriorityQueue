#include "PriorityQueue.h"
#include "PQTest.h"

/*Basic test cases for the PriorityQueue class*/
int main() {
	
	// Test 1: 100000 
	int size = 100000;
	PriorityQueue *queue = new PriorityQueue(size);
	pqInsertExtractTest(queue, size);
	queue->reset();
	pqIncreaseRemoveSearchTest(queue, size);
	queue->reset();
	pqIncreaseRemoveTest(queue, size);
	delete queue;
	
	// Test 2: 1000000 elements
	size = 1000000;
	queue = new PriorityQueue(size);
	pqInsertExtractTest(queue, size);
	delete queue;

	// Test 3: 5000000 elements
	size = 5000000;
	queue = new PriorityQueue(size);
	pqInsertExtractTest(queue, size);
	delete queue;

	return 0;
}
