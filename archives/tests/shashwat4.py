import math

class Calculator:
    def __init__(self):
        self.result = 0
        self.memory = 0

    def add(self, x: float, y: float) -> float:
        self.result = x + y
        return self.result

    def subtract(self, x: float, y: float) -> float:
        self.result = x - y
        return self.result

    def multiply(self, x: float, y: float) -> float:
        self.result = x * y
        return self.result

    def divide(self, x: float, y: float) -> float:
        if y != 0:
            self.result = x / y
        else:
            print("Error: Cannot divide by zero.")
        return self.result

    def square_root(self, x: float) -> float:
        if x >= 0:
            self.result = math.sqrt(x)
        else:
            print("Error: Cannot calculate square root of a negative number.")
        return self.result

    def clear_memory(self):
        self.memory = 0

    def store_to_memory(self, value: float):
        self.memory = value

    def recall_memory(self) -> float:
        return self.memory

def main():
    calculator = Calculator()

    result_add = calculator.add(10, 5)
    result_subtract = calculator.subtract(result_add, 3)
    result_multiply = calculator.multiply(result_subtract, 2)
    result_divide = calculator.divide(result_multiply, 4)

    calculator.store_to_memory(result_divide)
    memory_recall = calculator.recall_memory()
    calculator.clear_memory()

    result_square_root = calculator.square_root(25)

    print("Result of Addition: ", result_add)
    print("Result of Subtraction: ", result_subtract)
    print("Result of Multiplication: ", result_multiply)
    print("Result of Division: ", result_divide)
    print("Memory Recall: ", memory_recall)
    print("Result of Square Root: ", result_square_root)

if __name__ == "__main__":
    main()