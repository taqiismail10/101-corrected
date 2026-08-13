import math
import matplotlib.pyplot as plt


def main():
    # Given observed data
    x = [
        99.79, 99.56, 100.17, 100.33,
        100.26, 100.31, 99.98, 99.83,
        101.23, 100.27, 100.02, 100.47,
        99.55, 99.62, 99.65, 99.82
    ]

    n = len(x)

    # Calculate sample mean
    sample_mean = sum(x) / n

    # Sort observed data
    sorted_x = sorted(x)

    # Lists for Q-Q plot
    probabilities = []
    exponential_quantiles = []

    print("i Probability Sorted_Observed Exponential_Quantile")

    for i in range(1, n + 1):
        # Probability formula: (i - 0.5) / n
        p = (i - 0.5) / n

        # Exponential quantile formula
        q = -sample_mean * math.log(1 - p)

        probabilities.append(p)
        exponential_quantiles.append(q)

        print(f"{i} {p:.4f} {sorted_x[i - 1]:.4f} {q:.4f}")

    print(f"OK: SAMPLE_MEAN {sample_mean:.4f}")
    print(
        "OK: COMMENT If points are close to a straight line, "
        "exponential assumption is acceptable; here values cluster near 100, "
        "so exponential fit is weak."
    )

    # Draw Q-Q plot
    plt.figure(figsize=(8, 6))

    # X-axis = Exponential theoretical quantiles
    # Y-axis = Sorted observed values
    plt.scatter(exponential_quantiles, sorted_x, marker="o")

    plt.xlabel("Exponential Quantile")
    plt.ylabel("Sorted Observed Value")
    plt.title("Q-Q Plot for Exponential Distribution")
    plt.grid(True)

    # Save graph as PNG
    plt.savefig("qq_plot_exponential.png", dpi=300, bbox_inches="tight")
    plt.close()

    print("SUCCESS: PNG graph generated -> qq_plot_exponential.png")


if __name__ == "__main__":
    main()