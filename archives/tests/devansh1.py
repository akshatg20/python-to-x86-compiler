def check_prime(a) -> bool:
    for i in range(2, a):
        if i*i > a:
            break
        if a%i == 0:
            return False
    return True

def main() -> None:
    number_str : str = input("Please provide your number here: ")
    number : int = int(number_str)
    flag : bool = check_prime(number)
    if flag is True:
        print("The Given Number is prime")
    else:
        print("The Given number is not prime")

if __name__ == "__main__":
    main()
