import matplotlib.pyplot as plt


def print_plot(arrival, end, n, T):
    # Collect all important event time points
    times = [0, T]

    for i in range(n):
        times.append(arrival[i])
        times.append(end[i])

    # Sort and remove duplicate time values
    unique = sorted(set(times))

    # Lists for plotting
    x_points = []
    y_points = []

    print("TIME NUMBER_IN_SYSTEM")

    # Count number of customers in system at each event time
    for t in unique:
        count = 0

        for j in range(n):
            # A customer is in the system if:
            # arrival time <= current time
            # and service end time > current time
            if arrival[j] <= t and end[j] > t:
                count += 1

        print(f"PLOT {t} {count}")

        x_points.append(t)
        y_points.append(count)

    print("OK: USE_THESE_POINTS_FOR_STEP_GRAPH")

    # Draw step graph
    plt.figure(figsize=(10, 5))
    plt.step(x_points, y_points, where="post", marker="o")

    # Add labels and title
    plt.xlabel("Time")
    plt.ylabel("Number of Customers in System")
    plt.title("Q6: Time vs Number of Customers in System")

    # Add grid for better readability
    plt.grid(True)

    # Save the graph as PNG file
    plt.savefig("q6_time_vs_number_in_system.png", dpi=300, bbox_inches="tight")

    # Close the plot after saving
    plt.close()


def main():
    # Data from textbook Table 3.2 future event list
    # Customer arrival times:
    # C1 = 0, C2 = 1, C3 = 2, C4 = 8, C5 = 11, C6 = 18
    arrival = [0, 1, 2, 8, 11, 18]

    # Customer departure/service-end times:
    # C1 = 4, C2 = 6, C3 = 11, C4 = 15, C5 = 16, C6 = 23
    end = [4, 6, 11, 15, 16, 23]

    # Total simulation ending time
    T = 23

    print_plot(arrival, end, 6, T)

    # Final success message in CLI
    print("SUCCESS: PNG graph generated -> q6_time_vs_number_in_system.png")


if __name__ == "__main__":
    main()