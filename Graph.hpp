#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED

#include <iostream>
#include <set>
#include <queue>
#include <stack>
#include <string.h>

using namespace std;

//const int INT_MAX = 0x7fff ;

template <typename T>
struct ENode{
    int vertex;    //边的一端顶点，加上之后方便后面算法
    int adjvex;    //边的另一端顶点
    T weight;      //边的权值
    ENode<T> *next;

    ENode() { next=nullptr; }
    ENode(int vertex,int adjvertex,T w,ENode<T> *nextArc){
        this->vertex=vertex;
        adjvex=adjvertex;
        weight=w;
        next=nextArc;
    }
    operator T() const { return weight; }
    bool operator <(const ENode<T> &rhs) const{
        return this->weight > rhs.weight;//最小值优先
    }
};

template <typename T>
class Graph{            //邻接表的储存方式
private:
    ENode<T> **enodes;
    int n;              //顶点个数
    int edges;          //边的个数
    int connectedCount; //强连通分量个数
    int *id;            //由顶点索引的数组，存放顶点所属的连通分量标识符
    bool hasCycle;      //是否有环

    void DFS(int v,bool *visited);      //私有DFS，供递归调用
    void BFS(int v,bool *visited);      //私有BFS
public:
    Graph(int mSize);
    ~Graph();
    bool Exist(int u,int v) const;      //边u->v是否存在
    bool Insert(int u,int v, T w);      //插入边u->v
    bool Remove(int u,int v);           //删除边u->v
    void DFS();                         //公有接口，深度优先搜索
    void BFS();                         //公有接口，宽度优先搜索
    bool HasCycle();                    //判断是否有环

    void Dijkstra(int v0);              //迪杰特斯拉算法解决单源最短路径问题
    void Floyd();                       //弗洛伊德算法求所有顶点之间的最短路径
    T GetWeight(int u,int v);           //获得边u->v的权值
};

template <typename T>
Graph<T>::Graph(int mSize){
    n=mSize;
    edges=0;
    connectedCount=0;
    hasCycle=false;
    enodes=new ENode<T> *[n];
    id=new int[n];
    for(int i=0;i<n;i++){
        enodes[i]=nullptr;
        id[i]=0;
    }
}

template <typename T>
Graph<T>::~Graph(){
    ENode<T> *p,*q;
    for(int i=0;i<n;i++){
        p=enodes[i];
        while(p){
            q=p;
            p=p->next;
            delete[] q;
        }
    }
    delete[] enodes;
    delete[] id;
}

template <typename T>
bool Graph<T>::Exist(int u,int v) const {
    if(u<0 || v<0 || u>n-1 || v>n-1 || u==v){
        return false;       //输入参数无效
    }
    ENode<T> *p=enodes[u];
    while(p&&p->adjvex!=v){
        p=p->next;
    }
    if(p)
        return true;
    else
        return false;
}

template <typename T>
bool Graph<T>::Insert(int u,int v,T w){
    if(u<0 || v<0 || u>n-1 || v>n-1 || u==v){
        return false;       //输入参数无效
    }
    if(Exist(u,v)){
        cout<<"Duplicate"<<endl;
        return false;
    }
    else{
        //将新边结点插在由指针enodes[u]所指示的单链表最前面
//        ENode<T> *p = new ENode<T>(u,v,w,enodes[u]);
//        enodes[u]=p;

        //将新边结点插在由指针enodes[u]所指示的单链表最后面
        ENode<T> *q = enodes[u];
        ENode<T> *p = new ENode<T>(u,v,w,nullptr);
        if(q==nullptr){
            enodes[u] = new ENode<T>(u,v,w,nullptr);
        }
        else{
            while(q->next!=nullptr)
                q=q->next;
            q->next=p;
        }
        edges++;
        return true;
    }
}

template <typename T>
bool Graph<T>::Remove(int u,int v){
    if(u<0 || v<0 || u>n-1 || v>n-1 || u==v){
        return false;       //输入参数无效
    }
    ENode<T> *p=enodes[u];
    ENode<T> *q=nullptr;
    while(p&&p->adjvex!=v){
        q=p;
        p=p->next;
    }
    if(!p){
        cout<<"Not Exist."<<endl;
        return false;
    }
    if(p==enodes[u]){
        q=p;
        enodes[u]=p->next;
        delete q;
        edges--;
    }
    else{
        q->next=p->next;
        delete p;
        edges--;
    }
    return true;
}

//私有DFS，供递归调用
template <typename T>
void Graph<T>::DFS(int v,bool *visited){
    visited[v]=true;
    cout<<v<<" ";
    for(ENode<T> *w=enodes[v]; w ; w=w->next){
        if(!visited[w->adjvex]){
            DFS(w->adjvex,visited);
        }
    }
}
//公有接口，深度优先遍历
template <typename T>
void Graph<T>::DFS(){
    bool *visited=new bool[n];
    for(int i=0;i<n;i++){
        visited[i]=false;
    }
    for(int j=0;j<n;j++){
        if(!visited[j]){
            DFS(j,visited);
        }
    }
    delete[] visited;
}

//私有BFS
template <typename T>
void Graph<T>::BFS(int v, bool *visited) {
    visited[v]=true;
    cout<<v<<" ";
    queue<int> Q;
    Q.push(v);

    int s;
    while(!Q.empty()){
        s=Q.front();
        Q.pop();
        for(ENode<T> *w=enodes[s];w;w=w->next){
            if(!visited[w->adjvex]){
                visited[w->adjvex]=true;
                cout<<w->adjvex<<" ";
                Q.push(w->adjvex);
            }
        }
    }

}

//公有接口,宽度优先搜索
template <typename T>
void Graph<T>::BFS() {
    bool *visited = new bool[n];
    for(int i=0;i<n;i++){
        visited[i]=false;
    }
    for(int j=0;j<n;j++){
        if(!visited[j]){
            BFS(j,visited);
        }
    }
    delete[] visited;
}

template <typename T>
T Graph<T>::GetWeight(int u,int v){
    if(u==v)
        return 0;
    ENode<T> *p= enodes[u];
    while(p!=nullptr&&p->adjvex!=v){
        p=p->next;
    }
    if(p)
        return p->weight;
    else
        return INT_MAX;
}

#endif // GRAPH_HPP_INCLUDED
