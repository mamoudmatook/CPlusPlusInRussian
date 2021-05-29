#include <iostream>
#include <memory>
#include <sstream>
#include <math.h>
#include <iomanip>
#include <vector>
using namespace std;
class Figure
{
public:
    virtual string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
};

class Triangle : public Figure
{

public:
    Triangle(const double &a, const double &b, const double &c) : _a(a), _b(b), _c(c) {}
    string Name() const override
    {
        return "TRIANGLE";
    }
    double Area() const override
    {
        auto p = (_a + _b + _c) / 2;
        return sqrt(p * (p - _a) * (p - _b) * (p - _c));
    }
    double Perimeter() const override
    {
        return _a + _b + _c;
    }

private:
    double _a, _b, _c;
};

class Rect : public Figure
{
public:
    Rect(const double &width, const double &height) : _width(width), _height(height) {}
    string Name() const override
    {
        return "RECT";
    }
    double Area() const override
    {
        return _width * _height;
    }
    double Perimeter() const override
    {
        return (_width + _height) * 2;
    }

private:
    double _width, _height;
};
class Circle : public Figure
{
public:
    Circle(const double &radius) : _radius(radius) {}
    string Name() const override
    {
        return "CIRCLE";
    }
    double Area() const override
    {
        return _radius * _radius * 3.14;
    }
    double Perimeter() const override
    {
        return 2 * 3.14 * _radius;
    }

private:
    double _radius;
};
shared_ptr<Figure> CreateFigure(istringstream &is)
{
    string shape;
    is >> shape;
    if (shape == "RECT")
    {
        double width, height;
        is >> width >> height;
        return make_shared<Rect>(width, height);
    }
    else if (shape == "CIRCLE")
    {
        double radius;
        is >> radius;
        return make_shared<Circle>(radius);
    }
    else
    {
        double a, b, c;
        is >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
    }
}

int main()
{
    vector<shared_ptr<Figure> > figures;
    for (string line; getline(cin, line);)
    {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD")
        {
            // Пропускаем "лишние" ведущие пробелы.
            // Подробнее об std::ws можно узнать здесь:
            // https://en.cppreference.com/w/cpp/io/manip/ws
            is >> ws;
            figures.push_back(CreateFigure(is));
        }
        else if (command == "PRINT")
        {
            for (const auto &current_figure : figures)
            {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}