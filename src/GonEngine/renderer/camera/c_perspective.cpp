#include "GonEngine/renderer/camera/c_perspective.hpp"
#include "GonEngine/platform/windows_window.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"
#include "GonEngine/gon.hpp"

namespace gon {

    Perspective::Perspective(const glm::vec3& position, const glm::vec3& up, float yaw, float pitch)
        : Camera(position),
        m_worldUp(up), m_yaw(yaw), m_pitch(pitch), m_fov(k_FOV), m_near(0.1f), m_far(100.0f)
    {
        GON_TRACE("[CREATED] Perspective camera.");
        updateCameraVectors();
    }

    Perspective::Perspective(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
        : Camera(posX, posY, posZ), 
        m_worldUp(glm::vec3(upX, upY, upZ)), m_yaw(yaw), m_pitch(pitch), m_fov(k_FOV), m_near(0.1f), m_far(100.0f)
    {

        GON_TRACE("[CREATED] Perspective camera.");
        updateCameraVectors();
    }

    Perspective::~Perspective() { GON_TRACE("[DESTROYED] Perspective camera."); }

    const std::pair<glm::mat4, glm::mat4> Perspective::getViewProjectionMatrix() const
    {  
        auto wi = static_cast<float>(GonEngine::getGon().getPtrWindow().width());
        auto he = static_cast<float>(GonEngine::getGon().getPtrWindow().height());

        //GON_ERROR("{0} {1}",wi, he);

        std::pair<glm::mat4, glm::mat4> w;
        
        w.first = glm::mat4(1.0f); w.second = glm::mat4(1.0f);

        w.first   = glm::lookAt(m_position, m_position + m_front, m_up);
        w.second  = glm::perspective
        (
            glm::radians(m_fov),
            wi / he
                  ,
            m_near, m_far
        );
        return w;
    }


    void Perspective::updateCameraVectors() {
        glm::vec3 front;
        front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        front.y = sin(glm::radians(m_pitch));
        front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_front = glm::normalize(front);

        m_right = glm::normalize(glm::cross(m_front, m_worldUp));
        m_up = glm::normalize(glm::cross(m_right, m_front));
    }


}