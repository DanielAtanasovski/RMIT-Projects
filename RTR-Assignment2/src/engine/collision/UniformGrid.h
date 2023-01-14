#pragma once
#include <glm/ext/vector_float2.hpp>
#include <vector>

class UniformGrid {
public:
	UniformGrid(glm::vec2 gridSize, glm::vec2 cellSize);

	int getGridCell(glm::vec2 position);
private:
	void createGrid();

	std::vector<std::vector<int>> _grid;
	glm::vec2 _cellSize;
	glm::vec2 _gridSize;
};