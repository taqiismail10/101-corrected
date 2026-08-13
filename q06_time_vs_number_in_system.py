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
