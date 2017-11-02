
use std::{env, process};
use std::fs::File;
use std::io::prelude::*;

fn main() {
    let args: Vec<_> = env::args().collect();

    if args.len() != 3 {
        println!("Usage {} <in_file> <out_file>", args[0]);
        process::exit(-1);
    }

    println!("Opening {}...", args[1]);
    let contents = get_file_contents(&args[1]);

    let mut out_file = File::create(&args[2]).unwrap();
    out_file.write_fmt(format_args!("{}", contents)).unwrap();
}

fn get_file_contents(file_name: &String) -> String{
    let mut file = File::open(&file_name).unwrap();
    let mut contents = String::new();
    file.read_to_string(&mut contents).unwrap();

    contents
}

