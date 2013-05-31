#ifndef FLY_H
#define FLY_H

//whole set of chromosomes
enum SEX {male, female};

class Fly
{
public:
    SEX sex;
    double SLocus[2];
    void ShowFly();
    bool Mated;
    int IndexPartner;
};

#endif // FLY_H
