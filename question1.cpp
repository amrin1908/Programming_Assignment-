/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

queue<int>q; //Global queue to append data
mutex m;
int max_size=5; // max possible size of queue
void producer(int id)
{
    if(q.size()<max_size)
    {
        int data=rand()%10;
        cout<<"Producer "<<id<<" produced data="<<data<<endl;
        lock_guard<mutex> lock(m);
        q.push(data);
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    else{
       m.unlock();
       return;
    }

}

void consumer_thread()
{
    while(1){
        lock_guard<mutex> lock(m);
        if(!q.empty()){
            int n=q.front();
            cout<<"Consumed data="<<n<<endl;
            q.pop();
            this_thread::sleep_for(chrono::milliseconds(100));
            
        }
        else{
            m.unlock();
            this_thread::yield();
            continue;
        }
    }
}


int main()
{
    vector<thread> producers;
    for (int i = 0; i< 4; ++i)
    {
        producers.emplace_back(producer, i);
    }

    thread consumer(consumer_thread);

    for (auto& thread : producers)
    {
        thread.join();
    }

    consumer.join();

    return 0;
}

