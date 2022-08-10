#include "tests.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>


namespace Gon
{

	const std::vector<std::string>k_cubemap
	{
		{"../assets/textures/cubemaps/space/cubemap_0.png"},
		{"../assets/textures/cubemaps/space/cubemap_1.png"},
		{"../assets/textures/cubemaps/space/cubemap_2.png"},
		{"../assets/textures/cubemaps/space/cubemap_3.png"},
		{"../assets/textures/cubemaps/space/cubemap_4.png"},
		{"../assets/textures/cubemaps/space/cubemap_5.png"},
	};

	static unsigned int loadCubemap(std::vector<std::string> faces)
	{
		unsigned int textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		int width, height, nrChannels;
		for (unsigned int i = 0; i < faces.size(); i++)
		{
			unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
				);
				stbi_image_free(data);
			}
			else
			{
				std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
				stbi_image_free(data);
			}
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		return textureID;
	}

	unsigned int cubemapTexture = loadCubemap(k_cubemap);

	const Gon::WProps props
	{
		{ "TestWindow" },
		Gon::API::OpenGL,
		1920,
		1080
	};

	struct Engine
	{
		Engine()
			: m_window(props),
			m_camHandler(1920 / 1080)
		{
			m_running = true;
			Gon::RenderCall::init(true, true, true);
			m_window.setVsync(true);

			m_window.setCallBack(std::bind(&Engine::onEvent, this, std::placeholders::_1));
		}

		void onEvent(Event& e)
		{

		}
		void onUpdate()
		{
			RenderCall::setClearColor({ 0.15f, 0.15f, 0.15f, 1.0f });
			RenderCall::clear();



			m_window.swapBuffers();
		}

		void running()
		{
			while (m_running)
			{
				onUpdate();
			}
		}

	private:
		Window m_window;
		PerspHandler m_camHandler;
		bool m_running{ false };
	};
}



int main()
{	
	Gon::Engine engine;
	engine.running();
	return 0;
}


