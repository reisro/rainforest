#include "Resources/rfVertexBuffer.h"

rfVertexBuffer::rfVertexBuffer():
	Length(0)
{
}

rfVertexBuffer::~rfVertexBuffer()
{
}

bool rfVertexBuffer::Create()
{
	RFGE_LOG("Creating Vertex Buffer...");

	return true;
}

void rfVertexBuffer::AccessMemory()
{
}

bool rfVertexBuffer::Release()
{
	return false;
}

void rfVertexBuffer::Lock()
{
}

void rfVertexBuffer::Unlock()
{
}
