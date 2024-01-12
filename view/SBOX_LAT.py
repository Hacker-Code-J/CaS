import numpy as np
import matplotlib.pyplot as plt

def read_data_from_file(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()
    data = [line.strip().split() for line in lines]
    return data

def convert_hex_to_signed_int(matrix):
    matrix = np.array(matrix, dtype=str)
    matrix = np.vectorize(lambda x: int(x, 16))(matrix)
    matrix = np.vectorize(lambda x: x if x < 0x80 else x - 0x100)(matrix)
    return matrix

def plot_linear_graph(matrix):
    plt.figure(figsize=(15, 10))
    plt.title("4-bit S-box Linear Approximation Table (LAT) Analysis")

    # Plotting each row as a separate line
    for i, row in enumerate(matrix):
        plt.plot(row, label=f'Input {i:02X}')

    plt.xlabel("Output Mask")
    plt.ylabel("Value")
    plt.legend()
    plt.grid(True)
    plt.show()

# Replace with the path to your .txt file
file_path = 'SBOX_LAT.txt'

# Read and process the data
data = read_data_from_file(file_path)
matrix = convert_hex_to_signed_int(data)

# Plot the linear graph
plot_linear_graph(matrix)

# bias_values = matrix.flatten()

# # Create the histogram
# plt.figure(figsize=(10, 6))
# plt.hist(bias_values, bins=30, color='blue', alpha=0.7)
# plt.title("Histogram of Bias Values in LAT")
# plt.xlabel("Bias Value")
# plt.ylabel("Frequency")
# plt.grid(True)
# plt.show()