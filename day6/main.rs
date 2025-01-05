use std::{collections::HashSet, fs::File, io::Read};

fn answer1(map: &Vec<&str>) -> i32 {
    let (mut position, mut facing) = find_guard(map);
    let mut set = HashSet::new();
    set.insert(position);

    loop {
        if !can_move(&position, &facing, map.len().try_into().unwrap()) {
            break;
        };
        (position, facing) = {
            {
                if map
                    .get((position.0 + facing.0) as usize)
                    .unwrap()
                    .chars()
                    .nth((position.1 + facing.1).try_into().unwrap())
                    .unwrap()
                    == '#'
                {
                    facing = rotate(facing);
                }
            }
            ((position.0 + facing.0, position.1 + facing.1), facing)
        };
        set.insert(position);
    }

    return set.len().try_into().unwrap();
}

fn find_guard(map: &Vec<&str>) -> ((i32, i32), (i32, i32)) {
    for (row, line) in map.iter().enumerate() {
        for (col, c) in line.chars().enumerate() {
            if let Some(facing) = direction(c) {
                return ((row.try_into().unwrap(), col.try_into().unwrap()), facing);
            }
        }
    }
    panic!("Guard not found");
}

fn rotate(facing: (i32, i32)) -> (i32, i32) {
    match facing {
        (-1, 0) => (0, 1),
        (0, 1) => (1, 0),
        (1, 0) => (0, -1),
        (0, -1) => (-1, 0),
        _ => (0, 0),
    }
}

fn can_move(position: &(i32, i32), facing: &(i32, i32), size: i32) -> bool {
    let new_pos = ((position.0 + facing.0), (position.1 + facing.1));
    !(new_pos.0 < 0 || new_pos.1 < 0 || new_pos.0 == size || new_pos.1 == size)
}

fn direction(c: char) -> Option<(i32, i32)> {
    match c {
        '^' => Some((-1, 0)),
        '>' => Some((0, 1)),
        '<' => Some((0, -1)),
        'v' => Some((1, 0)),
        _ => None,
    }
}

fn main() {
    let mut f = File::open("input.txt").expect("Unable to find file");

    let mut str = String::new();
    f.read_to_string(&mut str).expect("Unable to read file");
    let v: Vec<&str> = str.lines().collect();

    println!("{}", answer1(&v))
}
