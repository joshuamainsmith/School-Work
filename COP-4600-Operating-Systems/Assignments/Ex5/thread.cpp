#include <thread>
#include <iostream>

void foo(int id, int num)
{
    while (1)
    {
        if (num == rand() % 10000)
            break;
    }
        std::cout << "Thread " << id << " completed." << std::endl;
}

int main(int argc, char* argv[])
{
    int num = atoi(argv[1]);

    std::thread threads[10];

    for (int i = 0; i <= 9; i++)
    {
        threads[i] = std::thread(foo, i, num);
    }

    for (int i = 0; i <= 9; i++)
    {
        threads[i].join();
    }

    std::cout << "All threads have finished finding numbers." << std::endl;

    return 0;
}
