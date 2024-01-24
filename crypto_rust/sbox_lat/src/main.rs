fn dot(u: i32, v: i32) -> i32 {
    let mut w = u & v;
    let mut dot = 0;

    // Using Kernighan's algorithm to count the number of set bits
    while w != 0 {
        dot ^= 1;
        w &= w - 1;  // clear the least significant bit set
    }

    dot
}

fn success(s: &[i32], alpha: i32, beta: i32, n: i32) -> i32 {
    let mut e = 0;
    let range = 1 << n;

    for x in 0..range {
        if (dot(alpha, x) ^ dot(beta, s[x as usize])) == 0 {
            e += 1;
        }
    }

    e
}

fn bias_integer(s: &[i32], alpha: i32, beta: i32, n: i32) -> i32 {
    let mut e = 0;
    let range = 1 << n;

    for x in 0..range {
        if (dot(alpha, x) ^ dot(beta, s[x as usize])) == 0 {
            e += 1;
        }
    }

    e - (range >> 1)
}

fn lat(s: &[i32], n: usize, m: usize) -> Vec<Vec<i32>> {
    let n_range = 1 << n;
    let m_range = 1 << m;

    // Allocate 2D vector and initialize with zeros
    let mut l = vec![vec![0; m_range]; n_range];

    // Compute the LAT
    for alpha in 0..n_range {
        for beta in 0..m_range {
            // l[alpha][beta] = success(s, alpha as i32, beta as i32, n as i32);
            l[alpha][beta] = bias_integer(s, alpha as i32, beta as i32, n as i32);
        }
    }

    l
}

fn print_lat(s: &[i32], n: usize, m: usize) {
    let l = lat(s, n, m);
    let n_range = 1 << n;
    let m_range = 1 << m;

    // Print column headers
    print!("     "); // Space for row header
    for beta in 0..m_range {
        print!("{:02X} ", beta);
    }
    println!(); // Newline

    // Print a separator line
    print!("   +"); // Alignment for row header
    for _ in 0..m_range {
        print!("---");
    }
    println!(); // Newline

    for alpha in 0..n_range {
        // Print row header
        print!("{:02X} | ", alpha);

        for beta in 0..m_range {
            print!("{:02} ", l[alpha][beta]);  // Right-align numbers in a field of width 2
        }
        println!(); // Newline at the end of each row
    }

    // No need to manually free memory, Rust's ownership model handles it
}

fn main() {
    // Block for one configuration (uncomment the block you want to use)
    /* // Configuration 1:
    let s = vec![0x7, 0x0, 0x6, 0x4, 0x5, 0x2, 0x1, 0x3]; // Example S-box
    let n = 3; // Example number of input bits
    let m = 3; // Example number of output bits
    */

    // Configuration 2:
    let s = vec![
        0xA, 0x8, 0xF, 0x4, 0x2, 0x9, 0xE, 0xD, 0xC, 0xB, 0x6, 0x0, 0x5, 0x1, 0x3, 0x7,
    ]; // Example S-box
    let n = 4; // Example number of input bits
    let m = 4; // Example number of output bits
    
    print_lat(&s, n, m);
}

