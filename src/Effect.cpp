#include "Effect.h"



Effect::~Effect()
{
}


void Buff::UpdateAndApply(float dt, float* stat)
{

	*stat += modifier_;

	if (timeleft_ >= 0)
		timeleft_ -= dt;
	

}



void Debuff::UpdateAndApply(float dt, float* stat)
{
	static bool firstrun = true;

	if (firstrun) {
		*stat -= modifier_;
		firstrun = false;
	}
	if (timeleft_ >= 0)
		timeleft_ -= dt;


}