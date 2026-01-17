#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "../include/jsonman.h"

std::string getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_c);
    
    //(YYYY-MM-DD HH:MM:SS)
    std::stringstream ss;
    ss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
};

Task* findTaskById(std::vector<Task> vector, int id){
    Task* taskId;
    for(auto &task: vector){
        if(task.id==id) return &task;
    }
    return nullptr;
}

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
    int numberOfTasks=tasks.size();//To be able to know if the vector is empty
    int maxId=0;
    if(numberOfTasks!=0){
        for(const auto task:tasks){
            if(maxId<task.id){
                maxId=task.id;
            }
        }
    }

    if (argc>=3 && std::string(argv[1])=="add" && !std::string(argv[2]).empty()){
        if(numberOfTasks==0){
            taskHolder.id=1;
        }else{
            taskHolder.id=maxId + 1;
        }
        taskHolder.description=argv[2];
        taskHolder.status="todo";
        taskHolder.createdAt=getCurrentTime();
        taskHolder.updatedAt=taskHolder.createdAt;
        tasks.push_back(taskHolder);
        std::cout<<"Task added successfully (ID:"<<taskHolder.id<<')'<<std::endl;
    }else if (argc>3 && std::string(argv[1])=="update" && !std::string(argv[2]).empty() && !std::string(argv[3]).empty()){
        int idToUpdate = std::stoi(argv[2]);
        if (numberOfTasks==0){
            std::cerr<<"There are no tasks in your list"<<std::endl;
            return 1;
        }
        if(idToUpdate>0){
            Task* targetTask = findTaskById(tasks, idToUpdate);
            if(targetTask){
                targetTask->description=argv[3];
                targetTask->updatedAt=getCurrentTime();
            }else{
                std::cerr<<"Such ID does not exist"<< '\n';
            }
        }else{
            std::cerr <<"ID must be greater than 0"<< '\n';
        }
    
    }else if (argc==3 && std::string(argv[1])=="delete" && !std::string(argv[2]).empty()){
        int idToDelete = std::stoi(argv[2]);
        if (numberOfTasks==0){
            std::cerr<<"There are no tasks in your list"<<std::endl;
            return 1;
        }
        if(idToDelete>0){
            bool found=false;
            for(auto task=tasks.begin(); task != tasks.end(); ++task){
                if(task->id==idToDelete){
                    tasks.erase(task);
                    found=true;
                    break;
                }
            }if(!found) std::cerr <<"Such ID does not exist"<< '\n';
        }else{
            std::cerr <<"ID must be greater than 0"<< '\n';
        }
    }else if (argc==3 && std::string(argv[1])=="mark-in-progress" && !std::string(argv[2]).empty()){
        int idToUpdate = std::stoi(argv[2]);
        if (numberOfTasks==0){
            std::cerr<<"There are no tasks in your list"<<std::endl;
            return 1;
        }
        if(idToUpdate>0){
            Task* targetTask = findTaskById(tasks, idToUpdate);
            if(targetTask){
                targetTask->status=argv[3];
                targetTask->updatedAt=getCurrentTime();
            }else{
                std::cerr<<"Such ID does not exist"<< '\n';
            }
        }else{
            std::cerr <<"ID must be greater than 0"<< '\n';
        }
    }else if (argc==3 && std::string(argv[1])=="mark-done" && !std::string(argv[2]).empty()){
        int idToUpdate = std::stoi(argv[2]);
        if (numberOfTasks==0){
            std::cerr<<"There are no tasks in your list"<<std::endl;
            return 1;
        }
        if(idToUpdate>0){
            Task* targetTask = findTaskById(tasks, idToUpdate);
            if(targetTask){
                targetTask->status=argv[3];
                targetTask->updatedAt=getCurrentTime();
            }else{
                std::cerr<<"Such ID does not exist"<< '\n';
            }
        }else{
            std::cerr <<"ID must be greater than 0"<< '\n';
        }
    }else if (std::string(argv[1])=="list"){
        if(argc==3 && std::string(argv[2])=="todo"){
            if (numberOfTasks==0){
                std::cerr<<"There are no tasks in your list"<<std::endl;
                return 1;
            }
            bool found=false;
            for(auto &task : tasks){
                if(task.status=="todo"){
                    found=true;
                    std::cout<<"ID:"<<task.id<<" Description:"<<task.description<<" Status:"<<task.status<<" Created At:"<<task.createdAt<<" Updated At:"<<task.updatedAt<<std::endl;
                }else if (!found){
                    std::cerr<<"There are no todo tasks in your list"<<std::endl;
                }
            }
        }else if(argc==3 && std::string(argv[2])=="done"){
            if (numberOfTasks==0){
                std::cerr<<"There are no tasks in your list"<<std::endl;
                return 1;
            }
            bool found=false;
            for(auto &task : tasks){
                if(task.status=="done"){
                    found=true;
                    std::cout<<"ID:"<<task.id<<" Description:"<<task.description<<" Status:"<<task.status<<" Created At:"<<task.createdAt<<" Updated At:"<<task.updatedAt<<std::endl;
                }else if (!found){
                    std::cerr<<"There are no done tasks in your list"<<std::endl;
                } 
            }
        }else if(argc==3 && std::string(argv[2])=="in-progress"){
            if (numberOfTasks==0){
                std::cerr<<"There is no tasks in your list"<<std::endl;
                return 1;
            }
            bool found=false;
            for(auto &task : tasks){
                if(task.status=="in-progress"){
                    found=true;
                    std::cout<<"ID:"<<task.id<<" Description:"<<task.description<<" Status:"<<task.status<<" Created At:"<<task.createdAt<<" Updated At:"<<task.updatedAt<<std::endl;
                }else if (!found){
                    std::cerr<<"There are no in-progress tasks in your list"<<std::endl;
                } 
            }
        }else{
            if (numberOfTasks==0){
                std::cerr<<"There are no tasks in your list"<<std::endl;
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