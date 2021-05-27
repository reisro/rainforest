#include "Renderer/rfRenderCommand.h"

rfRenderCommand::rfRenderCommand()
{
}

rfRenderCommand::rfRenderCommand(CommandType type)
{
}

void rfRenderCommand::SetRenderState(rfgeDX9RenderState state)
{
	rfRenderer::GetInstance()->SetRenderState();
}

void rfRenderCommand::Execute()
{
	RFGE_LOG("\n Executing Render Command...");


}