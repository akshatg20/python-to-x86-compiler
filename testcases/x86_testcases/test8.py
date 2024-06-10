class Rectangle:
    def __init__(self, width: int, height: int):
        self.width : int = width
        self.height : int = height

    def area(self) -> int:
        return (self.width * self.height)

class Square:
    def __init__(self, side: int):
        self.side : int = side

    def area(self) -> int:
        return (self.side * self.side)

def main() -> None:
    # Creating object of class and calling there methods
    rect : Rectangle = Rectangle(5, 4)
    area_rect : int = rect.area()
    print("Area of Rectangle: ", area_rect)

    # Creating object of class and calling there methods
    square : Square = Square(3)
    area_square : int = square.area()
    print("Area of Square: ", area_square)

    return

if __name__ == "__main__":
    main()
