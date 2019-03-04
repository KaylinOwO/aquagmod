namespace H
{
	Vector scn;

	inline void VectorAngles(Vector &forward, Vector &angles)
	{
		float tmp, yaw, pitch;

		if (forward.y == 0 && forward.x == 0)
		{
			yaw = 0;

			if (forward.z > 0)
				pitch = 270;
			else
				pitch = 90;
		}
		else
		{
			yaw = RAD2DEG(atan2f(forward.y, forward.x));

			if (yaw < 0)
				yaw += 360;

			tmp = forward.Length2D();
			pitch = RAD2DEG(atan2f(-forward.z, tmp));

			if (pitch < 0)
				pitch += 360;
		}

		angles[0] = pitch;
		angles[1] = yaw;
		angles[2] = 0;
	};

	std::pair<float, float> ComputeMove(const Vector &a, const Vector &b, CUserCmd* cmd)
	{
		Vector diff = (b - a);
		if (diff.Length() == 0)
			return{ 0, 0 };
		const float x = diff.x;
		const float y = diff.y;
		Vector vsilent(x, y, 0);
		float speed = sqrt(vsilent.x * vsilent.x + vsilent.y * vsilent.y);
		Vector ang;
		VectorAngles(vsilent, ang);
		float yaw = DEG2RAD(ang.y - cmd->viewangles.y);
		return{ cos(yaw) * 450, -sin(yaw) * 450 };
	}

	void MoveTo(const Vector &vector, CUserCmd* cmd)
	{
		C_GMOD_Player* pLocal = (C_GMOD_Player*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());
		auto result = ComputeMove(pLocal->Origin(), vector, cmd);
		cmd->forwardmove = result.first;
		cmd->sidemove = result.second;
	}

	inline bool IsKeyDown(DWORD key)
	{
		if (GetAsyncKeyState(key))
			return true;

		return false;
	}

	void RunFollowbot(CUserCmd* cmd)
	{

		for (int i = 1; i <= engine()->GetMaxClients(); i++)
		{
			if (i == engine()->GetLocalPlayer())
				continue;

			C_GMOD_Player* pLocal = (C_GMOD_Player*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());
			C_GMOD_Player* pEntity = (C_GMOD_Player*)cliententitylist()->GetClientEntity(i);

			if (!HackVars::Misc::FollowBot::Enabled)
				return;

			if (HackVars::Misc::FollowBot::Key)
			{
				if (!IsKeyDown(HackVars::Misc::FollowBot::Key))
					return;
			}

			if (!pEntity)
				continue;

			if (pEntity->IsDormant())
				continue;


			if (!pEntity->IsAlive())
				continue;

			if (pLocal->m_vecOrigin().DistTo(pEntity->m_vecOrigin()) > (float)HackVars::Misc::FollowBot::MaxDist)
				continue;

			if (pLocal->m_vecOrigin().DistTo(pEntity->m_vecOrigin()) < (float)HackVars::Misc::FollowBot::MinDist)
				continue;

			//if (pEntity->GetTeam() == pLocal->GetTeam())
			MoveTo(pEntity->Origin(), cmd);
		}
	}
}