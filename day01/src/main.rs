use std::{
    env,
    fs::File,
    io::{BufRead, BufReader},
};

struct Elf {
    calories: Vec<i32>,
}

impl Elf {
    fn sum_calories(&self) -> i32 {
        let sum: i32 = self.calories.iter().sum();
        return sum;
    }
}

fn read_file_to_elfs(path: &str) -> Vec<Elf> {
    let file: File = File::open(path).expect("Could not read file");
    let reader: BufReader<File> = BufReader::new(file);
    let mut calories: Vec<i32> = Vec::new();
    let mut elfs: Vec<Elf> = Vec::new();
    for line in reader.lines() {
        let line: String = line.unwrap();

        if line.is_empty() {
            elfs.push(Elf {
                calories: calories.to_vec(),
            });
            calories = Vec::new();
        } else {
            let value: i32 = line.parse().unwrap();
            calories.push(value);
        }
    }

    return elfs;
}

fn get_solution_part1(elfs: &Vec<Elf>) -> i32 {
    let sums: Vec<i32> = elfs.iter().map(|f: &Elf| f.sum_calories()).collect();
    let max_calorie_elf: i32 = sums.into_iter().max().unwrap_or(0);

    println!("Highest calorie elf: {}", max_calorie_elf);
    return max_calorie_elf;
}

fn get_solution_part2(elfs: &Vec<Elf>) -> i32 {
    let sums: Vec<i32> = elfs.iter().map(|f: &Elf| f.sum_calories()).collect();

    let mut sums_sorted_by_calories: Vec<i32> = sums.clone();
    sums_sorted_by_calories.sort_by(|a: &i32, b: &i32| b.cmp(a));

    let total_top_3_elfs_sum: i32 = sums_sorted_by_calories.iter().take(3).sum();
    println!("Total of top three elfs: {}", total_top_3_elfs_sum);
    return total_top_3_elfs_sum;
}

fn main() {
    let parsed_input: Vec<Elf> = read_file_to_elfs("input.txt");

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
