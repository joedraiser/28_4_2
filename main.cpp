#include <iostream>
#include <thread>
#include <mutex>

std::mutex green_light;
int trains_arrived=0;

void parovoz(int duration, char name)
{
    std::cout << "Train " << name << " started moving to railway station\n";
    std::this_thread::sleep_for(std::chrono::seconds(duration));
    std::cout << "Train " << name << " is waiting for free way to arrive\n";
    green_light.lock();
    std::cout << "Train " << name << " arrived at the station\n";
    trains_arrived++;
}

int main()
{
    char name[3]={'A', 'B', 'C'};
    int duration[3];

    for(int i=0;i<3;i++)
    {
        std::cout << "How much time will train #" << name[i] << " take to get to the railway station: ";
        std::cin >> duration[i];
    }

    std::cout << "Type 'depart' when to free the way\n";

    std::thread train1(parovoz, duration[0], name[0]);
    std::thread train2(parovoz, duration[1], name[1]);
    std::thread train3(parovoz, duration[2], name[2]);

    std::string input;

    while(trains_arrived!=2)
    {
        std::cin >> input;
        if(input=="depart")
        {
            green_light.unlock();
        }
    }

    train1.join();
    train2.join();
    train3.join();

    return 0;
}
