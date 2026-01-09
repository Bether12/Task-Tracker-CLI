#include<iostream>
#include<fstream>
#include "../include/jsonman.h"

int main(int argc, char* argv[]){
    //This conditional block makes sure enough commands are passed to the CLI
    if(argc<2){
        std::cout<<"Enter at least 2 commands, or read the README.md"<<std::endl;
        return 1;
    }
    std::vector<Task> tasks;//Task will be stored and processed through this vector
    Task taskHolder;//A generic Task object for pushing tasks to the vector
    Json file;
    file.getData(tasks);
    int numberOfTasks=tasks.size();//To be able to know which id the next task will have

    if (argv[1]=="add"){
        taskHolder.id=++numberOfTasks;
        taskHolder.description=argv[2];
        taskHolder.createdAt="";
        taskHolder.updatedAt="";
        tasks.push_back(taskHolder);
        std::cout<<"Task added successfully (ID:"<<taskHolder.id<<')'<<std::endl;
    }else if (argv[1]=="update"){
        /* code */
    }else if (argv[1]=="delete"){
        /* code */
    }else if (argv[1]=="mark-in-progress"){
        /* code */
    }else if (argv[1]=="mark-done"){
        /* code */
    }else if (argv[1]=="list"){
        /* code */
    }else{
        std::cerr<<"Unrecognized command, read README.md for a list of accepted commands";
    }
    
    

    return 0;
}