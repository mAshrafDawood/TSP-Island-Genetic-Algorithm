#include <iostream>
#include <vector>
#include <omp.h>

#include "utils.hpp"

std::vector<int> &shuffle(std::vector<int> &array, size_t n)
{
    size_t i, j;
    int t;

    if (n <= 1)
        return;

    // Shuffle
    for (i = 0; i < n - 1; i++)
    {
        j = i + rand() / (RAND_MAX / (n - i) + 1);
        swap(array[j], array[i]);
    }
    return array;
}

void mutate(std::vector<int> &individual, size_t n, float mutation_rate)
{

    float r = (float)rand() / (float)(RAND_MAX / 1);
    if (r > mutation_rate)
        return;

    int r1 = rand() / (RAND_MAX / (n - 1));
    do
    {
        int r2 = rand() / (RAND_MAX / (n - 1));
    } while (r1 == r2);

    // Mutate
    swap(individual[r1], individual[r2]);
}

void swap(int &x, int &y)
{
    int temp = x;
    x = y;
    y = temp;
}

void crossover(std::vector<int> &first_parent, std::vector<int> &second_parent, size_t n, float crossover_rate, std::vector<int> &first_offspring, std::vector<int> &second_offspring)
{
    float r = (float)rand() / (float)(RAND_MAX / 1);
    if (r > crossover_rate)
        return;

    int r1 = rand() / (RAND_MAX / (n - 1));
    do
    {
        int r2 = rand() / (RAND_MAX / (n - 1));
    } while (r1 == r2);

    for (int i = std::min(r1, r2); i < std::max(r1, r2); i++)
    {
        first_offspring[i] = first_parent[i];
        second_offspring[i] = second_parent[i];
    }

    int j1 = std::max(r1, r2);
    int j2 = j1;

    for (int i = j1; (i % n) != std::max(r1, r2); i++)
    {
        if (std::find(first_offspring.begin(), first_offspring.end(), second_parent[i % n]) == first_offspring.end())
        {
            first_offspring[j1] = second_parent[i % n];
            j1++;
        }
        if (std::find(second_offspring.begin(), second_offspring.end(), first_parent[i % n]) == second_offspring.end())
        {
            second_offspring[j2] = first_parent[i % n];
            j2++;
        }
    }
}

std::vector<std::vector<int>> read_table(std::vector<std::vector<int>> &distance_table)
{
    freopen("./data.txt", "r", std::stdin);
    for (i = 0; i < 48; i++)
    {
        for (j = 0; j < 48; j++)
        {
            std::cin >> distance_table[i][j];
        }
    }
    return distance_table;
}
