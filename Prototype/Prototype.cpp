#include <iostream>
#include <string>
#include <unordered_map>


class Shape {
public:
    virtual Shape* clone() const = 0;
    virtual void info() const = 0;
    virtual ~Shape() = default;
};


class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    Shape* clone() const override {
        return new Circle(*this);
    }

    void info() const override {
        std::cout << "Circle with radius " << radius << "\n";
    }
};


class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    Shape* clone() const override {
        return new Rectangle(*this);
    }

    void info() const override {
        std::cout << "Rectangle with width " << width << " and height " << height << "\n";
    }
};


class ShapeRegistry {
private:
    std::unordered_map<std::string, Shape*> prototypes;

public:
    Shape* getPrototype(const std::string& key) const {
        auto it = prototypes.find(key);
        if (it != prototypes.end()) {
            return it->second->clone();
        }
        return nullptr;
    }

    void addPrototype(const std::string& key, Shape* shape) {
        prototypes[key] = shape;
    }
};

int main() {
   
    Circle circlePrototype(5.0);
    Rectangle rectanglePrototype(4.0, 6.0);

   
    ShapeRegistry registry;
    registry.addPrototype("circle", &circlePrototype);
    registry.addPrototype("rectangle", &rectanglePrototype);

   
    Shape* clonedCircle = registry.getPrototype("circle");
    Shape* clonedRectangle = registry.getPrototype("rectangle");

    
    if (clonedCircle) {
        clonedCircle->info();
        delete clonedCircle;
    }

    if (clonedRectangle) {
        clonedRectangle->info();
        delete clonedRectangle;
    }

    return 0;
}