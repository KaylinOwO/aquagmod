typedef void(__thiscall* RenderViewFn)(void*, CViewSetup&,int,int);
RenderViewFn orgRenderView = nullptr;




void __fastcall hookRenderView(IViewRender* ViewRender, void* edx, CViewSetup& view,int nClearFlags, int whatToDraw)
{
	static bool enabledtp = false, check = false;

	if (GetAsyncKeyState(HackVars::Visuals::RenderView::Thirdperson))
	{
		if (!check)
			enabledtp = !enabledtp;
		check = true;
	}
	else
		check = false;

	C_GMOD_Player* LocalPlayer = (C_GMOD_Player*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());

	view.angles = ViewAngle;
	if (enabledtp && LocalPlayer)
	{
		Input()->m_fCameraInThirdPerson = true;
		float radx = DEG2RAD(view.angles.x); float rady = DEG2RAD(view.angles.y);
		Vector fwdzinvert = Vector(cos(radx) * cos(rady), cos(radx) * sin(rady), sin(radx) * -1);

		trace_t trace;
		Ray_t ray;
		CTraceFilter filter;
		filter.pSkip = LocalPlayer;
		ray.Init(view.origin, view.origin - (fwdzinvert * HackVars::Visuals::RenderView::ThirdPersonDistance), Vector(-7, -7, -7), Vector(7, 7, 7));
		EngineTrace()->TraceRay(ray, MASK_SOLID, &filter, &trace);

		view.origin = trace.endpos;
	}
	else
		Input()->m_fCameraInThirdPerson = false;

	if (HackVars::Visuals::RenderView::FOVEnabled)
		view.fov = HackVars::Visuals::RenderView::FOV;
	if (HackVars::Visuals::RenderView::ViewModelFOVEnabled)
		view.fovViewmodel = HackVars::Visuals::RenderView::ViewModelFOV;
	HackVars::FOV = view.fov;
	
	if(HackVars::CurCmd) {
		QAngle eye = H::Util::Math::FixAngles(HackVars::CurCmd->viewangles);
		LocalPlayer->EyeAngles() = eye; LocalPlayer->LocalEyeAngles() = eye;
		LocalPlayer->GetAnimState()->m_DebugAnimData.m_flAimPitch = eye.x;
		LocalPlayer->GetAnimState()->m_DebugAnimData.m_flAimYaw = eye.y;
		LocalPlayer->GetAnimState()->m_flEyePitch = eye.x;
		LocalPlayer->GetAnimState()->m_flEyeYaw = eye.y;
		LocalPlayer->GetAnimState()->Update(eye.y, eye.x);
		LocalPlayer->GetAnimState()->m_angRender.y = LocalPlayer->GetAnimState()->m_flCurrentFeetYaw;
	}
	return orgRenderView(ViewRender,view,nClearFlags,whatToDraw);
}


typedef void(__thiscall* ViewRenderFn)(void*, vrect_t* rect);
ViewRenderFn orgView_Render = nullptr;

void __fastcall hookView_Render(CHLClient* client, void* edx, vrect_t* rect) // index 26 
{
	orgView_Render(client, rect);

	static BYTE* IsRecordingMovie = *(BYTE**)(Util::Pattern::FindPattern("engine.dll", "55 8B EC A1 ? ? ? ? 81 EC ? ? ? ? D9 45 18"/*CL_StartMovie*/) + 0x3E);
	if (engine()->IsTakingScreenshot() || *IsRecordingMovie) // steam screenshot & startmovie checks
		return;

	float colormod[3] = { 1.f,1.f,1.f };
	IMaterial* DebugWhite = MaterialSystem()->FindMaterial("models/debug/debugwhite", TEXTURE_GROUP_MODEL);
	DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
	DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, true);
	DebugWhite->AddRef();

	Render()->Push3DView(ViewRender()->m_view, 0, nullptr, ViewRender()->GetFrustum());
	for (int i = 1; i <= globals()->maxClients; i++) {
		C_GMOD_Player* player = (C_GMOD_Player*)cliententitylist()->GetClientEntity(i);

		if (!player || !player->IsPlayer() || !player->IsAlive())
			continue;

		ModelRender()->ForcedMaterialOverride(DebugWhite);
		renderview()->SetColorModulation(colormod);
		player->GetClientRenderable()->DrawModel(STUDIO_RENDER);
		ModelRender()->ForcedMaterialOverride(nullptr);
	}
	Render()->PopView(ViewRender()->GetFrustum());

	surface()->StartDrawing();
	surface()->FinishDrawing();
}