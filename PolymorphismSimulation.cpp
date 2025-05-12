#include <iostream>
using namespace std;

// Polymorphism
class ShapeP // Interface
{
public:
    ShapeP() {} // The constructor cannot be virtual
    virtual void AreaP()=0;
    virtual void circumferenceP()=0;
    virtual void DrawP()=0;
//virtual  ̃~Shape() {} // The destructor should be virtual
};
class CircleP : public ShapeP
{
public:
    void AreaP() override {
        cout<<"Circle Area.\n";
    }
    void circumferenceP() override {
        cout<<"Circle circumference.\n";
    }
    void DrawP() override {
        cout<<"Circle Drawn.\n";
    } 
};

class SquareP : public ShapeP
{
public:
    void AreaP() override {
        cout<<"Square Area.\n";
    }
    void circumferenceP() override {
        cout<<"Square circumference.\n";
    }
    void DrawP() override {
        cout<<"Square Drawn.\n";
    } 
};
class TriangleP : public ShapeP
{
public:
    void AreaP() override {
        cout<<"Triangle Area.\n";
    }
    void circumferenceP() override {
        cout<<"Triangle circumference.\n";
    }
    void DrawP() override {
        cout<<"Triangle Drawn.\n";
    } 
};
class Run
{
protected:
    ShapeP* shape;
public:
    Run(ShapeP* sh) {shape=sh;}
    void Play() {shape->DrawP(); shape->AreaP(); shape->circumferenceP();}
};
void TestRun()
{
    ShapeP* shape = new CircleP;
    Run run(shape);
    run.Play();
    delete shape;
};

// Ploymorphism Simulation
struct Shape;
struct ShapeVtable
{
// The constructor is not virtual so it does not exist here
    void (*Area)(Shape*);
    void (*Circumference)(Shape*);
    void (*Draw)(Shape*);
};
struct Shape
{
    ShapeVtable* vtable;
};
// Functions
void ShapeDraw(Shape* shape)
{
    shape->vtable->Draw(shape);
}
void ShapeArea(Shape* shape)
{
    shape->vtable->Area(shape);
}
void ShapeCircumference(Shape* shape)
{
    shape->vtable->Circumference(shape);
}

// Circle
struct Circle
{
    Shape parent;
    int raduis;
    double area , circumference;
};
void CircleArea(Circle* circle)
{
    circle->area = circle->raduis * circle->raduis * 3.14;
}
void CircleCircumference(Circle* circle)
{
    circle->circumference = circle->raduis * 2 * 3.14;
}
void CircleDraw(Circle* circle)
{
    cout<<"Circle Area =  "<<circle->area
    <<", Circle Circumference = "<<circle->circumference
    <<" Units!"<<endl;
}

ShapeVtable circle_vtable ={

    (void(*)(Shape*)) CircleArea,
    (void(*)(Shape*)) CircleCircumference,
    (void(*)(Shape*)) CircleDraw
};
void CircleInitialize(Circle* circle)
{
    circle->parent.vtable=&circle_vtable;
    circle->raduis= 4;
    circle->area=0;
    circle->circumference=0;

}

// Square
struct Square
{
    Shape parent;
    int length;
    double area , circumference;
};
void SquareArea(Square* square)
{
    square->area = square->length * square->length ;
}
void SquareCircumference(Square* square)
{
    square->circumference = square->length * 4;
}
void SquareDraw(Square* square)
{
    cout<<"Square Area =  "<<square->area
    <<", Square Circumference = "<<square->circumference
    <<" Units!"<<endl;
}

ShapeVtable square_vtable ={

    (void(*)(Shape*)) SquareArea,
    (void(*)(Shape*)) SquareCircumference,
    (void(*)(Shape*)) SquareDraw
};
void SquareInitialize(Square* square)
{
    square->parent.vtable=&square_vtable;
    square->length= 4;
    square->area=0;
    square->circumference=0;

}
// Triangle 
struct Triangle
{
    Shape parent;
    int hight, length;
    double area , circumference;
};
void TriangleArea(Triangle* triangle)
{
    triangle->area = triangle->hight * triangle->length * 0.5;
}
void TriangleCircumference(Triangle* triangle)
{
    triangle->circumference = triangle->length * 3;
}
void TriangleDraw(Triangle* triangle)
{
    cout<<"Triangle Area =  "<<triangle->area
    <<", Triangle Circumference = "<<triangle->circumference
    <<" Units!"<<endl;
}

ShapeVtable triangle_vtable ={

    (void(*)(Shape*)) TriangleArea,
    (void(*)(Shape*)) TriangleCircumference,
    (void(*)(Shape*)) TriangleDraw
};
void TriangleInitialize(Triangle* triangle)
{
    triangle->parent.vtable=&triangle_vtable;
    triangle->hight= 4;
    triangle->length= 6; 
    triangle->area=0;
    triangle->circumference=0;

}
int main()
{
    // Ploymorphism
    ShapeP* myShape1 = new CircleP();   
    Run myRun1(myShape1);
    myRun1.Play();   
    delete myShape1;   // Clean up
    cout<<"***************\n";
    ShapeP* myShape2 = new SquareP();   
    Run myRun2(myShape2);
    myRun2.Play();   
    delete myShape2;   // Clean up
    cout<<"***************\n";
    ShapeP* myShape3 = new TriangleP();   
    Run myRun3(myShape3);
    myRun3.Play();   
    delete myShape3;   // Clean up
    cout<<"***************\n";
    // Circle
    Circle circle;
    CircleInitialize(&circle);
    // Square
    Square square;
    SquareInitialize(&square);
    // Triangle 
    Triangle triangle;
    TriangleInitialize(&triangle);

    Shape* shapes[3];
    shapes[0]=(Shape*)&circle; 
    shapes[1]=(Shape*)&square; 
    shapes[2]=(Shape*)&triangle; 

    int i;
    for(i=0;i<3;i++)
    {
        ShapeArea(shapes[i]);
        ShapeCircumference(shapes[i]);
        ShapeDraw(shapes[i]);
    }

}
