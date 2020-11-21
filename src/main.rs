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

fn get_int() -> u8 {
    let mut number = String::new();
    io::stdin().read_line(&mut number).expect("Failed to read line");
    let number: u8 = number.trim().parse().expect("Excepted an integer");
    return number;
}

impl Game {
    fn build_board(&mut self, x: u8, y: u8) {
        let mut mine_x: u8;
        let mut mine_y: u8;
        let mut mines_amount = 0;

        for column in 0..COLUMN_AMOUNT {
            self.number_array[column as usize][0] = 10;
            self.number_array[column as usize][11] = 10;
        }
        for row in 0..ROW_AMOUNT {
            self.number_array[0][row as usize] = 10;
            self.number_array[11][row as usize] = 10;
        }
        while mines_amount < MINE_AMOUNT {
            println!("{}", mines_amount);
            mine_x = rand::thread_rng().gen_range(1, (COLUMN_AMOUNT - 1) as u8);
            mine_y = rand::thread_rng().gen_range(1, (ROW_AMOUNT - 1) as u8);
            if self.number_array[mine_x as usize][mine_y as usize] == 0 {
                if (mine_x as i16 - x as i16).abs() > 1 && (mine_y as i16 - y as i16).abs() > 1
                {
                    self.number_array[mine_x as usize][mine_y as usize] = 9;
                    mines_amount += 1;
                }
            }
        }
        for x in 1..COLUMN_AMOUNT-1
        {
            for y in 1..ROW_AMOUNT-1
            {
                if self.number_array[x][y] == 0
                {
                    if self.number_array[x-1][y-1] == 9 { self.number_array[x][y] += 1 }
                    if self.number_array[x-1][y] == 9 { self.number_array[x][y] += 1 }
                    if self.number_array[x-1][y+1] == 9 { self.number_array[x][y] += 1 }
                    if self.number_array[x][y-1] == 9 { self.number_array[x][y] += 1 }
                    if self.number_array[x][y+1] == 9 { self.number_array[x][y] += 1 }
                    if self.number_array[x+1][y-1] == 9 { self.number_array[x][y] += 1 }
                    if self.number_array[x+1][y] == 9 { self.number_array[x][y] += 1 }
                    if self.number_array[x+1][y+1] == 9 { self.number_array[x][y] += 1 }
                }
            }
        }
    }
    fn output(&self) {
        print!(" ");
        for column in 1..COLUMN_AMOUNT-1 {
            print!(" {}", column);
        }
        println!();
        for row in 1..ROW_AMOUNT-1 {
            print!("{}", row);
            for column in 1..COLUMN_AMOUNT-1 {
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
                    print!("{}{}", self.number_array[row][column], color::Fg(color::White));
                }
                else {
                    print!("{}H", color::Fg(color::White));
                }
            }
            println!();
        }
    }
    fn spread(&mut self, x: i16, y: i16) {
        for i in -1..2 {
            for j in -1..2 {
                if i == 0 && j == 0 {
                    continue;
                }
                if !self.uncovered_array[(x + i) as usize][(y + j) as usize]
                {
                    self.uncovered_array[(x + i) as usize][(y + j) as usize] = true;
                    if self.number_array[(x + i) as usize][(y + j) as usize] == 0 {
                        self.spread(x + i, y + j);
                    }
                }
            }
        }
    }
    fn input(&mut self) -> bool {
        println!("Enter coordinates: (c/r)");
        let x = get_int();
        let y = get_int();
        self.uncovered_array[x as usize][y as usize] = true;
        if self.number_array[x as usize][y as usize] == 9 {
            return true;
        }
        if self.number_array[x as usize][y as usize] == 0 {
            self.spread(x as i16, y as i16)
        }
        return false;
    }
    fn first_input(&mut self) {
        println!("Enter coordinates: (c/r)");
        let x = get_int();
        let y = get_int();
        self.build_board(x, y);
        self.uncovered_array[x as usize][y as usize] = true;
        if self.number_array[x as usize][y as usize] == 0 { self.spread(x as i16, y as i16); }
    }
    fn check(&self) -> bool {
        let mut covered = 0;
        for column in 1..COLUMN_AMOUNT-1 {
            for row in 1..ROW_AMOUNT-1 {
                if !self.uncovered_array[column][row] { covered += 1; }
                if covered > MINE_AMOUNT {
                    return false;
                }
            }
        }
        return true;
    }
    fn core(&mut self) -> bool {
        self.first_input();
        self.output();
        while !self.check()
        {
            if self.input() {
                return false;
            }
            self.output();
        }
        return true;
    }
}

fn main() {
    let mut game: Game = Default::default();
    if game.core() {
        println!("Congratulations! You've won!");
    }
    else {
        println!("You've lost!");
    }
}
