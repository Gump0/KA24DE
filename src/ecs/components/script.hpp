///////////////////////////////////////////////////////////////
// component that represents what each userscript will contain
///////////////////////////////////////////////////////////////
#ifndef SCRIPT_H
#define SCRIPT_H

//---------------------------------------------------------------------------------
class Dictator;

class Script
{
public:
    ~Script() = default;

    virtual void Start(Dictator& dictator, Entity entity);
    virtual void Update(Dictator& dictator, Entity entity, double deltaTime);
    virtual void OnDestroy(Dictator& dictator, Entity entity);

    bool hasStarted {false};
};

#endif
