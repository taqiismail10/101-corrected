import math
import matplotlib.pyplot as plt


def main():
    # Given observed data
    x = [
        79.919, 3.081, 0.062, 1.961,
        3.027, 6.505, 0.021, 0.013,
        6.769, 59.89, 1.192, 34.76,
        18.38, 0.141, 43.56, 24.42
    ]

    n = len(x)

    # Calculate sample mean
    sample_mean = sum(x) / n

    # Sort observed data
    sorted_x = sorted(x)

    # Lists for plotting
    probabilities = []
    exponential_quantiles = []

    print("i Probability Observed Exponential_Quantile")

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
        "OK: COMMENT Use the observed-vs-theoretical pairs for the Q-Q plot; "
        "approximate linearity supports exponential distribution."
    )

    # Draw Q-Q plot
    plt.figure(figsize=(8, 6))

    # X-axis = theoretical exponential quantile
    # Y-axis = sorted observed value
    plt.scatter(exponential_quantiles, sorted_x, marker="o")

    plt.xlabel("Exponential Quantile")
    plt.ylabel("Sorted Observed Value")
    plt.title("Q-Q Plot for Exponential Distribution")
    plt.grid(True)

    # Save graph as PNG
    plt.savefig("q21_qq_plot_exponential.png", dpi=300, bbox_inches="tight")
    plt.close()

    print("SUCCESS: PNG graph generated -> q21_qq_plot_exponential.png")


if __name__ == "__main__":
    main()