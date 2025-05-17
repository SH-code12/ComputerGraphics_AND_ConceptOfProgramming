#include <iostream>
using namespace std;
struct HeroVtable;
struct Hero
{
HeroVtable* vtable;
};
struct HeroVtable
{
// The constructor is not virtual so it does not exist here
void (*Jump)(Hero*);
void (*Fire)(Hero*, int);
void (*Display)(Hero*);
void (*Fly)(Hero*); // The destructor is virtual

void (*Destroy)(Hero*); // The destructor is virtual
};
void HeroJump(Hero* hero)
{
hero->vtable->Jump(hero);
}
void HeroFire(Hero* hero, int armor)
{
hero->vtable->Fire(hero, armor);
}
void HeroDisplay(Hero* hero)
{
hero->vtable->Display(hero);
}
void HeroDestroy(Hero* hero)
{
hero->vtable->Destroy(hero);
}

void HeroFly(Hero* hero)
{
hero->vtable->Fly(hero);
}



struct Superman
{
Hero parent;
int num_jumps;
int fired_armor;
};
void SupermanJump(Superman* superman)
{
superman->num_jumps++;
}
void SupermanFire(Superman* superman, int armor)
{
superman->fired_armor+=armor;
}
void SupermanDisplay(Superman* superman)
{
cout<<"Superman jumped "<<superman->num_jumps
<<" times and fired "<<superman->fired_armor
<<" shots!"<<endl;
}
void SupermanFly(Superman* superman)
{
cout<<"Superman flyed "<<endl;
}
void SupermanDestroy(Superman* superman)
{
// Free resources here
}
HeroVtable superman_vtable=
{
(void(*)(Hero*)) SupermanJump,
(void(*)(Hero*,int)) SupermanFire,
(void(*)(Hero*)) SupermanDisplay,
(void(*)(Hero*)) SupermanFly ,
(void(*)(Hero*)) SupermanDestroy
};
void SupermanInitialize(Superman* superman)
{
superman->parent.vtable=&superman_vtable;
superman->num_jumps=0;
superman->fired_armor=0;
}
struct Batman
{
Hero parent;
int num_actions;
};
void BatmanJump(Batman* batman)
{
batman->num_actions++;
}
void BatmanFire(Batman* batman, int armor)
{
batman->num_actions++;
}
void BatmanDisplay(Batman* batman)
{
cout<<"Batman performed "<<batman->num_actions
<<" actions!"<<endl;
}

void BatmanFly(Batman* batman)
{
cout<<"Batman is flying  "<<batman->num_actions
<<" actions!"<<endl;
}
void BatmanDestroy(Batman* batman)
{
// Free resources here
}
HeroVtable batman_vtable=
{
(void(*)(Hero*)) BatmanJump,
(void(*)(Hero*,int)) BatmanFire,
(void(*)(Hero*)) BatmanDisplay,
(void(*)(Hero*)) BatmanFly,
(void(*)(Hero*)) BatmanDestroy
};
void BatmanInitialize(Batman* batman)
{
batman->parent.vtable=&batman_vtable;
batman->num_actions=0;
}

int main()
{
Superman superman;
SupermanInitialize(&superman);
Batman batman;
BatmanInitialize(&batman);
Hero* heroes[2];
heroes[0]=(Hero*)&superman; // heroes[0]=&superman.parent;
heroes[1]=(Hero*)&batman; // heroes[1]=&batman.parent;
int i;
for(i=0;i<2;i++)
{
HeroFire(heroes[i], 3);
HeroJump(heroes[i]);
HeroJump(heroes[i]);
HeroFly(heroes[i]);
HeroFire(heroes[i], 4);
}
for(i=0;i<2;i++)
{
HeroDisplay(heroes[i]);
HeroDestroy(heroes[i]);
}
return 0;
}