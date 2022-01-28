#include "statistic.cpp"


struct rgster
{
    int value;
    bool signal;
};
class RegFile
{
protected:
    rgster* r=new rgster[16];  ///Easy access to the register and a constant size.
public:
    RegFile();

    ~RegFile();

    void setVal(const int& val,const int& pos);
    rgster& operator[](const int& index) const;
};