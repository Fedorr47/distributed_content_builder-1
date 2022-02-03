//
//  INetwork.h
//  distributed_content_builder
//
//  Created by Евгений Курятов on 02.02.2022.
//

#ifndef INetwork_h
#define INetwork_h

#include "IRemoteAgent.h"

class INetwork {
public:
    virtual bool SendTaskToRemoteAgent(IRemoteAgent *target_agent, ITask *task) = 0;
    virtual IRemoteAgent::AgentStatus CheckAgentStatus(IRemoteAgent *target_agent) = 0;
    virtual void CollectTaskResult(IRemoteAgent *target_agent) = 0;
};

#endif /* INetwork_h */
