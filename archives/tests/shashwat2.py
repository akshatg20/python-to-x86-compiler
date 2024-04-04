def multiply_numbers(a: int, b: int) -> int:
    return a * b

def factorial(n: int) -> int:
    if n == 0 or n == 1:
        return 1
    else:
        return n * factorial(n - 1)

class MathOperations:
    def add(self, a: int, b: int) -> int:
        return a + b

    def add(self, a: float, b: float) -> float:
        return a + b

def main():
    result = multiply_numbers(4, 6)
    print("Result:", result)

    fact_result = factorial(5)
    print("Factorial of 5:", fact_result)

    math_obj = MathOperations()
    int_result = math_obj.add(3, 5)
    float_result = math_obj.add(2.5, 3.5)

    print("Integer Addition:", int_result)
    print("Float Addition:", float_result)

class CustomError(Exception):
    def __init__(self, message: str):
        self.message = message
        super().__init__(self.message)

def divide_numbers(a: int, b: int) -> float:
    try:
        result = a / b
        return result
    except ZeroDivisionError:
        raise CustomError("Cannot divide by zero")

try:
    division_result = divide_numbers(10, 2)
    print("Division Result:", division_result)
except CustomError as ce:
    print("Error:", ce.message)

student_grades = {'Alice': 85, 'Bob': 92, 'Charlie': 78}
print("Bob's Grade:", student_grades['Bob'])

even_numbers = [num for num in range(10) if num % 2 == 0]
print("Even Numbers:", even_numbers)

square = lambda x: x ** 2
print("Square of 7:", square(7))

unique_numbers = {1, 2, 3, 4, 5, 5, 4, 3, 2, 1}
print("Unique Numbers:", unique_numbers)

with open('output.txt', 'w') as file:
    file.write("This is a sample file content.")

with open('output.txt', 'r') as file:
    file_content = file.read()
    print("File Content:", file_content)

coordinates = (3, 7)
print("Coordinates:", coordinates)

if __name__ == "__main__":
    main()
