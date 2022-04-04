//
//  IRemoteAgent.h
//  distributed_content_builder
//
//  Created by Евгений Курятов on 02.02.2022.
//

#ifndef IRemoteAgent_h
#define IRemoteAgent_h

#include "ITask.hpp"
#include "Interfaces.hpp"

class IRemoteAgent : public IAgent {
public:
    IRemoteAgent() : IAgent() {};
    virtual ~IRemoteAgent() {}
    virtual void DoTask(ITask* job) = 0;
    virtual std::vector<std::string> CheckHashes(std::vector<std::string> hashes) = 0;
};

#endif /* IRemoteAgent_h */
