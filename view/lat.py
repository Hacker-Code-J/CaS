import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

def read_and_parse_data(file_path):
    with open(file_path, 'r') as file:
        # Read lines and split each line into elements
        lines = file.readlines()
        data = []
        for line in lines:
            # Convert each hex string to an integer, handling negative values
            row = [int(num, 16) if num[0] != '-' else -int(num[1:], 16) for num in line.split()]
            data.append(row)
        return np.array(data)

def visualize_data(data):
    sns.set()
    plt.figure(figsize=(10, 8))
    sns.heatmap(data, annot=True, fmt="d", cmap='coolwarm', linewidths=.5)
    plt.title('Bias Heatmap from 4-bit S-Box')
    plt.show()

# Replace 'path_to_your_file.txt' with your actual file path
file_path = 'SBOX_LAT.txt'
data = read_and_parse_data(file_path)
visualize_data(data)