#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include "plant.h"

/*
Authors:    Scott Skidmore, Patrick Schlegel, Tanner Rowlett, Poalo Diotaiuti, Drew Humphrey, Adam Bentley.
Course:     CS 3505, University of Utah, School of Computing
Date:       23 April 2024
Assignment: Educational App
            Header file for heap class. The heap handles all the plants that are planted on the heap.
Citations:
*/
class Heap
{
public:
    ///
    /// \brief Heap - constructor
    ///
    Heap();
    ///
    /// \brief plants - stores pointers to all plants on the heap
    ///
    std::vector<Plant*> plants;
    ///
    /// \brief plantMap - map of plants on the heap
    ///
    std::map<QString, Plant*> plantMap;

public slots:

    ///
    /// \brief updateHeapPlants Updates the growth of all plants on the heap, and they will change their image if needed.
    ///
    void updateHeapPlants();
};
#endif // HEAP_H
