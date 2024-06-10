class MathOperation:
    def __init__(self) -> None:
        self.lifespan : int = 0
        print("Inside the constructor for MathOperation class")
        return

    def uncalled(self, x : int) -> None:
        print("This is never called")
        return

def main():
    print("This is a simple testcase for classes")
    math : MathOperation = MathOperation()
    return

if __name__ == "__main__":
    main()
