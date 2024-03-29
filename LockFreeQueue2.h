/*======================================================
    > File Name: lockFreeQueue.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2016年03月27日 星期日 10时29分56秒
 =======================================================*/
#pragma once

#include <atomic>
#include <string>
#include <iostream>
#include <list>
#include <stdio.h>

template <typename T>
class LinkList
{
    public:
        T data;
        LinkList<T> *next;
};

template <typename T>
class LockFreeQueue
{
    public:
        LockFreeQueue();
        //入队
        void push_back(T t);
        //出队
        T pop_front(void);
        //判队空
        bool isEmpty(void);
    private:
        LinkList<T> *head_;
        LinkList<T> *tail_;
        std::atomic_int elementNumbers_;       
};

template <typename T>
LockFreeQueue<T>::LockFreeQueue()
    :head_(NULL),
    tail_(new LinkList<T>),
    elementNumbers_(0)
{
    head_ = tail_;
    tail_->next = NULL;     
}

template <typename T>
void LockFreeQueue<T>::push_back(T t)
{
    auto newVal = new LinkList<T>;
    newVal->data = t;
    newVal->next = NULL;

    LinkList<T> *p;
    do
    {
        //此操作暂时可删除，之后会跟新
        p = tail_;
    }while(!__sync_bool_compare_and_swap(&tail_->next,NULL,newVal));

    //移动tail_
    __sync_bool_compare_and_swap(&tail_,tail_,newVal);
    elementNumbers_++;
}

template <typename T>
T LockFreeQueue<T>::pop_front()
{
    LinkList<T> *p;
    
    do
    {
        //获取第一个节点快照
        p = head_->next;
        if(!p)
        {
            return 0;    
        }
    }while(!__sync_bool_compare_and_swap(&head_->next,p,p->next));
    elementNumbers_--;
    return p->data;   
}

template <typename T>
bool LockFreeQueue<T>::isEmpty()
{
    if(elementNumbers_ == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
