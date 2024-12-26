import matplotlib.pyplot as plt
from collections import Counter
from scipy.stats import entropy

def lyapunov_exponent_from_sequence(x_values, r= 4.99999999999):
    lyapunov_sum = 0
    
    for x in x_values:
        # Calculate the derivative at each point in the sequence
        derivative = logistic_map_derivative(x, r)
        
        # Sum up the log of the absolute value of the derivative
        lyapunov_sum += np.log(abs(derivative))
    
    # Return the average value
    return lyapunov_sum / len(x_values)

# Function to calculate digit frequency and plot a chart
def calculate_and_plot_digit_frequency(filename):
    with open(filename, 'r') as file:
        # Read all lines, concatenate into a single string to capture all digits

        data = file.readlines()

        digits = [ int(line.strip()) for line in data ]

    print(f"Entropy of {filename}: {entropy(digits)}")
    #print(f'Lapunov exponent of {filename}: {lyapunov_exponent_from_sequence(digits)}')
    # Count occurrences of each digit
    digit_count = Counter(digits)
    
    # Sort the counts by digit for consistent plotting
    sorted_digits = sorted(digit_count.keys())
    frequencies = [digit_count[digit] for digit in sorted_digits]
    
    # Plot the frequency distribution as a bar chart
    plt.figure(figsize=(10, 6))
    plt.bar(sorted_digits, frequencies, color='skyblue')
    plt.xlabel('Digit')
    plt.ylabel('Frequency')
    plt.title('Digit Frequency Distribution')
    plt.savefig(f"{filename}.png")

# Example usage

# calculate_and_plot_digit_frequency('simple_gen')
# calculate_and_plot_digit_frequency('double_map')
calculate_and_plot_digit_frequency('tent_seq_map')

