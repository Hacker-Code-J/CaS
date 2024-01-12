fn main() {
    // Define the S-box mapping
    let s_box = [0xA, 0x8, 0xF, 0x4, 0x2, 0x9, 0xE, 0xD, 0xC, 0xB, 0x6, 0x0, 0x5, 0x1, 0x3, 0x7];

    // Initialize the Linear Approximation Table
    let mut lat = [[0; 16]; 16];

    // Compute the LAT
    for input_mask in 0..16 {
        for output_mask in 0..16 {
            let mut sum = 0;
            for input in 0..16 {
                let output = s_box[input];
                if hamming_weight(input & input_mask) % 2 == hamming_weight(output & output_mask) % 2 {
                    sum += 1;
                }
            }
            lat[input_mask][output_mask] = sum - 8; // Subtract 8 to center around 0
        }
    }

    // Print the LAT
    for row in &lat {
        for &val in row {
            print!("{:03x} ", val);
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