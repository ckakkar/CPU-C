#include "RegFile.cpp"


class ALU
{
private:
    string opcode;
    int oper1,oper2,result,ins;
    void final();
public:
    ALU();
    ALU(const string& code, const int& a, const int& b);
    int getResult() const;
};