class ParentClass:
    def __init__(self):
        print("This is object of parent class")
    
    def parent_method(self):
        print("This is parent method")

class ChildClass(ParentClass):
    def __init__(self):
        print("This is object of child class")
    
    def child_method(self):
        print("This is child method")

def main():
    child_obj : ChildClass = ChildClass()
    child_obj.child_method()   # calling child_method
    child_obj.parent_method()  # calling parent_method inherited from ParentClass

if __name__ == "__main__":
    main()
