#pragma once
#include <glm/glm.hpp>
#include <utility>
namespace gon {

	class Camera
	{
	public:

		enum class Movement
		{
			Forward = 0,
			Backward = 1,
			Left = 2,
			Right = 3
		};
		
		Camera(const float x, const float y, const float z)  
			: m_position(glm::vec3(x,y,z)) {}

		Camera(const glm::vec3& position)
			: m_position(position) {}

		virtual ~Camera() = default;
	
		virtual const std::pair<glm::mat4, glm::mat4> getViewProjectionMatrix() const = 0;

		virtual const glm::vec3& getPosition()  = 0;
		virtual void setPosition(const glm::vec3& position) = 0;

		virtual void handleKeyboard(const Movement direction, const float dt) = 0;
		virtual void handleMouseMovement(const float xoffset, const float yoffset, const bool constrainPitch = true) = 0;
		virtual void handleMouseScroll(float yoffset) = 0;		

	protected:
		glm::vec3 m_position;
	};

}
