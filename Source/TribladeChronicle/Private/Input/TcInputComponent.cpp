// Copyright Woogle. All Rights Reserved.


#include "Input/TcInputComponent.h"

void UTcInputComponent::RemoveBinds(TArray<uint32>& BindHandles)
{
for (uint32 Handle : BindHandles)
	{
		RemoveBindingByHandle(Handle);
	}
	BindHandles.Reset();
}
