#pragma once
#include "GonEngine/renderer/camera.hpp"

namespace Gon {
        
    class CameraOrthographic : public Camera
    {
    public:
        CameraOrthographic(const glm::vec3& position);
            
        virtual ~CameraOrthographic();
        
        virtual const glm::mat4& getViewMatrix()	        override;
        virtual void updateViewMatrix()					    override;

        virtual const glm::vec3& getPosition()              override;
        virtual void setPosition(const glm::vec3& position) override;
        virtual void setRotation(const float rotate)        override;        

    private:    
      
    private:          
        float m_rotation;
    };


    // Camera handlers
    // -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
    class OrthographicCameraHandler : public CameraHandler
    {
    public:
        OrthographicCameraHandler(const glm::vec3& position, const float aspectratio = 1.0f, const bool rotation = true);
        virtual ~OrthographicCameraHandler() = default;

        virtual void onUpdate(const DeltaTime dt)   override;
        virtual void onEvent(Event& e)              override;   

        virtual void setAspectRatio(const float aspectratio) override;        
        virtual const float  getAspectRatio()                override;
        virtual void updateProjectionMatrix()                override;

        virtual glm::mat4& getProjectionMatrix()             override;

        
     

    private:

        glm::vec3   m_position;
        float       m_aspectRatio;
        bool        m_enableRotation; 
        float       m_zoom, m_speed, m_rotate, m_rotSpeed;
    };

}