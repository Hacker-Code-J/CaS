use std::sync::Mutex;
use rayon::prelude::*;

fn main() {
    // S-box mapping (4-bit input to 4-bit output)
    let s_box = [0xA, 0x8, 0xF, 0x4, 0x2, 0x9, 0xE, 0xD, 0xC, 0xB, 0x6, 0x0, 0x5, 0x1, 0x3, 0x7];

    // Initialize the Linear Approximation Table
    let lat = Mutex::new([[0; 16]; 16]);

    // Parallel computation of the LAT
    (0..16usize).into_par_iter().for_each(|input_mask| {
        for output_mask in 0..16 {
            let mut sum = 0;
            for input in 0..16 {
                let output = s_box[input];
                if hamming_weight(input & input_mask) % 2 == hamming_weight(output & output_mask) % 2 {
                    sum += 1;
                }
            }
            lat.lock().unwrap()[input_mask][output_mask] = sum - 8; // Center around 0
        }
    });

    // Print the LAT
    let lat = lat.lock().unwrap();
    for row in lat.iter() {
        for &val in row {
            print!("{:02x} ", val);
        }
        println!();
    }
}

// Function to calculate the Hamming weight (number of '1' bits)
fn hamming_weight(mut x: usize) -> usize {
    let mut count = 0;
    while x != 0 {
        count += x & 1;
        x >>= 1;
    }
    count
}