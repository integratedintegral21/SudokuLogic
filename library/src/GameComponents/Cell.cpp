//
// Created by wojciech on 12/12/2021.
//

#include "GameComponents/Cell.h"
#include "CellVerifiers/CellGroupObserver.h"
#include "stdexcept"

bool GameComponents::Cell::isEmpty() const{
    return this->number == 0;
}

void GameComponents::Cell::setNumber(int number) {
    if (number < 1 || number > 9){
        throw std::invalid_argument("Cell: Given number must be between [1, 9]");
    }
    int oldNumber = this->number;
    this->number = number;
    for (const auto &group: this->groups) {
        if (oldNumber >= 1){
            group->notifyClear(oldNumber);
        }
        group->notifySet(number);
    }
}

void GameComponents::Cell::clearCell() {
    if (this->number < 1){
        return;
    }
    for (const auto &group: this->groups) {
        group->notifyClear(this->number);
    }
    this->number = 0;
}

GameComponents::Cell::Cell(int number){
    this->setNumber(number);
}

void GameComponents::Cell::addGroupObserver(const std::shared_ptr<CellVerifiers::CellGroupObserver>& groupObserver) {
    if (this->number > 0){
        groupObserver->notifySet(number);
    }
    this->groups.push_back(groupObserver);
}

GameComponents::Cell::Cell() {

}

int GameComponents::Cell::getNumber() const {
    return number;
}

const std::vector<std::shared_ptr<CellVerifiers::CellGroupObserver>> &GameComponents::Cell::getGroups() const {
    return groups;
}

bool GameComponents::Cell::isNumberAllowed(int number) const {
    if (number < 1 || number > 9){
        throw std::invalid_argument("Cell: Given number must be between [1, 9]");
    }
    for (const auto &group: groups) {
        if (!group->isNumberAllowed(number)){
            return false;
        }
    }
    return true;
}

std::shared_ptr<GameComponents::Cell> GameComponents::Cell::clone() const{
    std::shared_ptr<Cell> newCell;
    if (this->number >= 1 && this->number <= 9){
        newCell = std::make_shared<Cell>(this->number);
    }
    else{
        newCell = std::make_shared<Cell>();
    }
    for (const auto &group: groups) {
        newCell->addGroupObserver(group->clone());
    }
    return newCell;
}

