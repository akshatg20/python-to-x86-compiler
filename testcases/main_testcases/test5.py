def add_numbers(a: int, b: int) -> int:
    """
        Function to add two integers
    """
    return a + b

def sum_elements(numbers: list[int]) -> int:
    """
        Function to sum every element present in a list
    """
    sum:int = 0
    i:int = 0
    for i in range(len(numbers)):
        sum += numbers[i]
    return sum

def is_positive_or_zero(num: int) -> str:
    """
        Function to check if a number is positive or not
    """
    if num > 0:
        return "Positive"
    elif num == 0:
        return "Zero"
    else:
        return "Negative"

class Animal:
    def __init__(self, name: str):
        self.name:str = name

    def make_sound(self) -> str:
        return "Some generic animal sound"

class Dog(Animal):
    def make_sound(self) -> str:
        return "Woof!"

def main():
    result:int = add_numbers(5, 3)
    print("Result:", result)

    numbers: list[int] = [1, 2, 3, 4]
    sum_of_numbers: int = sum_elements(numbers)
    print("Sum of Numbers:", sum_of_numbers)

    num_check:str = is_positive_or_zero(-7)
    print("Number Check:", num_check)

    my_dog: Dog = Dog("Buddy")
    print("Dog Name:", my_dog.name)
    print("Dog Sound:", my_dog.make_sound())

if __name__ == "__main__":
    main()
