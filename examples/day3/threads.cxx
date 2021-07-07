#include <array>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std::literals::chrono_literals;

void guest(
    std::mutex& left_fork,
    std::mutex& right_fork,
    std::mutex& io)
{
    for (int n = 0; n < 5; ++n) {
        std::scoped_lock eating_lock { left_fork, right_fork };
        {
            std::lock_guard io_lock { io };
            std::cout
                << "Guest #"
                << std::this_thread::get_id()
                << " is eating."
                << std::endl;
        }

        std::this_thread::sleep_for(100ms);
    }
}

int main()
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

    return 0;
}
