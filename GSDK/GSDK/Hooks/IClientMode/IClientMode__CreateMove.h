typedef bool(__thiscall* CreateMoveFn)(void*, float, CUserCmd*);
CreateMoveFn orgCreateMove = nullptr;

bool __fastcall hookCreateMove(ClientMode* ClientMode, void* edx, float flInputSampleTime, CUserCmd* cmd)
{
	if (!cmd)
		return false;
	C_GMOD_Player* LocalPlayer = (C_GMOD_Player*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());


	ViewAngle = cmd->viewangles;
	if (cmd->command_number == 0 || !engine()->IsInGame() || !LocalPlayer || !LocalPlayer->IsAlive()) {
		orgCreateMove(ClientMode, flInputSampleTime, cmd);
		return false;
	}
	bool ForcedPacket = false;

	if (engine()->GetNetChannel()->m_nChokedPackets >= 14)
		ForcedPacket = true;


	HackVars::CurCmd = cmd;

	DWORD move;
	_asm mov move, ebp;
	bool& sendpacket = *(***(bool****)(move)-1);


	CBaseCombatWeapon* weapon = LocalPlayer->GetActiveWeapon();
	QAngle viewpunchangle = LocalPlayer->m_vecViewPunch();
	bool HoldingTool = H::Util::IsHoldingTool();
	bool HoldingExplosiveWeapon = H::Util::IsExplosive();
	bool HoldingWeaponWithNospread = H::Util::IsNospreadWeapon();

	if (HackVars::Misc::Bunnyhop)
		H::Bhop(cmd);

	H::RunFollowbot(cmd);

	PredictionSystem.StartPrediction(cmd);
	
	QAngle SpreadAngle = H::SpreadAngle(cmd);
	if (!HoldingWeaponWithNospread && HackVars::Aimbot::Nospread && LocalPlayer->GetActiveWeapon()->CanShoot() && cmd->buttons.IsFlagSet(IN_ATTACK) && !HoldingTool && !HoldingExplosiveWeapon)
		cmd->viewangles += SpreadAngle;


	C_GMOD_Player* Target = nullptr;
	QAngle TargetAngle = QAngle(0, 0, 0);
	bool Aim = false;
	if (HackVars::Aimbot::Hotkey > 0)
	{
		if (GetAsyncKeyState(HackVars::Aimbot::Hotkey) && HackVars::Aimbot::Enabled && !HoldingTool && !HoldingExplosiveWeapon && !ForcedPacket) {
			if (H::ClosestTargetToCrosshair(cmd, Target, TargetAngle) && LocalPlayer->GetActiveWeapon()->CanShoot()) {
				if (!HoldingWeaponWithNospread && HackVars::Aimbot::Nospread)
					cmd->viewangles = TargetAngle + SpreadAngle;
				else
					cmd->viewangles = TargetAngle;
				if (HackVars::Aimbot::Autoshoot)
					cmd->buttons.SetFlag(IN_ATTACK);
				H::Util::CorrectMovement(cmd, ViewAngle);
				Aim = true;
				cmd->tick_count = TIME_TO_TICKS(Target->m_flSimulationTime());
				// ^ that will not hit anyone fake lagging in hvh fyi.
			}
		}
	}
	else
	{
		if (HackVars::Aimbot::Enabled && !HoldingTool && !HoldingExplosiveWeapon && !ForcedPacket) {
			if (H::ClosestTargetToCrosshair(cmd, Target, TargetAngle) && LocalPlayer->GetActiveWeapon()->CanShoot()) {
				if (!HoldingWeaponWithNospread && HackVars::Aimbot::Nospread)
					cmd->viewangles = TargetAngle + SpreadAngle;
				else
					cmd->viewangles = TargetAngle;
				if (HackVars::Aimbot::Autoshoot)
					cmd->buttons.SetFlag(IN_ATTACK);
				H::Util::CorrectMovement(cmd, ViewAngle);
				Aim = true;
				cmd->tick_count = TIME_TO_TICKS(Target->m_flSimulationTime());
				// ^ that will not hit anyone fake lagging in hvh fyi.
			}
		}
	}
	HackVars::Aimbot::AimbotTarget = Target;




	cmd->viewangles = H::Util::Math::FixAngles(cmd->viewangles);
	PredictionSystem.EndPrediction(cmd);
	orgCreateMove(ClientMode, flInputSampleTime,cmd);




	if (ForcedPacket)
		sendpacket = true;

	if (sendpacket) {
		HackVars::LastSentInfo::Position = LocalPlayer->GetRenderOrigin();
		HackVars::LastSentInfo::viewangles = cmd->viewangles;
	}

	if(Aim)
		return !HackVars::Aimbot::Silent;
	return false;
};
