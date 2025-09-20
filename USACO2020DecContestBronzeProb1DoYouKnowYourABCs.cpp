#include <iostream>
#include <queue>
#include <vector>

using namespace std;
int main()
{
    priority_queue<int, vector<int>, greater<int>> minHeap;
    int tem;
    for(int i=0;i<7;i++)
    {
        cin >> tem;
        minHeap.push(tem);
    }
    int a,b,c;
    a = minHeap.top();
    minHeap.pop();  
    b = minHeap.top();
    minHeap.pop();  
    if(minHeap.top()==a+b)
    {
        minHeap.pop();
    }
    c = minHeap.top();
    minHeap.pop(); 
    cout << a << " " << b << " " << c;
    return 0;
}