namespace H
{
	namespace ESP
	{
		void DrawBoundingBox(BaseEntity* Ent)
		{
			Vector Pos = Ent->GetRenderOrigin();
			auto& frame = *reinterpret_cast<matrix3x4_t*>(reinterpret_cast<uintptr_t>(Ent) + 0x308);

			Vector min = Pos + Ent->CollisionMins();
			Vector max = Pos + Ent->CollisionMaxs();

			Vector points[] = { Vector(min.x, min.y, min.z),
						Vector(min.x, max.y, min.z),
						Vector(max.x, max.y, min.z),
						Vector(max.x, min.y, min.z),
						Vector(max.x, max.y, max.z),
						Vector(min.x, max.y, max.z),
						Vector(min.x, min.y, max.z),
						Vector(max.x, min.y, max.z) };

			Vector vTransformed[8];

			Vector2D blb;
			Vector2D brb;
			Vector2D frb;
			Vector2D flb;

			Vector2D frt;
			Vector2D brt;
			Vector2D blt;
			Vector2D flt;

			int iY = 0;

			//if (!Util::Math::WorldToScreen(points[0], blb) || !Util::Math::WorldToScreen(points[1], brb) || !Util::Math::WorldToScreen(points[2], frb) || !Util::Math::WorldToScreen(points[3], flb) ||
			//	!Util::Math::WorldToScreen(points[4], frt) || !Util::Math::WorldToScreen(points[5], brt) || !Util::Math::WorldToScreen(points[6], blt) || !Util::Math::WorldToScreen(points[7], flt))
				//return;

			if (!Util::Math::WorldToScreen(points[3], flb) || !Util::Math::WorldToScreen(points[5], brt)
				|| !Util::Math::WorldToScreen(points[0], blb) || !Util::Math::WorldToScreen(points[4], frt)
				|| !Util::Math::WorldToScreen(points[2], frb) || !Util::Math::WorldToScreen(points[1], brb)
				|| !Util::Math::WorldToScreen(points[6], blt) || !Util::Math::WorldToScreen(points[7], flt))
				return;

			Vector2D arr[] = { blb,brb,frb,flb,frt,brt,blt,flt };
			float left = flb.x;
			float top = flb.y;
			float right = flb.x;
			float bottom = flb.y;

			for (int i = 1; i < 8; i++)
			{
				if (left > arr[i].x)
					left = arr[i].x;
				if (top < arr[i].y)
					top = arr[i].y;
				if (right < arr[i].x)
					right = arr[i].x;
				if (bottom > arr[i].y)
					bottom = arr[i].y;
			}

			float x = left;
			float y = bottom;
			float w = right - left;
			float h = top - bottom;

			x += ((right - left) / 8); //pseudo fix for those THICC boxes
			w -= ((right - left) / 8) * 2;



			if(Ent->IsPlayer() && Ent->IsAlive())
			{ 
				if (HackVars::Visuals::ESP::PlayerBox)
				{
					if (HackVars::Visuals::ESP::PlayerBoxStyle == 0)
					{
						H::Draw::DrawOutlineRect(x, y, w, h, HackVars::Visuals::ESP::fPBoxColor);
						H::Draw::DrawOutlineRect(x + 1, y + 1, w - 2, h - 2, HackVars::Visuals::ESP::fPBoxColor);
					}
					else if (HackVars::Visuals::ESP::PlayerBoxStyle == 1)
					{
						int VertLine;
						int HorzLine;
						VertLine = (((float)w) * (0.2f));
						HorzLine = (((float)h) * (0.2f));

						H::Draw::DrawOutlineRect(x, y - 1, VertLine, 1, Color(10, 10, 10, 150));
						H::Draw::DrawOutlineRect(x + w - VertLine, y - 1, VertLine, 1, Color(10, 10, 10, 150));
						H::Draw::DrawOutlineRect(x, y + h - 1, VertLine, 1, Color(10, 10, 10, 150));
						H::Draw::DrawOutlineRect(x + w - VertLine, y + h - 1, VertLine, 1, Color(10, 10, 10, 150));

						H::Draw::DrawOutlineRect(x - 1, y, 1, HorzLine, Color(10, 10, 10, 150));
						H::Draw::DrawOutlineRect(x - 1, y + h - HorzLine, 1, HorzLine, Color(10, 10, 10, 150));
						H::Draw::DrawOutlineRect(x + w - 1, y, 1, HorzLine, Color(10, 10, 10, 150));
						H::Draw::DrawOutlineRect(x + w - 1, y + h - HorzLine, 1, HorzLine, Color(10, 10, 10, 150));

						H::Draw::DrawOutlineRect(x, y, VertLine, 1, HackVars::Visuals::ESP::fPBoxColor);
						H::Draw::DrawOutlineRect(x + w - VertLine, y, VertLine, 1, HackVars::Visuals::ESP::fPBoxColor);
						H::Draw::DrawOutlineRect(x, y + h, VertLine, 1, HackVars::Visuals::ESP::fPBoxColor);
						H::Draw::DrawOutlineRect(x + w - VertLine, y + h, VertLine, 1, HackVars::Visuals::ESP::fPBoxColor);

						H::Draw::DrawOutlineRect(x, y, 1, HorzLine, HackVars::Visuals::ESP::fPBoxColor);
						H::Draw::DrawOutlineRect(x, y + h - HorzLine, 1, HorzLine, HackVars::Visuals::ESP::fPBoxColor);
						H::Draw::DrawOutlineRect(x + w, y, 1, HorzLine, HackVars::Visuals::ESP::fPBoxColor);
						H::Draw::DrawOutlineRect(x + w, y + h - HorzLine, 1, HorzLine, HackVars::Visuals::ESP::fPBoxColor);
					}
				}

				if (HackVars::Visuals::ESP::PlayerDrawname)
				{
					player_info_t player_info;
					if (engine()->GetPlayerInfo(Ent->entIndex(), &player_info))
					{
						H::Draw::Drawtext(player_info.name, HackVars::Fonts::DefaultFont, x + w + 2, y + iY);
						iY += 15;
					}
				}

				float health = Ent->GetHealth();

				int Red = 255 - (health*2.55);
				int Green = health*2.55;

				if (Ent->GetHealth() > 0 && HackVars::Visuals::ESP::PlayerDrawHealth)
				{
					H::Draw::Drawtext(std::to_string(Ent->GetHealth()).c_str(), HackVars::Fonts::DefaultFont, x + w + 2, y + iY, Color(Red, Green, 0, 255));
					iY += 15;
				}

				if (Ent->GetHealth() > 0 && HackVars::Visuals::ESP::PlayerDrawHealthBar)
				{
					float hh = (h);
					float offset = (hh / 4.f) + 5;
					float w = hh / 64.f;
					UINT hp = hh - (UINT)((hh * health) / 100); // Percentage

					H::Draw::DrawOutlineRect(x, y, w, h, Color(0, 0, 0, 0));
					H::Draw::DrawOutlineRect(x + 1, y + 1, w - 2, h - 2, Color(0, 0, 0, 0));
					H::Draw::Drawtext("", HackVars::Fonts::DefaultFont, x + w + 2, y + iY, Color(Red, Green, 0, 255));
					iY += 15;

					H::Draw::DrawOutlineRect((x - 6) - 1, y - 1, 3, hh + 2, Color(0, 0, 0, 255));
					H::Draw::DrawLine((x - 6), y + hp, (x - 6), y + hh, Color(Red, Green, 0, 255));
				}
			}
			else if(Ent->UsesLua())
			{
				if (HackVars::Visuals::ESP::LuaBox)
				{
					H::Draw::DrawLine(left, bottom, left, top, HackVars::Visuals::ESP::LBoxColor);
					H::Draw::DrawLine(left, top, right, top, HackVars::Visuals::ESP::LBoxColor);
					H::Draw::DrawLine(right, top, right, bottom, HackVars::Visuals::ESP::LBoxColor);
					H::Draw::DrawLine(right, bottom, left, bottom, HackVars::Visuals::ESP::LBoxColor);
				}
				if(HackVars::Visuals::ESP::LuaDrawName)
					H::Draw::Drawtext(Ent->GetLuaName(), HackVars::Fonts::DefaultFont, left, top + 2);
				
				if (Ent->GetHealth() > 0 && HackVars::Visuals::ESP::LuaDrawHealth)
					H::Draw::Drawtext(std::to_string(Ent->GetHealth()).c_str(), HackVars::Fonts::DefaultFont, left, top + 17, Color(255, 0, 0, 255));
				
			}

		}
		void FovCircle(float fov)
		{
			// wont be accurate around the edges when the aimbot fov is high, not like that matters.
			int scrw, scrh; engine()->GetScreenSize(scrw, scrh);
			if (fov > 180)
				fov = 180;
			H::Draw::DrawCircle(scrw / 2, scrh / 2, tan(DEG2RAD(fov) / 2) / tan(DEG2RAD(HackVars::FOV) / 2) * scrw, 100, Color(255, 255, 255, 255));
		}
		void DrawAimbotTargetLine()
		{
			if (HackVars::Aimbot::AimbotTarget == nullptr)
				return;

			int scrw, scrh; engine()->GetScreenSize(scrw, scrh);

			Vector2D Screen;

			if (!Util::Math::WorldToScreen(HackVars::Aimbot::AimbotPos, Screen))
				return;

			H::Draw::DrawLine(scrw / 2, scrh, Screen.x, Screen.y, Color(0, 255, 0, 255));
		}
		void DrawAimbotTarget()
		{
			if (HackVars::Aimbot::AimbotTarget == nullptr)
				return;

			player_info_t player_info;
			if (engine()->GetPlayerInfo(HackVars::Aimbot::AimbotTarget->entIndex(), &player_info))
			{
				H::Draw::Drawtext("Target: ", HackVars::Fonts::DefaultFont, 0, 0);
				H::Draw::Drawtext(player_info.name, HackVars::Fonts::DefaultFont, 45, 0);
			}
			DrawAimbotTargetLine();
		}
	};

};