def factorial(n: int) -> int:
    """
    Compute the factorial of a non-negative integer.
    
    Args:
        n (int): A non-negative integer.
    
    Returns:
        int: The factorial of n.
    """
    if n == 0:
        return 1
    else:
        return n * factorial(n - 1)

# Test the function
if __name__ == "__main__":
    num = 5
    print(f"The factorial of {num} is {factorial(num)}")
