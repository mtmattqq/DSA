#ifndef R_3_1
#define R_3_1

#include <string>
#include <stdexcept>

class GameEntry {
public:
    GameEntry(const std::string &n = "", int s = 0);
    std::string getName() const;
    int getScore() const;
private:
    std::string name;
    int score;
};

GameEntry::GameEntry(const std::string &n, int s)
    : name(n), score(s) {}

std::string GameEntry::getName() const {
    return name;
}

int GameEntry::getScore() const {
    return score;
}

class Scores {
public:
    Scores(int maxEnt = 10);
    ~Scores();
    void add(const GameEntry &e);
    GameEntry remove(int i);
    int count(const std::string &name);
private:
    int maxEntries;
    int numEntries;
    GameEntry *entries;
};

Scores::Scores(int maxEnt) {
    maxEntries = maxEnt;
    entries = new GameEntry[maxEntries];
    numEntries = 0;
}

Scores::~Scores() {
    delete[] entries;
}

int Scores::count(const std::string &name) {
    int ret{0};
    for(int i{0}; i < numEntries; ++i) {
        if(entries[i].getName() == name) {
            ret++;
        }
    }
    return ret;
}

void Scores::add(const GameEntry &e) {
    int newScore = e.getScore();
    int numName = count(e.getName());
    if(numName >= (maxEntries - 1) / 2 + 1) {
        return;
    }

    if(numEntries == maxEntries) {
        if(newScore <= entries[maxEntries - 1].getScore())
            return;
    } else {
        numEntries++;
    }

    int i = numEntries - 2;
    while(i >= 0 && newScore > entries[i].getScore()) {
        entries[i + 1] = entries[i];
        i--;
    }
    entries[i + 1] = e;
}

GameEntry Scores::remove(int i) {
    if(i < 0 || i >= numEntries) {
        throw std::out_of_range("Index out of bounds!");
    }
    GameEntry e = entries[i];
    for(int j = i; j < numEntries; ++j) {
        entries[j - 1] = entries[j];
    }
    numEntries--;
    return e;
}

#endif
