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
    for(int i=0;i<content.length()-1;i=Close){//content.length()-1 because there is no need to process the last ]
        startIndex = content.find(':', Open)+2;
        endIndex = content.find(',', startIndex);
        int j =0;
        while(j<=4){
            switch (j)
            {
            case 0:
                vector[numberOfTasks].id=std::stoi(content.substr(startIndex, endIndex - startIndex));
                startIndex = content.find(':', endIndex)+2;
                endIndex = content.find(',', startIndex);
                break;
            case 1:
                vector[numberOfTasks].description=content.substr(startIndex,endIndex - startIndex);
                vector[numberOfTasks].description.erase(vector[numberOfTasks].description.length()-1,1);
                vector[numberOfTasks].description.erase(0,1);
                startIndex = content.find(':', endIndex)+2;
                endIndex = content.find(',', startIndex);
                break;
            case 2:
                vector[numberOfTasks].createdAt=content.substr(startIndex, endIndex - startIndex);
                vector[numberOfTasks].createdAt.erase(vector[numberOfTasks].createdAt.length()-1,1);
                vector[numberOfTasks].createdAt.erase(0,1);
                startIndex = content.find(':', endIndex)+2;
                if (content.find(',', startIndex)==content.npos){
                    endIndex = content.find('}', startIndex);
                }else{
                    endIndex = content.find(',', startIndex);
                }
                break;
            case 3: 
                vector[numberOfTasks].updatedAt=content.substr(startIndex, endIndex - startIndex);
                vector[numberOfTasks].updatedAt.erase(vector[numberOfTasks].updatedAt.length()-1,1);
                vector[numberOfTasks].updatedAt.erase(0,1);
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
}

Json::~Json(){
    file.close();
}