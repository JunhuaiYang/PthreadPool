# PthreadPool
A Thread Pool  Realized by Pthread

## 简述
使用pthread实现的简单线程池，可以通过源码学习线程池的基本原理

## 特性
* 使用C++开发
* 在创建时指定线程池中的线程数量  

## 类定义

``` C++
class PthreadPool
{
private:
    pthread_mutex_t lock;                             // 互斥锁
    pthread_cond_t notify;                            // 条件变量
    queue<Pthreadpool_Runable> thread_queue;          // 任务队列
    pthread_t *threads;                               // 任务数组
    int shutdown;                                     // 表示线程池是否关闭
    static void *threadpool_thread(void *threadpool); // 运行函数

public:
    PthreadPool();
    ~PthreadPool();
    int thread_num;                                                  // 线程数量
    int running_num;                                                 // 正在运行的线程数
    int waiting_num;                                                 // 队列中等待的数目
    int Init(unsigned int num);                                      // 初始化线程池
    int AddTask(void (*function)(void *), void *argument = nullptr); // 加入任务
    int Destory(PthreadPool_Shutdown flag = graceful_shutdown);      // 停止正在进行的任务并摧毁线程池
};
```

## 对外接口
```C++
int Init(unsigned int num);                                      // 初始化线程池
int AddTask(void (*function)(void *), void *argument = nullptr); // 加入任务
int Destory(PthreadPool_Shutdown flag = graceful_shutdown);      // 停止正在进行的任务并摧毁线程池
```
在使用前先创建对象 `PthreadPool pool;`  
然后再初始化线程池 `pool.Init(4);`  
在线程池中加入任务 `pool.AddTask(&dummy_task)`  
在程序结束时销毁线程池 `pool.Destory();`  
销毁线程池可以提供参数  
``` C++
enum PthreadPool_Shutdown {
    graceful_shutdown  = 1,   // 等待线程结束后关闭
    immediate_shutdown = 2  // 立即关闭
};
```  
## 测试运行
提供了一个简单的测试程序  
`g++ PthreadPool.cpp Test.cpp -lpthread -std=c++11 -o pthreadpool`

## *参考资料*
https://blog.csdn.net/jcjc918/article/details/50395528