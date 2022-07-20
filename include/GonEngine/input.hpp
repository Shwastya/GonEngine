#pragma once

#include "GonEngine/events/keycodes.h"

namespace gon
{
	struct MousePosition {

		float x, y; 
	};
	enum class StateCursor { 

		visible = 0, 
		hidden, 
		locked 
	};
	// Input Polling - Static Global Manager -
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
	class Input	{

	public:

		Input() = delete;
		~Input() = delete;

		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		Input(Input&&) noexcept = delete;
		Input& operator=(Input&&) noexcept = delete;

		static bool  isKeyPressed(KeyCode keycode);
		static bool  isMouseButtonPressed(MouseButton button);
		static float getXmouse();
		static float getYmouse();
		static MousePosition getMousePos();
	};
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
}
// Tenemos un event system, podemos recibir eventos de tipo key, mouse y app
// Tratandose de un sistema de layers necesitamos empaquetar los cambios de 
// estado de alguna manera para poder administrar bien como se propogan estos 
// eventos y poder traducir las abstracciones a conceptos mas reales 
// relacionados con la  aplicacion.

// En caso de querer tener multiples ventanas, siendo la clase INPUT estatica
// habra que preguntar por un window en particular -puntero glgw a window-

// Engine es global y tiene el Window como propiedad, por lo que window debe proveer 
// una manera de devolver el window nativo o original y poder acceder a el desde 
// el engine global