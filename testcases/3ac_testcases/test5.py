class MathOperations:
    def __init__(self):
        print("Constructed object of type MathOperations")
    
    def add(self, a : int, b : int = 0, c : int = 0) -> int:
        return (a + b + c)

def main():
    math_ops : MathOperations = MathOperations()
    print("Sum with three parameters: ", math_ops.add(5, 3, 2))
    print("Sum with two parameters: ", math_ops.add(5, 3))
    print("Sum with one parameter: ", math_ops.add(5))

if __name__ == "__main__":
    main()
