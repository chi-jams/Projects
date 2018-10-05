
extern crate num;
extern crate rand;

use std::{env, process};
use rand::prelude::*;
use num::{Integer, BigUint, traits, pow, cast::FromPrimitive};

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
    while subset != traits::zero() {
        if subset.is_odd() {
            set.push(nums[i]);
        }
        i += 1;
        subset >>= 1;
    }
    
    set
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

    let k = match args[1].parse::<u64>() {
        Ok(n) => n,
        Err(_) => {
            println!("Please enter a positive integer for N!");
            process::exit(-1);
        },
    };

    println!("Magic number is {}!", n);
    println!("Target number is {}!", k);

    let nums = gen_nums(n);
    for i in 0..n {
        println!("{}: {}", i, nums[i as usize]);
    }

    let base = BigUint::from(2 as u32);
    let num_subsets = pow::pow(base, nums.len());
    println!("There are {} possible subsets, {}", num_subsets, nums.len());
    

    let mut i: BigUint = traits::zero();
    while i < num_subsets {
        let subset = get_slice(&i, &nums);
        let sum: u64 = subset.iter().sum();
        println!("{}: {} {:?}", i, sum, subset);
        i = i + 1 as u64;
    }
    /*
    for (i, val) in uh.iter().enumerate() {
        println!("{}: {}", i, val);
    }
    */

}
