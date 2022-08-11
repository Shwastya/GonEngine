#include "GonEngine/geometries/triangle.hpp"
#include "GonEngine/geometries/geometry.hpp"
#include "GonEngine/geometries/skybox.hpp"
#include <glm/detail/func_geometric.inl>
#include "GonEngine/geometries/cube.hpp"
#include "GonEngine/geometries/quad.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glad/glad.h>


namespace Gon 
{
    u_ptr<Geometry> Geometry::create(Geometry::Type type, const float size)
    {
        switch (type)
        {
        case Geometry::TRIANGLE: return make_u_ptr<Cube>(size);
        case Geometry::QUAD:     return make_u_ptr<Quad>(size);
        case Geometry::CUBE:     return make_u_ptr<Cube>(size);
        }
        GON_ASSERT(false, "Geometry bad type parameter");
        return nullptr;
    }  

    u_ptr<Geometry> Geometry::create(Geometry::Type type)
    {
        switch (type)
        {
        case Geometry::SKYBOX:   return make_u_ptr<SkyBox>();
        }
        GON_ASSERT(false, "Geometry bad type parameter");
        return nullptr;
    }
}