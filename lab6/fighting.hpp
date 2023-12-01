#pragma once
#include "npc.hpp"
#include "orc.hpp"
#include "squirrel.hpp"
#include "druids.hpp"

class TextObserver : public IFightObserver {
private:
    TextObserver() {};

public:
    static std::shared_ptr<IFightObserver> get() {
        static TextObserver instance;
        return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver *) {});
    }

    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override {
        if (win) {
            std::cout << std::endl
                      << "Murder --------" << std::endl;
            attacker->print();
            defender->print();
        }
    }
};

class FileObserver : public IFightObserver {
private:
    std::string file_name;
    std::ofstream fs;
    FileObserver(std::string _file_name)  {
        this->file_name = _file_name;
        this->fs = std::ofstream(_file_name);
        if(!(fs.good()) || !(fs.is_open())) {
            std::cout << "Observer's file openning error!" << std::endl;
        }
    }
    ~FileObserver() {
        this->fs.flush();
        this->fs.close();
    }

public:
    static std::shared_ptr<IFightObserver> get(std::string cur_file_name) {
        static FileObserver instance(cur_file_name); // single
        return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver *) {});
    }

    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override {
        if (win) {
            if(fs.good() && fs.is_open()) {
                fs << std::endl
                    << "Murder --------" << std::endl;
                attacker->print(fs);
                defender->print(fs);                
            }
            else {
                std::cout << std::endl;
                exit(-1);
            }
        }
    }
};
