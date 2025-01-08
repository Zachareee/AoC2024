use std::{collections::HashSet, fs::File, io::Read};

#[derive(Eq, PartialEq, Hash, Clone, Copy)]
struct Facing(i32, i32);
const UP: Facing = Facing(-1, 0);
const RIGHT: Facing = Facing(0, 1);
const DOWN: Facing = Facing(1, 0);
const LEFT: Facing = Facing(0, -1);

struct Guard<'a> {
    position: (i32, i32),
    facing: Facing,
    map: &'a Vec<Vec<u8>>,
    size: i32,
}

impl<'a> Guard<'a> {
    fn make_move(&mut self) {
        self.avoid((-1, -1));
    }

    fn avoid(&mut self, obstacle: (i32, i32)) {
        while self.next_position() == obstacle || self.next_space() == &b'#' {
            self.rotate();
        }

        self.position = self.next_position();
        while self.can_move() && self.next_space() == &b'#' {
            self.rotate();
        }
    }

    fn rotate(&mut self) {
        self.facing = match self.facing {
            UP => RIGHT,
            RIGHT => DOWN,
            DOWN => LEFT,
            LEFT => UP,
            _ => Facing(0, 0),
        }
    }

    fn next_position(&self) -> (i32, i32) {
        let Guard {
            position, facing, ..
        } = self;
        (position.0 + facing.0, position.1 + facing.1)
    }

    fn next_space(&self) -> &u8 {
        let (row, col) = self.next_position();
        self.map
            .get(row as usize)
            .unwrap()
            .get(col as usize)
            .unwrap()
    }

    fn can_move(&self) -> bool {
        let Guard { size, .. } = *self;
        let new_pos = self.next_position();
        !(new_pos.0 < 0 || new_pos.1 < 0 || new_pos.0 >= size || new_pos.1 >= size)
    }

    fn find_guard(map: &'a Vec<Vec<u8>>) -> Self {
        for (row, line) in map.iter().enumerate() {
            for (col, c) in line.iter().enumerate() {
                if c == &b'^' {
                    let position = (row.try_into().unwrap(), col.try_into().unwrap());
                    return Self {
                        position,
                        facing: UP,
                        map,
                        size: map.len().try_into().unwrap(),
                    };
                }
            }
        }
        panic!("Guard not found");
    }
}

impl<'a> Clone for Guard<'a> {
    fn clone(&self) -> Self {
        Guard { ..*self }
    }
}

fn answer1(map: &Vec<Vec<u8>>) -> i32 {
    let mut guard = Guard::find_guard(map);
    let mut set = HashSet::new();
    set.insert(guard.position);

    while guard.can_move() {
        guard.make_move();

        set.insert(guard.position);
    }
    set.len().try_into().unwrap()
}

fn answer2(map: &Vec<Vec<u8>>) -> i32 {
    let mut guard = Guard::find_guard(map);
    let mut obs = 0;
    let mut moved = HashSet::new();

    moved.insert(guard.position);
    while guard.can_move() {
        if !moved.contains(&guard.next_position()) && can_loop(&guard) {
            obs += 1
        }

        guard.make_move();
        moved.insert(guard.position);
    }
    obs
}

fn can_loop(guard: &Guard) -> bool {
    let mut set = HashSet::new();
    let mut guard = guard.clone();
    let obs = guard.next_position();

    set.insert((guard.position, guard.facing));

    guard.rotate();
    while guard.can_move() {
        guard.avoid(obs);

        if set.contains(&(guard.position, guard.facing)) {
            return true;
        }
        set.insert((guard.position, guard.facing));
    }
    false
}

fn main() {
    let map = read_file("input.txt");

    println!("{}", answer1(&map));
    println!("{}", answer2(&map));
}

fn read_file(filename: &str) -> Vec<Vec<u8>> {
    let mut f = File::open(filename).expect("Unable to find file");

    let mut str = String::new();
    f.read_to_string(&mut str).expect("Unable to read file");
    str.lines()
        .into_iter()
        .map(|line| line.bytes().collect())
        .collect()
}

#[test]
fn eg() {
    let map = read_file("eg.txt");

    assert_eq!(answer2(&map), 6);
}

#[test]
fn eg2() {
    let map = read_file("eg2.txt");

    assert_eq!(answer2(&map), 1);
}

#[test]
fn eg3() {
    let map = read_file("eg3.txt");

    assert_eq!(answer2(&map), 3);
}

#[test]
fn eg4() {
    let map = read_file("eg4.txt");

    assert_eq!(answer2(&map), 3);
}
