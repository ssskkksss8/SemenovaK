#pragma once

#include <iostream>
#include <memory>
#include <cstring>
#include <string>
#include <random>
#include <fstream>
#include <set>
#include <math.h>

struct NPC;
struct orc;
struct squirrel;
struct druids;

using set_t = std::set<std::shared_ptr<NPC>>;

enum NpcType {
    Unknown = 0,
    orcType = 1,
    squirrelType = 2,
    druidsType = 3
};

struct IFightObserver {
    virtual void on_fight(const std::shared_ptr<NPC> attacker,const std::shared_ptr<NPC> defender,bool win) = 0;
};

struct NPC : public std::enable_shared_from_this<NPC> {
    NpcType type;
    int x{0};
    int y{0};
    std::vector<std::shared_ptr<IFightObserver>> observers;

    NPC(NpcType t, int _x, int _y);
    NPC(NpcType t, std::istream &is);

    void subscribe(std::shared_ptr<IFightObserver>observer ); //add_observer
    void fight_notify(const std::shared_ptr<NPC> defender,bool win);
    virtual bool is_close(const std::shared_ptr<NPC> &other, size_t distance) const;

    virtual bool accept(std::shared_ptr<NPC> visitor) = 0;
    bool visit(std::shared_ptr<orc> ref);
    bool visit(std::shared_ptr<squirrel> ref);
    bool visit(std::shared_ptr<druids> ref);

    virtual bool fight(std::shared_ptr<orc> other) = 0;
    virtual bool fight(std::shared_ptr<squirrel> other) = 0;
    virtual bool fight(std::shared_ptr<druids> other) = 0;
    virtual void print() = 0;
    virtual void print(std::ostream &os) = 0;

    virtual void save(std::ostream &os);

    friend std::ostream &operator<<(std::ostream &os, NPC &npc);
};