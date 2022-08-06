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

    public:
        void setRotation(const float rotate);      
    private:          
        float m_rotation;
    };

    // Camera handlers
    // -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
    class OrthoHandler : public CameraHandler
    {
    public:

        struct Data 
        {
            glm::vec3   Position        { glm::vec3{ 0.0f, 0.0f, 0.0f} };
            float       Zoom            { 1.0f };
            float       Rotate          { 0.0f };
            bool        EnableRotation  { true };
        };

    public:
        OrthoHandler(const float aspectratio = 1.0f, const OrthoHandler::Data& data = OrthoHandler::Data());
        virtual ~OrthoHandler() = default;

        virtual void onUpdate(const DeltaTime dt)            override;
        virtual void onEvent(Event& e)                       override;

        virtual void setAspectRatio(const float aspectratio) override;        
        virtual const float  getAspectRatio()                override;
        virtual void updateProjectionMatrix()                override;

        virtual const glm::mat4& getProjectionMatrix()       override;
        virtual const glm::mat4& getViewMatrix()		     override;

        virtual void enablePrimeWindowResize()  override { m_enabled_prime_window = true; }
        virtual void disablePrimeWindowResize() override { m_enabled_prime_window = false; }            

    private:
        const Data getData() { return m_data; }
        void  setData(const Data& data);
        const bool handleMouseScroll(const OnMouseScrolled& e);

    private:        
        Data  m_data;
        float m_aspectRatio, m_speed, m_rotSpeed;
    };

}