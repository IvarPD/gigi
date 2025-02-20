#pragma once

#include <vector>
#include <string>


struct RenderGraph;

class EditorActionStack
{
public:
	void Push(const RenderGraph& renderGraph);
	bool Undo(RenderGraph& renderGraph);
	bool Redo(RenderGraph& renderGraph);
	void Clear();

private:
	int32_t m_currentIndex = -1;
	std::vector<std::string> m_actionStack;
};