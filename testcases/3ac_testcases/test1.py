class MyClass:
    def __init__(self):
        self.string : str = "This is MyClass object"
    
    def method1(self) -> None:
        print("This is method 1")

    def method2(self) -> None:
        print("This is method 2")

def main():
    obj : MyClass = MyClass()
    obj.method1()  # calling method1 using the object

if __name__ == "__main__":
    main()
