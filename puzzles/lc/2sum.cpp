#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    struct NumIdx {
        int v, i;
        NumIdx(int value, int index): v(value), i(index) {}
        bool operator<(NumIdx& other) {
            return v < other.v;
        }
    };

    std::vector<NumIdx> vs;
    for (int i = 0 ; i < nums.size(); i++)
        vs.emplace_back(nums[i], i);

    // skip nums too big
    std::sort(vs.begin(), vs.end());
    int end;
    int lowestValue = target - vs[0].v;
    for (end = vs.size() - 1; end > 0; end--)
        if (vs[end].v <= lowestValue)
            break;

    // std::cout <<"end: "<<end <<std::endl;

    // Work from outside in
    int start = 0;
    while (end >= 0) {
        while (start < end) {
            // std::cout <<start <<" : " <<end <<std::endl;
            const auto sum = vs[start].v + vs[end].v;
            // std::cout <<vs[start].v <<" + " << vs[end].v <<" = " <<sum <<std::endl;
            if (sum > target) {
                end--;
                if (start > 0) start--;
                break;
            }
            if (sum < target) {
                start++;
                continue;
            }
            return { vs[start].i, vs[end].i };
        }
    }
    return {};
}

void printResult(std::vector<int> v) {
    std::cout <<"result: ";
    if (v.size() == 2) {
        std::cout <<v[0] <<',' <<v[1] <<std::endl;
    } else {
        std::cout <<"err\n";
    }
}

int main() {
    auto v = std::vector<int>{2,7,11,15};
    printResult(twoSum(v, 9));
    v = std::vector<int>{3,2,4};
    printResult(twoSum(v, 6));
    v = std::vector<int>{3,3};
    printResult(twoSum(v, 6));
    v = std::vector<int>{0,4,3,0};
    printResult(twoSum(v, 0));
    v = std::vector<int>{-3,4,3,90};
    printResult(twoSum(v, 0));    
}