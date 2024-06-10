def main() -> None:
    """
    Compute the factorial of a number and print the same
    """
    x : int = 2
    y : int = 4
    for i in range(x + 1):
        j : int = 0
        val : int = 1
        for j in range(y + 1):
            val = x * y
        print("Value of product is ", val)
    return

if __name__ == "__main__":
    main()
