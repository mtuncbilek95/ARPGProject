// 2022 Metehan Tuncbilek TR, All rights reserved.


#include "AttackCameraShake.h"

UAttackCameraShake::UAttackCameraShake()
{
	OscillationDuration = 0.2f;
	OscillationBlendInTime = 0.0f;
	OscillationBlendOutTime = 0.1f;

	RotOscillation.Pitch.Amplitude = 0.5f;
	RotOscillation.Pitch.Frequency = 60.f;
	RotOscillation.Roll.Amplitude = 0.5f;
	RotOscillation.Roll.Frequency = 50.f;
	RotOscillation.Yaw.Amplitude = 0.5f;
	RotOscillation.Yaw.Frequency = 70.f;

	FOVOscillation.Amplitude = 0.5f;
	FOVOscillation.Frequency = 60.f;
}
