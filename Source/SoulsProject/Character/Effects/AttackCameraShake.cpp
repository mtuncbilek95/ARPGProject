// 2022 Metehan Tuncbilek TR, All rights reserved.


#include "AttackCameraShake.h"

UAttackCameraShake::UAttackCameraShake()
{
	OscillationDuration = 0.2f;
	OscillationBlendInTime = 0.f;
	OscillationBlendOutTime = 0.15f;

	RotOscillation.Pitch.Amplitude = 0.3f;
	RotOscillation.Pitch.Frequency = 30.f;
	RotOscillation.Roll.Amplitude = 0.5f;
	RotOscillation.Roll.Frequency = 30.f;
	RotOscillation.Yaw.Amplitude = 0.5f;
	RotOscillation.Yaw.Frequency = 30.f;

	FOVOscillation.Amplitude = 0.5f;
	FOVOscillation.Frequency = 25.f;
}
