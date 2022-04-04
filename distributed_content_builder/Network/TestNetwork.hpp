//
//  TestNetwork.hpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 20.01.2022.
//

#ifndef TestNetwork_hpp
#define TestNetwork_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

#include "Interfaces.hpp"
#include "ILogger.hpp"
#include "INetwork.hpp"
#include "IRemoteAgent.hpp"
#include "RemoteAgent.hpp"

class Agent;

class TestNetwork: public INetwork {
public:
    ILogger* logger_;
    int agent_count_;
public:
    TestNetwork(ILogger *logger, int agent_count)
        :logger_(logger)
        ,agent_count_(agent_count){}
    
    std::vector<IAgent*> GetAvailableAgents() {
        std::vector<IAgent*> remote_agents(agent_count_);
        std::generate(remote_agents.begin(), remote_agents.end(), 
            [&, counter = -1]() mutable { ++counter; return new RemoteAgent(counter, "../../test_content/agents/"); });
        return remote_agents;
    }
    
    bool SendTaskToRemoteAgent(IAgent*target_agent, ITask *task) {
        logger_->LogDebug("[Network]: Sending task to agent[" + std::to_string(target_agent->id_) + "]");
        target_agent->DoTask(task);
        return true;
    }
    
    IRemoteAgent::AgentStatus CheckAgentStatus(IAgent *target_agent) {
        return target_agent->state_;
    }
    
    void CollectTaskResult(IAgent *target_agent){
        return;
    }

    std::vector<std::string> CollectExistingFiles(std::vector<std::string> content_hashes, std::vector<IAgent*> agents){
        std::vector<std::string> existing_hashes;
        for (IAgent* agent : agents) {
            std::vector<std::string> existing_agent_hashes = static_cast<IRemoteAgent*>(agent)->CheckHashes(content_hashes);
            for (auto hash: existing_agent_hashes) {
                if (std::find(existing_hashes.begin(), existing_hashes.end(), hash) == existing_hashes.end()){
                    existing_hashes.push_back(hash);
                }
            }
        }
        return existing_hashes;
    };
};
#endif /* TestNetwork_hpp */
