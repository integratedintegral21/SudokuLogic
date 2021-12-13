//
// Created by wojciech on 13/12/2021.
//

#ifndef SUDOKULOGICLIBRARY_INTEGERSUMCELLGROUP_H
#define SUDOKULOGICLIBRARY_INTEGERSUMCELLGROUP_H

#include "CellVerifiers/AggregatedCellGroup.h"

class CellVerifiers::IntegerSumCellGroup: public CellVerifiers::AggregatedCellGroup<int>{
public:
    explicit IntegerSumCellGroup(int desiredResult, int groupSize): AggregatedCellGroup(
            desiredResult, 0, intSubtractAggregationFunction, intSumAggregationFunction),
                                                                    emptySlots(groupSize){}

    [[nodiscard]] bool isNumberAllowed(int number) const override {
        if (this->emptySlots == 0){
            return false;
        }
        if (this->emptySlots == 1){
            return currentResult + number == desiredResult;
        }
        return currentResult + number < desiredResult;
    }

    void notifySet(int number) override {
        CellVerifiers::AggregatedCellGroup<int>::notifySet(number);
        emptySlots--;
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
