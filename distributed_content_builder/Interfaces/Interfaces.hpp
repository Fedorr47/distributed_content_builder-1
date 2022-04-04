//
//  Interfaces.h
//  distributed_content_builder
//
//  Created by Евгений Курятов on 19.01.2022.
// 

#ifndef Interfaces_h
#define Interfaces_h

#include <string>
#include <vector>
#include "ITask.hpp"
#include "IHashManager.hpp"


// TODO: Split IAgent to IHost and IRemoteAgent
class IAgent {
public:
    enum class AgentStatus {
        STATE_AVAILABLE, STATE_BUSY, STATE_OFFLINE, STATE_TASK_COMPLETE
    };

    AgentStatus state_;
    int id_;
    ILogger* logger_;
    IHashManager* hash_manager_;
    
    virtual void DoTask(ITask* job) = 0;
    virtual std::vector<IAgent*> GetAvailableAgents() = 0;
    virtual double BuildContent(int content_size) = 0;
};


#endif /* Interfaces_h */
