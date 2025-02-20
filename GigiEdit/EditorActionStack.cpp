#include "EditorActionStack.h"

#include "Schemas/Types.h"
#include "Schemas/JSON.h"

void EditorActionStack::Push(const RenderGraph& renderGraph)
{
	// Remove all redo changes after this point
	if (!m_actionStack.empty() && m_currentIndex != m_actionStack.size() - 1)
	{
		m_actionStack.resize(m_currentIndex + 1);
	}

	std::string& bufferString = m_actionStack.emplace_back();
	WriteToJSONBuffer(renderGraph, bufferString, false);

	m_currentIndex = static_cast<int32_t>(m_actionStack.size() - 1);
}

bool EditorActionStack::Undo(RenderGraph& renderGraph)
{
	if (m_currentIndex >= 0)
	{
		ReadFromJSONBuffer(renderGraph, m_actionStack.at(m_currentIndex--));
		return true;
	}

	return false;
}

bool EditorActionStack::Redo(RenderGraph& renderGraph)
{
	if (!m_actionStack.empty() && m_currentIndex < static_cast<int32_t>(m_actionStack.size()) - 1)
	{
		ReadFromJSONBuffer(renderGraph, m_actionStack.at(m_currentIndex++));
		return true;
	}

	return false;
}

void EditorActionStack::Clear()
{
	m_actionStack.clear();
	m_currentIndex = -1;
}
