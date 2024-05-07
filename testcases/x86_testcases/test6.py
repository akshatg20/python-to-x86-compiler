# Function with more than 6 parameters
def calculate_sum(a: int, b: int, c: int, d: int, e: int, f: int, g: int) -> int:
    return a + b + c + d + e + f + g

# Array assignments and star expressions
def main() -> None:
    # Array operations using indexing
    array : list[int] = [1, 2, 3, 4, 5, 6, 7]
    print("The value of 3rd number in array is: ", array[2])
    array[2] = 10
    print("New value of 3rd number in array is: ", array[2])

    # Call to function with more than 6 parameters
    sum_fixed : int = calculate_sum(0, 1, 2, 3, 4, 5, 6)
    print("Sum of first 7 whole numbers is: ", sum_fixed)
    
    # Call to function with more than 6 parameters
    sum : int = calculate_sum(array[0], array[1], array[2], array[3], array[4], array[5], array[6])
    print("Sum of array is: ", sum)

    return

if __name__ == "__main__":
    main()
