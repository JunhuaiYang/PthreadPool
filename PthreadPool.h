#include <iostream>
#include <queue>
#include <algorithm>
#include <unistd.h>

using namespace std;

// 任务结构体
struct Pthreadpool_Runable
{
    void (*function)(void *);
    void *argument;
};

// 关闭方式定义
enum PthreadPool_Shutdown {
    graceful_shutdown  = 1,   // 等待线程结束后关闭
    immediate_shutdown = 2  // 立即关闭
};

// 错误码定义
enum PthreadPool_Error {
    Pthreadpool_invalid        = -1,
    Pthreadpool_lock_failure   = -2,
    Pthreadpool_queue_full     = -3,
    Pthreadpool_shutdown       = -4,
    Pthreadpool_thread_failure = -5
};

class PthreadPool
{
private:
    pthread_mutex_t lock;                   // 互斥锁
    pthread_cond_t notify;                  // 条件变量
    queue<Pthreadpool_Runable> thread_queue; // 任务队列
    pthread_t *threads;                     // 任务数组
    int thread_num;                         // 线程数量
    int running_num;                        // 正在运行的线程数
    int waiting_num;                        // 队列中等待的数目
    bool shutdown;                          // 表示线程池是否关闭
    static void *threadpool_thread(void *threadpool); // 运行函数

public:
    PthreadPool();
    ~PthreadPool();
    int Init(unsigned int num);                        // 初始化
    int AddTask(void (*function)(void *), void *argument = nullptr); // 加入任务
    int Destory(PthreadPool_Shutdown flag = graceful_shutdown);                                     //强行停止
};