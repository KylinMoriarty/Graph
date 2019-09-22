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
    int vertex;    //�ߵ�һ�˶��㣬����֮�󷽱�����㷨
    int adjvex;    //�ߵ���һ�˶���
    T weight;      //�ߵ�Ȩֵ
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
        return this->weight > rhs.weight;//��Сֵ����
    }
};

template <typename T>
class Graph{            //�ڽӱ�Ĵ��淽ʽ
private:
    ENode<T> **enodes;
    int n;              //�������
    int edges;          //�ߵĸ���
    int connectedCount; //ǿ��ͨ��������
    int *id;            //�ɶ������������飬��Ŷ�����������ͨ������ʶ��
    bool hasCycle;      //�Ƿ��л�

    void DFS(int v,bool *visited);      //˽��DFS�����ݹ����
    void BFS(int v,bool *visited);      //˽��BFS
public:
    Graph(int mSize);
    ~Graph();
    bool Exist(int u,int v) const;      //��u->v�Ƿ����
    bool Insert(int u,int v, T w);      //�����u->v
    bool Remove(int u,int v);           //ɾ����u->v
    void DFS();                         //���нӿڣ������������
    void BFS();                         //���нӿڣ������������
    bool HasCycle();                    //�ж��Ƿ��л�

    void Dijkstra(int v0);              //�Ͻ���˹���㷨�����Դ���·������
    void Floyd();                       //���������㷨�����ж���֮������·��
    T GetWeight(int u,int v);           //��ñ�u->v��Ȩֵ
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
        return false;       //���������Ч
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
        return false;       //���������Ч
    }
    if(Exist(u,v)){
        cout<<"Duplicate"<<endl;
        return false;
    }
    else{
        //���±߽�������ָ��enodes[u]��ָʾ�ĵ�������ǰ��
//        ENode<T> *p = new ENode<T>(u,v,w,enodes[u]);
//        enodes[u]=p;

        //���±߽�������ָ��enodes[u]��ָʾ�ĵ����������
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
        return false;       //���������Ч
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

//˽��DFS�����ݹ����
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
//���нӿڣ�������ȱ���
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

//˽��BFS
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

//���нӿ�,�����������
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
