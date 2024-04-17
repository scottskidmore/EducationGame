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
        case Plants::Potato:
            createPotato();
            break;
        case Plants::Grapes:
            createGrapes();
            break;
    }
    heapGrowthTrack = 0;
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

void Plant::updateHeapGrowth()
{
    if (heapGrowthTrack < 4)
        heapGrowthTrack++;
    else
        return;
    switch (heapGrowthTrack) {
        case 0: break;
        case 1:
            if (thisPlant == Plants::Tree)
                imagePath = ":/Flowers/Images/tree_r1.png";
            else
                imagePath = ":/Flowers/Images/grapes_r1.png";
            break;
        case 2:
            if (thisPlant == Plants::Tree)
                imagePath = ":/Flowers/Images/tree_r2.png";
            else
                imagePath = ":/Flowers/Images/grapes_r2.png";
            break;
        case 3:
            if (thisPlant == Plants::Tree)
                imagePath = ":/Flowers/Images/tree_r3.png";
            else
                imagePath = ":/Flowers/Images/grapes_r3.png";
            break;
        case 4:
            if (thisPlant == Plants::Tree)
                imagePath = ":/Flowers/Images/tree_dead.png";
            else
                imagePath = ":/Flowers/Images/grapes_dead.png";
            break;
    }
}



// std::string Plant::displayName()
// {

// }

void Plant::createCorn()
{
    cost = 10;
    onHeap = false;
    reward = 1;
    stackCode = "Corn c;";
    heapCode = "Corn c = new Corn();";
    imagePath = ":/Flowers/Images/corn.png";

}

void Plant::createFlower()
{
    cost = 10;
    onHeap = false;
    reward = 1;
    stackCode = "Flower f;";
    heapCode = "Flower f = new Flower();";
    imagePath = ":/Flowers/Images/flower.png";
}

void Plant::createTree()
{
    cost = 50;
    onHeap = true;
    reward = 1;
    stackCode = "Tree t;";
    heapCode = "Tree t = new Tree();";
    imagePath = ":/Flowers/Images/tree_new.png"; // needs to be changed when heap grows
}

void Plant::createPotato()
{
    cost = 10;
    onHeap = true;
    reward = 1;
    stackCode = "Potato p;";
    heapCode = "Potato p = new Potato();";
    imagePath = ":/Flowers/Images/potato.png";
}

void Plant::createGrapes()
{
    cost = 25;
    onHeap = true;
    reward = 1;
    stackCode = "Grapes g;";
    heapCode = "Grapes g = new Grapes();";
    imagePath = ":/Flowers/Images/grapes_new.png"; // needs to be changed when heap grows
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

