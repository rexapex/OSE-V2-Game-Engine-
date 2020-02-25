#pragma once

namespace ose::engine
{
	class EngineTask
	{
		// called every game update for every task in pool
		virtual void Update() = 0;
	};
}