#ifndef OBJECT_H
#define OBJECT_H

class IObject
{
protected:
    ~IObject() = default;

public:
    // Pure virtual functions (abstract functions)
    virtual int Initialize() = 0;
    virtual int Draw() = 0;
    virtual void Finalize() const = 0;
};

#endif // !OBJECT_H
