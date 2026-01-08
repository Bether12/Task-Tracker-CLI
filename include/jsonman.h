#ifndef TASK_JSONMAN_H_
#define TASK_JSONMAN_H_
#include<fstream>
#include<iostream>
#include<vector>
#include "task.h"

class Json{
    std::fstream file;
    public:
        Json();
        void getData(std::vector<Task> vector);
        void setData(std::vector<Task> vector);
        ~Json();
};

#endif TASK_JSONMAN_H_