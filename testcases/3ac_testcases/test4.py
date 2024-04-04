class Grandparent:
    def method1(self):
        print("This is method 1 from Grandparent")

class Parent(Grandparent):
    def method2(self):
        print("This is method 2 from Parent")

class Child(Parent):
    def method3(self):
        print("This is method 3 from Child")

def main():
    obj = Child()
    obj.method1()  # inherited from Grandparent
    obj.method2()  # inherited from Parent
    obj.method3()  # defined in Child

if __name__ == "__main__":
    main()
