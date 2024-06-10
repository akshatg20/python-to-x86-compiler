class Calculator:
    def __init__(self):
        self.result:float = 0.0
        self.memory:float = 0.0

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

    def clear_memory(self):
        self.memory = 0.0

    def store_to_memory(self, value: float):
        self.memory = value

    def recall_memory(self) -> float:
        return self.memory

def main():
    calculator: Calculator = Calculator()

    result_add : float = calculator.add(10, 5)
    result_subtract : float = calculator.subtract(result_add, 3)
    result_multiply : float = calculator.multiply(result_subtract, 2)
    result_divide : float = calculator.divide(result_multiply, 4)

    calculator.store_to_memory(result_divide)
    memory_recall:float = calculator.recall_memory()
    calculator.clear_memory()

    print("Result of Addition: ",result_add)
    print("Result of Subtraction: ", result_subtract)
    print("Result of Multiplication: ", result_multiply)
    print("Result of Division: ", result_divide)
    print("Memory Recall: ", memory_recall)

if __name__ == "__main__":
    main()
