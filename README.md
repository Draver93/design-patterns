# Design Patterns in C++ (Visual Studio Project)

## Overview
This project is a C++ implementation of various design patterns, structured to help refresh and reinforce knowledge of design patterns. It follows the classic design pattern categories: Creational, Structural, and Behavioral. The implementation is built as a Visual Studio project.

## Design Patterns Implemented

### Creational Patterns
- **Singleton** - Ensures a class has only one instance and provides a global point of access.
- **Prototype** - Creates new objects by copying an existing object.
- **Factory Method** - Defines an interface for creating an object but lets subclasses alter the type of objects created.
- **Abstract Factory** - Provides an interface for creating families of related or dependent objects.
- **Builder** - Separates the construction of a complex object from its representation.

### Structural Patterns
- **Adapter** - Allows incompatible interfaces to work together.
- **Bridge** - Decouples an abstraction from its implementation so they can vary independently.
- **Composite** - Composes objects into tree structures to represent part-whole hierarchies.
- **Decorator** - Dynamically adds responsibilities to objects.
- **Facade** - Provides a simplified interface to a larger body of code.
- **Flyweight** - Shares common object data to reduce memory usage.
- **Proxy** - Provides a surrogate or placeholder for another object.

### Behavioral Patterns
- **Chain of Responsibility** - Passes a request along a chain of handlers.
- **Command** - Encapsulates a request as an object.
- **Interpreter** - Defines a grammar for a simple language and interprets sentences in the language.
- **Observer** - Defines a dependency between objects so that when one changes, all its dependents are notified.
- **State** - Allows an object to change its behavior when its internal state changes.
- **Strategy** - Encapsulates algorithms and makes them interchangeable.
- **Template Method** - Defines the skeleton of an algorithm in the superclass but lets subclasses override specific steps.
- **Visitor** - Encapsulates operations on elements of an object structure.

## Project Structure
The project is divided into three main directories:
```
DesignPatternsProject/
│-- Creational/
│   │-- Singleton/
│   │-- Prototype/
│   │-- FactoryMethod/
│   │-- AbstractFactory/
│   │-- Builder/
│-- Structural/
│   │-- Adapter/
│   │-- Bridge/
│   │-- Composite/
│   │-- Decorator/
│   │-- Facade/
│   │-- Flyweight/
│   │-- Proxy/
│-- Behavioral/
│   │-- ChainOfResponsibility/
│   │-- Command/
│   │-- Interpreter/
│   │-- Observer/
│   │-- State/
│   │-- Strategy/
│   │-- Iterator/
│   │-- Mediator/
│   │-- Memento/
│   │-- TemplateMethod/
│   │-- Visitor/
│-- main.cpp
```

## Running the Project
1. Open the project in **Visual Studio**.
2. Build the project using **C++17 or later**.
3. Run the executable.
4. The console output will demonstrate the various design patterns, displaying descriptions and executing examples.

## Example: Flyweight Pattern

The Flyweight pattern is demonstrated using a **Pepsi bottle label** where thousands of bottles share a single label instance to save memory.

```cpp
std::shared_ptr<Factory> pepsi_factory = std::make_shared<PepsiFactory>();
std::vector<std::shared_ptr<Bottle>> bottles;
for (int i = 0; i < 1000; i++) {
    bottles.push_back(pepsi_factory->create_bottle());
}
```

## Contributions
Feel free to contribute additional patterns or improvements by submitting a pull request.

## License
This project is open-source and free to use for educational purposes.

