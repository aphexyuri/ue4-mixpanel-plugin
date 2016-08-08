//
//  Created by Robert Segal on 2016-03-31.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "MixpanelFunctions.generated.h"


UCLASS(NotBlueprintable)
class UMixpanelFunctions : public UObject {
	GENERATED_BODY()
	
public:
    
    UFUNCTION(BlueprintCallable, meta = (Keywords = "Mixpanel analytics"), Category = "Mixpanel")
    static void MixpanelIdentify(FString distinctID);
    
    UFUNCTION(BlueprintCallable, meta = (Keywords = "Mixpanel analytics"), Category = "Mixpanel")
    static void MixpanelTrack(FString eventName, TArray<FString> eventKeys, TArray<FString> eventValues);
    
    UFUNCTION(BlueprintCallable, meta = (Keywords = "Mixpanel analytics"), Category = "Mixpanel")
    static void MixpanelTrackCharge(float charge, TArray<FString> eventKeys, TArray<FString> eventValues);
    
};
