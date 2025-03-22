#include "BarebonesEngine.h"

namespace Barebones
{
	void StartEngine()
	{
		GL::Init();
	}

	void StopEngine()
	{
		GL::End();
	}
}

