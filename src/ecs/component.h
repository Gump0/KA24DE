#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>
#include <string>
//---------------------------------------------------------------------------------
class Component
{
public:
    virtual void Update();
private:
    Component();
    ~Component();
};

#endif
