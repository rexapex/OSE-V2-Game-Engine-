#pragma once

#include "OSE-Core/Types.h"
#include "Scene/SceneManager.h"
#include "OSE-Core/Entity/EntityList.h"
#include "OSE-Core/Input/InputManager.h"
#include "ThreadManager.h"
#include "Time.h"
#include "Camera/Camera.h"
#include <ctime>

namespace ose
{
	class Scene;
	class Project;
	class ProjectLoader;
	class WindowManager;
	class RenderingEngine;
	class Chunk;
	class Entity;
	class Component;
	class SpriteRenderer;
	class MeshRenderer;
	class ScriptingEngine;
	struct CustomObject;

	// Represents a runtime object of a game
	// Provides a simple way of interacting with the game
	// TODO - Use template inheritance to allow game type with different scene switch type
	class Game : public SceneManager, public EntityList, public InputManager
	{
	public:
		Game();
		virtual ~Game() noexcept;
		Game(Game &) = delete;
		Game(Game && other) noexcept = default;
		Game & operator=(Game &) = delete;
		Game & operator=(Game &&) noexcept = delete;

		// Start execution of the game
		void StartGame();

		// Activate an entity along with activated sub-entities
		// Should NEVER be called directly by a script, enable entity instead
		void OnEntityActivated(Entity & entity);

		// Deactivate an entity along with all its sub-entities
		// Should NEVER be called directly by a script, disable entity instead
		void OnEntityDeactivated(Entity & entity);

		// Activate a chunk along with activated sub-entities
		// Should NEVER be called directly by a script, enable chunk instead
		virtual void OnChunkActivated(Chunk & chunk) override;

		// Deactivate a chunk along with all its sub-entities
		// Should NEVER be called directly by a script, disable chunk instead
		virtual void OnChunkDeactivated(Chunk & chunk) override;

		// Find all the entities with the given name
		// Includes persistent entities, scene entities, and loaded chunk entities
		std::vector<Entity *> FindAllEntitiesWithName(std::string_view name) const;

		// Set the active camera
		// If c is nullptr, the active camera is set to the default camera
		// If the user destroys the active camera, the active camera must be set to nullptr (or a valid camera) to prevent errors
		void SetActiveCamera(Camera * c) { active_camera_ = c ? c : &default_camera_; active_camera_->SetGameReference(this); }

		// Get the active camera
		Camera * GetActiveCamera() const { return active_camera_; }

		// Get the time object
		Time const & GetTime() { return time_; }

		// Load a custom data file
		uptr<CustomObject> LoadCustomDataFile(std::string const & path);

		// Save a custom data file
		void SaveCustomDataFile(std::string const & path, CustomObject const & object);

	protected:
		// Called upon a project being activated
		// Project is activated upon successful load
		// Only one project can be active at a time
		virtual void OnProjectActivated(Project & project);

		// Called upon a project being deactivated
		// Project is deactivated when a new project is loaded
		virtual void OnProjectDeactivated(Project & project);

		// Called upon a scene being activated
		// Depending on switch manager, could be multiple active scenes
		virtual void OnSceneActivated(Scene & scene);

		// Called upon a scene being deactivated
		// Depending on switch manager, could be multiple active scenes
		virtual void OnSceneDeactivated(Scene & scene);

	private:
		// Window manager handles window creation, events and input
		uptr<WindowManager> window_manager_;

		// Thread manager handles multithreading and updating of engines
		///uptr<ThreadManager> thread_manager_;

		// Rendering engine handles all rendering of entity render objects
		uptr<RenderingEngine> rendering_engine_;

		// Scripting engine handles execution of game developer created scripts
		uptr<ScriptingEngine> scripting_engine_;

		// TODO - current iteration of render pool
		///uptr<RenderPool> render_pool_;

		// The active camera (rendering is done relative to the active camera transform)
		Camera * active_camera_ { nullptr };

		// The default camera
		Camera default_camera_;

		// Time handles calculation of delta time, fps etc. and provides a way for scripts to get the timing variables
		Time time_;

		// True iff the game is currently running (paused is a subset of running)
		bool running_;

		// Called from startGame, runs a loop while running_ is true
		void RunGame();
	};
}
