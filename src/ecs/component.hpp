#ifndef COMPONENT_H
#define COMPONENT_H

//---------------------------------------------------------------------------------
class Component
{
public:
    virtual void Update();
    virtual void ComponentDebug(int objectId);      // temporary method that debugs component name

    Component();
    ~Component();
    Component(const Component &obj);
};

#endif
