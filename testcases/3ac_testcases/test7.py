class MyClass:
    static_variable = 10

    def __init__(self, value):
        self.instance_variable = value

    def instance_method(self):
        print("This is an instance method")
        print("Instance variable:", self.instance_variable)
        print("Static variable:", MyClass.static_variable)

    @staticmethod
    def static_method():
        print("This is a static method")
        print("Static variable:", MyClass.static_variable)

    @staticmethod
    def iterate_range(start, stop, step=1):
        for i in range(start, stop, step):
            print(i)

def main():
    obj = MyClass(5)

    # Calling instance method
    obj.instance_method()

    # Calling static method
    MyClass.static_method()

    # Iterating over range specified using range() function
    print("Iterating over range specified using range() function:")
    MyClass.iterate_range(1, 10, 2)

if __name__ == "__main__":
    main()
