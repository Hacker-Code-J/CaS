fn main() {
    let n = 4; // Example for a 4-bit S-box
    let s_box = generate_s_box(n);

    let size = 1 << n;
    let mut lat = vec![vec![0i32; size]; size]; // Using i32 to allow negative values

    for input_mask in 0..size {
        for output_mask in 0..size {
            let mut sum = 0i32; // Use i32 here
            for input in 0..size {
                let output = s_box[input];
                if hamming_weight(input ^ output) & input_mask == output_mask {
                    sum += 1;
                }
            }
            lat[input_mask][output_mask] = sum - (size as i32 / 2); // Cast size to i32
        }
    }

    // Print the LAT
    for row in &lat {
        for &val in row {
            print!("{:02X} ", val);
        }
        println!();
    }
}

fn generate_s_box(n: usize) -> Vec<usize> {
    // Example S-box generation logic. Replace with your own logic.
    (0..1<<n).collect()
}

fn hamming_weight(mut x: usize) -> usize {
    let mut count = 0;
    while x != 0 {
        count += x & 1;
        x >>= 1;
    }
    count
}