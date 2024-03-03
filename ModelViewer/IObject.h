#ifndef OBJECT_H
#define OBJECT_H

class IObject
{
protected:
    ~IObject() = default;

public:
    // Pure virtual functions (abstract functions)
    virtual int Initialize() = 0;
    virtual int Update() = 0;
    virtual int Draw() = 0;
};

#endif // !OBJECT_H
