#pragma once
#include "npc.hpp"

struct squirrel : public NPC {
    squirrel(int x, int y);
    squirrel(std::istream &is);
    void print() override;
    void print(std::ostream &os) override;
    void save(std::ostream &os) override;
    bool accept(std::shared_ptr<NPC> visitor) override;
    bool fight(std::shared_ptr<orc> other) override;
    bool fight(std::shared_ptr<squirrel> other) override;
    bool fight(std::shared_ptr<druids> other) override;
    friend std::ostream &operator<<(std::ostream &os, squirrel &squirrel);
};