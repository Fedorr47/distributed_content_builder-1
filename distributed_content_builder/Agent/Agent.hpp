//
//  Agent.hpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 16.12.2021.
//

#ifndef Agent_hpp
#define Agent_hpp

#include <stdio.h>
#include <memory>

#include "ILogger.hpp"
#include "Interfaces.hpp"

class Queue;
class TaskCompress;

class Agent: public IAgent {  
    AgentStatus state_;
    int identity_;
    int count_;
    std::unique_ptr<ILogger> logger_;
public:
    Agent(int id, int count, char LoggerType = 'M');
    
    void DoTask(ITask* job);
    std::vector<IAgent*> GetAvailableAgents() override;
    double BuildContent(int content_size);
    
private:
    std::vector<IAgent*> Agent::GenerateAgents(int count);
};

#endif /* Agent_hpp */
