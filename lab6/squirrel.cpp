#include "orc.hpp"
#include "squirrel.hpp"
#include "druids.hpp"

squirrel::squirrel(int x, int y) : NPC(squirrelType, x, y) {}
squirrel::squirrel(std::istream &is) : NPC(squirrelType, is) {}

void squirrel::print() {
    std::cout << *this;
}

void squirrel::print(std::ostream &outfs) {
    outfs << *this;
}

void squirrel::save(std::ostream &os) {
    os << squirrelType << std::endl;
    NPC::save(os);
}

bool squirrel::accept(std::shared_ptr<NPC> visitor) {
    std::shared_ptr<squirrel> This = std::make_shared<squirrel>(*this);
    return visitor->visit(This);
}


bool squirrel::fight(std::shared_ptr<orc> other) {
    fight_notify(other, false);
    return false;
}

bool squirrel::fight(std::shared_ptr<druids> other) {
    fight_notify(other, false);
    return true;
}

bool squirrel::fight(std::shared_ptr<squirrel> other) {
    fight_notify(other, false);
    return false;
}

std::ostream &operator<<(std::ostream &os, squirrel &squirrel) {
    os << "squirrel: " << *static_cast<NPC *>(&squirrel) << std::endl;
    return os;
}