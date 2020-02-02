#pragma once

//#include "OSE-Core/EngineReferences.h"
#include "EProjectionMode.h"
//#include "OSE-Core/Engine/Engine.h"
//#include "OSE-Core/Entity/Entity.h"
//#include "OSE-Core/Entity/SpriteRenderer.h"
#include "RenderPool.h"

namespace ose
{
	struct RenderingSettings;

	/// Templated on the type of pool on which the rendering engine acts
	class RenderingEngine
	{
	public:
		RenderingEngine(int fbwidth, int fbheight);
		virtual ~RenderingEngine();

		/// called every game update for every data object in pool
		/// IMPORTANT - stub method should not be called...
		/// ...used to allow update method with RenderObject sub-class to be called
		virtual void Update() = 0;

		// Apply rendering settings to the rendering engine
		void ApplyRenderingSettings(RenderingSettings const & rendering_settings);

		// saves having to resize framebuffers twice
		void SetProjectionModeAndFbSize(const EProjectionMode & projection_mode, const int width, const int height);

		void SetProjectionMode(const EProjectionMode & projection_mode);

		void SetFramebufferSize(const int width, const int height);

		// Get a reference to the render pool, s.t. new render objects can be added
		// NOTE - No render pool object exists in generic RenderEngine, required pool must be member of sub-class
		virtual RenderPool & GetRenderPool() = 0;

	protected:
		// update the projection matrix based on the projection mode
		void UpdateProjectionMatrix();

	private:
		// how the scene will be projected, e.g. ORTHOGRAPHIC, PERSPECTIVE
		EProjectionMode projection_mode_;

		// width and height of the window framebuffer
		int fbwidth_, fbheight_;

		// znear and zfar of a perspective projection
		float znear_ { 0 }, zfar_ { 0 };

		// child functions to update the projection matrix to either orthographic or perspective
		virtual void UpdateOrthographicProjectionMatrix(const int fbwidth, const int fbheight) = 0;
		virtual void UpdatePerspectiveProjectionMatrix(const float fovyDeg, const int fbwidth, const int fbheight, const float znear, const float zfar) = 0;
	};
}
