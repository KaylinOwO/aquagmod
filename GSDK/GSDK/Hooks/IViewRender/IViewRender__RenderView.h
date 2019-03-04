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
