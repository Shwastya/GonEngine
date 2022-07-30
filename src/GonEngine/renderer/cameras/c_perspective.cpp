#include "GonEngine/renderer/cameras/c_perspective.hpp"
#include "GonEngine/platform/windows_window.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"
#include "GonEngine/gon.hpp"

namespace Gon {

    Perspective::Perspective(const glm::vec3& up, float yaw, float pitch)
        : Camera(glm::mat4(1.0f), glm::mat4(1.0f)),
        m_worldUp(up), m_yaw(yaw), m_pitch(pitch), m_fov(k_FOV), m_near(0.1f), m_far(100.0f)
    {
        GON_TRACE("[CREATED] Perspective camera.");
        setPosition(glm::vec3{ 0.0f, 0.0f, 3.0f });
    }

    Perspective::Perspective(float upX, float upY, float upZ, float yaw, float pitch)
        : Camera(glm::mat4(1.0f), glm::mat4(1.0f)),
        m_worldUp(glm::vec3(upX, upY, upZ)), m_yaw(yaw), m_pitch(pitch), m_fov(k_FOV), m_near(0.1f), m_far(100.0f)
    {
        setPosition(glm::vec3{ 0.0f, 0.0f, 3.0f });
        GON_TRACE("[CREATED] Perspective camera.");
    }

    Perspective::~Perspective() { GON_TRACE("[DESTROYED] Perspective camera."); }

    const glm::mat4& Perspective::getViewMatrix() const
    {
        return m_viewMatrix;
    }

    const glm::mat4& Perspective::getProjectionMatrix() const
    {
        return m_projectionMatrix;
    }
    const glm::vec3& Perspective::getPosition()
    {
        return m_position;
    }
    void Perspective::setPosition(const glm::vec3& position)
    {
        m_position = position;
       // Perspective::updateCameraVectors();
        Perspective::updateViewMatrix();
    }

    void Perspective::setRotation(const float rotate)
    {
        GON_WARN("{0}", rotate);
    }

    void Perspective::updateViewMatrix() {
        m_viewMatrix = glm::lookAt(m_position, m_position + m_front, m_up);
        m_projectionMatrix = glm::perspective
        (
            glm::radians(m_fov),
            static_cast<float>(GonEngine::getGon().getPtrWindow().width()) /
            static_cast<float>(GonEngine::getGon().getPtrWindow().height()),
            m_near, m_far
        );
    }
    void Perspective::updateProjectionMatrix()
    {
        m_projectionMatrix = glm::perspective
        (
            glm::radians(m_fov),
            static_cast<float>(GonEngine::getGon().getPtrWindow().width()) /
            static_cast<float>(GonEngine::getGon().getPtrWindow().height()),
            m_near, m_far
        );
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