#include<bits/stdc++.h>
using namespace std;
#include<experimental/filesystem>
//#include<filesystem>

namespace fs=experimental::filesystem;
mutex m;
atomic<int> no_of_files(0); //atomic library allows only one r/w operation at a time
atomic<int> no_of_dirs(0);

void count(const string& path){
    int no_of_local_files=0;
    int no_of_local_dirs=0;
    for(const auto& entry: fs::directory_iterator(path)){
        if(entry.is_regular_file()){
            ++no_of_local_files; //To minimise potential race conditions, we avoid post-increment operator which creates a temporary object
        }else if(entry.is_directory()){
            ++no_of_local_dirs;
            count(entry.path().string());
        }
    }
  //critical section
    lock_guard<mutex> lock(m);
    no_of_files+=no_of_local_files;
    no_of_dirs+=no_of_local_dirs;
    cout<< "Directory: "<<path<< "Total subdirectories: "<<no_of_dirs<<" "<<"Total files"<<no_of_files<<endl;
    cout<<endl;
}


int main(){
    string rootpath="C::/Users/mohamedthusthakeershahulhameed/Desktop/portfolio3";
    vector<thread>threads;
    for(const auto& entry: fs::directory_iterator(path)){
        if(entry.is_directory()){
            threads.emplace_back(count,entry.path().string());
        }
    }
    for(auto& thread:threads){
        thread.join();
    }
    cout<<"Total no of files="<<no_of_files<<endl;
    cout<<"Total no of subdirectories="<<no_of_dirs<<endl;
    return 0;
}
