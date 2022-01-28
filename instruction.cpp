#include "instruction.h"

instruction::instruction()
=default;
instruction::instruction(ifstream& f): memory(f)
{
    converttobin();
    v.resize(inst.size());
    decoder();
}
string instruction::int2binary(const long int& s)
{
    long int num=s;
    vector <char> a,b;
    for(int i=0;num>0;i++)
    {
        if(num%2==1)
            a.push_back('1');
        else
            a.push_back('0');
        num/=2;
    }
    for(int i=a.size()-1;i>=0;i--)
    {
        b.push_back(a[i]);
    }
    if(a.size()<32)
    {
        int diff=32-b.size();
        for(int i=0;i<diff;i++)
        {
            vector<char>::iterator it=b.emplace(b.begin(),'0');
        }
    }
    string str;
    for(int i=0;i<b.size();i++)
    {
        str+=b[i];
    }
    return str;
}
void instruction::converttobin()
{
    for(int i=0;i<PC.size();i++)
    {
        string str=this->int2binary(PC[i]);
        inst.push_back(str);
    }
}
void instruction::decoder()
{
    for(int z=0;z<inst.size();z++)
    {
        string temp=inst[z],str=inst[z];
        temp.resize(2);
        v[z].type=temp;
        if(temp=="00")
        {
            for(int i=0;i<4;i++)
            {
                v[z].opCode+=str[i+2];
            }
            for(int i=0;i<5;i++)
            {
                v[z].dest+=str[i+6];
            }
            for(int i=0;i<5;i++)
            {
                v[z].src1+=str[i+11];
            }
            for(int i=0;i<5;i++)
            {
                v[z].src2+=str[i+16];
            }
        }
        else if(temp=="01")
        {
            for(int i=0;i<4;i++)
            {
                v[z].opCode+=str[i+2];
            }
            for(int i=0;i<5;i++)
            {
                v[z].dest+=str[i+6];
            }
            for(int i=0;i<5;i++)
            {
                v[z].src1+=str[i+11];
            }
            for(int i=0;i<16;i++)
            {
                v[z].imme+=str[i+16];
            }
        }
        else if(temp=="10")
        {
            string jump;
            for(int i=0;i<30;i++)
            {
                jump+=str[i+2];
            }
            v[z].imme=jump;
        }
        else if(temp=="11")
        {
            for(int i=0;i<4;i++)
            {
                v[z].opCode+=str[i+2];
            }
            v[z].dest="10";
        }
    }

}
int instruction::instNum() const
{
    return inst.size();
}
string instruction::getOpcode(const int& z) const
{
    return v[z].opCode;
}
string instruction::getDest(const int& z) const
{
    return v[z].dest;
}
string instruction::getSrc1(const int& z) const
{
    return v[z].src1;
}
string instruction::getSrc2(const int& z) const
{
    return v[z].src2;
}
string instruction::getImme(const int& z) const
{
    return v[z].imme;
}
string instruction::getType(const int& z) const
{
    return v[z].type;
}
string instruction::getInstruct(const int& v) const
{
    return this->inst[v];
}