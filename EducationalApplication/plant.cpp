#include "plant.h"

Plant::Plant(Plants plantType) {
    thisPlant = plantType;
    switch (plantType) {
        case Plants::Corn:
            createCorn();
            break;
        case Plants::Flower:
            createFlower();
            break;
        case Plants::Tree:
            createTree();
            break;
    }
}

std::string Plant::hintCode(){
    std::string heapOrStack = "stack";
    if (onHeap)
        heapOrStack = "heap";
    std::string code = "This is a " + toString(thisPlant)
                       + "\nIt should be planted on the " + heapOrStack
                       + "\nThe stack code should look like " + stackCode
                       + "\nThe heap code should look like\n   " + heapCode;
    return code;
}

// std::string Plant::displayName()
// {

// }

void Plant::createCorn()
{
    cost = 0;
    onHeap = false;
    reward = 1;
    stackCode = "Corn c;";
    heapCode = "Corn c = new Corn();";

}

void Plant::createFlower()
{
    cost = 0;
    onHeap = false;
    reward = 1;
    stackCode = "Flower f;";
    heapCode = "Flower f = new Flower();";
}

void Plant::createTree()
{
    cost = 1;
    onHeap = true;
    reward = 3;
    stackCode = "Tree t;";
    heapCode = "Tree t = new Tree();";
}


std::string Plant::toString(Plants p)
{
    switch (p)
    {
    case Plants::Corn:   return "Corn";
    case Plants::Flower:   return "Flower";
    case Plants::Tree: return "Tree";
    default:      return "Unknown Plant";
    }
}

