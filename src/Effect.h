#ifndef __EFFECTS__
#define __EFFECTS__
#include <string>

enum class Type
{
	Multiplier = 1,
	BonusPenalty = 2
};

class Effect
{
protected:
	int duration_;
	float timeleft_;
	Type type_;
	std::string name_;
	std::string description_;


public:
	Effect(int duration, float timeleft, std::string name): duration_(duration), timeleft_(timeleft), type_(Type::Multiplier), name_(name) {}
	virtual ~Effect();
	virtual void UpdateAndApply(float dt, float* stat) = 0;
	virtual bool HasTimedOut() { return timeleft_ <= 0.0f; }
};




class Buff : public Effect
{
private:
	float modifier_;

public:
	Buff(int duration, float modifier, std::string name): Effect(duration, (float)duration, name), modifier_(modifier) {
		type_ = Type::BonusPenalty;
	}
	virtual ~Buff() {}
	virtual void UpdateAndApply(float dt, float* stat);

};




class Debuff : public Effect
{
private:
	float modifier_;

public:
	Debuff(int duration, float modifier, std::string name): Effect(duration, (float)duration, name), modifier_(modifier) {
		type_ = Type::BonusPenalty;
	}
	virtual ~Debuff() {}
	virtual void UpdateAndApply(float dt, float* stats);

};

#endif
