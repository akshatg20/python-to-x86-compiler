INF : int = 100000000000

def multiply_numbers(a: int, b: int) -> int:
    return a * b

def factorial(n: int) -> int:
    if n == 0 or n == 1:
        return 1
    else:
        return n * factorial(n - 1)

class MathOperations:
    def __init__(self):
        print("Created object of type MathOperations")

    def add(self, a: int, b: int) -> int:
        return a + b

    def add(self, a: float, b: float) -> float:
        return a + b

def divide_numbers(a: int, b: int) -> float:
    if(b == 0):
        print("Zero Division Error!")
        return INF
    else:
        return a/b

def main():
    result : int = multiply_numbers(4, 6)
    print("Result: ", result)

    fact_result : int = factorial(5)
    print("Factorial of 5: ", fact_result)

    math_obj : MathOperations = MathOperations()
    int_result : int = math_obj.add(3, 5)
    float_result : float = math_obj.add(2.5, 3.5)

    print("Integer Addition: ", int_result)
    print("Float Addition: ", float_result)

    division_result : float = divide_numbers(10, 2)
    if(division_result == INF):
        print("Divison Error!")
    else:
        print("Divison result = ", division_result)

    student_names : list[str] = ["Alice", "Bob", "Charlie"]
    student_grades : list[int] = [ 85, 92, 78]
    print("Bob's Grade: ", student_grades[1])

    coordinates : list[int] = [3, 7]
    print("Coordinates: ", coordinates[0], ",", coordinates[1])

if __name__ == "__main__":
    main()
