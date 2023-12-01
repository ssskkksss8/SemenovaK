#include "druids.hpp"
#include "squirrel.hpp"
#include "orc.hpp"

druids::druids(int x, int y) : NPC(druidsType, x, y) {}
druids::druids(std::istream &is) : NPC(druidsType, is) {}

void druids::print() {
    std::cout << *this;
}

void druids::print(std::ostream &outfs) {
    outfs << *this;
}

void druids::save(std::ostream &os) {
    os << druidsType << std::endl;
    NPC::save(os);
}

bool druids::accept(std::shared_ptr<NPC> visitor) {
    std::shared_ptr<druids> This = std::make_shared<druids>(*this);
    return visitor->visit(This);
}

bool druids::fight(std::shared_ptr<orc> other) {
    fight_notify(other, false);
    return false;
}

bool druids::fight(std::shared_ptr<druids> other) {
    fight_notify(other, false);
    return false;
}

bool druids::fight(std::shared_ptr<squirrel> other) {
    fight_notify(other, true);
    return true;
}

std::ostream &operator<<(std::ostream &os, druids &druids) {
    os << "druids: " << *static_cast<NPC *>(&druids) << std::endl;
    return os;
}