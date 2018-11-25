#pragma once
#include "PriorityQueue.h"
#include "Random.h"

// test function for insertion and extraction
void pqInsertExtractTest(PriorityQueue* queue, int size);
// test function for increase and delete operations with sequential search
void pqIncreaseRemoveSearchTest(PriorityQueue* queue, int size);
// test function for increase and delete operations using the refArray
void pqIncreaseRemoveTest(PriorityQueue* queue, int size);