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

    if (argc>=3 && std::string(argv[1])=="add" && !std::string(argv[2]).empty()){
        taskHolder.id=++numberOfTasks;
        taskHolder.description=argv[2];
        taskHolder.status="todo";
        taskHolder.createdAt="1";
        taskHolder.updatedAt="2";
        tasks.push_back(taskHolder);
        std::cout<<"Task added successfully (ID:"<<taskHolder.id<<')'<<std::endl;
    }else if (argc>3 && std::string(argv[1])=="update" && !std::string(argv[2]).empty() && !std::string(argv[3]).empty()){
        int idToUpdate = std::stoi(argv[2]);
        if (numberOfTasks==0){
            std::cerr<<"There is no tasks in your list"<<std::endl;
            return 1;
        }
        if(idToUpdate>0){
            for(auto &task: tasks){
                if(task.id==idToUpdate){
                    task.description=std::string(argv[3]);
                    break;
                }else if(&task==&tasks.back() && task.id!=idToUpdate){
                    std::cerr <<"Such ID does not exist"<< '\n';
                }
            }
        }else{
            std::cerr <<"ID must be greater than 0"<< '\n';
        }
    
    }else if (argc==3 && std::string(argv[1])=="delete" && !std::string(argv[2]).empty()){
        int idToDelete = std::stoi(argv[2]);
        if (numberOfTasks==0){
            std::cerr<<"There is no tasks in your list"<<std::endl;
            return 1;
        }
        if(idToDelete>0){
            for(auto task=tasks.begin(); task != tasks.end(); ++task){
                if(task->id==idToDelete){
                    tasks.erase(task);
                    break;
                }else if(task==tasks.end() && task->id!=idToDelete){
                    std::cerr <<"Such ID does not exist"<< '\n';
                }
            }
        }else{
            std::cerr <<"ID must be greater than 0"<< '\n';
        }
    }else if (argc==3 && std::string(argv[1])=="mark-in-progress" && !std::string(argv[2]).empty()){
        int idToUpdate = std::stoi(argv[2]);
        if (numberOfTasks==0){
            std::cerr<<"There is no tasks in your list"<<std::endl;
            return 1;
        }
        if(idToUpdate>0){
            for(auto task=tasks.begin(); task != tasks.end(); ++task){
                if(task->id==idToUpdate){
                    task->status="in-progress";
                    break;
                }else if(task==tasks.end() && task->id!=idToUpdate){
                    std::cerr <<"Such ID does not exist"<< '\n';
                }
            }
        }else{
            std::cerr <<"ID must be greater than 0"<< '\n';
        }
    }else if (argc==3 && std::string(argv[1])=="mark-done" && !std::string(argv[2]).empty()){
        int idToUpdate = std::stoi(argv[2]);
        if (numberOfTasks==0){
            std::cerr<<"There is no tasks in your list"<<std::endl;
            return 1;
        }
        if(idToUpdate>0){
            for(auto task=tasks.begin(); task != tasks.end(); ++task){
                if(task->id==idToUpdate){
                    task->status="done";
                    break;
                }else if(task==tasks.end() && task->id!=idToUpdate){
                    std::cerr <<"Such ID does not exist"<< '\n';
                }
            }
        }else{
            std::cerr <<"ID must be greater than 0"<< '\n';
        }
    }else if (std::string(argv[1])=="list"){
        if(argc==3 && std::string(argv[2])=="todo"){
            if (numberOfTasks==0){
                std::cerr<<"There is no tasks in your list"<<std::endl;
                return 1;
            }
            for(auto &task : tasks){
                if(task.status=="todo"){
                    std::cout<<"ID:"<<task.id<<" Description:"<<task.description<<" Status:"<<task.status<<" Created At:"<<task.createdAt<<" Updated At:"<<task.updatedAt<<std::endl;
                }//need to implement a check for printed todo tasks 
            }
        }else if(argc==3 && std::string(argv[2])=="done"){
            if (numberOfTasks==0){
                std::cerr<<"There is no tasks in your list"<<std::endl;
                return 1;
            }
            for(auto &task : tasks){
                if(task.status=="done"){
                    std::cout<<"ID:"<<task.id<<" Description:"<<task.description<<" Status:"<<task.status<<" Created At:"<<task.createdAt<<" Updated At:"<<task.updatedAt<<std::endl;
                }//need to implement a check for printed done tasks 
            }
        }else if(argc==3 && std::string(argv[2])=="in-progress"){
            if (numberOfTasks==0){
                std::cerr<<"There is no tasks in your list"<<std::endl;
                return 1;
            }
            for(auto &task : tasks){
                if(task.status=="in-progress"){
                    std::cout<<"ID:"<<task.id<<" Description:"<<task.description<<" Status:"<<task.status<<" Created At:"<<task.createdAt<<" Updated At:"<<task.updatedAt<<std::endl;
                }//need to implement a check for printed todo tasks 
            }
        }else{
            if (numberOfTasks==0){
                std::cerr<<"There is no tasks in your list"<<std::endl;
                return 1;
            }
            for(auto &task : tasks){
                std::cout<<"ID:"<<task.id<<" Description:"<<task.description<<" Status:"<<task.status<<" Created At:"<<task.createdAt<<" Updated At:"<<task.updatedAt<<std::endl; 
            }
        }
    }else{
        std::cerr<<"Unrecognized or invalid command, read README.md for a list of accepted commands"<<std::endl;
    }
    
    file.setData(tasks);

    return 0;
}