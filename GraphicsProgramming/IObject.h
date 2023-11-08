#ifndef OBJECT_H
#define OBJECT_H

class IObject
{
protected:
    ~IObject() = default;

public:
    // Pure virtual functions (abstract functions)
    virtual int initialize() = 0;
    virtual void finalize() = 0;
    virtual int update() = 0;
    virtual int draw() = 0;
};

#endif // !OBJECT_H
