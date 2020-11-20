use std::io;
use std::cmp::Ordering;
use rand::Rng;

fn main() {
    let mines_amount = rand::thread_rng().gen_range(1, 129); // [a,b)

    loop {
        println!("Please input:");
        let mut x = String::new();
        io::stdin().read_line(&mut x).expect("Failed to read line");
        let x: u32 = match x.trim().parse() {
            Ok(num) => num,
            Err(_) => continue,
        };

        match x.cmp(&mines_amount) {
            Ordering::Less => println!("Too small!"),
            Ordering::Greater => println!("Too big!"),
            Ordering::Equal => {
                println!("You win!");
                break;
            }
        }
    }
}
