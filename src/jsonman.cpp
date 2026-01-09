#include "../include/jsonman.h"

Json::Json(){
    file.open("data.json", std::ios::in | std::ios::out);
    if(!file.is_open()){
        file.open("data.json", std::ios::out);
        file << "[ ]";
        file.close();

        file.open("data.json", std::ios::in | std::ios::out);
    }
}

void Json::getData(std::vector<Task> &vector){
    std::string holder;
    std::string content;

    while(std::getline(file, holder)){
        content += holder;
    }
    holder="";
    std::cout<<content<<"\n";

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
        while(j<=4){
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
                task.createdAt=content.substr(startIndex, endIndex - startIndex);
                task.createdAt.erase(task.createdAt.length()-1,1);
                task.createdAt.erase(0,1);
                startIndex = content.find(':', endIndex)+2;
                endIndex = content.find('}', startIndex);
                break;
            case 3: 
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
        std::cout<<task.id<<'\n';
        std::cout<<task.description<<'\n';
        std::cout<<task.createdAt<<'\n';
        std::cout<<task.updatedAt<<'\n';
        vector.push_back(task);
    }
}

void Json::setData(std::vector<Task> &vector){
    file<<"[";

    for (const auto &task: vector){
        file<<"{";
        file<<"\"id\": "<<task.id<<",";
        file<<"\"description\": "<<task.description<<",";
        file<<"\"createdAt\": "<<task.createdAt<<",";
        file<<"\"updatedAt\": "<<task.updatedAt;
        file<<"}";
    }

    file<<"]";
}

Json::~Json(){
    file.close();
}