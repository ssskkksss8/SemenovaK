#include "npc.hpp"
#include "orc.hpp"
#include "druids.hpp"
#include "squirrel.hpp"
#include <sstream>

#include <thread>
#include <mutex>
#include <chrono>
#include <queue>
#include <optional>
#include <array>

#define CONST_TIME 30

using namespace std::chrono_literals;
std::mutex print_mutex;//для синхронизации вывода

// Text Observer
class TextObserver : public IFightObserver {
private:
    TextObserver(){};

public:
    static std::shared_ptr<IFightObserver> get() {
        static TextObserver instance;
        return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver *) {});
    }

    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override {
        if (win) {
            std::lock_guard<std::mutex> lck(print_mutex);
            std::cout << std::endl
                      << "Murder --------" << std::endl;
            attacker->print();
            defender->print();
        }
    }
};

// Фабрики -----------------------------------
std::shared_ptr<NPC> factory(std::istream &is) {
    std::shared_ptr<NPC> result;
    int type{0};
    if (is >> type) {
        switch (type) {
        case BanditType:
            result = std::make_shared<Bandit>(is);
            break;
        case KnightType:
            result = std::make_shared<Knight>(is);
            break;
        case ElfType:
            result = std::make_shared<Elf>(is);
            break;
        }
    }
    else
        std::cerr << "unexpected NPC type:" << type << std::endl;

    if (result)
        result->subscribe(TextObserver::get());
    return result;
}

std::shared_ptr<NPC> factory(NpcType type, int x, int y) {
    std::shared_ptr<NPC> result;
    switch (type) {
    case ElfType:
        result = std::make_shared<Elf>(x, y);
        break;
    case KnightType:
        result = std::make_shared<Knight>(x, y);
        break;
    case BanditType:
        result = std::make_shared<Bandit>(x, y);
        break;
    default:
        break;
    }
    if (result)
        result->subscribe(TextObserver::get());

    return result;
}

// save array to file
void save(const set_t &array, const std::string &filename) {
    std::ofstream fs(filename);
    fs << array.size() << std::endl;
    for (auto &n : array)
        n->save(fs);
    fs.flush();
    fs.close();
}

set_t load(const std::string &filename) {
    set_t result;
    std::ifstream is(filename);
    if (is.good() && is.is_open())
    {
        int count;
        is >> count;
        for (int i = 0; i < count; ++i)
            result.insert(factory(is));
        is.close();
    }
    else
        std::cerr << "Error: " << std::strerror(errno) << std::endl;
    return result;
}

// print to screen
std::ostream &operator<<(std::ostream &os, const set_t &array) {
    for (auto &n : array)
        n->print();
    return os;
}

set_t fight(const set_t &array, size_t distance) {
    set_t dead_list;

    for (const auto &attacker : array)
        for (const auto &defender : array)
            if ((attacker != defender) &&
                attacker->is_close(defender, distance) &&
                defender->accept(attacker))
                dead_list.insert(defender);

    return dead_list;
}

struct print : std::stringstream {
    ~print()
    {
        static std::mutex mtx;//обеспечение многопоточной безопасности
        std::lock_guard<std::mutex> lck(print_mutex);
        std::cout << this->str();//вывод
        std::cout.flush();//для сброса буфера и убеждения
    }
};

struct FightEvent {
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
};

std::atomic<bool> move_thread_exit(false);
std::atomic<bool> fight_thread_exit(false);

class FightManager {
private:
    std::queue<FightEvent> events;
    std::shared_mutex mtx;

    FightManager() {}

public:
    static FightManager &get() {
        static FightManager instance;
        return instance;
    }

    void add_event(FightEvent &&event) {
        std::lock_guard<std::shared_mutex> lock(mtx);
        events.push(event);
    }

    void operator()() {
        while (!fight_thread_exit) { 
            {
                std::optional<FightEvent> event;

                {
                    std::lock_guard<std::shared_mutex> lock(mtx);
                    if (!events.empty()) {
                        event = events.back();
                        events.pop();
                    }
                }

                if (event) {
                    try {
                        if (event->attacker->is_alive())     // no zombie fighting!
                            if (event->defender->is_alive()) // already dead!
                                if (event->defender->accept(event->attacker))
                                    event->defender->must_die();
                    }
                    catch (...) {
                        std::lock_guard<std::shared_mutex> lock(mtx);
                        events.push(*event);
                    }
                }
                else
                    std::this_thread::sleep_for(100ms);
            }
        }
    }
};

int main() {
    set_t array; // монстры

    const int MAX_X{100};
    const int MAX_Y{100};
    const int DISTANCE{10};
    
    std::time_t start_time = std::time(nullptr);
    std::time_t finish_time = start_time + CONST_TIME;

    // Гененрируем начальное распределение монстров
    std::cout << "Generating ..." << std::endl;
    for (size_t i = 0; i < 50; ++i)
        array.insert(factory(NpcType(std::rand() % 3 + 1),
                             std::rand() % MAX_X,
                             std::rand() % MAX_Y));

    std::cout << "Starting list:" << std::endl
              << array;

    std::thread fight_thread(std::ref(FightManager::get()));// обрабатывает битвы

    int second_counter = 0;
    std::thread move_thread([&array, MAX_X, MAX_Y, DISTANCE, &second_counter]() {//управляет движением и добавляет события в очередь
            while (!move_thread_exit) {
                // move phase
                for (std::shared_ptr<NPC> npc : array) {
                    if(npc->is_alive()){
                        int shift_x = std::rand() % 20 - 10;
                        int shift_y = std::rand() % 20 - 10;
                        npc->move(shift_x, shift_y, MAX_X, MAX_Y);
                    }
                }
                // lets fight
                for (std::shared_ptr<NPC> npc : array)
                    for (std::shared_ptr<NPC> other : array)
                        if (other != npc)
                            if (npc->is_alive())
                            if (other->is_alive())
                            if (npc->is_close(other, DISTANCE))
                                FightManager::get().add_event({npc, other});

                std::this_thread::sleep_for(1s);
                ++second_counter;
            } });

    
    while (start_time < finish_time) {
        const int grid{20}, step_x{MAX_X / grid}, step_y{MAX_Y / grid}; {
            std::array<char, grid * grid> fields{0};
            for (std::shared_ptr<NPC> npc : array) {
                auto [x, y] = npc->position();
                int i = x / step_x;
                int j = y / step_y;

                if (npc->is_alive()) {
                    switch (npc->get_type()) {
                    case ElfType:
                        fields[i + grid * j] = 'E';
                        break;
                    case KnightType:
                        fields[i + grid * j] = 'K';
                        break;
                    case BanditType:
                        fields[i + grid * j] = 'B';
                        break;

                    default:
                        break;
                    }
                }
                else
                    fields[i + grid * j] = '.';
            }

            if(second_counter > 30) {
                break;
            }
            std::lock_guard<std::mutex> lck(print_mutex);
            for (int j = 0; j < grid; ++j) {
                for (int i = 0; i < grid; ++i) {
                    char c = fields[i + j * grid];
                    if (c != 0)
                        std::cout << "[" << c << "]";
                    else
                        std::cout << "[ ]";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        std::this_thread::sleep_for(1s);
        start_time = std::time(nullptr);
    }

    fight_thread_exit = true;
    move_thread_exit = true;

    move_thread.join();
    fight_thread.join();

    return 0;
}
