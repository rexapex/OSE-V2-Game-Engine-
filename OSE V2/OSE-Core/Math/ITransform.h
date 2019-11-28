#pragma once
#include "OSE-Core/EngineDependencies/glm/glm.hpp"
#include "OSE-Core/EngineDependencies/glm/gtc/quaternion.hpp"

namespace ose::math
{
	class ITransform
	{
	protected:
		ITransform() {}

	public:
		virtual ~ITransform() {}

		// Defaults copy/move constructors
		ITransform(const ITransform & other) noexcept = default;
		ITransform & operator=(const ITransform & other) noexcept = default;
		ITransform(ITransform && other) noexcept = default;
		ITransform & operator=(ITransform && other) noexcept = default;

		virtual const glm::vec3 & GetPosition() const = 0;
		virtual const glm::quat & GetOrientation() const = 0;
		virtual const glm::vec3 & GetScale() const = 0;

		virtual const glm::mat4 GetPositionMatrix() const = 0;
		virtual const glm::mat4 GetOrientationMatrix() const = 0;
		virtual const glm::mat4 GetScaleMatrix() const = 0;

		virtual const glm::mat4 GetTransformMatrix() const = 0;

		virtual const glm::vec3 GetUp() const = 0;
		virtual const glm::vec3 GetForward() const = 0;
		virtual const glm::vec3 GetRight() const = 0;
	};
}