#pragma once

#include "Logging/LogMacros.h"

DECLARE_LOG_CATEGORY_EXTERN(LogDreamSMTC, All, All);

#define DSMTC_LOG(V, F, ...) UE_LOG(LogDreamSMTC, V, F, ##__VA_ARGS__)