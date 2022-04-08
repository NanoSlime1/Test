#include "SortTask.h"


SortTask::SortTask(ATestGameMode* GameMode)
{
	TestGameMode = GameMode;
}

SortTask::~SortTask()
{
	
}

void SortTask::DoWork()
{
	TestGameMode->SortAims();
}

void SortTask::DoMainWork()
{
	DoWork();
}
