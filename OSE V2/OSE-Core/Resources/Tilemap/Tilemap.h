#pragma once
#include "OSE-Core/Types.h"

namespace ose
{
	class Tilemap
	{
	public:
		Tilemap(std::string const & name, std::string const & path);
		~Tilemap();
		// Copying is not allowed (same as ResourceManager)
		Tilemap(Tilemap &) = delete;
		Tilemap & operator=(Tilemap &) = delete;
		// Moving is allowed (same as ResourceManager)
		Tilemap(Tilemap &&) noexcept;
		Tilemap & operator=(Tilemap &&) noexcept;

		int32_t GetWidth() const { return width_; }
		int32_t GetHeight() const { return height_; }

		void CreateTileGrid(int32_t width, int32_t height) noexcept;
		void DeleteTileGrid() noexcept;

		int32_t & operator[](size_t index) { return tile_grid_[index]; }
		int32_t & operator()(size_t col, size_t row) { return tile_grid_[col + row*width_]; }

		int32_t operator[](size_t index) const { return tile_grid_[index]; }
		int32_t operator()(size_t col, size_t row) const { return tile_grid_[col + row*width_]; }

	protected:
		std::string name_;
		std::string path_;

		int32_t * tile_grid_;

		int32_t width_;
		int32_t height_;
	};
}
