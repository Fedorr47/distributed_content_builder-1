//
// Created by Евгений Курятов on 17.02.2022.
//

#ifndef DISTRIBUTED_CONTENT_BUILDER_TASKCOMPRESS_PPH
#define DISTRIBUTED_CONTENT_BUILDER_TASKCOMPRESS_PPH

#include <string>
#include <thread>
#include <cstdlib>
#include <filesystem>

#include "ITask.hpp"
#include "HashManager.hpp"
#include "UnixLogger.hpp"

class TaskCompress: public ITask {
private:
    std::string executor_;
public:
    TaskCompress(std::string executor, std::string file_path) {
        status_ = TaskStatus::TASK_READY_FOR_BUILD;
        executor_ = executor;
        file_path_ = file_path;
        auto* logger = new UnixLogger();
        auto* hash_manager = new HashManager(logger);
        file_hash_ = hash_manager->GenerateFileHash(file_path);
        size_ = 0;
    }

    TaskStatus GetStatus(){
        return status_;
    }

    void SetStatus(TaskStatus new_status){
        status_ = new_status;
    }

    int GetSize(){
        return size_;
    }

    void Do(std::string result_dir) {
        auto file_path = std::filesystem::path(file_path_);
        std::filesystem::path result_dir_path(result_dir);

        result_dir_path += file_path;

        std::string exec_command = executor_ + " " + file_path_ + " " + result_dir_path.string();
        std::system(exec_command.c_str());
    }

//    std::string GetResultPath() {
//        return result_path_;
//    }
};

#endif //DISTRIBUTED_CONTENT_BUILDER_TASKCOMPRESS_PPH
