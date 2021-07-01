#ifndef ___THREAD_POOL___
#define ___THREAD_POOL___

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

/*
Adapted from
    github.com/progschj/ThreadPool
*/
class ThreadPool
{
public:
    // Constructor
    ThreadPool(size_t);

    // Submit jobs
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args)
        ->std::future<typename std::result_of<F(Args...)>::type>;

    // Destructor
    ~ThreadPool();

private:
    // Workers
    std::vector< std::thread > workers;

    // Queue
    std::queue< std::function<void()>> task_queue;

    // Synchronization
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

// Constructor just launches some amount of workers
inline ThreadPool::ThreadPool(size_t threads)
    : stop(false)
{
    for (size_t i = 0; i < threads; ++i)
    {
        workers.emplace_back
        (
            [this]
            {
                for (;;)
                {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock, [this] { return this->stop || !this->task_queue.empty(); });
                        if (this->stop && this->task_queue.empty())
                        {
                            return;
                        }
                        task = std::move(this->task_queue.front());
                        this->task_queue.pop();
                    }
                    task();
                }
            }
        );
    }
}

// Submit new work item to the pool
template<class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args)
-> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared< std::packaged_task<return_type()> >
        (
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
            );

    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);

        // don't allow enqueueing after stopping the pool
        if (stop)
        {
            throw std::runtime_error("enqueue on stopped thread pool");
        }

        task_queue.emplace([task]() { (*task)(); });
    }
    condition.notify_one();
    return res;
}

// the destructor joins all threads
inline ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for (std::thread& worker : workers)
    {
        worker.join();
    }
}

/*
    Other threadpool implementations:

        github.com/mtrebi/thread-pool
        vorbrodt.blog/2019/02/27/advanced-thread-pool/
        stackoverflow.com/questions/23896421/efficiently-waiting-for-all-tasks-in-a-threadpool-to-finish
*/

/*
    You can also deduce the number of threads isuing the code below:

    unsigned int n = std::thread::hardware_concurrency();
    std::cout << n << " concurrent threads are supported.\n";
*/

#endif
