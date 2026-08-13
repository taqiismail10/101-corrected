import matplotlib.pyplot as plt


def print_plot(arrival, end, n, T):
    # Collect all important time points
    times = [0, T]
    for i in range(n):
        times.append(arrival[i])
        times.append(end[i])

    # Sort and keep only unique times
    unique = sorted(set(times))

    # Store graph points
    x_points = []
    y_points = []

    print("TIME NUMBER_IN_SYSTEM")

    # For each unique time, count how many customers are in the system
    for t in unique:
        count = 0
        for j in range(n):
            if arrival[j] <= t and end[j] > t:
                count += 1

        print(f"PLOT {t} {count}")
        x_points.append(t)
        y_points.append(count)

    print("OK: USE_THESE_POINTS_FOR_STEP_GRAPH")

    # Draw step graph
    plt.figure(figsize=(10, 5))
    plt.step(x_points, y_points, where='post', marker='o')
    plt.xlabel("Time")
    plt.ylabel("Number of Customers in System")
    plt.title("Q5: Time vs Number of Customers in System")
    plt.grid(True)

    # Save graph as PNG
    plt.savefig("q5_time_vs_number_in_system.png", dpi=300, bbox_inches='tight')
    plt.close()


def main():
    # Given data from the C code
    arrival = [0, 2, 6, 7, 9, 15]
    end = [2, 3, 9, 11, 12, 19]

    print_plot(arrival, end, 6, 19)

    # Success message in CLI
    print("SUCCESS: PNG graph generated -> q5_time_vs_number_in_system.png")


if __name__ == "__main__":
    main()