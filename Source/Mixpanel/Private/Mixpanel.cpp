//
//  Created by Robert Segal on 2016-03-31.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

#include "MixpanelPrivatePCH.h"
#include "MixpanelSettings.h"
#include "ISettingsModule.h"

#if PLATFORM_IOS

#elif PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "AndroidApplication.h"
#endif

DEFINE_LOG_CATEGORY(LogMixpanel);

#define LOCTEXT_NAMESPACE "Mixpanel"

class FMixpanel : public IMixpanel
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FMixpanel, Mixpanel )

void FMixpanel::StartupModule()
{
	// register settings
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "Mixpanel",
										 LOCTEXT("RuntimeSettingsName", "Mixpanel"),
										 LOCTEXT("RuntimeSettingsDescription", "Configure the Mixpanel plugin"),
										 GetMutableDefault<UMixpanelSettings>()
										 );
	}
    
    const UMixpanelSettings *settings = GetDefault<UMixpanelSettings>();
    
#if PLATFORM_IOS

#elif PLATFORM_ANDROID
    // Initilization of Android is done through plugin APL file.
    //
#endif
}


void FMixpanel::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
