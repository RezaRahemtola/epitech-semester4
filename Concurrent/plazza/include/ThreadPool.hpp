/*
** EPITECH PROJECT, 2023
** plazza
** File description:
** ThreadPool
*/

#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <thread>

namespace plazza {
    class ThreadPool {
        public:
            explicit ThreadPool(std::size_t threadsNb) : _running(true)
            {
                for (std::size_t i = 0; i < threadsNb; i++)
                    _threads.emplace_back(&ThreadPool::taskWrapper, this, i);
            }

            ~ThreadPool()
            {
                {
                    std::unique_lock<std::mutex> lock(_mutex);
                    _running = false;
                }
                _condVar.notify_all();

                for (auto &thread: _threads)
                    thread.join();
            };

            void addTask(const std::function<void(void)> &func)
            {
                {
                    std::unique_lock<std::mutex> lock(_mutex);
                    _tasks.push(func);
                }
                _condVar.notify_one();
            };

            [[nodiscard]] bool allFree() const noexcept
            {
                return std::all_of(_occupied.begin(), _occupied.end(), [](bool status) {
                    return !status;
                });
            }

        private:
            void taskWrapper(std::size_t index)
            {
                std::function<void(void)> task;
                _occupied[index] = false;
                while (true) {
                    {
                        std::unique_lock<std::mutex> lock(_mutex);
                        while (_running && _tasks.empty())
                            _condVar.wait(lock);
                        if (!_running && _tasks.empty())
                            return;
                        task = _tasks.front();
                        _tasks.pop();
                    }
                    _occupied[index] = true;
                    task();
                    _occupied[index] = false;
                }
            }

            std::mutex _mutex;
            std::condition_variable _condVar;

            bool _running;
            std::queue<std::function<void()>> _tasks;
            std::vector<std::thread> _threads;
            std::vector<bool> _occupied;
    };
}
