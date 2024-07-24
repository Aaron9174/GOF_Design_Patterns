/**
 * The decorator design pattern describes how to solve such problems:
 * - Responsibilities should be added to (and removed from) an object dynamically at run-time
 * - A flexible alternative to subclassing for extending functionality should be provided
 * Credit for proof of concept:
 * https://en.wikipedia.org/wiki/Decorator_pattern
 */

#include <iostream>
#include <memory>

/**
 * Beverage class to be decorated later
 * It's interface defines a single drink() function
 */
class Beverage {
public:
  virtual void drink() = 0;
  virtual ~Beverage() = default;
};

/**
 * A concrete implementation of a beverage, defines drinking coffee
 */
class Coffee : public Beverage {
public:
  virtual void drink() override {
    std::cout << "Drinking coffee";
  }
};

/**
 * A concrete implementation of a beverage, defines drinking soda
 */
class Soda : public Beverage {
public:
  virtual void drink() override {
    std::cout << "Drinking soda";
  }
};

/**
 * The decorator!
 * Wraps a beverage via composition and creates a new function 'callComponentDrink' that passes calls to the it
 */
class BeverageDecorator : public Beverage {
public:
  BeverageDecorator() = delete;
  BeverageDecorator(std::unique_ptr<Beverage> _component): component(std::move(_component)) {}

  virtual void drink() = 0;

  protected:
    void callComponentDrink() {
      if (component) {
        component->drink();
      }
    }

  private:
    std::unique_ptr<Beverage> component;
};

/**
 * Milk uses the decorator to build off it's drink result, essentially 'decorating' it with a milk-specific context
 */
class Milk : public BeverageDecorator {
  public:
    Milk(std::unique_ptr<Beverage> _component, float _percentage)
      : BeverageDecorator(std::move(_component))
      , percentage(_percentage) {}
    
    virtual void drink() override {
      callComponentDrink();
      std::cout << ", with milk of richness " << percentage << "%";
    }

  private:
  float percentage;
};

/**
 * Ice-cubes leverage the decorator in the same manner, it builds off the drink function to add ice-cube specific context
 */
class IceCubes : public BeverageDecorator {
public:
  IceCubes(std::unique_ptr<Beverage> _component, int _count)
    : BeverageDecorator(std::move(_component))
    , count(_count) {}

  virtual void drink() override {
    callComponentDrink();
    std::cout << ", with " << count << " ice cubes";
  }

private:
  int32_t count;
};

/**
 * Sugar does the same, buildinf off the drink result and adding a sugar decorator to it
 */
class Sugar : public BeverageDecorator {
  public:
    Sugar(std::unique_ptr<Beverage> _component, int _spoons)
      : BeverageDecorator(std::move(_component))
      , spoons(_spoons) {}
    
    virtual void drink() override {
      callComponentDrink();
      std::cout << ", sweetened with " << spoons << " spoons of sugar";
    }
    
  private:
    int32_t spoons = 1;
};

int main() {
  // Example 1
  std::unique_ptr<Beverage> soda = std::make_unique<Soda>();
  soda = std::make_unique<IceCubes>(std::move(soda), 3);
  soda = std::make_unique<Sugar>(std::move(soda), 1);
  soda->drink();

  std::cout << std::endl;

  // Example 2
  std::unique_ptr<Beverage> coffee = std::make_unique<Coffee>();
  coffee = std::make_unique<Sugar>(std::move(coffee), 2);
  coffee = std::make_unique<Milk>(std::move(coffee), 70);
  coffee->drink();

  std::cout << std::endl;
}