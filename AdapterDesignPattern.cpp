#include <iostream>

class Square
{
  public:
    void calculateArea(int side)
    {
      int area = side * side;
      std::cout << "Area of square: " << area << std::endl;
    }
};

class Rectangle
{
  public:
    void calculateArea(int length, int width)
    {
      int area = length * width;
      std::cout << "Area of rectangle: " << area << std::endl; 
    }
};

class ShapeAdapter
{
  public:
    virtual void getArea() = 0;
};

class SquareAdapter: public ShapeAdapter {
  public:
    SquareAdapter(Square squareInput)
    {
      square = squareInput;
    }

    void getArea()
    {
      square.calculateArea(5);
    }

  private:
    Square square;
};

class RectangleAdapter: public ShapeAdapter
{
  public:
    RectangleAdapter(Rectangle rectangleInput)
    {
      rectangle = rectangleInput;
    } 

    void getArea()
    {
      rectangle.calculateArea(5, 5);
    }

  private:
    Rectangle rectangle;
};

int main(void) {
  std::cout << "Hello World!" << std::endl;
  Square square;
  Rectangle rectangle;

  SquareAdapter squareAdapter(square);
  RectangleAdapter rectangleAdapter(rectangle);

  squareAdapter.getArea();
  rectangleAdapter.getArea();

  return 0;
}