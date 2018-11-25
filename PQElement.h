#pragma once

class PQElement {
private:
	int priority; /* priority of the element */
	int id; /* id of the element */
public:
	// default constructor
	PQElement() { this->priority = -1; this->id = -1; }
	// parameter constructors
	PQElement(int prio) { this->priority = prio; }
	PQElement(int id, int prio) { this->id = id; this->priority = prio; }
	// copy constructor
	PQElement(const PQElement& pq);
	// destructor
	~PQElement() {};
	// overloaded assignment operator
	PQElement& operator=(const PQElement& pq);
	// overloaded compare operators
	bool operator== (const PQElement& e) const {
		return priority == e.priority;
	}
	bool operator< (const PQElement& e) const {
		return priority < e.priority;
	}
	bool operator>(const PQElement& e) const {
		return this->priority > e.priority;
	}
	// getter and setter methods
	int getPriority(void) const { return this->priority; }
	int getId(void) const { return this->id; }
	void setPriority(int priority) { this->priority = priority; }
	void setId(int id) { this->id = id; }

};