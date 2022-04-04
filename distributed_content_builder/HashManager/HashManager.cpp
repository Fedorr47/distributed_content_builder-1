//
// Created by Евгений Курятов on 10.03.2022.
//

#include <memory>
#include <openssl/md5.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "HashManager.hpp"
#include "HashList.hpp"

std::vector<std::string> HashManager::GetArtifactsFromHashlist(HashList* local_hashes, std::vector<std::string> requested_hashes){
    std::vector<std::string> existing_files;
    for (const std::string& hash : requested_hashes) {
        for (const FileHash& file : local_hashes->hash_list_){
            if (file.file_hash_ == hash) {
                existing_files.push_back(file.file_hash_);
                logger_->LogDebug("[HashManager]: Found on agent: \n-- File: " + file.file_path_ + "\n-- Hash: " + file.file_hash_);
                break;
            }
        }
    }
    return existing_files;
}

std::string HashManager::GenerateFileHash(std::string path) 
{
    unsigned char result[MD5_DIGEST_LENGTH];

    std::filesystem::path path_file(path);
    std::ifstream file_stream(path_file, std::ios_base::binary);
    if (!file_stream.is_open())
    {
        exit(-1);
    }

    size_t file_buffer_size = std::filesystem::file_size(path_file);
    if (!file_buffer_size)
    {
        exit(-1);
    }
    
    std::vector<char> file_buffer(file_buffer_size);
    file_stream.read(file_buffer.data(), file_buffer_size);

    MD5((unsigned char*)file_buffer.data(), file_buffer_size, result);

    return StringFromBuffer(result);
}

std::string HashManager::StringFromBuffer(unsigned char* md) {
    std::string hash_result;
    for(int i=0; i < MD5_DIGEST_LENGTH; i++) {

        int size_s = std::snprintf( nullptr, 0, "%02x", md[i] ) + 1; // Extra space for '\0'
        if( size_s <= 0 ){ logger_->LogError( "Error during formatting." ); }
        auto size = static_cast<size_t>( size_s );
        std::unique_ptr<char[]> buf( new char[ size ] );
        std::snprintf( buf.get(), size, "%02x", md[i] );

        hash_result += std::string( buf.get(), buf.get() + size - 1 );
    }
    return hash_result;
}

