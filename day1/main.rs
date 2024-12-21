use std::{collections::HashSet, fs::File, io::Read};

fn main() {
    let mut f = File::open("input.txt").unwrap();

    let mut bytes = Vec::new();
    f.read_to_end(&mut bytes).unwrap();

    let lines = String::from_utf8(bytes).unwrap();
    let iterator = lines.split("\n");

    let mut arr1: Vec<i32> = Vec::new();
    let mut arr2: Vec<i32> = Vec::new();

    for line in iterator {
        if !line.is_empty() {
            let strings = line.split_once("   ").ok_or(0).unwrap();
            arr1.push(strings.0.parse().unwrap());
            arr2.push(strings.1.parse().unwrap());
        }
    }

    println!("{}", answer1(arr1.as_mut(), arr2.as_mut()));
    println!("{}", answer2(arr1, arr2));
}

fn answer1(arr1: &mut Vec<i32>, arr2: &mut Vec<i32>) -> i32 {
    arr1.sort();
    arr2.sort();

    arr1.iter()
        .zip(arr2.iter())
        .fold(0, |acc, (a, b)| acc + (a - b).abs())
}

fn answer2(arr1: Vec<i32>, arr2: Vec<i32>) -> i32 {
    HashSet::<i32>::from_iter(arr1).iter().fold(0, |acc, x| {
        acc + x * arr2.iter().filter(|y| x == *y).count() as i32
    })
}
