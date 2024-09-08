#include "Utils.h"

int Debug::nDebugLine;
char Debug::whiteSpaces[120] = { '\0' };

void Debug::Log(const char* fmt, ...)
{
	char dest[1024];
	static clock_t startTime = clock();

	if (whiteSpaces[0] == '\0') { // if not initialized yet.
		memset(whiteSpaces, ' ', 120);
		whiteSpaces[119] = '\0';
	}

	va_list argPtr;

	va_start(argPtr, fmt);

	Borland::GotoXY(47, nDebugLine++ % 50);
	vsprintf(dest, fmt, argPtr);
	va_end(argPtr);
	printf("[%5d: %.3f] %s", nDebugLine, (clock() - startTime) / 1000.0f, dest);
	printf("\n%s", whiteSpaces);
}