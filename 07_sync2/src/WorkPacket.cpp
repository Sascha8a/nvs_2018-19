#include <iostream>
#include "WorkPacket.h"

using namespace std;

WorkPacket::WorkPacket(int id) : _id(id)
{
}

int WorkPacket::get_id()
{
    return _id;
}