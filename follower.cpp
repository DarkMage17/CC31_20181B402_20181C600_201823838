#include "follower.h"

Follower::Follower()
{

}

int Follower::getIdu()
{
    return idU;
}

int Follower::getIdf()
{
    return idf;
}

Follower::Follower(int idu, int idf)
{
    this->idU = idu;
    this->idf = idf;
}
