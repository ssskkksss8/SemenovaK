#include "npc.hpp"

const int ORC_MURDER_DISTANCE{10};
const int SQUIRREL_MURDER_DISTANCE{5};
const int DRUIDS_MURDER_DISTANCE{10};

const int ORC_MOVE_DISTANCE{20};
const int SQUIRREL_MOVE_DISTANCE{5};
const int DRUIDS_MOVE_DISTANCE{10};

NPC::NPC(NpcType t, int _x, int _y) : type(t), x(_x), y(_y) {}
NPC::NPC(NpcType t, std::istream &is) : type(t) {
    is >> x;
    is >> y;
}

void NPC::subscribe(std::shared_ptr<IFightObserver> observer) {
    observers.push_back(observer);
}

void NPC::fight_notify(const std::shared_ptr<NPC> defender, bool win) {
    for (auto &o : observers)
        o->on_fight(std::shared_ptr<NPC>(this, [](NPC *) {}), defender, win);
}

bool NPC::is_close(const std::shared_ptr<NPC> &other, size_t distance) {
    auto [other_x, other_y] = other->position();
    std::lock_guard<std::mutex> lck(mtx);
    switch (this->type) {
    case ORCType:
        distance = ORC_MURDER_DISTANCE;
        break;
    case SQUIRRELType:
        distance = SQUIRREL_MURDER_DISTANCE;
        break;
    case DRUIDSType:
        distance = DRUIDS_MURDER_DISTANCE;
        break;
    default:
        break;
    }

    if ((std::pow(x - other_x, 2) + std::pow(y - other_y, 2)) <= std::pow(distance, 2))
        return true;
    else
        return false;
}

NpcType NPC::get_type() {
    std::lock_guard<std::mutex> lck(mtx);
    return type;
}

std::pair<int, int> NPC::position() {
    std::lock_guard<std::mutex> lck(mtx);
    return {x, y};
}

void NPC::save(std::ostream &os) {
    os << x << std::endl;
    os << y << std::endl;
}

std::ostream &operator<<(std::ostream &os, NPC &npc) {
    os << "{ x:" << npc.x << ", y:" << npc.y << "} ";
    return os;
}

void NPC::move(int shift_x, int shift_y, int max_x, int max_y) {
    std::lock_guard<std::mutex> lck(mtx);
    switch (this->type) {
    case ORCType:
        if(shift_y % 2 == 0) {
            shift_x = ORC_MOVE_DISTANCE*pow(-1, shift_x);
            shift_y = ORC_MOVE_DISTANCE*pow(-1, shift_y);
        } else {
            shift_x = ORC_MOVE_DISTANCE*pow(-1, shift_x);
            shift_y = ORC_MOVE_DISTANCE*pow(-1, shift_y);
        }
        break;
    case SQUIRRELType:
        if(shift_y % 2 == 0) {
            shift_x = SQUIRREL_MOVE_DISTANCE*pow(-1, shift_x);
            shift_y = SQUIRREL_MOVE_DISTANCE*pow(-1, shift_y);
        } else {
            shift_x = SQUIRREL_MOVE_DISTANCE*pow(-1, shift_x);
            shift_y = SQUIRREL_MOVE_DISTANCE*pow(-1, shift_y);
        }
        break;
    case DRUIDSType:
        if(shift_y % 2 == 0) {
            shift_x = DRUIDS_MOVE_DISTANCE*pow(-1, shift_x);
            shift_y = DRUIDS_MOVE_DISTANCE*pow(-1, shift_y);
        } else {
            shift_x = DRUIDS_MOVE_DISTANCE*pow(-1, shift_x);
            shift_y = DRUIDS_MOVE_DISTANCE*pow(-1, shift_y);
        }
        break;
    default:
        break;
    }

    if ((x + shift_x >= 0) && (x + shift_x <= max_x))
        x += shift_x;
    if ((y + shift_y >= 0) && (y + shift_y <= max_y))
        y += shift_y;
}

bool NPC::is_alive() {
    std::lock_guard<std::mutex> lck(mtx);
    return alive;
}

void NPC::must_die() {
    std::lock_guard<std::mutex> lck(mtx);
    alive = false;
}