// Task08.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include "CPoint.h"
#include <vector>
#include <memory>
#include <sstream>

/*
Интерфейс объектов, способных сохранять (SaveTo) и
восстанавливать (RestoreFrom) своё состояние из/в стандартных потоков чтения/записи
В случае ошибки выбрасывают исключения runtime_error
*/
class ISerializable
{
public:
    virtual ~ISerializable() = default;
    virtual void SaveTo(std::ostream& stream) const = 0;
    virtual void RestoreFrom(std::istream& stream) = 0;
};

/* Интерфейс холста. Позволяет рисовать отрезки прямых линий и эллипсы */
class ICanvas
{
public:
    virtual ~ICanvas() = default;
    virtual void DrawLine(CPoint from, CPoint to) = 0;
    virtual void DrawEllipse(CPoint center, double majorAxis, double minorAxis) = 0;
};

/* Интерфейс объектов, которые могут быть нарисованы (Draw) на холсте (canvas) */
class ICanvasDrawable
{
public:
    virtual void Draw(ICanvas& canvas) const = 0;
    virtual ~ICanvasDrawable() = default;
};

/* Интерфейс объектов, умеющих говорить (Speak). */
class ISpeakable
{
public:
    virtual void Speak() const = 0;
};

/* Прямоугольник. Может быть нарисован на холсте, а также является сериализуемым */
class Rectangle 
    : public ISerializable
    , public ICanvasDrawable
{
public:
    Rectangle(CPoint leftTop, double width, double height)
        : m_leftTop(leftTop)
        , m_width(width)
        , m_height(height)
    {}
    void SaveTo(std::ostream& stream) const final
    {
        stream << m_leftTop.x << " " << m_leftTop.y << " " << m_width << " " << m_height;
    }

    void RestoreFrom(std::istream& stream) final
    {
        CPoint leftTop;
        double width;
        double height;
        if (stream >> leftTop.x && stream >> leftTop.y && stream >> width && stream >> height)
        {
            m_leftTop.x = leftTop.x;
            m_leftTop.y = leftTop.y;
            m_width = width;
            m_height = height;
        }
        else
        {
            throw std::runtime_error("Invalid state for rectangle");
        }
    }

    CPoint GetLeftTop() const
    {
        return m_leftTop;
    }

    CPoint GetRightTop() const
    {
        return CPoint({ m_leftTop.x + m_width, m_leftTop.y });
    }

    CPoint GetRightBottom() const
    {
        return CPoint({ m_leftTop.x + m_width, m_leftTop.y + m_height });
    }

    CPoint GetLeftBottom() const
    {
        return CPoint({ m_leftTop.x, m_leftTop.y + m_height });
    }

    void Draw(ICanvas& canvas) const final
    {
        canvas.DrawLine(GetLeftTop(), GetRightTop());
        canvas.DrawLine(GetRightTop(), GetRightBottom());
        canvas.DrawLine(GetRightBottom(), GetLeftBottom());
        canvas.DrawLine(GetLeftBottom(), GetLeftTop());
    }

private:
    CPoint m_leftTop;
    double m_width;
    double m_height;
};

/* Эллипс. Может быть нарисован на холсте, а также является сериализуемым */
class Ellipse
    : public ISerializable
    , public ICanvasDrawable
{
public:
    void SaveTo(std::ostream& stream) const final
    {
        stream << m_center.x << " " << m_center.y << " " << m_majorAxis << " " << m_minorAxis;
    }
    void RestoreFrom(std::istream& stream) final
    {
        CPoint center;
        double majorAxis;
        double minorAxis;
        if (stream >> center.x && stream >> center.y && stream >> majorAxis && stream >> minorAxis)
        {
            m_center.x = center.x;
            m_center.y = center.y;
            m_majorAxis = majorAxis;
            m_minorAxis = minorAxis;
        }
        else
        {
            throw std::runtime_error("Invalid state for ellipse");
        }
    }
    void Draw(ICanvas& canvas) const final
    {
        canvas.DrawEllipse(m_center, m_majorAxis, m_minorAxis);
    }

private:
    CPoint m_center;
    double m_majorAxis, m_minorAxis;
};

/* Треугольник. Может быть нарисован на холсте, а также является сериализуемым */
class Triangle
    : public ISerializable
    , public ICanvasDrawable
{
public:
    Triangle(CPoint vertex1, CPoint vertex2, CPoint vertex3)
        : m_vertex1(vertex1)
        , m_vertex2(vertex2)
        , m_vertex3(vertex3)
    {}
    void SaveTo(std::ostream& stream) const final
    {
        stream << m_vertex1.x << " " << m_vertex1.y << " " << m_vertex2.x << " " << m_vertex2.y << " " << m_vertex3.x << " " << m_vertex3.y;
    }
    void RestoreFrom(std::istream& stream) final
    {
        CPoint vertex1;
        CPoint vertex2;
        CPoint vertex3;
        if (stream >> vertex1.x && stream >> vertex1.y && 
            stream >> vertex2.x && stream >> vertex2.y &&
            stream >> vertex3.x && stream >> vertex3.y)
        {
            m_vertex1.x = vertex1.x;
            m_vertex1.y = vertex1.y;
            m_vertex2.x = vertex2.x;
            m_vertex2.y = vertex2.y;
            m_vertex3.x = vertex3.x;
            m_vertex3.y = vertex3.y;
        }
        else
        {
            throw std::runtime_error("Invalid state for triangle");
        }
    }
    void Draw(ICanvas& canvas) const final
    {
        canvas.DrawLine(m_vertex1, m_vertex2);
        canvas.DrawLine(m_vertex2, m_vertex3);
        canvas.DrawLine(m_vertex3, m_vertex1);
    }

private:
    CPoint m_vertex1, m_vertex2, m_vertex3;
};

/* Холст. Вместо фактического рисования выводит в cout команды рисования и их параметры */
class CoutCanvas : public ICanvas
{
    void DrawLine(CPoint from, CPoint to) final
    {
        std::cout << "Draw line from " << from.x << " " << from.y << " to " << to.x << " " << to.y << std::endl;
    }

    void DrawEllipse(CPoint center, double majorAxis, double minorAxis) final
    {
        std::cout << "Draw ellipse in center " << center.x << " " << center.y << 
            " with major axis " << majorAxis << " and minor axis " << minorAxis << std::endl;
    }
};

/* Кот. Обладает координатами (в центре головы). Может быть нарисован на холсте
 может говорить (мяукая) */
class Cat
    : public ICanvasDrawable
    , public ISpeakable
{
public:
    Cat(CPoint headCoords)
        : m_headCoords(headCoords)
    {}
    void Speak() const final
    {
        std::cout << "meow";
    }
    void Draw(ICanvas& canvas) const final
    {
        canvas.DrawEllipse(m_headCoords, 10, 10);
        canvas.DrawLine(CPoint{ m_headCoords.x + 8, m_headCoords.y }, CPoint{ m_headCoords.x + 12, m_headCoords.y });
        canvas.DrawLine(CPoint{ m_headCoords.x - 8, m_headCoords.y }, CPoint{ m_headCoords.x - 12, m_headCoords.y });
    }

private:
    CPoint m_headCoords;
};

/* Человек. Обладает именем и годом рождения.
может говорить (называет своё имя и год рождения) */
class Person : public ISpeakable
{
public:
    Person(std::string name, int birthYear)
        : m_name(name)
        , m_birthYear(birthYear)
    {}
    void Speak() const final
    {
        std::cout << "My name is " << m_name << " and I was born at " << m_birthYear;
    }
private:
    std::string m_name;
    int m_birthYear;
};

/* Ведёт разговор с набором объектов, с которыми можно побеседовать */
void SmallTalk(std::vector<std::shared_ptr<ISpeakable>> const& speakableObjects)
{
    for (auto& object : speakableObjects)
    {
        object->Speak();
    }
}

/* Рисует набор объектов, которые можно нарисовать на переданном холсте (принимает объекты и холст) */
void Draw(std::vector<std::shared_ptr<ICanvasDrawable>> const& drawableObjects, CoutCanvas canvas)
{
    for (auto& object : drawableObjects)
    {
        object->Draw(canvas);
    }
}

/* Копирует состояние из одного сериализуемого объекта в другой */
void CopyState(const ISerializable& from, ISerializable& to)
{
    std::stringstream stream;
    stream = std::stringstream();
    from.SaveTo(stream);
    to.RestoreFrom(stream);
}

int main()
{
    /*
    Нарисовать при помощи функции Draw домик с котиком рядом с ним:
        /\
       /  \
      / O  \
     --------
      |    |
      |    |
      ------
      до 8 баллов (8-6-4)
    */
    Rectangle houseRect(CPoint{ 30, 30 }, 30, 30);
    Triangle triangle(CPoint{ 30, 30 }, CPoint{ 60, 30 }, CPoint{ 45, 10 });
    Cat cat(CPoint{ 60, 20 });
    CoutCanvas canvas;
    std::vector<std::shared_ptr<ICanvasDrawable>> drawableObjects;
    drawableObjects.push_back(std::make_shared<Rectangle>(houseRect));
    drawableObjects.push_back(std::make_shared<Triangle>(triangle));
    drawableObjects.push_back(std::make_shared<Cat>(cat));
    Draw(drawableObjects, canvas);

    /* Создать прямоугольник.
     Скопировать в него при помощи CopyState состояние из прямоугольника,
     задающего стены дома
      до 6 баллов (6-5-3)
    */
    
    Rectangle rect(CPoint{ 0, 0 }, 10, 10);
    CopyState(houseRect, rect);
    std::cout << std::endl;
    rect.Draw(canvas);

    /*
    Создать человека по имени Ivanov Ivan 1980 года рождения.
    При помощи SmallTalk побеседовать с этим человеом и вышесозданным котом
      до 6 баллов (6-5-3)
    */

    Person person("Ivanov Ivan", 1977);
    std::vector<std::shared_ptr<ISpeakable>> speakableObjects;
    speakableObjects.push_back(std::make_shared<Person>(person));
    speakableObjects.push_back(std::make_shared<Cat>(cat));
    SmallTalk(speakableObjects);

    return 0;
}
