///////////////////////////////////////////////////////////////////
// handles user-made scripts and injects them into core game-loop
// requires (Script *custom made by user)
///////////////////////////////////////////////////////////////////
#ifndef SCRIPTING_LAYER_H
#define SCRIPTING_LAYER_H

#include "../system.hpp"
#include <memory>
#include <map>
#include <vector>
//---------------------------------------------------------------------------------
class ScriptingLayer : public System
{
public:
    void Init(Dictator* dictator)
    {
        mDictator = dictator;
    };

    void Start()
    {
        for(auto const& entity : mEntities)
        {
            auto it = mScriptMap.find(entity);
            if(it != mScriptMap.end())
            {
                std::vector<std::unique_ptr<Script>>& scripts = it->second;
                for(auto& script : scripts)
                {
                    if(!script->hasStarted)
                    {
                        script->Start(*mDictator, entity);
                        script->hasStarted {true};
                    }
                }
            }
        }
    };

    void Update(double deltaTime)
    {
        for(auto const& entity : mEntities)
        {
            auto it = mScriptMap.find(entity);
            if(it != mScriptMap.end())
            {
                std::vector<std::unique_ptr<Script>>& scripts = it->second;
                for(auto& script : scripts)
                {
                    if(!script->hasStarted)
                    {
                        script->Start();
                        script->hasStarted {true};
                    }
                    script->Update(*mDictator, entity, deltaTime);
                }
            }
        }
    };

    template<typename T>
    T* AddScript(Entity entity)
    {
        static_assert(std::is_base_of<Script, T>::value, "T must derive from Script");

        auto script = std::make_unique<T>();
        T* scriptPtr = script.get();

        mScriptMap[entity].push_back(std::move(script));

        return scriptPtr;
    };

    void RemoveAllScripts(Entity entity)
    {
        auto it = mScriptMap.find(entity);
        if(it != mScriptMap.end())
        {
            for(auto& script : it->second)
            {
                script->OnDestroy(*mDictator, entity);
            }
            mScriptMap.erase(it);
        }
    }

    void EntityDestroyed(Entity entity)
    {
        RemoveAllScripts(entity);
    }

protected:
    // std::vector<Script> mScripts {};
    std::map<Entity, std::vector<std::unique_ptr<Script>>> mScriptMap {};
    Dictator* mDictator {nullptr};
};

#endif
