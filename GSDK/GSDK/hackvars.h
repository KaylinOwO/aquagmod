QAngle ViewAngle = QAngle(0, 0, 0);
namespace HackVars
{
	CUserCmd* CurCmd = nullptr;

	float FOV = 90.0f;
	namespace Fonts
	{
		int DefaultFont = 0;
	};
	namespace convars
	{
		ConVar* FOV = nullptr;
	}
	namespace LastSentInfo
	{
		QAngle viewangles = QAngle(0, 0, 0);
		Vector Position = Vector(0, 0, 0);
	};
	namespace Aimbot
	{
		BaseEntity* AimbotTarget = nullptr;
		Vector AimbotPos = Vector(0, 0, 0);
		bool Enabled;
		bool Silent;
		bool Autoshoot;
		bool Nospread;
		bool EnemyOnly;

		int Hotkey;
		int FOV = 30;
		int Smooth = 5;
	};
	namespace Visuals
	{
		bool Enabled;
		bool Hitmarker;
		bool Nightmode;
		bool WireframeHands;
		namespace Aimbot
		{
			bool FOVCircle;
			bool DrawTarget;
		};
		namespace RenderView
		{
			int Thirdperson;
			int ThirdPersonDistance = 100;
			bool FOVEnabled;
			int FOV = 0;
			bool ViewModelFOVEnabled;
			int ViewModelFOV = 0;
		};
		namespace ESP
		{
			//player 
			bool PlayerESP;
			bool EnemyOnly;

			bool PlayerBox;
			int PlayerBoxStyle;
			bool PlayerDrawname;
			bool PlayerDrawHealth;
			bool PlayerDrawHealthBar;
			float fPBoxColor[4] = { 1, 1, 1, 1 };
			Color PBoxColor = Color(255, 255, 255, 255);

			bool PlayerChamsEnabled;
			bool PlayerXQZ;
			bool PlayerCFlat;
			int PlayerChamsStyle;
			int WeaponChamsStyle;
			float fVPlayerChamsColor[4] = { 0, 0.82f, 0, 0 };
			float fNVPlayerChamsColor[4] = { 0, 0, 1, 0 };

			float WireframeHandsColor[4] = { 0, 0.82f, 0, 0 };

			// lua esp
			bool LuaESP;

			bool LuaBox = false;
			bool LuaDrawName = false;
			bool LuaDrawHealth = false;

			float fLBoxColor[4] = { 1, 1, 1, 1 };
			Color LBoxColor = Color(255, 255, 255, 255);

			bool LuaChamsEnabled = false;
			bool LuaXQZ;
			bool LuaCFlat = false;
			float fVLuaChamsColor[4] = { 1, 1, 1, 0 };
			float fNVLuaChamsColor[4] = { 1, 1, 1, 0 };

			// weapon esp
			bool WeaponESP;

			bool WeaponChamsEnabled;
			bool WeaponXQZ;
			bool WeaponCFlat;
			float fVWeapChamsColor[4] = { 1, 0, 0, 0 };
			float fNVWeapChamsColor[4] = { 1, 1, 0, 0 };
		};
	};

	namespace Misc
	{
		bool Bunnyhop;
		bool Hitsound;

		namespace FollowBot {
			bool Enabled;
			int Key;
			float MaxDist = 175.f;
			float MinDist = 35.f;
		}
	}
};