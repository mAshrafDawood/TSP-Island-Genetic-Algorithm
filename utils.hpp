#include <vector>

void swap(int &x, int &y);

std::vector<int> &shuffle(std::vector<int> &array, size_t n);

void mutate(std::vector<int> &individual, size_t n, float mutation_rate);

void crossover(
    std::vector<int> &first_parent,
    std::vector<int> &second_parent,
    size_t n,
    float crossover_rate,
    std::vector<int> &first_offspring,
    std::vector<int> &second_offspring);

std::vector<std::vector<int>> read_table(std::vector<std::vector<int>> &distance_table);