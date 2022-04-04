//
//  main.cpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 16.12.2021.
//

#include <cstdlib>

#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <openssl/md5.h>

#include "HashList/HashList.hpp"
#include "MacLogger.hpp"
#include "UnixLogger.hpp"
#include "Controller.hpp"
#include "TestContent.hpp"
#include "Content.hpp"
#include "DebugControllerDecorator.hpp"
#include "TestNetwork.hpp"
#include "HashManager.hpp"

const int kAgentCount = 5; // Wat if we have more than 22 nodes?
const int kTestsCount = 1;

int main() 
{

    auto* logger = new UnixLogger();
    auto* hash_manager = new HashManager(logger);
    auto* network = new TestNetwork(logger, kAgentCount);
    auto* content = new Content(logger, "../../test_content");
    auto* controller = new Controller(logger, network, hash_manager);
    auto* d_controller = new DebugControllerDecorator(controller);

    for(int i = 0; i < kTestsCount; i++) {
        d_controller->BuildContent(content);
    }
    
    return 0;
}
