
use std::io::{self, Write};

fn input_number(message: &str) -> usize {
    loop {
        print!("{}", message);
        io::stdout().flush().unwrap();

        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();

        match input.trim().parse::<usize>() {
            Ok(n) if n > 0 => return n,
            _ => println!("1 이상의 정수를 입력하세요."),
        }
    }
}

fn main() {
    let rows = input_number("행의 크기: ");
    let cols = input_number("열의 크기: ");

    let mut a = vec![vec![0i32; cols]; rows];
    let mut b = vec![vec![0i32; cols]; rows];
    let mut result = vec![vec![0i32; cols]; rows];

    println!("\n첫 번째 행렬 입력");
    for i in 0..rows {
        for j in 0..cols {
            loop {
                print!("A[{}][{}]: ", i, j);
                io::stdout().flush().unwrap();

                let mut input = String::new();
                io::stdin().read_line(&mut input).unwrap();

                if let Ok(value) = input.trim().parse::<i32>() {
                    a[i][j] = value;
                    break;
                }
                println!("정수를 입력하세요.");
            }
        }
    }

    println!("\n두 번째 행렬 입력");
    for i in 0..rows {
        for j in 0..cols {
            loop {
                print!("B[{}][{}]: ", i, j);
                io::stdout().flush().unwrap();

                let mut input = String::new();
                io::stdin().read_line(&mut input).unwrap();

                if let Ok(value) = input.trim().parse::<i32>() {
                    b[i][j] = value;
                    break;
                }
                println!("정수를 입력하세요.");
            }
        }
    }

    for i in 0..rows {
        for j in 0..cols {
            result[i][j] = a[i][j]
                .checked_add(b[i][j])
                .expect("덧셈 결과가 i32 범위를 초과했습니다.");
        }
    }

    println!("\n행렬 덧셈 결과");
    for i in 0..rows {
        for j in 0..cols {
            print!("{:5}", result[i][j]);
        }
        println!();
    }
}

