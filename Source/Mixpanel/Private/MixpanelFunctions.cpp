//
//  Created by Robert Segal on 2016-03-31.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

#include "MixpanelPrivatePCH.h"

#if PLATFORM_IOS
#import "Mixpanel/Mixpanel.h"
#elif PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "AndroidApplication.h"
#endif

bool ValidateValues(TArray<FString> &Keys, TArray<FString> &Values)
{
    const int32 kNumKeys   = Keys.Num();
    const int32 kNumValues = Values.Num();
    
    if (kNumKeys == 0 || kNumValues == 0)
    {
        return false;
    }
    
    if (kNumKeys != kNumValues)
    {
        return false;
    }
    
    return true;
}

void UMixpanelFunctions::MixpanelIdentify(FString distinctID)
{
#if PLATFORM_IOS
    Mixpanel *mixpanel = [Mixpanel sharedInstance];
    
    [mixpanel identify:distinctID->GetNSString()];
    
#elif PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        static jmethodID Method = FJavaWrapper::FindMethod(Env,
                                                           FJavaWrapper::GameActivityClassID,
                                                           "AndroidThunkJava_MixpanelIdentify",
                                                           "(Ljava/lang/String;)V",
                                                           false);
        
        jstring MixPanelDistinctID = Env->NewStringUTF(TCHAR_TO_UTF8(*distinctID));
        
        FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, Method, MixPanelDistinctID);
        
        Env->DeleteLocalRef(MixPanelDistinctID);
    }
#endif
    
}

void UMixpanelFunctions::MixpanelTrack(FString eventName, TArray<FString> eventKeys, TArray<FString> eventValues)
{
    if ( ValidateValues(eventKeys, eventValues) )
    {
#if PLATFORM_IOS
        NSDictionary *p = CreateNSDictionary(eventKeys, eventValues);
        
        Mixpanel *mixpanel = [Mixpanel sharedInstance];
        [mixpanel track:eventName->GetNSString() properties:p];
        
#elif PLATFORM_ANDROID
        if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
        {
            static jmethodID Method = FJavaWrapper::FindMethod(Env,
                                                               FJavaWrapper::GameActivityClassID,
                                                               "AndroidThunkJava_MixpanelTrack",
                                                               "(Ljava/lang/String;[java/lang/String;[java/lang/String;)V",
                                                               false);
            
            jobjectArray EventKeysArray   = (jobjectArray)Env->NewObjectArray(eventKeys.Num(),   FJavaWrapper::JavaStringClass, NULL);
            jobjectArray EventValuesArray = (jobjectArray)Env->NewObjectArray(eventValues.Num(), FJavaWrapper::JavaStringClass, NULL);
            
            for (uint32 Param = 0; Param < EventKeysArray.Num(); Param++)
            {
                jstring StringValue = Env->NewStringUTF(TCHAR_TO_UTF8(*eventKeys[Param]));
                
                Env->SetObjectArrayElement(EventKeysArray, Param, StringValue);
                Env->DeleteLocalRef(StringValue);
                
                StringValue = Env->NewStringUTF(TCHAR_TO_UTF8(*eventValues[Param]));
                
                Env->SetObjectArrayElement(EventValuesArray, Param, StringValue);
                Env->DeleteLocalRef(StringValue);
            }
            
            FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, Method, EventKeysArray, EventValuesArray);
            
            Env->DeleteLocalRef(EventKeysArray);
            Env->DeleteLocalRef(EventValuesArray);
        }
#endif
    }
    else
    {
        UE_LOG(LogMixpanel, Log, TEXT("keys and/or value arguments are empty or nil"));
    }
}
