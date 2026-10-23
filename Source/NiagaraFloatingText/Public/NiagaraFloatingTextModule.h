// © at0mic Games

#pragma once

#include "Modules/ModuleManager.h"

class FNiagaraFloatingTextModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
