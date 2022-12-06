#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <deque>

using namespace std;

typedef char crate_t;
typedef std::deque<crate_t> cratestack_t;

struct instruction_s
{
    int count;
    int from;
    int to;
};

typedef std::deque<instruction_s> instructionlist_t;

struct cratesetup_s
{
    std::deque<cratestack_t> cratestacks;
    instructionlist_t instructionlist;
};

// Read in text file to a cratesetup
cratesetup_s read_input_to_cratesetup()
{
    cratesetup_s cratesetup;
    ifstream input_file("input.txt");
    string line;

    bool is_parsing_crates = true;

    while (getline(input_file, line))
    {
        if (is_parsing_crates)
        {
            if (line.find("1") != std::string::npos) // let's use this to know we're done
            {
                is_parsing_crates = false;
            }
            else
            {
                for (int index = 1; index < line.size(); index += 4)
                {
                    char crate = line.at(index);
                    if (!std::isspace(crate))
                    {
                        int stack_number = index / 4;
                        // if too few stacks, create new stacks
                        for (int index = cratesetup.cratestacks.size(); index <= stack_number; index++)
                        {
                            cratestack_t cs;
                            cratesetup.cratestacks.push_back(cs);
                        }
                        cratesetup.cratestacks.at(stack_number).push_front(crate);
                    }
                }
            }
        }
        else
        { // is parsing moves
            instruction_s instruction;
            std::stringstream ss(line);
            std::string _move, _from, _to;
            ss >> _move >> instruction.count >> _from >> instruction.from >> _to >> instruction.to;
            cratesetup.instructionlist.push_back(instruction);
        }
    }
    return cratesetup;
}

void get_result(cratesetup_s &cratesetup)
{
    int number_of_stacks = cratesetup.cratestacks.size();
    int index = 0;
    char result[99];
    for (std::deque<crate_t> cratestack : cratesetup.cratestacks)
    {
        result[index++] = cratestack.back();
    }
    result[index++] = '\0';
    cout << result << endl;
}

void solve_part_1(cratesetup_s &cratesetup)
{
    // do all instructions one by one
    for (instruction_s instruction : cratesetup.instructionlist)
    {
        for (int moved = 0; moved < instruction.count; moved++)
        {
            crate_t crate = cratesetup.cratestacks.at(instruction.from - 1).back();
            cratesetup.cratestacks.at(instruction.from - 1).pop_back();
            cratesetup.cratestacks.at(instruction.to - 1).push_back(crate);
        }
    }
    get_result(cratesetup);
}

void solve_part_2(cratesetup_s &cratesetup)
{
    // do all instructions one by one
    for (instruction_s instruction : cratesetup.instructionlist)
    {
        std::deque<crate_t> temp;
        for (int moved = 0; moved < instruction.count; moved++)
        {
            crate_t crate = cratesetup.cratestacks.at(instruction.from - 1).back();
            cratesetup.cratestacks.at(instruction.from - 1).pop_back();
            temp.push_front(crate);
        }
        for (crate_t crate : temp)
        {
            cratesetup.cratestacks.at(instruction.to - 1).push_back(crate);
        }
    }
    get_result(cratesetup);
}

int main()
{
    cratesetup_s cratesetup = read_input_to_cratesetup();
    cout << "C++" << endl;

    char *part = getenv("part");
      if (part == NULL) {
        solve_part_1(cratesetup);
      } else if (string(part) == "part1") {
        solve_part_1(cratesetup);
      } else if (string(part) == "part2") {
        solve_part_2(cratesetup);
      } else {
        cout << "Unknown part" << endl;
      }

    return 0;
}