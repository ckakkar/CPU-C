#include "memory.cpp"

struct divd
{
    string opCode,dest,src1,src2,imme,type;
};
class instruction : public memory
{
private:
    string int2binary(const long int& s);
    void converttobin();
    void decoder();
    vector <string> inst;
    vector <divd> v;
public:
    instruction();
    instruction(ifstream& f);
    string getOpcode(const int& z) const;
    string getDest(const int& z) const;
    string getSrc1(const int& z) const;
    string getSrc2(const int& z) const;
    string getImme(const int& z) const;
    string getType(const int& z) const;
    string getInstruct(const int& v) const;
    int instNum() const;
};