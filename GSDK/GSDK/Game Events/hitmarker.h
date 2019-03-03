#include <Windows.h>
#pragma comment(lib, "Winmm.lib") 

class hitmarker
{
	class player_hurt_listener
		: public IGameEventListener
	{
	public:
		void start()
		{
			if (!GameEventManager()->AddListener(this, "player_hurt", false)) {
				//ok
			}
		}
		void stop()
		{
			GameEventManager()->RemoveListener(this);
		}
		void FireGameEvent(IGameEvent *event) override
		{
			hitmarker::singleton()->on_fire_event(event);
		}
	};
public:
	static hitmarker* singleton()
	{
		static hitmarker* instance = new hitmarker;
		return instance;
	}

	void initialize()
	{
		_listener.start();
	}

	void on_fire_event(IGameEvent* event)
	{
		if (!strcmp(event->GetName(), "player_hurt")) {
			int attacker = event->GetInt("attacker");
			if (engine()->GetPlayerForUserID(attacker) == engine()->GetLocalPlayer()) {
				//g_pSurface->PlaySound doesnt work for some reason
				//engine()->ClientCmd_Unrestricted("say pew");
				//Beep();
				_flHurtTime = globals()->curtime + 0.25;
			}
		}
	}

	void on_paint()
	{
		auto curtime = globals()->curtime;
		auto lineSize = 8;
		if (_flHurtTime + 0.25f >= curtime) {
			int screenSizeX, screenCenterX;
			int screenSizeY, screenCenterY;
			engine()->GetScreenSize(screenSizeX, screenSizeY);

			screenCenterX = screenSizeX / 2;
			screenCenterY = screenSizeY / 2;

			surface()->DrawSetColor(200, 200, 200, 255);
			surface()->DrawLine(screenCenterX - lineSize, screenCenterY - lineSize, screenCenterX - (lineSize / 4), screenCenterY - (lineSize / 4));
			surface()->DrawLine(screenCenterX - lineSize, screenCenterY + lineSize, screenCenterX - (lineSize / 4), screenCenterY + (lineSize / 4));
			surface()->DrawLine(screenCenterX + lineSize, screenCenterY + lineSize, screenCenterX + (lineSize / 4), screenCenterY + (lineSize / 4));
			surface()->DrawLine(screenCenterX + lineSize, screenCenterY - lineSize, screenCenterX + (lineSize / 4), screenCenterY - (lineSize / 4));
		}
	}

private:
	player_hurt_listener    _listener;
	const char*             _soundFileName = "csgo\\sound\\hitsound.wav";
	float                   _flHurtTime;
};
