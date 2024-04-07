#include <gtest/gtest.h>
#include <Hash_table/Hash_table.h>
#include <time.h> 


TEST(HashTableTests, operators_test) {
	HashTable<size_t, size_t> h_table(7, 1), second = h_table;
	h_table.insert_or_assigned(10, 20);
	second.erase_all_occurences(10);
	EXPECT_TRUE(h_table.find(10));
	EXPECT_FALSE(second.find(10));
	EXPECT_FALSE(h_table == second);
}

TEST(HashTableTests, erase_test) {
}


TEST(HashTableTestsr, erase_test) {
	HashTable<size_t, size_t> h_table(10, 1);
	srand(299);
	h_table.insert(10, 20);
	std::cout << h_table;
	h_table.erase(10);
	EXPECT_FALSE(h_table.find(10));
}