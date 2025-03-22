#include "GL.h"

namespace Barebones
{
	GL::GL()
	{
		glfwInit();

		// Require OpenGL 3.3:
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		// Explicitly use the core-profile (no backwards compatible features required)
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Mac Initialization:
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		// CREATE WINDOW:
		window = glfwCreateWindow(1280, 720, "LearnOpenGL", NULL, NULL);
		if (window == NULL)
		{
			throw std::runtime_error("Failed to create GLFW window");
		}
		glfwMakeContextCurrent(window);

		// GLAD: LOAD ALL OPENGL FUNCTION POINTERS
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw std::runtime_error("Failed to initialize GLAD");
		}

		//UNIFORM BUFFER OBJECT
		uboMatrices.Initialize("Matrices", 0, 1 * sizeof(glm::mat4));
		uboLights.Initialize("Lights", 1, 
			sizeof(glm::vec4) + 
			sizeof(int) * 4 + 
			sizeof(glm::vec4) * MAX_LIGHT_COUNT + 
			sizeof(glm::vec4) * MAX_LIGHT_COUNT
		);
		// 
		//glGenBuffers(1, &UBO);
		//glBindBuffer(GL_UNIFORM_BUFFER, UBO);
		//glBufferData(GL_UNIFORM_BUFFER, 1 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
		//glBindBuffer(GL_UNIFORM_BUFFER, 0);

		//glBindBufferRange(GL_UNIFORM_BUFFER, 0, UBO, 0, 1 * sizeof(glm::mat4));
	}

	GL::~GL()
	{
		glfwTerminate();
	}

	bool GL::WindowShouldClose()
	{
		return glfwWindowShouldClose(window);
	}

	void GL::BeginFrame()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void GL::EndFrame()
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void GL::SetupCameraProperties(const glm::mat4& viewProjMat)
	{
		uboMatrices.Bind();
		uboMatrices.SetData(0, sizeof(glm::mat4), glm::value_ptr(viewProjMat));
		uboMatrices.Unbind();
		/*glBindBuffer(GL_UNIFORM_BUFFER, UBO);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(viewProjMat));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);*/
	}

	void GL::SetAmbientLight(const glm::vec3& ambientLight)
	{
		uboLights.Bind();
		uboLights.SetData(0, sizeof(glm::vec4), glm::value_ptr(ambientLight));
		uboLights.Unbind();
	}

	void GL::SetAdditionalLightCount(unsigned int lightCount)
	{
		uboLights.Bind();
		uboLights.SetData(sizeof(glm::vec4), sizeof(int), &lightCount);
		uboLights.Unbind();
	}

	void GL::SetAdditionalLight(unsigned int index, const Transform& transform, const Light& light)
	{
		const unsigned long long positionsOffset = sizeof(glm::vec4) + sizeof(int) * 4;
		const unsigned long long propertiesOffset = positionsOffset + sizeof(glm::vec4) * MAX_LIGHT_COUNT;
		uboLights.Bind();

		unsigned long long lightOffset = index * sizeof(glm::vec4);

		glm::vec4 positionRange = glm::vec4(transform.GetDirtyWorldPosition(), 1.0f / (light.range * light.range));
		glm::vec4 properties = glm::vec4(light.color * light.intensity, 0.0f);
		uboLights.SetData(positionsOffset + lightOffset, sizeof(glm::vec4), glm::value_ptr(positionRange));
		uboLights.SetData(propertiesOffset + lightOffset, sizeof(glm::vec4), glm::value_ptr(properties));

		uboLights.Unbind();
	}

	void GL::DrawMeshRenderer(Transform& transform, const MeshRenderer& renderer)
	{
		//TODO: set model matrix
		auto shader = renderer.material->shader.lock();
		if (!shader)
		{
			std::cout << "Null Shader\n";
			return;
		}

		if (!shader->setUBOs)
		{
			shader->setUBOs = true;
			/*unsigned int ubo_matrices = glGetUniformBlockIndex(shader->ID, "Matrices");
			glUniformBlockBinding(shader->ID, ubo_matrices, 0);*/
			uboMatrices.SetShaderUBO(shader->ID);
			uboLights.SetShaderUBO(shader->ID);
		}
		

		shader->Use();
		glm::mat4 modelMat = transform.GetLocalToWorldMatrix();

		renderer.material->SetPassCall();


		//if (auto baseMap = renderer.material->baseMap.lock())
		//{
		//	shader->SetInt("_BaseMap", 0);
		//	baseMap->Use(0);
		//}

		

		//shader->SetMat4("_ViewProj", viewProjMat);
		shader->SetMat4("_Model", modelMat);
		renderer.mesh->Draw();
	}
}

