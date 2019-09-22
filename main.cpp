#include <iostream>
#include "Graph.hpp"

using namespace std;

int main()
{
    int n=6;
    Graph<int> graph(n);
    set<int> edgeInput[n];

    //有权无向图
    //测试最小生成树的Prim算法和Kruskal算法
    graph.Insert(0, 1, 6);
    graph.Insert(0, 2, 1);
    graph.Insert(0, 3, 5);
    graph.Insert(1, 0, 6);
    //graph.Insert(1, 2, 5);
    graph.Insert(1, 4, 3);
    graph.Insert(2, 0, 1);
    //graph.Insert(2, 1, 5);
    //graph.Insert(2, 3, 5);
    graph.Insert(2, 4, 6);
    //graph.Insert(2, 5, 4);
    graph.Insert(3, 0, 5);
    //graph.Insert(3, 2, 5);
    graph.Insert(3, 5, 2);
    graph.Insert(4, 1, 3);
    graph.Insert(4, 2, 6);
   //graph.Insert(4, 5, 6);
    //graph.Insert(5, 2, 4);
    graph.Insert(5, 3, 2);
    //graph.Insert(5, 4, 6);


    //    //测试深度优先遍历
    cout<<"DFS:";
    graph.DFS();
    cout<<endl;

//    //测试宽度优先遍历
    cout<<"BFS:";
    graph.BFS();
    cout<<endl;

    return 0;
}
