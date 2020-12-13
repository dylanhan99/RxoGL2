#pragma once
#include <functional>
#include "../Constants.h"

class Scene
{
protected:
	std::vector<std::shared_ptr<Layer>> m_Layers;
public:
	Scene() {}
	virtual ~Scene() {}

	virtual void OnPlay(){}// = 0;
	virtual void OnStop(){}// = 0;
	virtual void OnUpdate(float deltatime);
	virtual void OnRender();
	virtual void OnImguiRender();

	sPtrLayer AddLayer(Layer& newLayer);
};

class SceneMenu : public Scene
{
private:
	std::unordered_map<std::string, sPtrScene> m_Scenes;
	sPtrScene m_CurrentScene;
public:
	SceneMenu();
	SceneMenu(Scene* currentScenePointer);
	~SceneMenu();

	void OnImguiRender() override;

	template<typename T>
	std::shared_ptr<T> RegisterScene(const std::string& sceneName)
	{
		std::cout << "Registering " << sceneName << std::endl;
		std::shared_ptr<T> sPtr{ new T() };
		m_Scenes[sceneName] = sPtr;
		return sPtr;
	}

	// Getters/Setters
	inline const sPtrScene CurrentScene() const { return m_CurrentScene; }
	inline void LoadScene(std::string sceneName)
	{
		try
		{
			if (!m_Scenes.at(sceneName))
				throw sceneName;
			if(m_CurrentScene)
				m_CurrentScene->OnStop();
			std::cout << "Loading '" << sceneName << "'..." << std::endl;
			m_CurrentScene = m_Scenes.at(sceneName);
			m_CurrentScene->OnPlay();
		}
		catch (std::string ex)
		{
			std::cout << "Exception: Scene '" << ex << "' does not exist" << std::endl;
		}
	}
};