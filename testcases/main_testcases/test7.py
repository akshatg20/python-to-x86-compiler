def is_prime(x : int) -> bool:
    i : int = 2
    for i in range(2, x):
        if i * i > x:
            break
        if x % i == 0:
            print("The given number is divisible by ", i)
            return False
    return True

def main() -> None:
    x : int = int(input("Enter your number here: "))
    check : bool = is_prime(x)
    if check == True:
        print("The given number is prime.")
    else:
        print("The given number is not prime.")
    return

if __name__ == "__main__":
    main()
