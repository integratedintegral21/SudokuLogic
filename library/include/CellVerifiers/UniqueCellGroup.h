//
// Created by wojciech on 12/12/2021.
//

#ifndef SUDOKULOGICLIBRARY_UNIQUECELLGROUP_H
#define SUDOKULOGICLIBRARY_UNIQUECELLGROUP_H

#include "CellGroupObserver.h"

class CellVerifiers::UniqueCellGroup: public CellVerifiers::CellGroupObserver{
private:
    bool allowanceMask[9];
public:
    UniqueCellGroup();

    UniqueCellGroup(const UniqueCellGroup& uniqueCellGroup);

    void notifySet(int number) override;

    void notifyClear(int number) override;

    [[nodiscard]] bool isNumberAllowed(int number) const override;

};


#endif //SUDOKULOGICLIBRARY_UNIQUECELLGROUP_H
