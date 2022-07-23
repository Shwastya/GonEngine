#include "GonEngine/platform/windows_window.hpp"
#include "GonEngine/input.hpp"
#include "GonEngine/gon.hpp"
#include <GLFW/glfw3.h> 

#define GON_WIN	  static_cast<Window*>(&GonEngine::getGon().getPtrWindow()); // void* ptr
#define GLFW_WIN  static_cast<GLFWwindow*>

namespace gon {

	bool Input::isKeyPressed(KeyCode keycode)
	{
		// obtenemos el puntero a window especifico desde Engine global que 
		// tiene el atributo GLFW window de las clases derrivadas de SWindow.hpp 
		// (no global) asegurando que sea una instancia de Window, ya que este 
		// input tiene que ser especifico para windows		

		Window& w = *GON_WIN;

		int K = glfwGetKey 
		(
			GLFW_WIN(w.getWindow()),static_cast<int32_t>(keycode)
		);
		return (K == GLFW_PRESS || K == GLFW_REPEAT);
	}
	bool Input::isMouseButtonPressed(MouseButton button)
	{
		Window& w = *GON_WIN;

		int b = glfwGetMouseButton // get button mouse state
		(
			GLFW_WIN(w.getWindow()),static_cast<int32_t>(button)
		);
		return (b == GLFW_PRESS);
	}
	float Input::getXmouse()
	{
		Window& w = *GON_WIN;

		double x, y;

		glfwGetCursorPos // get mouse cursor position
		(
			GLFW_WIN(w.getWindow()),&x, &y
		);
		return static_cast<float>(x);
	}
	float Input::getYmouse()
	{
		Window& w = *GON_WIN;

		double x, y;
		glfwGetCursorPos // get mouse cursor position
		(
			GLFW_WIN(w.getWindow()),&x, &y
		);
		return static_cast<float>(y);
	}
	MousePosition Input::getMousePos()
	{
		Window& w = *GON_WIN;

		double x, y;
		glfwGetCursorPos // get mouse cursor position
		(
			GLFW_WIN(w.getWindow()), &x, &y
		);
		return
		{
			static_cast<float>(x), 
			static_cast<float>(y)  
		};
	}	
}