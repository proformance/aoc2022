use std::{
    env,
    fs::File,
    io::{BufRead, BufReader},
};

const ROCK: i32 = 1;
const PAPER: i32 = 2;
const SCISSOR: i32 = 3;

// const LOSE: i32 = 1;
const DRAW: i32 = 2;
const WIN: i32 = 3;

// #[derive(Copy, Clone)]
enum SecondColumn {
    X, // how do I set values here instead??
    Y,
    Z,
}

impl SecondColumn {
    fn from(input: &str) -> SecondColumn {
        match input {
            "X" => SecondColumn::X,
            "Y" => SecondColumn::Y,
            "Z" => SecondColumn::Z,
            _ => SecondColumn::X,
        }
    }

    fn value(&self) -> i32 {
        // ugly fix, would prefer to use the enum values
        match self {
            SecondColumn::X => 1,
            SecondColumn::Y => 2,
            SecondColumn::Z => 3,
        }
    }
}

enum OpponentChoice {
    A,
    B,
    C,
}

impl OpponentChoice {
    fn from(input: &str) -> OpponentChoice {
        match input {
            "A" => OpponentChoice::A,
            "B" => OpponentChoice::B,
            "C" => OpponentChoice::C,
            _ => OpponentChoice::A,
        }
    }

    fn value(&self) -> i32 {
        // ugly fix, would prefer to use the enum values
        match self {
            OpponentChoice::A => ROCK,
            OpponentChoice::B => PAPER,
            OpponentChoice::C => SCISSOR,
        }
    }
}

struct Round {
    second_column: SecondColumn,
    opponent_choice: OpponentChoice,
}

impl Round {
    fn get_points_with_2nd_col_as_own_choice(&self) -> i32 {
        let own_choice = &self.second_column;

        let is_win: bool = own_choice.value() == ROCK && self.opponent_choice.value() == SCISSOR
            || own_choice.value() == PAPER && self.opponent_choice.value() == ROCK
            || own_choice.value() == SCISSOR && self.opponent_choice.value() == PAPER;

        let is_draw: bool = own_choice.value() == self.opponent_choice.value();

        let win_points: i32 = if is_win {
            6 // win gives 6 points
        } else if is_draw {
            3 // draw gives 3 points
        } else {
            0 // lose gives zero points
        };

        let own_points: i32 = self.second_column.value(); // always get 1/2/3 for your own choice

        return win_points + own_points;
    }

    fn get_points_with_2nd_col_as_end_result(&self) -> i32 {
        let end_result = &self.second_column;

        let end_result_is_win: bool = end_result.value() == WIN;
        let end_result_is_draw: bool = end_result.value() == DRAW;

        let win_points: i32 = if end_result_is_win {
            6
        } else if end_result_is_draw {
            3
        } else {
            0
        };

        let own_points: i32 = if end_result_is_win {
            if self.opponent_choice.value() == PAPER {
                SCISSOR // to win, use scissor
            } else if self.opponent_choice.value() == ROCK {
                PAPER // to win, use paper
            } else { // value is SCISSOR
                ROCK // to win, use rock
            }
        } else if end_result_is_draw {
            self.opponent_choice.value()
        } else { // need to lose
            if self.opponent_choice.value() == SCISSOR {
                PAPER // to lose, use paper
            } else if self.opponent_choice.value() == ROCK {
                SCISSOR // to lose, use scissor
            } else { // value is PAPER
                ROCK // to lose, use rock
            }
        };
        return win_points + own_points;
    }
}

fn read_file(path: &str) -> Vec<Round> {
    let file: File = File::open(path).expect("Could not read file");
    let reader: BufReader<File> = BufReader::new(file);

    let mut rounds: Vec<Round> = Vec::new();

    for line in reader.lines() {
        let text = line.unwrap();

        let mut columns = text.as_str().split_ascii_whitespace();

        let opponent_choice = columns.next().unwrap(); // first item is opponent
        let second_column = columns.next().unwrap(); // second item is my choice

        let round = Round {
            second_column: SecondColumn::from(second_column),
            opponent_choice: OpponentChoice::from(opponent_choice),
        };

        rounds.push(round);
    }
    return rounds;
}

fn get_solution_part1(rounds: &Vec<Round>) -> i32 {
    return rounds
        .iter()
        .map(|f| f.get_points_with_2nd_col_as_own_choice())
        .sum();
}

fn get_solution_part2(rounds: &Vec<Round>) -> i32 {
    return rounds
        .iter()
        .map(|f| f.get_points_with_2nd_col_as_end_result())
        .sum();
}

fn main() {
    let parsed_input: Vec<Round> = read_file("input.txt");

    get_solution_part1(&parsed_input);

    get_solution_part2(&parsed_input);

    let part: String = match env::var("part") {
        Ok(val) => val,
        Err(_e) => "part1".to_string(),
    };

    if part == "part2" {
        println!("{}", get_solution_part2(&parsed_input));
    } else {
        println!("{}", get_solution_part1(&parsed_input));
    }
}
