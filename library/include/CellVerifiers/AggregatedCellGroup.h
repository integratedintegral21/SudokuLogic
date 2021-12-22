//
// Created by wojciech on 12/12/2021.
//

#ifndef SUDOKULOGICLIBRARY_AGGREGATEDCELLGROUP_H
#define SUDOKULOGICLIBRARY_AGGREGATEDCELLGROUP_H

#include "CellGroupObserver.h"
#include "functional"


template <typename T>
class CellVerifiers::AggregatedCellGroup: public CellVerifiers::CellGroupObserver{
public:
    /**
     * Takes a desired aggregation result after completing the group, an initial aggregation result,
     * an aggregation and inversion function
     * @param desiredResult the desired result
     * @param currentResult the base case
     * @param aggregationFunction the aggregation function
     * @param aggregationInversionFunction the inversion function
     */
    AggregatedCellGroup(T desiredResult, T currentResult, const std::function<T(T, int)> &aggregationFunction,
                        const std::function<T(T, int)> &aggregationInversionFunction) : desiredResult(desiredResult),
                                                                                        currentResult(currentResult),
                                                                                        aggregationFunction(
                                                                                                aggregationFunction),
                                                                                        aggregationInversionFunction(
                                                                                                aggregationInversionFunction) {}


    void notifySet(int number) override {
        this->currentResult = aggregationFunction(this->currentResult, number);
    }

    void notifyClear(int number) override {
        this->currentResult = aggregationInversionFunction(this->currentResult, number);
    }

protected:
    T desiredResult;
    T currentResult;
    std::function<T(T, int)> aggregationFunction;
    std::function<T(T, int)> aggregationInversionFunction;
};


#endif //SUDOKULOGICLIBRARY_AGGREGATEDCELLGROUP_H
