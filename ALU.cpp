#include "ALU.h"

ALU::ALU()
=default;
ALU::ALU(const string& code, const int& a, const int& b)
{
    this->opcode=code;
    this->oper1=a;
    this->oper2=b;
    this->ins=ins;
    this->final();
}
void ALU::final()
{
    if(opcode=="0000")
    {
        result=oper1+oper2;
    }
    else if(opcode=="0001")
    {
        result=oper1-oper2;
    }
    else if(opcode=="0010")
    {
        result=oper1*oper2;
    }
    else if(opcode=="0011")
    {
        result=oper1/oper2;
    }
    else if(opcode=="0100")
    {
        result=oper1%oper2;
    }
    else if(opcode=="0111")
    {
        this->result=oper1;
    }
    else if(opcode=="1000")
    {
        this->result=oper1;
    }
}
int ALU::getResult() const
{
    if(opcode=="1000")
        cout<<"\nFinal result is: "<<this->result;
    return this->result;
}