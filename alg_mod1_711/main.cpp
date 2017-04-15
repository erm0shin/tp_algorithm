#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> weight, power;

    int w = 0, p = 0;
    while(std::cin >> w >> p) {
        weight.push_back(w);
        power.push_back(p);
    }
    std::sort(weight.begin(), weight.end());
    std::sort(power.begin(), power.end());

    int cur_weight = weight[0], cur_height = 1;
    for(int i = 1; i < weight.size(); i++)
        if(power[i] >= cur_weight) {
            cur_weight += weight[i];
            cur_height++;
        }

    std::cout << cur_height << std::endl;
    return 0;
}