#include "../include/jsonman.h"

Json::Json(){}

 void Json::trim(std::string &s){
        if(s.empty()){return;}
        auto start=s.find_first_not_of(" \"");
        if(start==std::string::npos){s.clear(); return;}
        auto end=s.find_last_not_of(" \"");
        s=s.substr(start, end-start + 1);
    }

void Json::getData(std::vector<Task> &vector){
    std::ifstream file;
    file.open("data.json", std::ios::in);
    if(!file.is_open()){
        std::cerr<<"Error while trying to read the data"<<std::endl;
    }

    std::string holder;
    std::string content;

    while(std::getline(file, holder)){
        content += holder;
    }
    file.close();
    holder="";
    if(content.empty() || content=="[]"){
        return;
    }
    
    //algorithm to find each piece of data
    int Open=content.find_first_of('{'); 
    int index=0;

    while (Open!=std::string::npos){
        Task task;
        index=content.find("\"id\"", Open);
        if(index!=std::string::npos){
            index=content.find(':', index) + 1;
        }else{
            std::cerr<<"Error while reading the data"<<std::endl;
            break;
        }

        try{
            task.id = std::stoi(content.substr(index, content.find(',', index)-index));
        }catch(const std::invalid_argument &e){
            std::cerr<<"Invalid ID format, ID is not a number"<<std::endl;
            Open=content.find('{', index);
            continue;
        }catch(const std::out_of_range &e){
            std::cerr<<"ID value is too large "<<std::endl;
            Open=content.find('{', index);
            continue;
        }
        
        index=content.find(':', content.find("\"description\"", index)) + 1;

        task.description=content.substr(index, content.rfind(',', content.find("\"status\"", index)) - index);
        trim(task.description);
        index=content.find(':', content.find("\"status\"", index)) + 1;

        task.status=content.substr(index, content.find(',', index)-index);
        trim(task.status);
        index=content.find(':', content.find("\"createdAt\"", index)) + 1;

        task.createdAt=content.substr(index, content.find(',', index)-index);
        trim(task.createdAt);
        index=content.find(':', content.find("\"updatedAt\"", index)) + 1;

        task.updatedAt=content.substr(index, content.find('}', index)-index);
        trim(task.updatedAt);

        vector.push_back(task);
        Open=content.find('{', index);
    }
}

void Json::setData(std::vector<Task> &vector){
    std::ofstream tempFile;
    std::string fileName = "data.json";
    std::string tempFileName = fileName+".temp";
    tempFile.open(tempFileName);
    if(!tempFile.is_open()){
        std::cerr<<"Error while trying to save the data"<<std::endl;
    }
    tempFile<<"[";

    for (auto &task: vector){
        tempFile<<"{";
        tempFile<<"\"id\": "<<task.id<<",";
        tempFile<<"\"description\": "<<'\"'+task.description+'\"'<<",";
        tempFile<<"\"status\": "<<'\"'+task.status+'\"'<<",";
        tempFile<<"\"createdAt\": "<<'\"'+task.createdAt+'\"'<<",";
        tempFile<<"\"updatedAt\": "<<'\"'+task.updatedAt+'\"';
        tempFile<<"}";
        if(!(&task==&vector.back())){
            tempFile<<",";
        }else{break;}
    }
    tempFile<<"]";
    tempFile.close();
    if(tempFile.fail()){
        std::remove(tempFileName.c_str());
        std::cerr<<"Error, new data could not be saved"<<std::endl;
    }else{
        std::remove(fileName.c_str());
        if(std::rename(tempFileName.c_str(), fileName.c_str()) !=0){
            perror("Error while trying to create data.json");
        }
    }
}

Json::~Json(){}