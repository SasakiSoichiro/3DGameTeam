#include "slow.h"

//ÉOÉçÅ[ÉoÉãïœêîêÈåæ
Slow g_Slow;

void InitSlow(void)
{
	g_Slow.fMulti = 1.0f;
	g_Slow.fDivi = 1.0f;
	g_Slow.nMulti = 1;
	g_Slow.nDivi = 1;
	g_Slow.bUse = false;
}

void SetSlow()
{

	if (g_Slow.bUse == true)
	{
		g_Slow.fMulti = (int)SLOW;
		g_Slow.fDivi = 1.0 / SLOW;
		g_Slow.nMulti = SLOW;
	}
	else if (g_Slow.bUse == false)
	{
		g_Slow.fMulti = 1.0f;
		g_Slow.fDivi = 1.0f;
		g_Slow.nMulti = 1;
	}
}

Slow*GetSlow(void)
{
	return &g_Slow;
}