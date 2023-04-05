// Load Balance with Round Robin
// Yuchuan Wang
// yuchuan.wang@gmail.com

#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

class LoadBalanceRoundRobin
{
public: 
    LoadBalanceRoundRobin()
    {
        current = -1;
    }

    ~LoadBalanceRoundRobin()
    {
    }

    bool AddServer(const std::string& srv)
    {
        servers.push_back(srv);
        return true;
    }

    // Simulate a new request
    bool NextRequest()
    {
        if(servers.empty())
        {
            std::cout << "Please add servers first. " << std::endl;
            return false; 
        }

        // Move to next server
        current = (current + 1) % servers.size();
        // Update stats
        stats[servers[current]]++;

        return true; 
    }

    void PrintStats() const
    {
        std::cout << "Server Hit stats with round robin: ";
        for(auto x : stats)
        {
            std::cout << std::endl;
            std::cout << x.first << ": " << x.second;
        }
        std::cout << std::endl;
    }

private:
    // The servers to be balanced
    std::vector<std::string> servers; 
    // Index of server hit
    int current;
    // Stats, key is the server, value is the hit count
    std::unordered_map<std::string, int> stats; 
};
