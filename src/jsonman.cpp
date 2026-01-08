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

void Json::getData(std::vector<Task> vector){
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
    std::string id;
    std::string description;
    std::string createdAt;
    std::string updatedAt;
    for(int i=0;i<content.length()-1;i=Close){//content.length()-1 because there is no need to process the last ]
        startIndex = content.find(':', Open)+2;
        endIndex = content.find(',', startIndex);
        int j =0;
        while(j<=4){
            switch (j)
            {
            case 0:
                id=content.substr(startIndex, endIndex - startIndex);
                startIndex = content.find(':', endIndex)+2;
                endIndex = content.find(',', startIndex);
                break;
            case 1:
                description=content.substr(startIndex,endIndex - startIndex);
                description.erase(description.length()-1,1);
                description.erase(0,1);
                startIndex = content.find(':', endIndex)+2;
                endIndex = content.find(',', startIndex);
                break;
            case 2:
                createdAt=content.substr(startIndex, endIndex - startIndex);
                createdAt.erase(createdAt.length()-1,1);
                createdAt.erase(0,1);
                startIndex = content.find(':', endIndex)+2;
                if (content.find(',', startIndex)==content.npos){
                    endIndex = content.find('}', startIndex);
                }else{
                    endIndex = content.find(',', startIndex);
                }
                break;
            case 3: 
                updatedAt=content.substr(startIndex, endIndex - startIndex);
                updatedAt.erase(updatedAt.length()-1,1);
                updatedAt.erase(0,1);
                break;
            default:
                Open=content.find('{', Close); 
                Close=content.find('}', Open);
                break;
            }
            j++;  
        }
        numberOfTasks++;
    }
    std::cout<<id<<'\n'<<description<<'\n'<<createdAt<<'\n'<<updatedAt<<'\n';
}

Json::~Json(){
    file.close();
}