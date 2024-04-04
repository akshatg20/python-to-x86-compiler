class Shape:
    def __init__(self, name: str):
        self.name = name

    def get_area(self) -> float:
        pass

class Circle(Shape):
    def __init__(self, name: str, radius: float):
        super().__init__(name)
        self.radius = radius

    def get_area(self) -> float:
        return 3.14 * self.radius ** 2

class Square(Shape):
    def __init__(self, name: str, side_length: float):
        super().__init__(name)
        self.side_length = side_length

    def get_area(self) -> float:
        return self.side_length ** 2

class ShapeManager:
    def __init__(self):
        self.shapes = []

    def add_shape(self, shape: Shape):
        self.shapes.append(shape)

    def calculate_total_area(self) -> float:
        total_area = 0
        for shape in self.shapes:
            total_area += shape.get_area()
        return total_area

circle1 = Circle("Circle1", 5.0)
square1 = Square("Square1", 4.0)
circle2 = Circle("Circle2", 3.0)

manager = ShapeManager()
manager.add_shape(circle1)
manager.add_shape(square1)
manager.add_shape(circle2)

total_area = manager.calculate_total_area()
print("Total Area of Shapes:", total_area)