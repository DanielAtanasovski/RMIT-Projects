#include "UniformGrid.h"

UniformGrid::UniformGrid(glm::vec2 gridSize, glm::vec2 cellSize)
{
	_gridSize = gridSize;
	_cellSize = cellSize;
	createGrid();
}

int UniformGrid::getGridCell(glm::vec2 position)
{
	return 0;
}

void UniformGrid::createGrid()
{

}
