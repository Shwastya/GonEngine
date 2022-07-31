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
    void CameraPerspective ::setRotation(const float rotate) { GON_WARN("{0}", rotate); }

    void CameraPerspective ::updateViewMatrix() 
    {
        m_viewMatrix = glm::lookAt(m_position, m_position + m_front, m_up);
    }




    // Camera handlers
    // -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
    PerspectiveCameraHandler::PerspectiveCameraHandler(const glm::vec3& pos, const float ratio)
        : m_position(pos),
          m_worldUp(glm::vec3{0.0f, 1.0f, 0.0f}),
          m_aspectRatio(ratio),
          m_yaw(-90.0f), 
          m_pitch(0.0f),
          m_fov(45.0f),
          m_speed(2.5f),
          m_near(0.1f),
          m_far(100.0f),
          m_mouseSentitivity(0.1f),
          m_firstMouse(true),
          m_enableMouseDisplacement(false)
    {
        m_camera = std::make_unique<CameraPerspective>(pos);        

        PerspectiveCameraHandler::updateCameraVectors(); 
        m_camera->setPosition(pos);
        updateProjectionMatrix();
    }

    void PerspectiveCameraHandler::onUpdate(const DeltaTime dt)
    {

        if (Input::isKeyPressed(GON_KEY_W)) 
        {
            m_position += m_front * (m_speed * dt); m_camera->setPosition(m_position);
            updateProjectionMatrix();
        } 
        else if (Input::isKeyPressed(GON_KEY_S))
        {
            m_position -= m_front * (m_speed * dt); m_camera->setPosition(m_position);
            updateProjectionMatrix();
        }
        if (Input::isKeyPressed(GON_KEY_A)) 
        {
            m_position -= m_right * (m_speed * dt); m_camera->setPosition(m_position);
            updateProjectionMatrix();
        }
        else if (Input::isKeyPressed(GON_KEY_D)) 
        {
            m_position += m_right * (m_speed * dt); m_camera->setPosition(m_position);
            updateProjectionMatrix();
        } 
       
        if (Input::isMouseButtonPressed(Gon::MouseButton::Left))
        {
            m_enableMouseDisplacement = true;            
            GonEngine::getGon().getPtrWindow().setCaptureMode(true);
        }
        else
        {
            if (!m_firstMouse)
            {
                m_firstMouse = true;
                m_enableMouseDisplacement = false;
                GonEngine::getGon().getPtrWindow().setCaptureMode(false);
            }            
        }
    }

    void PerspectiveCameraHandler::onEvent(Event& e)
    {
        if (m_enableMouseDisplacement)
        {
            if (e.getEventType() == EventType::MouseMoved)
                onMouseMoved(dynamic_cast<OnMouseMoved&>(e));
        }
        
        if (e.getEventType() == EventType::MouseScrolled)
            handleMouseScroll(dynamic_cast<OnMouseScrolled&>(e).GetYOffset());

    }

    void PerspectiveCameraHandler::setAspectRatio(const float aspectratio) { m_aspectRatio = aspectratio; }
    const float PerspectiveCameraHandler::getAspectRatio() { return m_aspectRatio; }
    void PerspectiveCameraHandler::updateProjectionMatrix()
    {       
        m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);        
    }

    glm::mat4& PerspectiveCameraHandler::getProjectionMatrix()
    {        
        return m_projectionMatrix;
    }    

    void PerspectiveCameraHandler::updateCameraVectors()
    {    
        glm::vec3 front;
        front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        front.y = sin(glm::radians(m_pitch));
        front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

        m_front = glm::normalize(front);
        dynamic_cast<CameraPerspective&>(*m_camera).setFront(m_front);

        m_right = glm::normalize(glm::cross(m_front, m_worldUp));

        const glm::vec3 up{ glm::normalize(glm::cross(m_right, m_front))};
        dynamic_cast<CameraPerspective&>(*m_camera).setUp(up);
    }

    void PerspectiveCameraHandler::handleMouseMovement(float xoffset, float yoffset, bool constrainPitch)
    {
        const float xoff = xoffset * m_mouseSentitivity;
        const float yoff = yoffset * m_mouseSentitivity;

        m_yaw   += xoff;
        m_pitch += yoff;

        if (constrainPitch)
        {
            if (m_pitch > 89.0f)  m_pitch = 89.0f;
            if (m_pitch < -89.0f) m_pitch = -89.0f;
        }
        updateCameraVectors();       
    }
    void PerspectiveCameraHandler::handleMouseScroll(const float yoffset)
    {
        if (m_fov >= 0.1f && m_fov <= 140.0f) m_fov -= yoffset;
        if (m_fov <= 0.1f) m_fov    = 0.1f;
        if (m_fov >= 140.0f) m_fov  = 140.0f;
        updateProjectionMatrix();
    }
    

    bool PerspectiveCameraHandler::onMouseMoved(OnMouseMoved& e)
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


}