#include<iostream>
#include<fstream>
#include "../include/jsonman.h"

int main(int argc, char* argv[]){
    //This conditional block makes sure enough commands are passed to the CLI
    if(argc>2){
        std::cout<<argv[1]<<' '<<argv[2];
    }else{
        std::cout<<"Enter at least 2 commands, or read the README.md"<<std::endl;
    }

    std::vector<Task> tasks;//Task will be stored and processed through this vector

    Json file;
    file.getData(tasks);
    return 0;
}