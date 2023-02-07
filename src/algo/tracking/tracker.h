#pragma once

#include <data/data.h>


// General 
template <typename T>
class Tracker {
private:
    nl::Rectangle2d<T> rect; 

protected:



public:
    // default constructor
    Tracker() {}




    ~Tracker() {}
};



// Object for Tracker
template <typename T>
class TrackedObject {
private:
// --------------------------------------

protected:
// --------------------------------------

public:
    TrackedObject() {}



    ~TrackedObject() {}
};