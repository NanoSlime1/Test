#pragma once

#include "CoreMinimal.h"
#include "Test/TestGameMode.h"

class SortTask : public  FNonAbandonableTask
{
	
public:
	SortTask(ATestGameMode* GameMode);

	~SortTask();

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(SortTask, STATGROUP_ThreadPoolAsyncTasks)
	}

	void DoWork();

	void DoMainWork();

private:
	ATestGameMode* TestGameMode;
};
