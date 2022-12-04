#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

struct Rucksack
{
    string compartment1;
    string compartment2;
};

// Read in text file to a vector of rucksacks
std::vector<Rucksack> read_input_to_rucksack()
{
    std::vector<Rucksack> rucksacks;
    ifstream input_file("input.txt");
    string line;

    while (getline(input_file, line))
    {
        istringstream iss(line);
        string a;
        if (!(iss >> a))
            break; // If error then break

        int nof_items_in_compartment = line.size() / 2;

        Rucksack rucksack;
        rucksack.compartment1 = line.substr(0, nof_items_in_compartment);
        rucksack.compartment2 = line.substr(nof_items_in_compartment, nof_items_in_compartment);

        rucksacks.push_back(rucksack);
    }

    return rucksacks;
}

// Find common item in both compartments for rucksack
char get_first_common_item(Rucksack rucksack)
{
    std::set<char> compartment1_set;
    for (char c : rucksack.compartment1)
    {
        compartment1_set.insert(c);
    }
    for (char c : rucksack.compartment2)
    {
        if (compartment1_set.count(c))
        {
            return c;
        }
    }
    return 0;
}

int get_priority_value(char item)
{
    if (item >= 65 && item <= 90)
    {
        return item - 38; // offset uppercase ascii letters to priority
    }
    else if (item >= 97 && item <= 122)
    {
        return item - 96; // offset lowercase ascii letters to priority
    }
    return 0;
}

// Find common badge in three rucksacks
char get_first_common_badge(Rucksack* rucksack1, Rucksack* rucksack2, Rucksack* rucksack3)
{
    std::set<char> rucksack1_set;
    std::set<char> rucksack2_set;

    for (char c : rucksack1->compartment1 + rucksack1->compartment2)
    {
        rucksack1_set.insert(c);
    }
    for (char c : rucksack2->compartment1 + rucksack2->compartment2)
    {
        rucksack2_set.insert(c);
    }

    vector<char> rucksack_intsec;
    std::set_intersection(
        rucksack1_set.begin(), rucksack1_set.end(),
        rucksack2_set.begin(), rucksack2_set.end(), std::back_inserter(rucksack_intsec));

    for (char r1r2 : rucksack_intsec)
    {
        for (char c : rucksack3->compartment1 + rucksack3->compartment2)
        {
            if (r1r2 == c)
            {
                return c;
            }
        }
    }
    return 0;
}

int solve_part_1(std::vector<Rucksack> &rucksacks){
    int sum = 0;
    for (Rucksack rucksack : rucksacks)
    {
        char item = get_first_common_item(rucksack);

        sum += get_priority_value(item);
    }
    return sum;
}

int solve_part_2(std::vector<Rucksack> &rucksacks){
    int sum = 0;

    int number_of_rucksacks = rucksacks.size();

    for (int index = 0; index < number_of_rucksacks - 2; index += 3)
    {
        char badge = get_first_common_badge(&rucksacks[index], &rucksacks[index + 1], &rucksacks[index + 2]);
        sum += get_priority_value(badge);
    }
    return sum;
}

int main()
{
    std::vector<Rucksack> rucksacks = read_input_to_rucksack();

    cout << "C++" << endl;

    char *part = getenv("part");
      if (part == NULL) {
        printf("%d\n", solve_part_1(rucksacks));
      } else if (string(part) == "part1") {
        printf("%d\n", solve_part_1(rucksacks));
      } else if (string(part) == "part2") {
        printf("%d\n", solve_part_2(rucksacks));
      } else {
        cout << "Unknown part" << endl;
      }

    return 0;
}