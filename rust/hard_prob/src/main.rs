
extern crate num;
extern crate rand;

use std::{env, process};
use rand::prelude::*;
use num::{Integer, BigUint, pow};

fn gen_nums(n: u64) -> Vec<u64> {
    let mut rand_nums = Vec::with_capacity(n as usize);
    let mut rng = thread_rng();
    for _ in 0..n {
        rand_nums.push(rng.gen_range(0, 100));
    }

    rand_nums
}

fn get_slice(n: &BigUint, nums: &Vec<u64>) -> Vec<u64> {
    
    let mut subset = n.clone();
    let mut i = 0;
    let mut set = Vec::new();
    while subset != BigUint::from(0 as u32) {
        if subset.is_odd() {
            set.push(nums[i]);
        }
        i += 1;
        subset >>= 1;
    }
    
    set
}

fn subset_sum(nums: &Vec<u64>, k: u64) -> (bool, BigUint) {
    let base = BigUint::from(2 as u32);
    let num_subsets = pow::pow(base, nums.len());

    let mut i = BigUint::from(0 as u32);
    while i < num_subsets {
        let subset = get_slice(&i, &nums);
        let sum: u64 = subset.iter().sum();
        if sum == k {
            return (true, i);
        }
        //println!("{}: {} {:?}", i, sum, subset);
        i = i + 1 as u64;
    }

    (false, BigUint::from(0 as u32))
}

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() != 3 {
        println!("Usage {} <N> <k>", args[0]);
        process::exit(-1);
    }

    let n = match args[1].parse::<u64>() {
        Ok(n) => n,
        Err(_) => {
            println!("Please enter a positive integer for N!");
            process::exit(-1);
        },
    };

    let k = match args[2].parse::<u64>() {
        Ok(k) => k,
        Err(_) => {
            println!("Please enter a positive integer for k!");
            process::exit(-1);
        },
    };

    println!("Magic number is {}!", n);
    println!("Target number is {}!", k);

    let nums = gen_nums(n);

    let (exists, subset) = subset_sum(&nums, k);

    if exists {
        println!("There exists a subset that equals {} and it is: {:?}", k, get_slice(&subset, &nums));
    }
}
