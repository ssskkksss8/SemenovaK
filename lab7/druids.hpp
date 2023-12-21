#pragma once
#include "npc.hpp"

struct druids : public NPC {
    druids(int x, int y);
    druids(std::istream &is);
    void print() override;
    void print(std::ostream &os) override;
    void save(std::ostream &os) override;
    // bool is_druids() const override;
    bool accept(std::shared_ptr<NPC> visitor) override;
    bool fight(std::shared_ptr<druids> other) override;
    bool fight(std::shared_ptr<orc> other) override;
    bool fight(std::shared_ptr<squirrel> other) override;
    friend std::ostream &operator<<(std::ostream &os, druids &druids);
};