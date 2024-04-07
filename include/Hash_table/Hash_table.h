#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <string>
#define LEN_WORD (sizeof(size_t) * 8)
#define L 11
#define A 0.5


template<typename Key, typename Value>
class HashTable {
	struct Pair {
		Key key;
		Value value;
		friend bool operator==(Pair& first, Pair& second) {
			return true;// first.key == second.key && first.value == second.value;
		}
	};

	size_t hash(size_t key) const{
		size_t tmp = key * A;
		return	((tmp >> L) | (tmp << (sizeof(size_t) - L)));
	}

	std::vector<std::vector<Pair>> _data;
public:
	HashTable(size_t size) {
		if (size == 0)
			throw std::invalid_argument("size = 0?!");
		_data.resize(size);
	}

	HashTable(size_t size, int) {
		if (size == 0)
			throw std::invalid_argument("size = 0?!");
		_data.resize(size);
		for (size_t i = 0; i < size; ++i) {
			insert(rand(), rand());
		}
	}

	HashTable(const HashTable& second){
		_data = second._data;
	}

	void operator=(const HashTable& second) {
		_data = second._data;
	}

	Pair* find(const Key& key) const{
		size_t ind = hash(key) % _data.size();
		for (Pair p : _data[ind]) {
			if (p.key == key)
				return &p;
		}
		return nullptr;
	}

	void insert(const Key& key, const Value& value) {
		size_t ind = hash(key) % _data.size();
		Pair new_pair;
		new_pair.key = key;
		new_pair.value = value;
		_data[ind].push_back(new_pair);
	}

	void insert_or_assigned(const Key& key, const Value& value) {
		Pair* tmp = find(key);
		if (tmp)
			tmp->value = value;
		else {
			size_t ind = hash(key) % _data.size();
			Pair new_pair;
			new_pair.key = key;
			new_pair.value = value;
			_data[ind].push_back(new_pair);
		}
	}

	bool contains(const Value& value) const{
		for (std::vector<Pair> v : _data) {
			for (Pair p : v)
				if (p.value == value)
					return true;
		}
		return false;
	}

	bool erase(const Key& key) {
		size_t v_index = 0;
		for (std::vector<Pair> v : _data) {
			size_t p_ind = 0;
			for (Pair p : v) {
				if (p.key == key) {
					_data[v_index].erase(_data[v_index].begin() + p_ind);
					return true;
				}
				++p_ind;
			}
			++v_index;
		}
		return false;
	}

	bool erase_all_occurences(const Key& key) {
		size_t v_index = 0;
		bool answer = false;
		for (std::vector<Pair> v : _data) {
			size_t p_ind = 0;
			for (Pair p : v) {
				if (p.key == key) {
					_data[v_index].erase(_data[v_index].begin() + p_ind);
					answer = true;
				}
				++p_ind;
			}
			++v_index;
		}
		return answer;
	}

	size_t count(const Key& key) const{
		size_t ans = 0;
		for (std::vector<Pair> v : _data)
			for (Pair p : v)
				if (p.key == key)
					++ans;
		return ans;
	}

	friend bool operator==(const HashTable& first, const HashTable& second){
		bool ans = true;
		size_t v_index = 0;
		if (first._data.size() != second._data.size())
			return false;
		for (std::vector<Pair> v : first._data) {
			if (v.size() != second._data[v_index].size())
				return false;
			size_t p_ind = 0;
			for (Pair p : v) {
				if (p.key != second._data[v_index][p_ind].key || p.value != second._data[v_index][p_ind].value) {
					return false;
				}
				++p_ind;
			}
			++v_index;
		}
		return true;
	}

	friend std::ostream& operator << (std::ostream& os, const Pair* pair) {
		Key a = pair->key;
		Value b = pair->value;
		if (pair) {
			os << "key= " << a << ", value= " << b << std::endl;
		}
		else
			os << "Pair is empty!" << std::endl;
		return os;
	}

	friend std::ostream& operator<<(std::ostream& os, const HashTable& table) {
		os << "Hash Table:" << std::endl;
		for (std::vector<Pair> v : table._data) {
			size_t k = 1;
			for (Pair p : v) {
				for (int i = 0; i < k; ++i)
					os << "\t";
				os << "key= " << p.key << ", value= " << p.value << std::endl;
				k += 1;
			}
		}
		return os;
	}
};

