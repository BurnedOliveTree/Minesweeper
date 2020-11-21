extern crate termion;

use std::io;
use rand::Rng;
use termion::{color};

const ROW_AMOUNT: usize = 10+2*1;
const COLUMN_AMOUNT: usize = 10+2*1;
const MINE_AMOUNT: u64 = 10;

struct Game {
    number_array: [[u8; COLUMN_AMOUNT]; ROW_AMOUNT],
    uncovered_array: [[bool; COLUMN_AMOUNT]; ROW_AMOUNT],
}

impl Default for Game {
    fn default() -> Game {
        Game {
            number_array: [[0; COLUMN_AMOUNT]; ROW_AMOUNT],
            uncovered_array: [[false; COLUMN_AMOUNT]; ROW_AMOUNT],
        }
    }
}

impl Game {
    fn build_mines(&mut self, x: u8, y: u8) {
        let mut mine_x: u8;
        let mut mine_y: u8;
        let mut mines_amount = 0;

        while mines_amount < MINE_AMOUNT {
            mine_x = rand::thread_rng().gen_range(1, (COLUMN_AMOUNT + 2) as u8);
            mine_y = rand::thread_rng().gen_range(1, (ROW_AMOUNT + 2) as u8);
            if self.number_array[mine_x as usize][mine_y as usize] == 0 {
                if (mine_x as i16 - x as i16).abs() > 1 && (mine_y as i16 - y as i16).abs() > 1
                {
                    self.number_array[mine_x as usize][mine_y as usize] = 9;
                    mines_amount += 1;
                }
            }
        }
        for x in 1..COLUMN_AMOUNT
        {
            for y in 1..ROW_AMOUNT
            {
                if self.number_array[x][y] == 0
                {
                    if self.number_array[x-1][y-1] == 9 { self.number_array[x-1][y-1] += 1 }
                    if self.number_array[x-1][y] == 9 { self.number_array[x-1][y] += 1 }
                    if self.number_array[x-1][y+1] == 9 { self.number_array[x-1][y+1] += 1 }
                    if self.number_array[x][y-1] == 9 { self.number_array[x][y-1] += 1 }
                    if self.number_array[x][y+1] == 9 { self.number_array[x][y+1] += 1 }
                    if self.number_array[x+1][y-1] == 9 { self.number_array[x+1][y-1] += 1 }
                    if self.number_array[x+1][y] == 9 { self.number_array[x+1][y] += 1 }
                    if self.number_array[x+1][y+1] == 9 { self.number_array[x+1][y+1] += 1 }
                }
            }
        }
    }
    fn output(&self) {
        print!(" ");
        for column in 1..COLUMN_AMOUNT {
            print!(" {}", column);
        }
        println!();
        for row in 1..ROW_AMOUNT {
            print!("{}", row);
            for column in 1..COLUMN_AMOUNT {
                print!(" ");
                if self.uncovered_array[row][column] {
                    match self.number_array[row][column] {
                        0 => print!("{}", color::Fg(color::Black)),
                        1 => print!("{}", color::Fg(color::LightGreen)),
                        2 => print!("{}", color::Fg(color::LightBlue)),
                        3 => print!("{}", color::Fg(color::LightYellow)),
                        4 => print!("{}", color::Fg(color::LightRed)),
                        5 => print!("{}", color::Fg(color::Green)),
                        6 => print!("{}", color::Fg(color::Blue)),
                        7 => print!("{}", color::Fg(color::Yellow)),
                        8 => print!("{}", color::Fg(color::Red)),
                        9 => print!("{}", color::Fg(color::Magenta)),
                        _ => print!("{}", color::Fg(color::White)),
                    }
                    print!("{}", self.number_array[row][column])
                }
                else {
                    print!("{}H", color::Fg(color::White));
                }
            }
            println!();
        }
    }
    fn spread(&mut self, x: i16, y: i16) -> bool {
        for i in -1..2 {
            for j in -1..2 {
                if i == 0 && j == 0 { continue; }
                if !self.uncovered_array[(x + i) as usize][(y + j) as usize]
                {
                    self.uncovered_array[(x + i) as usize][(y + j) as usize] = true;
                    if self.number_array[(x + i) as usize][(y + j) as usize] == 0 { self.spread(x + i, y + j); }
                    else if self.number_array[(x + i) as usize][(y + j) as usize] == 9 { return true; }
                }
            }
        }
        return false;
    }
    fn input(&mut self) -> bool {
        let mut x = String::new();
        let mut y = String::new();
        io::stdin().read_line(&mut x).expect("Failed to read line");
        let x: u8 = x.trim().parse().expect("Excepted an integer");
        io::stdin().read_line(&mut y).expect("Failed to read line");
        let y: u8 = y.trim().parse().expect("Excepted an integer");
        self.uncovered_array[x as usize][y as usize] = true;
        if self.number_array[x as usize][y as usize] == 0 {
            if self.spread(x as i16, y as i16) {
                return true;
            }
        }
        return false;
    }
    fn first_input(&mut self) {
        let mut x = String::new();
        let mut y = String::new();
        io::stdin().read_line(&mut x).expect("Failed to read line");
        let x: u8 = x.trim().parse().expect("Excepted an integer");
        io::stdin().read_line(&mut y).expect("Failed to read line");
        let y: u8 = y.trim().parse().expect("Excepted an integer");
        self.build_mines(x, y);
        self.uncovered_array[x as usize][y as usize] = true;
        if self.number_array[x as usize][y as usize] == 0 { self.spread(x as i16, y as i16); }
    }
    fn check(&self) -> bool {
        let mut covered = 0;
        for column in 1..COLUMN_AMOUNT {
            for row in 1..ROW_AMOUNT {
                if !self.uncovered_array[column][row] { covered += 1; }
                if covered > MINE_AMOUNT { return false; }
            }
        }
        return true;
    }
    fn core(&mut self) -> bool {
        self.first_input();
        self.output();
        while self.check()
        {
            self.output();
            if self.input() { return false; }
        }
        return true;
    }
}

fn main() {
    let mut game: Game = Default::default();
    game.core();
}
