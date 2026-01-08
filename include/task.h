#ifndef TASK_TASK_H_
#define TASK_TASK_H_
#include<string>

struct Task
{
    int id;
    std::string description;
    std::string status;
    std::string createdAt;
    std::string updatedAt;
};

#endif