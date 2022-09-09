# Clean Code Principles

# Code Guidelines

 * C++ Core Guidelines: https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines
 * Google C++ Style Guide: https://google.github.io/styleguide/cppguide.html

# SOLID Principles

Principles for design. Managing dependencies (between components) - how change propagates through a system.
There can be similar concerns expressed for data (e.g. dependencies of data artifacts)

## Single Responsibility Principle (SRP)

A class should have one and only one reason to change.

## Open/Closed Principle (OCP)

You should be able to extend a class' behaviour without modifying it.

Typically done by subclassing a base class:

 * We extend the behaviour
 * We reuse methods of the superclass
 * The superclass is completely unaware of its subclasses

If the superclass changes its behaviour, it will affect the subclasses.

 * another way is to extract interfaces and supply different implementations
 * an interface is declarative, does not supply implementation and hence subclasses will not be coupled to a specific superclass implementation detail
 
In C++ there are no actual interfaces, but they can be emulated via classes and structs.

 * This is done by having only pure virtual member functions.

## Liskov Substitution Principle (LSP)

Objects of a superclass should be replaceable by objects of a subclass without breaking the application.

## Interface Segregation Principle (ISP)

 * No client should be forced to depend on methods it does not use
 * Keep interfaces small
 * It is preferred to implement multiple interfaces instead of a big general purpose one
 
In C++ there are no interfaces. But C++ has multiple inheritance, so we can technically derive from multiple pure virtual base classes.

## Dependency Inversion Principle (DIP)

Higher level modules should not depend on lower level modules.
Both should depend on abstractions.
Abstractions should not depend on details.
Details should depend on abstractions.

# Generic Rules

 * KISS (Keep It Simple, Stupid)
 * DRY (Don't Repeat Yourself)
 * Rule of 3
 * YAGNI (You Ain't Gonna Need It)
 * Composition over inheritance
 * Readability counts
 * Principle of least surprise

# Best practices & Idioms

 * RAII - Resource Acquisition Is Initialization
 * Const Correctness
 * Avoid raw new, never use raw delete
 * Rule of 3/5/0
 * Avoid shared mutable state


 private/mutable  |   private/immutable
 shared/mutable   |   shared/immutable
