#include "WorkPacket.h"

WorkPacket::WorkPacket(int id) : id(id)
{
}

int WorkPacket::get_id()
{
    return id;
}