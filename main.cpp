#include<iostream>

int main(int argc, char* argv[]){
    if(argc>2){
        std::cout<<argv[1]<<' '<<argv[2];
    }else{
        std::cout<<"Enter at least 2 commands, or read the README.md"<<std::endl;
    }
    return 0;
}