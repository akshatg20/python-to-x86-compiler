class MyClass:
    def __init__(self, name):
        self.name = name
    
    def greet(self):
        print("Hello,", self.name)

def main():
    # Creating an object of MyClass with a name parameter
    obj = MyClass("Alice")
    # Calling the greet method
    obj.greet()

if __name__ == "__main__":
    main()
