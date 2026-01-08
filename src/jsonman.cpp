#include "../include/jsonman.h"

Json::Json(){
    file.open("data.json", std::ios::in | std::ios::out);
    if(!file.is_open()){
        file.open("data.json", std::ios::out);
        file << "[ ]";
        file.close();

        file.open("data.json", std::ios::in | std::ios::out);
    }else{
        std::cerr<<"Error while trying to open the file data.json"<<std::endl;
    }
}

void Json::getData(std::vector<Task> vector){
    std::string holder;
    std::string content;

    while(std::getline(file, holder)){
        content += holder;
    }
    std::cout<<content<<"\n";
}

Json::~Json(){
    file.close();
}