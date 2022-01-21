#include "Common.h"
#include "test_runner.h"
#include <sstream>

using namespace std;

string Print(const Expression *e)
{
    if (!e)
    {
        return "Null expression provided";
    }
    stringstream output;
    output << e->ToString() << " = " << e->Evaluate();
    return output.str();
}
class ValueExpr : public Expression
{
public:
    ValueExpr(int value) : value_(value) {}
    int Evaluate() const override
    {
        return value_;
    }
    string ToString() const override
    {
        return to_string(value_);
    }

private:
    int value_;
};

class SumExpr : public Expression
{
public:
    SumExpr(unique_ptr<Expression> left, unique_ptr<Expression> right) : left_(move(left)), right_(move(right)) {}
    int Evaluate() const override
    {
        return left_->Evaluate() + right_->Evaluate();
    }
    string ToString() const override
    {
        return "(" + left_->ToString() + ")" + "+" +
               "(" + right_->ToString() + ")";
    }

private:
    unique_ptr<Expression> left_, right_;
};

class ProdExpr : public Expression
{
public:
    ProdExpr(unique_ptr<Expression> left, unique_ptr<Expression> right) : left_(move(left)), right_(move(right)) {}
    int Evaluate() const override
    {
        return left_->Evaluate() * right_->Evaluate();
    }
    string ToString() const override
    {
        return "(" + left_->ToString() + ")" + "*" +
               "(" + right_->ToString() + ")";
    }

private:
    unique_ptr<Expression> left_, right_;
};

ExpressionPtr Value(int value)
{
    return make_unique<ValueExpr>(value);
}
ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right)
{
    return make_unique<SumExpr>(move(left), move(right));
}
ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right)
{

    return make_unique<ProdExpr>(move(left), move(right));
}

void Test()
{
    ExpressionPtr e1 = Product(Value(2), Sum(Value(3), Value(4)));
    ASSERT_EQUAL(Print(e1.get()), "(2)*((3)+(4)) = 14");

    ExpressionPtr e2 = Sum(move(e1), Value(5));
    ASSERT_EQUAL(Print(e2.get()), "((2)*((3)+(4)))+(5) = 19");

    ASSERT_EQUAL(Print(e1.get()), "Null expression provided");
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, Test);
    return 0;
}