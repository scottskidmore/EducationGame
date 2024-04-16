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
                       + "\nThe stack code should look like " + stackCode.toStdString()
                       + "\nThe heap code should look like\n   " + heapCode.toStdString();
    return code;
}

std::string Plant::basicInfo()
{
    return "This is a " + toString(thisPlant)
            + "\nType your code below to plant"
            + "\nor click the hint button if\nyou are stuck";
}



// std::string Plant::displayName()
// {

// }

void Plant::createCorn()
{
    cost = 10;
    onHeap = false;
    reward = 15;
    stackCode = "Corn c;";
    heapCode = "Corn c = new Corn();";
    imagePath = ":/Flowers/Images/wild_flower_14.png";

}

void Plant::createFlower()
{
    cost = 10;
    onHeap = false;
    reward = 15;
    stackCode = "Flower f;";
    heapCode = "Flower f = new Flower();";
    imagePath = ":/Flowers/Images/flower_complete.png";
}

void Plant::createTree()
{
    cost = 50;
    onHeap = true;
    reward = 70;
    stackCode = "Tree t;";
    heapCode = "Tree t = new Tree();";
    imagePath = ":/Flowers/Images/flower_complete.png"; // needs to be updated
}

void Plant::createPotato()
{
    cost = 10;
    onHeap = true;
    reward = 15;
    stackCode = "Potato p;";
    heapCode = "Potato p = new Potato();";
    imagePath = ":/Flowers/Images/flower_complete.png"; // needs to be updated
}

void Plant::createGrapes()
{
    cost = 25;
    onHeap = true;
    reward = 40;
    stackCode = "Grapes g;";
    heapCode = "Grapes g = new Grapes();";
    imagePath = ":/Flowers/Images/flower_complete.png"; // needs to be updated
}


std::string Plant::toString(Plants p)
{
    switch (p)
    {
    case Plants::Corn:   return "Corn";
    case Plants::Flower:   return "Flower";
    case Plants::Tree: return "Tree";
    case Plants::Potato: return "Potato";
    case Plants::Grapes: return "Grapes";
    default:      return "Unknown Plant";
    }
}

