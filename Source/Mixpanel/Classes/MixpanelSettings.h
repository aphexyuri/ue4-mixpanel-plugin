//
//  Created by Robert Segal on 2016-03-31.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "MixpanelSettings.generated.h"

UCLASS(config = Engine, defaultconfig)
class UMixpanelSettings : public UObject
{
	GENERATED_BODY()
	
public:
	UMixpanelSettings(const FObjectInitializer& ObjectInitializer);
};
