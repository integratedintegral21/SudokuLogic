//
// Created by wojciech on 13/12/2021.
//

#ifndef SUDOKULOGICLIBRARY_INTEGERSUMCELLGROUP_H
#define SUDOKULOGICLIBRARY_INTEGERSUMCELLGROUP_H

#include "CellVerifiers/AggregatedCellGroup.h"

class CellVerifiers::UnsignedIntegerSumCellGroup: public CellVerifiers::AggregatedCellGroup<unsigned int>{
public:
    explicit UnsignedIntegerSumCellGroup(unsigned int desiredResult, unsigned int groupSize): AggregatedCellGroup(
            desiredResult, 0, intSumAggregationFunction, intSubtractAggregationFunction),
                                                                            emptySlots(groupSize){}

    [[nodiscard]] bool isNumberAllowed(int number) const override {
        if (number < 0){
            return false;
        }
        if (this->emptySlots == 0){
            return false;
        }
        if (this->emptySlots == 1){
            return currentResult + number == desiredResult;
        }
        return currentResult + number < desiredResult;
    }

    void notifySet(int number) override {
        AggregatedCellGroup::notifySet(number);
        emptySlots--;
    }

    [[nodiscard]] std::shared_ptr<CellVerifiers::CellGroupObserver> clone() const override {
        std::shared_ptr<UnsignedIntegerSumCellGroup> newGroup = std::make_shared<UnsignedIntegerSumCellGroup>(desiredResult, emptySlots);
        newGroup->currentResult = currentResult;
        return newGroup;
    }

    void notifyClear(int number) override {
        AggregatedCellGroup::notifyClear(number);
        emptySlots--;
    }


private:
    static constexpr int intSumAggregationFunction(int currentResult, int newNumber){
        return currentResult + newNumber;
    }

    static constexpr int intSubtractAggregationFunction(int currentResult, int deletedNumber) {
        return currentResult - deletedNumber;
    }

    int emptySlots;
};



#endif //SUDOKULOGICLIBRARY_INTEGERSUMCELLGROUP_H
