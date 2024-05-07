def main() -> None:
    """
    Compute the factorial of a number and print the same
    """
    x : int = 10
    i : int = 0
    for i in range(x + 1):
        j : int = 0
        val : int = 1
        for j in range(i):
            val = val * (j + 1)
        print("Value of factorial of ", i, " is equal to ", val)
    return

if __name__ == "__main__":
    main()
