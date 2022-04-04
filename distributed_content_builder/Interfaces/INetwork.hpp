//
//  INetwork.h
//  distributed_content_builder
//
//  Created by Евгений Курятов on 02.02.2022.
//

#ifndef INetwork_h
#define INetwork_h

#include "Interfaces.hpp"

class INetwork {
public:
    virtual std::vector<IAgent*> GetAvailableAgents() = 0;
    virtual bool SendTaskToRemoteAgent(IAgent*target_agent, ITask *task) = 0;
    virtual IAgent::AgentStatus CheckAgentStatus(IAgent*target_agent) = 0;
    virtual void CollectTaskResult(IAgent*target_agent) = 0;
    virtual std::vector<std::string> CollectExistingFiles(std::vector<std::string> content_hashes, std::vector<IAgent*> agents) = 0;
};

#endif /* INetwork_h */
