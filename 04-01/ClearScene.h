#pragma once
#include <Novice.h>
#include "IScene.h"

class ClearScene : public IScene
{
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
};

