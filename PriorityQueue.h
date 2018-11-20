#pragma once
#include <string>
#include <sstream>
#include "PQElement.h"

using namespace std;

class PriorityQueue {
	int amount; /* aktuelle Laenge */
	int length; /* Gesamtlaenge=Aufnahmekapazitaet */
	int refLength;
	PQElement *queue; /* fuer das Feld */
	int *ref; /* Referenzarray */
	int newID = 0;
public:
	PriorityQueue(int l = 1000) {
		length = l;
		refLength = l;
		amount = 0;
		queue = new PQElement[length + 1];
		ref = new int[refLength + 1];
	}
	~PriorityQueue();
	PQElement& getMin(void) const;
	PQElement extractMin(void);

	string toString() const;
	string toStringDebug() const;
	operator string() const;

	int getSize(void) const { return length; }
	int getParentIndex(int i) const;
	int getRightChildIndex(int i) const;
	int getLeftChildIndex(int i) const;

	bool isValid() const;
	void insert(const PQElement&);
	void heapDown(int i) const;
	void heapUp(int i) const;
	void swap(PQElement& a, PQElement& b) const;

	void increaseSearch(int id, int value);
	void increase(int id, int value);
	void removeSearch(int id);
	void remove(int id);
};