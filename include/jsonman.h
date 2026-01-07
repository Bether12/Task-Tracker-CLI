#ifndef TASK_JSONMAN_H_
#define TASK_JSONMAN_H_
#include<fstream>
#include<iostream>
#include<vector>

class Json{
    std::fstream file;
    public:
        Json();
        void getData();
        void setData();
        ~Json();
};

#endif TASK_JSONMAN_H_