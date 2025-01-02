/************************************************************************** */
/*																			*/
/*		   ▄███████▄    ▄████████     ███        ▄████████    ▄████████		*/
/*		  ███    ███   ███    ███ ▀█████████▄   ███    ███   ███    ███		*/
/*		  ███    ███   ███    █▀     ▀███▀▀██   ███    ███   ███    ███		*/
/*		  ███    ███  ▄███▄▄▄         ███   ▀  ▄███▄▄▄▄██▀   ███    ███		*/
/*		▀█████████▀  ▀▀███▀▀▀         ███     ▀▀███▀▀▀▀▀   ▀███████████		*/
/*		  ███          ███    █▄      ███     ▀███████████   ███    ███		*/
/*		  ███          ███    ███     ███       ███    ███   ███    ███		*/
/*		 ▄████▀        ██████████    ▄████▀     ███    ███   ███    █▀ 		*/
/*                                              ███    ███             		*/
/*																			*/
/************************************************************************** */

#ifndef PETRA_GESTALT_HPP
#define PETRA_GESTALT_HPP

# include <vector>
# include <nsl.h>

/*# define GESTALT_ACTIVE(classT)								\
	static const bool	Gestalt##classT##Register = []		\
	{														\
		PV_GestaltUtils::forCreateGameObjects.push_back(	\
			reinterpret_cast<Gestalt* (*)(void)>(			\
			static_cast< classT * (*)(void)>(				\
				[]()										\
				{											\
					return (new classT());					\
				})											\
			));												\
		return (true);										\
	}();*/

# define PV_GESTALT_CREATE_OBJECTS(class)	\
	PVGestaltUtils::CreateObjects<class>("class")

class Gestalt
{
public:
	static void
	InitObjects(void);

protected:
	FORCEINLINE
	Gestalt(void) = default;

	FORCEINLINE
	virtual
	~Gestalt(void) = default;

	virtual void
	BeforePulse(void)
	{
		std::cout << "Before GestaltCore pulse\n";
	};

	virtual void
	Pulse(float dt)
	{
		(void)dt;
		std::cout << "GestaltCore pulse\n";
	};

	virtual void
	AfterPulse(void)
	{
		std::cout << "After GestaltCore pulse\n";
	};

public:
	FORCEINLINE
	static void
	Consciousness(float deltaTime)
	{
		for (Gestalt* i : Gestalt::gameObjects)
			i->Pulse(deltaTime);
	}

	FORCEINLINE
	static void
	Begin(void)
	{
		for (Gestalt* i : Gestalt::gameObjects)
			i->BeforePulse();
	}

	FORCEINLINE
	static void
	End(void)
	{
		for (Gestalt* i : Gestalt::gameObjects)
			i->AfterPulse();
	}

	static void
	DestroyObjects(void)
	{
		for (Gestalt* i : Gestalt::gameObjects)
			delete(i);
	}

public:
	static std::vector<Gestalt*>
	gameObjects;
	static std::vector<void (*)(void)>
	gameSpecialFunctions;
};

namespace PV_GestaltUtils
{
	template <typename T, typename... TArgs>
	FORCEINLINE
	void
	CreateObjects(TArgs&&... constructorArgs)
	{
		Gestalt::gameObjects.push_back(new T(Meta::Move(constructorArgs)...));
	}

	extern std::vector<Gestalt* (*)(void)>
	forCreateGameObjects;
};

#endif
