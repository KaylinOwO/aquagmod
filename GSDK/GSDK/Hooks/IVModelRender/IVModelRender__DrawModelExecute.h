typedef void(__thiscall* DrawModelExecuteFn)(IVModelRender*, DrawModelState_t &state, ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld);
DrawModelExecuteFn orgDrawModelExecute = nullptr;

void __fastcall hookDrawModelExecute(IVModelRender* modelrender, void* edx, DrawModelState_t &state, ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
{
	if (pInfo.entity_index)
	{
		C_GMOD_Player* LocalPlayer = (C_GMOD_Player*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());
		BaseEntity* Ent = (BaseEntity*)cliententitylist()->GetClientEntity(pInfo.entity_index);
		const char* ModelName = ModelInfo()->GetModelName((model_t*)pInfo.pModel);

		if(!Ent || Ent->IsWorld())
			return orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);

		float colormod[3];
		colormod[0] = 1.f; colormod[1] = 1.f; colormod[2] = 1.f;

		IMaterial* DebugWhite = MaterialSystem()->FindMaterial("models/debug/debugwhite", TEXTURE_GROUP_MODEL);
		DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
		DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
		DebugWhite->AddRef();

		IMaterial* WireFrame = MaterialSystem()->FindMaterial("models/wireframe", TEXTURE_GROUP_MODEL);
		WireFrame->AddRef();

		if (HackVars::Visuals::Enabled && Ent != LocalPlayer && Ent->IsPlayer() && Ent->IsAlive())
		{
			if (HackVars::Visuals::ESP::PlayerXQZ)
			{
				if (HackVars::Visuals::ESP::PlayerChamsStyle == 0)
					DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
				else if (HackVars::Visuals::ESP::PlayerChamsStyle == 1)
					DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, true);
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
				WireFrame->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
				colormod[0] = HackVars::Visuals::ESP::fNVPlayerChamsColor[0]; colormod[1] = HackVars::Visuals::ESP::fNVPlayerChamsColor[1]; colormod[2] = HackVars::Visuals::ESP::fNVPlayerChamsColor[2];
				renderview()->SetColorModulation(colormod);
				if (HackVars::Visuals::ESP::PlayerChamsStyle == 0 || HackVars::Visuals::ESP::PlayerChamsStyle == 1)
					ModelRender()->ForcedMaterialOverride(DebugWhite);
				else if (HackVars::Visuals::ESP::PlayerChamsStyle == 2)
					ModelRender()->ForcedMaterialOverride(WireFrame);
				orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
			}
			if (HackVars::Visuals::ESP::PlayerChamsEnabled)
			{
				if (HackVars::Visuals::ESP::PlayerChamsStyle == 0)
					DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
				else if (HackVars::Visuals::ESP::PlayerChamsStyle == 1)
					DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, true);
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
				colormod[0] = HackVars::Visuals::ESP::fVPlayerChamsColor[0]; colormod[1] = HackVars::Visuals::ESP::fVPlayerChamsColor[1]; colormod[2] = HackVars::Visuals::ESP::fVPlayerChamsColor[2];
				renderview()->SetColorModulation(colormod);
				if (HackVars::Visuals::ESP::PlayerChamsStyle == 0 || HackVars::Visuals::ESP::PlayerChamsStyle == 1)
					ModelRender()->ForcedMaterialOverride(DebugWhite);
				else if (HackVars::Visuals::ESP::PlayerChamsStyle == 2)
					ModelRender()->ForcedMaterialOverride(WireFrame);
				orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
				colormod[0] = 1.f; colormod[1] = 1.f; colormod[2] = 1.f;
				renderview()->SetColorModulation(colormod);
				ModelRender()->ForcedMaterialOverride(nullptr);
				return;
			}
			DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
			DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
			colormod[0] = 1.f; colormod[1] = 1.f; colormod[2] = 1.f;
			renderview()->SetColorModulation(colormod);
			ModelRender()->ForcedMaterialOverride(nullptr);
			return orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
		}
		else if (HackVars::Visuals::Enabled && HackVars::Visuals::ESP::WeaponESP && Ent->IsWeapon() && !Ent->IsHands())
		{
			if (HackVars::Visuals::ESP::WeaponXQZ)
			{
				if (HackVars::Visuals::ESP::WeaponChamsStyle == 0)
					DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
				else if (HackVars::Visuals::ESP::WeaponChamsStyle == 1)
					DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, true);
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
				WireFrame->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
				colormod[0] = HackVars::Visuals::ESP::fNVWeapChamsColor[0]; colormod[1] = HackVars::Visuals::ESP::fNVWeapChamsColor[1]; colormod[2] = HackVars::Visuals::ESP::fNVWeapChamsColor[2];
				renderview()->SetColorModulation(colormod);
				if (HackVars::Visuals::ESP::WeaponChamsStyle == 0 || HackVars::Visuals::ESP::WeaponChamsStyle == 1)
					ModelRender()->ForcedMaterialOverride(DebugWhite);
				else if (HackVars::Visuals::ESP::WeaponChamsStyle == 2)
					ModelRender()->ForcedMaterialOverride(WireFrame);
				orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
			}
			if (HackVars::Visuals::ESP::WeaponChamsEnabled)
			{
				if (HackVars::Visuals::ESP::WeaponChamsStyle == 0)
					DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
				else if (HackVars::Visuals::ESP::WeaponChamsStyle == 1)
					DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, true);
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
				colormod[0] = HackVars::Visuals::ESP::fVWeapChamsColor[0]; colormod[1] = HackVars::Visuals::ESP::fVWeapChamsColor[1]; colormod[2] = HackVars::Visuals::ESP::fVWeapChamsColor[2];
				renderview()->SetColorModulation(colormod);
				if (HackVars::Visuals::ESP::WeaponChamsStyle == 0 || HackVars::Visuals::ESP::WeaponChamsStyle == 1)
					ModelRender()->ForcedMaterialOverride(DebugWhite);
				else if (HackVars::Visuals::ESP::WeaponChamsStyle == 2)
					ModelRender()->ForcedMaterialOverride(WireFrame);
				orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
				colormod[0] = 1.f; colormod[1] = 1.f; colormod[2] = 1.f;
				renderview()->SetColorModulation(colormod);
				ModelRender()->ForcedMaterialOverride(nullptr);
				return;
			}
			DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
			DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
			colormod[0] = 1.f; colormod[1] = 1.f; colormod[2] = 1.f;
			renderview()->SetColorModulation(colormod);
			ModelRender()->ForcedMaterialOverride(nullptr);
			return orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
		}
		else if (HackVars::Visuals::WireframeHands && Ent->IsHands()) {
			float colormod[3];
			colormod[0] = HackVars::Visuals::ESP::WireframeHandsColor[0]; colormod[1] = HackVars::Visuals::ESP::WireframeHandsColor[1]; colormod[2] = HackVars::Visuals::ESP::WireframeHandsColor[2];
			ModelRender()->ForcedMaterialOverride(WireFrame);
			renderview()->SetColorModulation(colormod);
			orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
			ModelRender()->ForcedMaterialOverride(nullptr);
			colormod[0] = 1; colormod[1] = 1; colormod[2] = 1;
			renderview()->SetColorModulation(colormod);
			return;
		}
		else if (HackVars::Visuals::Nightmode)
		{
			if (strstr(ModelName, "models/props"))
			{
				renderview()->SetBlend(0.5f);
			}
		}


	}
	return orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
}
