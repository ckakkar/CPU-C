#include "ALU.cpp"
struct dab
{
    string type;
    string OP;
    int s1=-1,s2=-1;
    int destination;
    bool v1=0,v2=0;
    bool done;
    int ROB_ID;
};
struct ReorderBuffer
{
    int ID;
    string type;
    string OP;
    int s1,s2;
    int destination;
};
class pipeline
{
private:
    void fetch();
    void execute();
    void commit();
    void updateInst(instruction& t,const int& ind);
    void showStats();
    time_t start=time(NULL),end=time(NULL);
    deque <ReorderBuffer> ROB;
    deque <dab> IQ;
    RegFile r;
    statistic stat;
    int count=-FETCH_WIDTH,fatherCounter=0;
    int jmp;
public:
    pipeline();
    pipeline(ifstream& f);
};