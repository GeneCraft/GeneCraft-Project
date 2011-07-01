#ifndef STATISTIC_H
#define STATISTIC_H

namespace GeneLabCore{

class Statistic
{
public:
    Statistic();

    virtual void update() = 0;
    float getValue() { return value; }

protected:

    float value;
};

}

#endif // STATISTIC_H
