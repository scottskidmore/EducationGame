#include "plant.h"

/*
Authors:    Scott Skidmore, Patrick Schlegel, Tanner Rowlett, Paolo Diotaiuti, Drew Humphrey, Adam Bentley.
Course:     CS 3505, University of Utah, School of Computing
Date:       23 April 2024
Assignment: Educational App
            Implementation file for the Plants class. Plants stores information on the various plant types in the game.
*/
Plant::Plant(Plants plantType, QString name, QObject *parent)
    : QObject{parent}
{
    myName = name;
    deleteCode = "delete " + myName + ";";
    thisPlant = plantType;
    switch (plantType)
    {
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

std::string Plant::hintCode()
{
    std::string heapOrStack = "stack";
    if (onHeap)
    {
        heapOrStack = "heap";
    }
    std::string code = "This plant's type is " + toString(thisPlant)
                       + "\nIt should be planted on the " + heapOrStack
                       + "\nThe stack code should look like " + stackCode.toStdString()
                       + "\nThe heap code should look like\n   " + heapCode.toStdString();
    return code;
}

std::string Plant::basicInfo()
{
    return "This plant's type is " + toString(thisPlant)
            + "\nType your code below to plant"
           + "\nor click the hint button if\nyou are stuck";
}

void Plant::deleteMyButton()
{
    emit removeThisPlantsButton();
}

void Plant::updateHeapGrowth()
{
    if (heapGrowthTrack < 4)
    {
        heapGrowthTrack++;
    }
    else
    {
        return;
    }
    if (thisPlant != Plants::Tree && thisPlant != Plants::Grapes)  // Only update plant growth for grapes and trees
    {
        return;
    }
    switch (heapGrowthTrack)      // The switch handles different levels of plant growth
    {
        case 0: break;
        case 1:
            if (thisPlant == Plants::Tree)
            {
                imagePath = ":/Flowers/Images/tree_r1.png";
            }
            else
            {
                imagePath = ":/Flowers/Images/grapes_r1.png";
            }
            break;
        case 2:
            if (thisPlant == Plants::Tree)
            {
                imagePath = ":/Flowers/Images/tree_r2.png";
            }
            else
            {
                imagePath = ":/Flowers/Images/grapes_r2.png";
            }
            break;
        case 3:
            if (thisPlant == Plants::Tree)
            {
                imagePath = ":/Flowers/Images/tree_r3.png";
            }
            else
            {
                imagePath = ":/Flowers/Images/grapes_r3.png";
            }
            break;
        case 4:
            if (thisPlant == Plants::Tree)
            {
                imagePath = ":/Flowers/Images/tree_dead.png";
            }
            else
            {
                imagePath = ":/Flowers/Images/grapes_dead.png";
            }
            break;
        }
        emit updateButtonImage(QIcon(QPixmap(imagePath)));
}

void Plant::myPlantClicked()
{
    if (onHeap)
    {
        emit updateTextForDelete(this);
    }
}

void Plant::setMyButton(QPushButton *button)
{
    myButton = button;
}

void Plant::createCorn()
{
    stackCost = 20;
    heapCost = 30;
    onHeap = false;
    reward = 2;
    stackCode = "Corn c;";
    heapCode = "Corn c = new Corn();";
    imagePath = ":/Flowers/Images/corn.png";
    stackPattern = R"(Corn\s(.+);)";
    heapPattern = R"(Corn\s([^=\s]+)\s*=\s*new Corn\(\);)";

}

void Plant::createFlower()
{
    stackCost = 10;
    heapCost = 30;
    onHeap = false;
    reward = 1;
    stackCode = "Flower f;";
    heapCode = "Flower f = new Flower();";
    imagePath = ":/Flowers/Images/flower.png";
    stackPattern = R"(Flower\s(.+);)";
    heapPattern = R"(Flower\s([^=\s]+)\s*=\s*new Flower\(\);)";

}

void Plant::createTree()
{
    stackCost = 30;
    heapCost = 30;
    onHeap = true;
    reward = 2;
    stackCode = "Tree t;";
    heapCode = "Tree t = new Tree();";
    imagePath = ":/Flowers/Images/tree_new.png"; // needs to be changed when heap grows
    stackPattern = R"(Tree\s(.+);)";
    heapPattern = R"(Tree\s([^=\s]+)\s*=\s*new Tree\(\);)";

}

void Plant::createPotato()
{
    stackCost = 10;
    heapCost = 30;
    onHeap = true;
    reward = 1;
    stackCode = "Potato p;";
    heapCode = "Potato p = new Potato();";
    imagePath = ":/Flowers/Images/potato.png";
    stackPattern = R"(Potato\s(.+);)";
    heapPattern = R"(Potato\s([^=\s]+)\s*=\s*new Potato\(\);)";

}

void Plant::createGrapes()
{
    stackCost = 30;
    heapCost = 30;
    onHeap = true;
    reward = 2;
    stackCode = "Grapes g;";
    heapCode = "Grapes g = new Grapes();";
    imagePath = ":/Flowers/Images/grapes_new.png"; // needs to be changed when heap grows
    stackPattern = R"(Grapes\s(.+);)";
    heapPattern = R"(Grapes\s([^=\s]+)\s*=\s*new Grapes\(\);)";

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

