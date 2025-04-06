// Student ID: 20587063

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Hanoi.h"

using namespace std;

std::string Hanoi::lookup_moves(int num_discs, int src, int dst) {
    /*
    if (_cache[num_discs][src][dst] == "") {return "";}
    return _cache[num_discs][src][dst]; */
    size_t st_num_discs = num_discs;
    size_t st_src = src;
    size_t st_dst = dst;
    if(_cache.size() <= st_num_discs) return "";
    if(_cache[st_num_discs].size() <= st_src) return "";
    if(_cache[st_num_discs][st_src].size() <= st_dst) return "";
    return _cache[st_num_discs][st_src][st_dst];
}


void Hanoi::store_moves(int num_discs, int src, int dst, string s) {

    _cache[num_discs][src][dst] = s;
}


std::string Hanoi::get_moves(int num_discs, int src, int dst, int tmp) {
    size_t st_num_discs = num_discs;
    size_t st_src = src;
    size_t st_dst = dst;
    if(_cache.size() <= st_num_discs) _cache.resize(st_num_discs+1);
    if(_cache[st_num_discs].size() <= st_src) _cache[st_num_discs].resize(st_src+1);
    if(_cache[st_num_discs][st_src].size() <= st_dst) _cache[st_num_discs][st_src].resize(st_dst+1);


    std::string s = lookup_moves(num_discs, src, dst);
    if (s != "") {return s;}
    if (num_discs == 0) {s = "";}
    else if (num_discs == 1) {
        s = std::to_string(src) + "->" + std::to_string(dst) + "\n";
    }
    else {
        s = get_moves(num_discs-1, src, tmp, dst) + 
            std::to_string(src) + "->" + std::to_string(dst) + "\n" + 
            get_moves(num_discs-1, tmp, dst, src);
        //store_moves(num_discs, src, dst, s);
    }
    //_cache[num_discs][src][dst] = s;
    store_moves(num_discs, src, dst, s);
    if(st_num_discs > 1) {
        _cache[st_num_discs - 1].clear();
    }
    return s;
}

std::string Hanoi::solve(int num_discs, int src, int dst, int tmp) {
    return "# Below, 'A->B' means 'move the top disc on pole A to pole B'\n" + 
        get_moves(num_discs, src, dst, tmp);
}
