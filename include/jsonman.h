#ifndef TASK_JSONMAN_H_
#define TASK_JSONMAN_H_
#include<fstream>
#include<iostream>
#include<vector>
#include<cstdio>
#include "task.h"

class Json{
    public:
        Json();
        void trim(std::string &s);
        void getData(std::vector<Task> &vector);
        void setData(std::vector<Task> &vector);
        ~Json();
};

#endif