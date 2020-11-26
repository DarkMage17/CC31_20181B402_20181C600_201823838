#ifndef FOLLOWER_H
#define FOLLOWER_H


class Follower
{
public:
    Follower(int idu, int idf);
    Follower();
    int getIdu();
    int getIdf();
private:
    int idf;
    int idU;
};

#endif // FOLLOWER_H
