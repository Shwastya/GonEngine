#include "GonEngine/renderer/camera/c_orthographic.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"


namespace gon {

	Orthographic::Orthographic(const float x, const float y, const float z, const float orthodistant)
		: Camera(x,y,z), m_rotation(0.0f),
		m_left(orthodistant * -1.0f),	m_right(orthodistant),
		m_bottom(orthodistant * -1.0f),	m_top(orthodistant)
	{
		GON_TRACE("[CREATED] Orthographic camera.");
	}
	Orthographic::Orthographic(const glm::vec3& position, const float orthodistant) 
		: Camera(position), m_rotation(0.0f),
		m_left(orthodistant * -1.0f), m_right(orthodistant),
		m_bottom(orthodistant * -1.0f), m_top(orthodistant)
	{
		GON_TRACE("[CREATED] Orthographic camera.");
	}	
	Orthographic::~Orthographic() {	GON_TRACE("[DESTROYED] Orthographic camera.");}
	

	const std::pair<glm::mat4, glm::mat4> Orthographic::getViewProjectionMatrix() const
	{
		const glm::mat4 transform{ glm::translate(glm::mat4(1.0f), m_position) *
			glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(0, 0, 1)) };

		glm::mat4 view{ 1.0f };
		view = glm::inverse(transform);		
		
		const std::pair<glm::mat4, glm::mat4> viewProj
		{ 
			view,
			glm::ortho(m_left, m_right, m_bottom, m_top, m_zNear, m_zFar)
		};
		return viewProj;
	}
}
