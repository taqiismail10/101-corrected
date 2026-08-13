import matplotlib.pyplot as plt


def print_plot(arrival, end, n, T):
    # ------------------------------------------------------------
    # Step 1: Collect all important time points
    # Important time points are:
    # 1. simulation starting time
    # 2. simulation ending time
    # 3. all arrival times
    # 4. all service ending/departure times
    # ------------------------------------------------------------
    times = [0, T]

    for i in range(n):
        times.append(arrival[i])
        times.append(end[i])

    # ------------------------------------------------------------
    # Step 2: Sort the time points and remove duplicate values
    # This is similar to qsort + unique array in the C code
    # ------------------------------------------------------------
    unique_times = sorted(set(times))

    # These lists will be used for drawing the step graph
    x_points = []
    y_points = []

    print("TIME NUMBER_IN_SYSTEM")

    # ------------------------------------------------------------
    # Step 3: Count number of customers in the system at each time
    # A customer is inside the system if:
    # arrival_time <= current_time AND end_time > current_time
    # ------------------------------------------------------------
    for t in unique_times:
        count = 0

        for j in range(n):
            if arrival[j] <= t and end[j] > t:
                count += 1

        print(f"PLOT {t} {count}")

        x_points.append(t)
        y_points.append(count)

    print("OK: USE_THESE_POINTS_FOR_STEP_GRAPH")

    # ------------------------------------------------------------
    # Step 4: Draw the step graph
    # X-axis = Time
    # Y-axis = Number of customers in system
    # ------------------------------------------------------------
    plt.figure(figsize=(10, 5))
    plt.step(x_points, y_points, where="post", marker="o")

    plt.xlabel("Time")
    plt.ylabel("Number of Customers in System")
    plt.title("Q5: Time vs Number of Customers in System")
    plt.grid(True)

    # ------------------------------------------------------------
    # Step 5: Save the graph as PNG
    # No Output.txt will be created
    # ------------------------------------------------------------
    plt.savefig("q05_time_vs_number_in_system.png", dpi=300, bbox_inches="tight")
    plt.close()


def main():
    # ------------------------------------------------------------
    # Hardcoded data from the given C code
    # No input is taken from Input.txt
    # ------------------------------------------------------------
    arrival = [0, 2, 6, 7, 9, 15]
    end = [2, 3, 9, 11, 12, 19]

    n = 6
    T = 19

    print_plot(arrival, end, n, T)

    print("SUCCESS: PNG graph generated -> q05_time_vs_number_in_system.png")


if __name__ == "__main__":
    main()
