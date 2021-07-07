#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <future>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

using namespace std::literals::chrono_literals;

/*
struct parameters {
    std::mutex& left_fork;
    std::mutex& right_fork;
    std::mutex& io;
};

void* pthread_guest(void* context)
{
    auto const& [left_fork, right_fork, io] = *(parameters*)context;
    return nullptr;
}
*/

namespace dining_philosophers {
void guest(
    std::mutex& left_fork,
    std::mutex& right_fork,
    std::mutex& io)
{
    for (int n = 0; n < 5; ++n) {
        std::scoped_lock eating_lock { left_fork, right_fork };
        {
            {
                std::lock_guard io_lock { io };
                std::cout
                    << "Guest #"
                    << std::this_thread::get_id()
                    << " starts to eat."
                    << std::endl;
            }

            std::this_thread::sleep_for(100ms);

            {
                std::lock_guard io_lock { io };
                std::cout
                    << "Guest #"
                    << std::this_thread::get_id()
                    << " finished eating."
                    << std::endl;
            }
        }

        std::this_thread::sleep_for(100ms);
    }
}

void main()
{
    std::mutex io;
    std::array<std::mutex, 5> forks;
    std::array<std::thread, 5> guests {
        std::thread { guest, std::ref(forks[0]), std::ref(forks[1]), std::ref(io) },
        std::thread { guest, std::ref(forks[1]), std::ref(forks[2]), std::ref(io) },
        std::thread { guest, std::ref(forks[2]), std::ref(forks[3]), std::ref(io) },
        std::thread { guest, std::ref(forks[3]), std::ref(forks[4]), std::ref(io) },
        std::thread { guest, std::ref(forks[4]), std::ref(forks[0]), std::ref(io) },
    };

    for (auto& g : guests) {
        g.join();
    }
}
}

namespace exceptions_with_async {
int die()
{
    // heavy math simulation
    std::this_thread::sleep_for(200ms);
    throw std::runtime_error { "that's weird" };
}

void main()
{
    std::future<int> answer = std::async(std::launch::async, &die);
    try {
        std::cout << "The answer is " << answer.get() << std::endl;
    } catch (std::runtime_error const& ex) {
        std::cerr << "HOUSTON! We have a problem: " << ex.what() << std::endl;
    }
}
}

namespace ping_pong {
enum class Active {
    Sender,
    Receiver
};

std::string message;

void sender(Active& current, std::mutex& m, std::condition_variable& cv)
{
    for (int n = 0; n < 10; ++n) {
        {
            std::unique_lock lock { m };
            cv.wait(lock, [&current] {
                return current == Active::Sender;
            });

            message = "Hey, my number is: " + std::to_string(n);

            current = Active::Receiver;
            lock.unlock();
            cv.notify_one();
        }

        // wait for response
        {
            std::unique_lock lock { m };
            cv.wait(lock, [&current] {
                return current == Active::Sender;
            });

            std::cout << "Got response: " << message << std::endl;
        }
    }
}

void receiver(Active& current, std::mutex& m, std::condition_variable& cv)
{
    for (int n = -10; n < 0; ++n) {
        std::unique_lock lock { m };
        cv.wait(lock, [&current] {
            return current == Active::Receiver;
        });

        std::cout << "Got message: " << message << std::endl;
        message = "Ok, my number is " + std::to_string(n);

        current = Active::Sender;
        lock.unlock();
        cv.notify_one();
    }
}

void main()
{
    Active current { Active::Sender };
    std::mutex m;
    std::condition_variable cv;

    std::thread s { sender, std::ref(current), std::ref(m), std::ref(cv) };
    std::thread r { receiver, std::ref(current), std::ref(m), std::ref(cv) };

    s.join();
    r.join();
}
}

namespace one_generator_many_readers {
void generator(std::vector<int>& numbers, std::mutex& m, std::condition_variable& cv)
{
    int a = 0;
    int b = 1;
    for (int x = 0; x < 5; ++x) {
        std::unique_lock lock { m };
        for (int y = 0; y < 4; ++y) {

            numbers.push_back(a);
            int const tmp = a;
            a = b;
            b = tmp + b;
        }
        lock.unlock();
        cv.notify_all();
    }
}

void worker(std::vector<int>& numbers, std::mutex& m, std::condition_variable& cv)
{
    for (int n = 0; n < 5; ++n) {
        int current_value;
        {
            std::unique_lock lock { m };
            cv.wait(lock, [&numbers] {
                return !numbers.empty();
            });

            current_value = numbers.back();
            numbers.pop_back();
        }
        std::this_thread::yield();

        std::cout
            << std::this_thread::get_id()
            << "Got number: "
            << current_value
            << std::endl;

        //std::this_thread::sleep_for(200ms);
    }
}

void main()
{
    std::vector<int> numbers;
    std::mutex m;
    std::condition_variable cv;

    std::thread gen { generator, std::ref(numbers), std::ref(m), std::ref(cv) };
    std::array<std::thread, 4> workers {
        std::thread { worker, std::ref(numbers), std::ref(m), std::ref(cv) },
        std::thread { worker, std::ref(numbers), std::ref(m), std::ref(cv) },
        std::thread { worker, std::ref(numbers), std::ref(m), std::ref(cv) },
        std::thread { worker, std::ref(numbers), std::ref(m), std::ref(cv) },
    };

    gen.join();
    for (auto& w : workers) {
        w.join();
    }
}
}

int main()
{
    exceptions_with_async::main();
    dining_philosophers::main();
    ping_pong::main();
    one_generator_many_readers::main();

    return 0;
}
