#pragma once

class PQElement {
private:
	int priority; /* hier: p(a) ist eine ganze Zahl */
	int id;
public:
	PQElement() { this->priority = -1; this->id = -1; }
	PQElement(int prio) { this->priority = prio; }
	PQElement(int id, int prio) { this->id = id; this->priority = prio; }
	PQElement(const PQElement& pq);
	~PQElement() {};
	PQElement& operator=(const PQElement& pq);
	bool operator== (const PQElement& e) const {
		return priority == e.priority;
	}
	bool operator< (const PQElement& e) const {
		return priority < e.priority;
	}
	bool operator>(const PQElement& e) const {
		return this->priority > e.priority;
	}

	int getPriority(void) const { return this->priority; }
	int getId(void) const { return this->id; }
	void setPriority(int priority) { this->priority = priority; }
	void setId(int id) { this->id = id; }

};