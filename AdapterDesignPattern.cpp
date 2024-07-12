/**
 * The adapter design pattern describes how to solve such problems:
 * - Define a separate adapter class that converts the (incompatible) interface of a class (adaptee) into another interface (target) clients require.
 * - Work through an adapter to work with (reuse) classes that do not have the required interface.
 * Credit for proof of concept:
 * https://refactoring.guru/design-patterns/adapter/cpp/example
 */

#include <stdio.h>
#include <string>
#include <iostream>

/**
 * The Target defines the domain-specific interface used by the client
 * E.G. a request that returns a static string
 * 
 * This is the interface we want to adapt too
 */
class Target {
  public:
    virtual ~Target() = default;
    
    virtual std::string Request() const {
      return "Target: The default target's behavior.";
    }
};

/**
 * The Adaptee contains some useful behavior, but its interface is incompatible with the existing client code.
 * The Adaptee needs some adaptation before the client code can use it.
 * 
 * E.G. In this case, the adaptee presents a string that is in-reverse
 */
class Adaptee {
  public:
    std::string SpecificRequest() const {
      return ".eetpadA eht fo roivaheb laicepS";
    };
};

/**
 * The Adapter class makes the Adaptee's interface compatible with the Target's interface
 */
class Adapter : public Target {
  private:
    Adaptee *adaptee_;

  public:
    // Constructor
    Adapter(Adaptee *adaptee) : adaptee_(adaptee) {}

    // The function responsible for the heavy lifting, adapts the response of adaptee request to something the client can handle
    std::string Request() const override {
      std::string to_reverse = this->adaptee_->SpecificRequest();
      std::reverse(to_reverse.begin(), to_reverse.end());
      return "Adapter: (TRANSLATED) " + to_reverse;
    } 
};

/**
 * The client code supports all classes that follow the Target interface 
 */
void ClientCode(const Target *target) {
  std::cout << target->Request() << std::endl;
}

int main() {
  std::cout << "Client: I can work just fine with the Target objects:\n";

  Target *target = new Target;
  ClientCode(target);
  std::cout << "\n\n";

  Adaptee *adaptee = new Adaptee;
  std::cout << "Client: the Adaptee class has a weird interface. See, I don't understand it:\n";
  std::cout << "Adaptee: " << adaptee->SpecificRequest();
  std::cout << "\n\n";

  std::cout << "Client: But I can work with it via the Adapter:\n";
  Adapter *adapter = new Adapter(adaptee);
  ClientCode(adapter);
  std::cout << "\n";

  delete target;
  delete adaptee;
  delete adapter;

  return 0;
}
