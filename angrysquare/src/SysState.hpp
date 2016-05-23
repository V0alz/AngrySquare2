#pragma once

struct SysState
{
public:
	enum States
	{
		STATE_STARTUP,
		STATE_LOAD,
		STATE_MENU,
		STATE_PLAYING,
		STATE_CLEANUP
	};
	static inline States Get() { return m_sysState; }
	static inline void Set( States state ) { m_sysState = state; }

private:
	static States m_sysState;
};

SysState::States SysState::m_sysState = SysState::States::STATE_STARTUP;
