#include "squirrel.hpp"
#include "druids.hpp"
#include "orc.hpp"

orc::orc(int x, int y) : NPC(orcType, x, y) {}
orc::orc(std::istream &is) : NPC(orcType, is) {}

void orc::print() {
    std::cout << *this;
}

void orc::print(std::ostream &outfs) {
    outfs << *this;
}

void orc::save(std::ostream &os) {
    os << orcType << std::endl;
    NPC::save(os);
}


bool orc::accept(std::shared_ptr<NPC> visitor) {
    std::shared_ptr<orc> This = std::make_shared<orc>(*this);
    return visitor->visit(This);
}

bool orc::fight(std::shared_ptr<squirrel> other) {
    fight_notify(other, true);
    return true;
}

bool orc::fight(std::shared_ptr<orc> other) {
    fight_notify(other, false);
    return false;
}

bool orc::fight(std::shared_ptr<druids> other) {
    fight_notify(other, true);
    return false;
}

std::ostream &operator<<(std::ostream &os, orc &orc) {
    os << "orc: " << *static_cast<NPC *>(&orc) << std::endl;
    return os;
}