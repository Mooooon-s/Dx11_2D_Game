#include "MnPaintShader.h"
#include "MnTexture.h"

namespace Mn::graphics
{
	void PaintShader::Binds()
	{
		_Target->BindUnorderedAccessViews(0);

		_GroupX = _Target->GetWidth() / _ThreadGroupCountX + 1;
		_GroupY = _Target->GetHeight() / _ThreadGroupCountY + 1;
		_GroupZ = 1;
	}
	void PaintShader::Clear()
	{
		_Target->ClearUnorderedAccessViews(0);
	}
}