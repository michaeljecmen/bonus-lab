#include <chrono>
#include <iostream>
#include <random>
#include <thread>

/*
 * Hallmarks of a Singleton:
 *  1. static getInstance method which creates the singleton object
 *      if it doesn't already exist
 *  2. private constructor (only this class' code can create the object)
 *  3. private destructor (only this class' code can delete the object)
 *  4. deleted copy and move semantics (only one can exist, we determine that instance)
 *
 */
class MySingletonTimer {
   public:
    static MySingletonTimer& getInstance() {
        static MySingletonTimer instance;
        return instance;
    }

    void printTimeSinceCreation() {
        auto now = std::chrono::system_clock::now();
        double seconds_since = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();

        std::cout << "time since creation: " << seconds_since << "s" << std::endl;
    }

   private:
    MySingletonTimer() {
        std::cout << "creating timer singleton" << std::endl;
        start = std::chrono::system_clock::now();
    }

    ~MySingletonTimer() {
        std::cout << "destroying timer singleton" << std::endl;
    }

    MySingletonTimer(const MySingletonTimer&) = delete;
    MySingletonTimer& operator=(const MySingletonTimer&) = delete;
    MySingletonTimer(MySingletonTimer&&) = delete;
    MySingletonTimer& operator=(MySingletonTimer&&) = delete;

    // this is just the ugly type for a time point. most of the
    // time you'll use auto, but when it's a member variable
    // you can't get away with that
    std::chrono::time_point<std::chrono::system_clock> start;
};

bool flipCoin() {
    if ((double)rand() / RAND_MAX > .5) {
        std::cout << "coin heads!" << std::endl;
        return true;
    }
    std::cout << "coin tails!" << std::endl;
    return false;
}

int main() {
    // MySingletonTimer::printTimeSinceCreation();

    // allows us to use 5s, 10s, 2ms, etc
    using namespace std::chrono_literals;
    std::cout << "start of main" << std::endl;

    // EXAMPLE A:
    // MySingletonTimer& timer = MySingletonTimer::getInstance();
    // timer.printTimeSinceCreation();

    // std::this_thread::sleep_for(2s);
    // timer.printTimeSinceCreation();

    // EXAMPLE B:
    // MySingletonTimer::getInstance().printTimeSinceCreation();
    // std::this_thread::sleep_for(2s);
    // MySingletonTimer::getInstance().printTimeSinceCreation();

    // EXAMPLE C:
    // this just sets the random "seed" to something new each time
    // (demo without this line too)
    // srand(std::chrono::system_clock::now().time_since_epoch().count());

    // if (flipCoin()) {
    //     auto& timer = MySingletonTimer::getInstance();
    // }
    // std::this_thread::sleep_for(2s);
    // auto& timer = MySingletonTimer::getInstance();
    // timer.printTimeSinceCreation();

    std::cout << "end of main" << std::endl;
}






// there is also a pointer-based approach if that method makes more sense than
// the reference based approach. it is harder to understand, in my opinion, and
// thus more error prone. I do not recommend it unless you need a pointer specifically
class Singleton {
   public:
    static Singleton* getInstance() {
        if (!instance) {
            instance = new Singleton();
        }
        return instance;
    }

   private:
    // necessary so the destroyer class can use our destructor
    friend class SingletonDestroyer;
    static Singleton* instance;
    Singleton() {
        std::cout << "creating singleton" << std::endl;
    }

    ~Singleton() {
        std::cout << "destroying singleton" << std::endl;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;
};

// when this destroyer object destructs, delete the
// singleton instance pointer too
struct SingletonDestroyer {
    ~SingletonDestroyer() {
        delete Singleton::instance;
    }
};

// two necessary evils of this approach
Singleton* Singleton::instance = nullptr;
SingletonDestroyer destroyer;

// int main() {
//     Singleton* sing = Singleton::getInstance();
// }