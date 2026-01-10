#include "../include/jsonman.h"

Json::Json(){}

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
    holder="";
    if(content.empty() || content=="[]"){
        return;
    }

    //algorithm to find each piece of data
    int Open=content.find('{'); 
    int Close=content.find('}', Open);
    int startIndex=0;
    int endIndex=0;
    int numberOfTasks=0;
    for(int i=0;i<content.length()-1;i=Close){//content.length()-1 because there is no need to process the last ]
        startIndex = content.find(':', Open)+2;
        endIndex = content.find(',', startIndex);
        Task task;
        int j =0;
        while(j<=5){
            switch (j)
            {
            case 0:
                task.id=std::stoi(content.substr(startIndex, endIndex - startIndex));
                startIndex = content.find(':', endIndex)+2;
                endIndex = content.find(',', startIndex);
                break;
            case 1:
                task.description=content.substr(startIndex,endIndex - startIndex);
                task.description.erase(task.description.length()-1,1);
                task.description.erase(0,1);
                startIndex = content.find(':', endIndex)+2;
                endIndex = content.find(',', startIndex);
                break;
            case 2:
                task.status=content.substr(startIndex,endIndex - startIndex);
                task.status.erase(task.status.length()-1,1);
                task.status.erase(0,1);
                startIndex = content.find(':', endIndex)+2;
                endIndex = content.find(',', startIndex);
                break;
            case 3:
                task.createdAt=content.substr(startIndex, endIndex - startIndex);
                task.createdAt.erase(task.createdAt.length()-1,1);
                task.createdAt.erase(0,1);
                startIndex = content.find(':', endIndex)+2;
                endIndex = content.find('}', startIndex);
                break;
            case 4: 
                task.updatedAt=content.substr(startIndex, endIndex - startIndex);
                task.updatedAt.erase(task.updatedAt.length()-1,1);
                task.updatedAt.erase(0,1);
                break;
            default:
                Open=content.find('{', Close); 
                Close=content.find('}', Open);
                break;
            }
            j++;  
        }
        vector.push_back(task);
    }
    file.close();
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