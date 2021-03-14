#include <iostream>
#include <fstream>
#include <vector>

int main() {
	std::vector<int> nums;
	std::ifstream is("1.input.txt");
	
	while (is) {
		int n;
		is >> n;
		nums.emplace_back(n);
	}
	
	int i, j, k;
	for (i = 0; i < nums.size(); i++)
		for (j = 0; j < nums.size(); j++)
			for (k = 0; k < nums.size(); k++)
				if (nums[i] + nums[j] + nums[k] == 2020 && i != j && j != k && i != k)
					std::cout <<i * j * k <<std::endl;
}
