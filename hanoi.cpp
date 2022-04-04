#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

int main() {
    int pile_num;
    int pile_size;
    std::cout << "insert pile number: ";
    std::cin >> pile_num;
    std::cout << "insert pile size: ";
    std::cin >> pile_size;

    std::vector<std::list<int>> piles(pile_num, std::list<int>());

    for (int j = pile_size; j > 0; j--) {
        piles[0].push_back(j);
    }

    int level = 0;
    int last_out = 0;
    int last_in = 0;
    while (true) {
        auto pile = std::max_element(piles.begin(), piles.end(), [&](const std::list<int>& lhs, const std::list<int>& rhs) {
            return lhs.back() < rhs.back();
            });
        if (level > 0) {
            pile = std::find_if(piles.begin(), piles.end(), [&](const std::list<int>& lhs) {
                return lhs.back() == pile->back() - level;
                });
            if (pile == piles.end()) {
                level++;
                continue;
            }
        }

        int diskNum = pile->back();
        pile->pop_back();
        int index = pile - piles.begin();
        int pos;
        std::cout << "index: " << index << "\n";

        for (int i = (index + 1) % piles.size(); i != index; i++) {
            i = i % piles.size();
            pos = i;
            if ((piles[i].back() > diskNum || piles[i].back() == 0) && !(diskNum == last_out && last_in == piles[i].back())) {
                break;
            }
            if ((i + 1) % piles.size() == index) {
                pos = index;
            }
        }

        if (pos == index) {
            level++;
            pile->push_back(diskNum);
            std::cout << "level: " << level << "\n";
            continue;
        }
        level = 0;
        last_in = pile->back();
        last_out = diskNum;

        std::cout << diskNum << " num " << pile->back() << "\n";

        piles[pos].push_back(diskNum);

        if (diskNum == 1 && pos == 2) {
            int last_pos = pile_num - 1;
            int n = *piles[piles.size() - 1].begin() + 1;
            if (n == pile_size + 1) {
                for (auto j = piles[last_pos].begin(); j != piles[last_pos].end(); j++) {
                    std::cout << *j << "\n";
                    if (n - *j != 1) {
                        std::cout << "Not Hanoi\n";
                        break;
                    }
                    n = *j;
                }
                if (n == 1) {
                    std::cout << "Hanoi\n";
                    return 0;
                }
            }
        }
        for (int i = 0; i < piles.size(); i++) {
            std::cout << i << "n\n";
            std::cout << piles[i].back() << "\n";
        }
    }
}