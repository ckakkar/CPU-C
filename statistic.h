#include "instruction.cpp"

class statistic
{
private:
    int clk;
    vector <int> throughput, latency;
public:
    statistic();

    void updateCLK();
    void updateLatency(const double& time);
    void updateThroughput(const int& lat);
    void print_stats();
};