#ifndef ENGINE_H
#define ENGINE_H

#include "Viewport.h"

struct SEngine {
 
	SEngine() {};

	int Initialize(void);
	int Run(void);
	void Finalize(void);

private:
	SViewport m_Viewport{};

};

#endif
