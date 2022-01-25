#include "Common.h"
using namespace std;
class Rectangle : public IShape
{
public:
    std::unique_ptr<IShape> Clone() const override
    {
        unique_ptr<Rectangle> cloned = make_unique<Rectangle>();
        cloned->SetPosition(pos);
        cloned->SetSize(sz);
        cloned->SetTexture(texture);
        return cloned;
    }

    void SetPosition(Point p) override
    {
        pos = p;
    }
    Point GetPosition() const override
    {
        return pos;
    }

    void SetSize(Size s) override
    {
        sz = s;
    }
    Size GetSize() const override
    {
        return sz;
    }

    void SetTexture(std::shared_ptr<ITexture> t) override
    {
        texture = t;
    }
    ITexture *GetTexture() const override
    {
        return texture.get();
    }

    void Draw(Image &image) const override
    {
        for (int i = pos.y; i < image.size(); ++i)
        {
            if (i - pos.y < sz.height)
            {
                for (int j = pos.x; j < image[i].size(); ++j)
                {
                    if (j - pos.x < sz.width)
                    {
                        if (texture == nullptr)
                        {
                            image[i][j] = '.';
                        }
                        else
                        {
                            if ((i >= pos.y && i < pos.y + texture->GetSize().height) && (j >= pos.x && j < pos.x + texture->GetSize().width))
                            {
                                image[i][j] = texture->GetImage()[i - pos.y][j - pos.x];
                            }
                            else
                            {
                                image[i][j] = '.';
                            }
                        }
                    }
                }
            }
        }
    }

private:
    Size sz;
    Point pos;
    shared_ptr<ITexture> texture;
};

class Ellipse : public IShape
{
public:
    std::unique_ptr<IShape> Clone() const override
    {
        unique_ptr<Ellipse> cloned = make_unique<Ellipse>();
        cloned->SetPosition(pos);
        cloned->SetSize(sz);
        cloned->SetTexture(texture);
        return cloned;
    }

    void SetPosition(Point p) override
    {
        pos = p;
    }
    Point GetPosition() const override
    {
        return pos;
    }

    void SetSize(Size s) override
    {
        sz = s;
    }
    Size GetSize() const override
    {
        return sz;
    }

    void SetTexture(std::shared_ptr<ITexture> t) override
    {
        texture = t;
    }
    ITexture *GetTexture() const override
    {
        return texture.get();
    }
    void Draw(Image &image) const override
    {
        for (int i = pos.y; i < image.size(); ++i)
        {
            if (i - pos.y < sz.height)
            {
                for (int j = pos.x; j < image[i].size(); ++j)
                {
                    if (j - pos.x < sz.width)
                    {
                        if (texture == nullptr)
                        {
                            image[i][j] = '.';
                        }
                        else
                        {
                            if (IsPointInEllipse({j - pos.x, i - pos.y}, sz))
                            {
                                if ((i >= pos.y && i < pos.y + texture->GetSize().height) && (j >= pos.x && j < pos.x + texture->GetSize().width))
                                {
                                    image[i][j] = texture->GetImage()[i - pos.y][j - pos.x];
                                }
                                else
                                {
                                    image[i][j] = '.';
                                }
                            }
                        }
                    }
                }
            }
        }
    }

private:
    Size sz;
    Point pos;
    shared_ptr<ITexture> texture;
};

unique_ptr<IShape> MakeShape(ShapeType shape_type)
{
    if (shape_type == ShapeType::Rectangle)
    {
        return make_unique<Rectangle>();
    }
    else
    {
        return make_unique<Ellipse>();
    }
}