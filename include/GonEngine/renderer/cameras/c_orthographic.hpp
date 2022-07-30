#pragma once
#include "GonEngine/renderer/camera.hpp"

namespace Gon {

    constexpr float k_zNear = -1.0f;
    constexpr float k_zFar  =  1.0f;  
    
    class Orthographic : public Camera
    {
    public:
        Orthographic(const float left = -1.0f, const float right = 1.0f, const float bottom = -1.0f, const float top = 1.0f);
            
        virtual ~Orthographic();
        
        virtual const glm::mat4& getViewMatrix()		const override;
        virtual const glm::mat4& getProjectionMatrix()	const override;

        virtual const glm::vec3& getPosition()              override;
        virtual void setPosition(const glm::vec3& position) override;
        virtual void setRotation(const float rotate) override;

        void updateProjectionMatrix(const float left, const float right, const float bottom, const float top);

    private:    
        void updateViewMatrix();
        

    private:          
        float m_rotation;
    };





    // Camera handlers
    // -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
    class OrthoHandler : public CameraHandler
    {
    public:
        OrthoHandler(const glm::vec3& position, const float ratio = 1.0f, const bool rotation = true);
        virtual ~OrthoHandler() = default;

        virtual void onUpdate(const DeltaTime dt)   override;
        virtual void onEvent(Event& e)              override;   

   // non virtual
        const void updateApectRatio() const;

    private:

        glm::vec3 m_position;
        float m_aspectRatio;
        float m_zoom;
        bool m_enableRotation; 
        float m_rotate;
        float m_speed;
        float m_rotSpeed;
    };

}