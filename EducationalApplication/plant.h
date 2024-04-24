/*
Authors:    Scott Skidmore, Patrick Schlegel, Tanner Rowlett, Paolo Diotaiuti, Drew Humphrey, Adam Bentley.
Course:     CS 3505, University of Utah, School of Computing
Date:       23 April 2024
Assignment: Educational App
            Header file for the Plants class. Plants stores information on the various plant types in the game.
*/

#ifndef PLANT_H
#define PLANT_H
#include <string>
#include <QString>
#include <QPushButton>
#include "qobject.h"
#include <regex>

enum class Plants;

class Plant : public QObject
{
    Q_OBJECT
public:
    ///
    /// \brief Plant Constructor
    /// \param plantType the type: grape, tree, corn, flower, potato
    /// \param name the plant's variable name
    /// \param parent
    ///
    explicit Plant(Plants plantType, QString name, QObject *parent = nullptr);
    Plants thisPlant;
    bool onHeap;
    int heapCost;
    int stackCost;
    int reward;
    int heapGrowthTrack;    // this tracks the heap growth, to change image and points
    QString heapCode;
    QString stackCode;
    QString imagePath;
    QString deleteCode;
    QString myName;         // this is the plant's name, its used as the key for the heap or stack
    QPushButton* myButton;
    std::regex heapPattern;
    std::regex stackPattern;
    std::regex deletePattern;
    ///
    /// \brief hintCode Has different hint codes for the different plant types and
    /// helps the player know what to type to put the plant on the stack or the heap.
    /// \return The hint string for this type of plant.
    ///
    std::string hintCode();
    ///
    /// \brief basicInfo Stores the basic information for this type of plant,
    /// such as what the plant type is.
    /// \return The basic info string for this type of plant.
    ///
    std::string basicInfo();
    ///
    /// \brief deleteMyButton Deletes this plants' button
    ///
    void deleteMyButton();

public slots:
    ///
    /// \brief updateHeapGrowth Updates the plant's image if it is in the heap and grows.
    /// Grapes and trees grow, other plants won't be updated.
    ///
    void updateHeapGrowth();
    ///
    /// \brief myPlantClicked Updates which type of plant was clicked on the heap.
    ///
    void myPlantClicked();
    ///
    /// \brief setMyButton Changes this plant's myButton variable to be the button parameter.
    ///
    void setMyButton(QPushButton*);

signals:
    void updateButtonImage(QIcon);
    void removeThisPlantsButton();
    void updateTextForDelete(Plant* p);

private:
    ///
    /// \brief createCorn Creates corn plant
    ///
    void createCorn();
    ///
    /// \brief createFlower Creates flower plant
    ///
    void createFlower();
    ///
    /// \brief createTree Creates tree plant
    ///
    void createTree();
    ///
    /// \brief createPotato Creates potato plant
    ///
    void createPotato();
    ///
    /// \brief createGrapes Creates grape plant
    ///
    void createGrapes();
    ///
    /// \brief toString Returns the type of the plant parameter as a string.
    /// \param p The plant parameter.
    /// \return This plant's type as a string.
    ///
    std::string toString(Plants p);

};

///
/// \brief The Plants enum contains all possible plant types
///
enum class Plants {
    Corn,
    Flower,
    Tree,
    Potato,
    Grapes
};

#endif
