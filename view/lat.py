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
    # sns.set()
    plt.figure(figsize=(10, 8))
    # sns.heatmap(data, annot=True, fmt="d", cmap='coolwarm', linewidths=.5)
    # plt.title('Bias Heatmap from 4-bit S-Box')
    # plt.show()
    # Create the heatmap
    ax = sns.heatmap(data, annot=True, fmt="d", cmap='coolwarm', linewidths=.5)

    # Calculate absolute values and find the largest and second largest values
    absolute_data = np.abs(data)
    flat_data = absolute_data.flatten()
    sorted_values = np.sort(np.unique(flat_data))  # Sort unique values to find the top 2

    # Extract the largest and second largest values
    if len(sorted_values) >= 2:
        largest, second_largest = sorted_values[-1], sorted_values[-2]
    elif len(sorted_values) == 1:
        largest = sorted_values[0]
        second_largest = None
    else:
        largest = second_largest = None

    # Highlight the positions of the largest and second largest values (considering absolute values)
    if largest is not None:
        largest_positions = np.where(absolute_data == largest)
        for x, y in zip(largest_positions[0], largest_positions[1]):
            ax.add_patch(plt.Rectangle((y, x), 1, 1, fill=False, edgecolor='red', lw=3))

    if second_largest is not None:
        second_largest_positions = np.where(absolute_data == second_largest)
        for x, y in zip(second_largest_positions[0], second_largest_positions[1]):
            ax.add_patch(plt.Rectangle((y, x), 1, 1, fill=False, edgecolor='blue', lw=3))

    plt.title('Bias Heatmap from 4-bit S-Box')
    plt.show()
    
# Replace 'path_to_your_file.txt' with your actual file path
file_path = 'SBOX_LAT.txt'
data = read_and_parse_data(file_path)
visualize_data(data)