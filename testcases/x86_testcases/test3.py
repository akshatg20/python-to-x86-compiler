def factorial(x : int) -> int:
    if x <= 1:
        return 1
    else:
        return x * factorial (x - 1)

def main() -> None:
    x : int = 10
    i : int = 0
    for i in range(x + 1):
        y : int = factorial(i)
        print("Value of factorial of ", i, " is equal to ", y)
    return

if __name__ == "__main__":
    main()
