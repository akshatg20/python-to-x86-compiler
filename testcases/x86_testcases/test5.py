def add(x: int, y: int) -> int:
    ans : int = x + y
    return ans

def subtract(x: int, y: int) -> int:
    ans : int = x - y
    return ans

def multiply(x: int, y: int) -> int:
    ans : int = x * y
    return ans

def divide(x: int, y: int) -> int:
    ans : int = 0
    if y != 0:
        ans = x / y
    else:
        print("Error: Cannot divide by zero.")
    return ans

def relational(x : int, y : int) -> bool:
    ans : bool = ( x == y)
    return ans

def assignment(x : int, y : int) -> int:
    x |= y
    ans : int = x
    return ans

def main():
    result_add : int = add(10, 5)
    print("Result of Addition: ",result_add)

    result_subtract : int = subtract(10, 5)
    print("Result of Subtraction: ", result_subtract)

    result_multiply : int = multiply(10, 5)
    print("Result of Multiplication: ", result_multiply)

    result_divide : int = divide(10, 5)
    print("Result of Division: ", result_divide)

    result_relational : int = relational(10, 5)
    print("Result of Relational Operation: ", result_relational)

    result_assignment : int = assignment(10, 5)
    print("Result of Assignment Operation: ", result_assignment)

if __name__ == "__main__":
    main()
