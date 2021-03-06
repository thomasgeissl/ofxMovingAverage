#pragma once

#include <iostream>
#include <stddef.h>
#include <assert.h>
 
template <class T>
class ofxMovingAverage {
public:
	ofxMovingAverage(unsigned int period) :
		period(period), window(new T[period]), head(NULL), tail(NULL), total(0) {
		assert(period >= 1);
	}
	~ofxMovingAverage() {
		delete[] window;
	}
 
	// Adds a value to the average, pushing one out if nescessary
	T add(T val) {
		// Special case: Initialization
		if (head == NULL) {
			head = window;
			*head = val;
			tail = head;
			inc(tail);
			total = val;
			return avg();
		}
 
		// Were we already full?
		if (head == tail) {
			// Fix total-cache
			total -= *head;
			// Make room
			inc(head);
		}
 
		// Write the value in the next spot.
		*tail = val;
		inc(tail);
 
		// Update our total-cache
		total += val;
        return avg();
	}
 
	// Returns the average of the last P elements added to this SMA.
	// If no elements have been added yet, returns 0.0
	T avg() const {
		ptrdiff_t size = this->size();
		if (size == 0) {
			return 0; // No entries => 0 average
		}
		return total / (double) size; // Cast to double for floating point arithmetic
	}
 
private:
	unsigned int period;
	T * window; // Holds the values to calculate the average of.
 
	// Logically, head is before tail
	T * head; // Points at the oldest element we've stored.
	T * tail; // Points at the newest element we've stored.
 
	T total; // Cache the total so we don't sum everything each time.
 
	// Bumps the given pointer up by one.
	// Wraps to the start of the array if needed.
	void inc(T * & p) {
		if (++p >= window + period) {
			p = window;
		}
	}
 
	// Returns how many numbers we have stored.
	ptrdiff_t size() const {
		if (head == NULL)
			return 0;
		if (head == tail)
			return period;
		return (period + tail - head) % period;
	}
};