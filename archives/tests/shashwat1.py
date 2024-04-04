def add_numbers(a: int, b: int) -> int:
    return a + b

def square_elements(numbers: List[int]) -> List[int]:
    squared = [num ** 2 for num in numbers]
    return squared

def is_positive_or_zero(num: int) -> str:
    if num > 0:
        return "Positive"
    elif num == 0:
        return "Zero"
    else:
        return "Negative"

class Animal:
    def __init__(self, name: str):
        self.name = name

    def make_sound(self) -> str:
        return "Some generic animal sound"

class Dog(Animal):
    def make_sound(self) -> str:
        return "Woof!"

def main():
    result = add_numbers(5, 3)
    print("Result:", result)

    numbers = [1, 2, 3, 4]
    squared_numbers = square_elements(numbers)
    print("Squared Numbers:", squared_numbers)

    num_check = is_positive_or_zero(-7)
    print("Number Check:", num_check)

    my_dog = Dog("Buddy")
    print("Dog Name:", my_dog.name)
    print("Dog Sound:", my_dog.make_sound())

if __name__ == "__main__":
    main()