#pragma once
#ifndef _Scene_HPP_
#define _Scene_HPP_

#include <engine/Entity.hpp>
#include <engine/Shader.hpp>

#include <vector>
#include <memory>

namespace engine
{

    class Scene
    {
    private:
        std::vector<std::pair<std::unique_ptr<Entity>, std::unique_ptr<Shader>>> m_entities;

    public:
    };

} // namespace engine

#endif /* _Scene_HPP_ */