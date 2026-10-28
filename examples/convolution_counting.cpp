#include "../library/convolution/all.hpp"

int main(){
    auto ordered = cp_transform::pair_sum_counts({1, 1, 2}, {0, 2});
    auto unordered = cp_transform::unordered_pair_sum_counts({1, 1, 2});
    auto distribution = cp_transform::sum_distribution_mod({0, 1, 1}, 2, 4);
    assert(ordered[3] == 2 && unordered[3] == 2 && distribution[3] == mint(2));
    cout << ordered[3] << ' ' << unordered[3] << ' ' << distribution[3] << '\n';
}
