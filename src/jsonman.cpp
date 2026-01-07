#include "jsonman.h"

Json::Json(){
    file.open("data.json");
}

Json::~Json(){
    file.close();
}