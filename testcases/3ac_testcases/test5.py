class MathOperations:
    def add(self, a, b=0, c=0):
        return a + b + c

def main():
    math_ops = MathOperations()
    print("Sum with two parameters:", math_ops.add(5, 3))
    print("Sum with three parameters:", math_ops.add(5, 3, 2))

if __name__ == "__main__":
    main()
