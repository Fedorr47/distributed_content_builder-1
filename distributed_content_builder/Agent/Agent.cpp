//
//  Agent.cpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 16.12.2021.
//

#include <thread>
#include <algorithm>

#include "Agent.hpp"
#include "Queue.hpp"
#include "MacLogger.hpp"
#include "UnixLogger.hpp"
#include "TestNetwork.hpp"

Agent::Agent(int id, int count, char LoggerType /*= 'M'*/) :
    state_{ AgentStatus::STATE_AVAILABLE },
    identity_{id},
    count_{ count }
{
    switch (LoggerType)
    {
    case 'M':
        logger_ = std::make_unique<MacLogger>();
        break;
    case 'U':
        logger_ = std::make_unique<UnixLogger>();
        break;
    default:

        break;
    }
}

void Agent::DoTask(ITask* job) {
    auto payload = [](ITask* job, Agent* agent){
        agent->state_ = AgentStatus::STATE_BUSY;
        std::system("pwd");
        job->SetStatus(ITask::TaskStatus::TASK_DONE);
        agent->state_ = AgentStatus::STATE_TASK_COMPLETE;
    };
    std::thread thread(payload, job, this);
    thread.detach();
}

std::vector<IAgent*> Agent::GetAvailableAgents() {
    return GenerateAgents(count_); // TODO: Replace to INetwork->GetAvailableAgents
}

double Agent::BuildContent(int content_size) {
    return 1;
}

std::vector<IAgent*> Agent::GenerateAgents(int count) {
    std::vector<IAgent*> Agents(count);
    std::generate(Agents.begin(), Agents.end(), [&, counter = -1]() mutable { ++counter; return new Agent(counter, count); });
    return Agents;
}
