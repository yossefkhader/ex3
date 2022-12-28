#include "HealthPoints.h"

HealthPoints::HealthPoints(int healthPoints) : 
   m_MAXHP(healthPoints)
{
   if (healthPoints <= 0)
   {
      throw InvalidArgument();
   }

   this->m_healthPoints = healthPoints;
}

HealthPoints& HealthPoints::operator=(const HealthPoints& hp)
{
   this->m_healthPoints = hp.m_healthPoints;
   this->m_MAXHP = hp.m_MAXHP;

   return *this;
}

HealthPoints& HealthPoints::operator+(const int num)
{
   
   HealthPoints *tmp = nullptr;

   try
   {
      tmp = new HealthPoints(*this);
   }
   catch (std::bad_alloc &e) 
   {
      std::cerr << e.what() << std::endl;
      throw;
   }
   
   tmp->m_healthPoints += num;

   if(tmp->m_healthPoints > tmp->m_MAXHP)
   {
      tmp->m_healthPoints = tmp->m_MAXHP;
   }
   
   if(tmp->m_healthPoints < 0)
   {
      tmp->m_healthPoints = 0;
   }

   return *tmp;
}

HealthPoints& HealthPoints::operator-(const int num)
{
   return *this + (-1*num);
}

HealthPoints& HealthPoints::operator+=(const HealthPoints& hp)
{
   return *this += hp.m_healthPoints;
}

HealthPoints& HealthPoints::operator+=(const int num)
{
   this->m_healthPoints += num;
   
   if(this->m_healthPoints < 0)
   {
      this->m_healthPoints = 0;
   }
   else if(this->m_healthPoints > this->m_MAXHP)
   {
      this->m_healthPoints = this->m_MAXHP;
   }
   
   return *this;
}

HealthPoints& HealthPoints::operator-=(const HealthPoints& hp)
{
   return *this -= hp.m_healthPoints;
}

HealthPoints& HealthPoints::operator-=(const int num)
{
   this->m_healthPoints -= num;
   
   if(this->m_healthPoints < 0)
   {
      this->m_healthPoints = 0;
   }
   if(this->m_healthPoints > this->m_MAXHP)
   {
      this->m_healthPoints = this->m_MAXHP;
   }
   
   return *this;
}

HealthPoints& operator+(const int num, HealthPoints& hp)
{
   return hp + num;
}

bool operator==(const HealthPoints& hp1, const HealthPoints& hp2)
{

   return (hp1.m_healthPoints == hp2.m_healthPoints);
}

bool operator!=(const HealthPoints& hp1, const HealthPoints& hp2)
{

   return !(hp1 == hp2);
}

bool operator>=(const HealthPoints& hp1, const HealthPoints& hp2)
{

   return !(hp1.m_healthPoints < hp2.m_healthPoints);
}

bool operator>(const HealthPoints& hp1, const HealthPoints& hp2)
{

   return (hp1.m_healthPoints > hp2.m_healthPoints);
}

bool operator<=(const HealthPoints& hp1, const HealthPoints& hp2)
{

   return !(hp1.m_healthPoints > hp2.m_healthPoints);
}

bool operator<(const HealthPoints& hp1, const HealthPoints& hp2)
{

   return (hp1.m_healthPoints < hp2.m_healthPoints);
}

std::ostream& operator<<(std::ostream& os, const HealthPoints& hp)
{
   return os << hp.m_healthPoints << "(" << hp.m_MAXHP << ")";
}