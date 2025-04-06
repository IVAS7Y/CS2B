// Student ID: 20587063

#ifndef Hanoi_h
#define Hanoi_h

#include <iostream>
#include <sstream>
#include <ostream>
#include <string>
#include <vector>


using namespace std;

class Hanoi {
    private:
        int _num_poles = 3;
        int _num_discs = 10;
        // TODO: Declare the _cache member using an appropriate
        // level of nesting within std::vectors to put each string
        // of moves. You should be able to access the cache like so:
        // _cache[num_discs][src][dst] = "move1\nmove2\n..."
        vector<vector<vector<string>>> _cache;
        //_cache = vector<vector<vector<string>>>(_num_discs, vector<vector<string> >(_num_poles, vector<string>(_num_poles)));


        std::string lookup_moves(int num_discs, int src, int dst);
        std::string get_moves(int num_discs, int src, int dst, int tmp);
        void store_moves(int num_discs, int src, int dst, string s);

    public:
        // Use freebie default constructor
        Hanoi() {
            /*
            _cache.resize(_num_discs);

            for (int i = 0; i < _num_discs; i++) {
                _cache[i].resize(_num_poles + 1);
                for (int j = 0; j <= _num_poles; j++)
                    _cache[i][j].resize(_num_poles+1, "");
            }*/
        }
        std::string solve(int num_discs, int src, int dst, int tmp);
        friend class Tests; // Don't remove this line
};

#endif /* Hanoi_h */