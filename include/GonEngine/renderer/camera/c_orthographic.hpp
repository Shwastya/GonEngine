#pragma once
#include "GonEngine/renderer/camera/camera.hpp"

namespace gon {

    constexpr float m_zNear = -1.0f;
    constexpr float m_zFar  =  1.0f;    
    
    class Orthographic : public Camera
    {
    public:
        Orthographic() = default;
        Orthographic(const float x, const float y, const float z, const float orthodistant = 1.0f, const float rotation = 0.0f);
        Orthographic(const glm::vec3& position, const float orthodistant = 1.0f, const float rotation = 0.0f);       
        
        ~Orthographic();
        
        virtual const std::pair<glm::mat4, glm::mat4> getViewProjectionMatrix() const override;        

        virtual const glm::vec3& getPosition() override { return m_position; };
        virtual void setPosition(const glm::vec3& position) override { m_position = position; };
        

        virtual void handleKeyboard(const Movement direction, const float dt) override {};
        virtual void handleMouseMovement(const float xoffset, const float yoffset, const bool constrainPitch = true) override {};
        virtual void handleMouseScroll(float yoffset) override {};
        
       // virtual void setRotation(const float rot) override;
        // non-virtual
        // -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
        void setRotation(const float rot);
      


    private:        
        float m_rotation, m_right, m_left, m_top, m_bottom;       
       
    };
}