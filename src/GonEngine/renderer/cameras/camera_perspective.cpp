#include "GonEngine/renderer/cameras/camera_perspective.hpp"
#include "GonEngine/platform/windows_window.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/input.hpp"
#include "GonEngine/log.hpp"
#include "GonEngine/gon.hpp"

namespace Gon {

    CameraPerspective::CameraPerspective(const glm::vec3& position)
        : Camera(position), m_up(0.0f), m_front(0.0f)
    {        
        GON_TRACE("[CREATED] Perspective camera.");
    }

    CameraPerspective ::~CameraPerspective () { GON_TRACE("[DESTROYED] Perspective camera."); }

    const glm::mat4& CameraPerspective::getViewMatrix() 
    {
        updateViewMatrix();
        return m_viewMatrix;
    }   
    const glm::vec3& CameraPerspective ::getPosition() { return m_position; }
    void CameraPerspective ::setPosition(const glm::vec3& position)
    {
        m_position = position;
    }
    void CameraPerspective ::updateViewMatrix() 
    {
        m_viewMatrix = glm::lookAt(m_position, m_position + m_front, m_up);
    }




    // Camera handlers
    // -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
    PerspHandler::PerspHandler(const float ratio, const PerspHandler::Data& data)
        : m_worldUp(glm::vec3{0.0f, 1.0f, 0.0f}), 
          m_aspectRatio(ratio), m_speed(2.5f), m_near(0.1f), m_far(100.0f),
          m_firstMouse(true), m_enableMouseDisplacement(false)
    {                
        m_camera = make_u_ptr<CameraPerspective>(data.Position);
        setData(data);
    }

    void PerspHandler::onUpdate(const DeltaTime dt)
    {
        if (Input::isKeyPressed(GON_KEY_W))        
            m_camera->setPosition(m_data.Position += m_data.Front * (m_speed * dt));        
        else if (Input::isKeyPressed(GON_KEY_S))        
            m_camera->setPosition(m_data.Position -= m_data.Front * (m_speed * dt));
        if (Input::isKeyPressed(GON_KEY_A))        
            m_camera->setPosition(m_data.Position -= m_data.Right * (m_speed * dt));
        else if (Input::isKeyPressed(GON_KEY_D))
            m_camera->setPosition(m_data.Position += m_data.Right * (m_speed * dt));
       
        if (Input::isMouseButtonPressed(Gon::MouseButton::Right))        
            GonEngine::getGon().getPtrWindow().setCaptureMode(m_enableMouseDisplacement = true);        
        else
        {
            if (!m_firstMouse)
            {
                m_firstMouse = true;
                GonEngine::getGon().getPtrWindow().setCaptureMode(m_enableMouseDisplacement = false);
            }            
        }
    }

    void PerspHandler::onEvent(Event& e)
    {
        if (m_enableMouseDisplacement && (e.getEventType() == EventType::MouseMoved))
                onMouseMoved(dynamic_cast<OnMouseMoved&>(e));        
        
        if (e.getEventType() == EventType::MouseScrolled)
            handleMouseScroll(dynamic_cast<OnMouseScrolled&>(e).GetYOffset());

        if (m_enabled_prime_window && (e.getEventType() == EventType::WindowResize))
        {
            OnWindowResize& _e = dynamic_cast<OnWindowResize&>(e);
            m_aspectRatio = static_cast<float>(_e.GetWidth()) / static_cast<float>(_e.GetHeight());
        }
    }

    void PerspHandler::setAspectRatio(const float aspectratio) { m_aspectRatio = aspectratio; }
    const float PerspHandler::getAspectRatio() { return m_aspectRatio; }
    void PerspHandler::updateProjectionMatrix()
    {       
        m_projectionMatrix = glm::perspective(glm::radians(m_data.Fov), m_aspectRatio, m_near, m_far);        
    }

    const glm::mat4& PerspHandler::getProjectionMatrix()
    {        
        updateProjectionMatrix();
        return m_projectionMatrix;
    }

    const glm::mat4& PerspHandler::getViewMatrix()
    {
        return m_camera->getViewMatrix();
    }

    void PerspHandler::updateCameraVectors()
    {    
        glm::vec3 front;
        front.x = cos(glm::radians(m_data.Yaw)) * cos(glm::radians(m_data.Pitch));
        front.y = sin(glm::radians(m_data.Pitch));
        front.z = sin(glm::radians(m_data.Yaw)) * cos(glm::radians(m_data.Pitch));

        m_data.Front = glm::normalize(front);
        dynamic_cast<CameraPerspective&>(*m_camera).setFront(m_data.Front);

        m_data.Right = glm::normalize(glm::cross(m_data.Front, m_worldUp));
        dynamic_cast<CameraPerspective&>(*m_camera).setUp
        (
            glm::normalize(glm::cross(m_data.Right, m_data.Front))
        );
    }

    void PerspHandler::handleMouseMovement(float xoffset, float yoffset, bool constrainPitch)
    {
        const float xoff = xoffset * m_mouseSensitivity;
        const float yoff = yoffset * m_mouseSensitivity;

        m_data.Yaw   += xoff;
        m_data.Pitch += yoff;

        if (constrainPitch)
        {
            if (m_data.Pitch > 89.0f)  m_data.Pitch = 89.0f;
            if (m_data.Pitch < -89.0f) m_data.Pitch = -89.0f;
        }
        updateCameraVectors();       
    }
    void PerspHandler::handleMouseScroll(const float yoffset)
    {
        if (m_data.Fov >= 0.1f && m_data.Fov <= 140.0f) m_data.Fov -= yoffset;
        if (m_data.Fov <= 0.1f) m_data.Fov = 0.1f;
        if (m_data.Fov >= 140.0f) m_data.Fov = 140.0f;
    }    

    bool PerspHandler::onMouseMoved(OnMouseMoved& e)
    {
        if (m_firstMouse)
        {
            m_lastX = e.getX();
            m_lastY = e.getY();
            m_firstMouse = false;
        }
        const float Xoffset = e.getX() - m_lastX;
        const float Yoffset = m_lastY - e.getY();

        m_lastX = e.getX();
        m_lastY = e.getY();

        handleMouseMovement(Xoffset, Yoffset, true);
        return false;
    }

    void PerspHandler::setData(const Data& data)
    {
        m_data = data;
        updateCameraVectors();
    }


}