// Load Balance with Random
// Yuchuan Wang
// yuchuan.wang@gmail.com

#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

class LoadBalanceRandom
{
public: 
    LoadBalanceRandom()
    {
    }

    ~LoadBalanceRandom()
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

        // Pickup a random server
        int current = rand() % servers.size();
        // Update stats
        stats[servers[current]]++;

        return true; 
    }

    void PrintStats() const
    {
        std::cout << "Server Hit stats with random: ";
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
    // Stats, key is the server, value is the hit count
    std::unordered_map<std::string, int> stats; 
};
