//Student ID: 20587063

#include <iostream>
#include "Automaton.h"
#include <vector>
#include <string>
#include <bitset>

using namespace std;

Automaton::Automaton(size_t num_parents, size_t rule){
	_extreme_bit = 0;
	if(num_parents > MAX_PARENTS){
		_is_valid = false;
		_num_parents = 0;
	}
	else {
		_num_parents = num_parents;
		set_rule(rule);
	}
}

string
Automaton::get_first_n_generations(size_t n, size_t width){
	string result = "";
	if(width % 2 == 0){
		return result;
	}
	vector <int> current_gen, next_gen;
	for(size_t i = 0; i < n; i++){
		if (make_next_gen(current_gen, next_gen)){
			result += generation_to_string(next_gen, width) + "\n";
			current_gen = next_gen;
			next_gen.clear();
		}
	}
	return result;
}

bool
Automaton::make_next_gen(const vector<int> &current_gen, vector<int> &next_gen){
	next_gen.clear();
	if(current_gen.size() == 0){
		if(!_is_valid){
			return false;
		}
		_extreme_bit = 0;
		next_gen.push_back(1);
		return true;
	}
	if(!_is_valid || current_gen.size() % 2 == 0){
		return false;
	}
	vector <int> temp;
	size_t i;
	for(i = 0; i < _num_parents -1; i++){
		temp.push_back(_extreme_bit);
	}
	for(i = 0; i < current_gen.size(); i++){
		temp.push_back(current_gen[i]);
	}
	for(i = 0; i < _num_parents-1; i++){
		temp.push_back(_extreme_bit);
	}
	for(i = 0; i < current_gen.size() + _num_parents -1; i++){
		next_gen.push_back(_rules[translate_n_bits_starting_at(temp, i, _num_parents)]);
		if(_extreme_bit == 0){
			_extreme_bit = _rules[0];
		}
		else{
			_extreme_bit = _rules[_rules.size()-1];
		}
	}
	return true;
}

bool
Automaton::equals(const Automaton& that){
	if(!(this->_is_valid && that._is_valid) || (this->_is_valid && that._is_valid)){
		if((this->_num_parents == that._num_parents) 
			&& (this->_rules == that._rules)
			&& (this->_extreme_bit == that._extreme_bit)){
			return true;
		}
	}
	return false;
}

bool 
Automaton::set_rule(size_t rule){
	size_t max_permitted = pow_2(pow_2(_num_parents))-1;
	if(rule > max_permitted){
		_is_valid = false;
		return false;
	}
	bitset<32> bit(rule);
	for(size_t i = 0; i < pow_2(_num_parents); i++){
		_rules.push_back(bit.test(i));
	}
	_is_valid = true;
	return true;
}

string
Automaton::generation_to_string(const vector<int>& gen, size_t width){
	//#if 0
	string result = "";
	size_t gen_size = gen.size();
	if(!_is_valid|| width % 2 == 0 ){//|| gen_size % 2 == 0 ){
		return result;
	}
	if(width < gen_size){
		for (size_t i = (gen_size - width)/2; i < gen_size - ((gen_size - width)/2); i++){
			string s = (gen[i] == 0)? " ":"*";
			result += s;
		}
	}
	else{
		size_t pad = (width - gen_size) / 2;
		for(size_t i = 0; i < pad; i++){
			result += (_extreme_bit == 0)? " ":"*";
		}
		for(size_t i = 0; i < gen_size; i++){
			string s = (gen[i] == 0)? " ":"*";
			result += s;
		}
		for(size_t i = 0; i < pad; i++){
			result += (_extreme_bit == 0)? " ":"*";
		}
	}
	return result;
	//#endif
}

size_t
Automaton::translate_n_bits_starting_at(const vector<int>& bits, size_t pos, size_t n){
	size_t result = 0;
	if(pos + n <= bits.size()){
		for(size_t i = pos; i < pos + n; i++){
			result += bits[i] * pow_2(n-1-i+pos);
		}
	}
	return result;
}