//
//  RemoteAgent.hpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 03.02.2022.
//

#ifndef RemoteAgent_hpp
#define RemoteAgent_hpp

#include <stdio.h>

#include "Agent.hpp"
#include "IRemoteAgent.hpp"

class RemoteAgent: public IRemoteAgent {
public:
    std::string base_directory_;
public:
    RemoteAgent(int id, std::string base_dir);
    void DoTask(ITask* job) override;
    std::vector<std::string> CheckHashes(std::vector<std::string> hashes) override;
    std::vector<IAgent*> GetAvailableAgents() override { return std::vector<IAgent*>(); };
    double BuildContent(int content_size) override { return 0.0f; };
};

#endif /* RemoteAgent_hpp */
