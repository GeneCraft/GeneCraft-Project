#ifndef STATISTIC_H
#define STATISTIC_H

namespace GeneLabCore{

class Statistic
{
public:
    Statistic();

    virtual void update() = 0;
    float getValue() { return value; }
    bool wantToBeUpdatedEachStep() { return updateEachStep; }

protected:

    float value;
    bool updateEachStep;
};

}

#endif // STATISTIC_H
