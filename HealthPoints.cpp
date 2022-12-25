#include "HealthPoints.h"
#include <new>

HealthPoints::HealthPoints(int healthPoints):
 m_MAXHP(healthPoints)
{
    if(m_MAXHP<=0)
    {
        throw  InvalidArgument{};
    }
    this->m_healthPoints = healthPoints;
}    

HealthPoints& HealthPoints::operator+(const HealthPoints& hp){

 HealthPoints *temp;
 try{
    temp = new HealthPoints(hp.m_healthPoints + this->m_healthPoints);
 }
 catch(const std::bad_alloc& e){
    std::cerr<< e.what()<<std::endl;
    throw std::exception();
 }
 return  * temp;
}

HealthPoints& HealthPoints::operator-(const HealthPoints& hp){
 
 HealthPoints *temp;
 try{
    temp = new HealthPoints(hp.m_healthPoints - this->m_healthPoints);
 }
 catch(const std::bad_alloc& e){
    std::cerr<< e.what()<<std::endl;
    throw std::exception();
 }
 return  * temp;
}
HealthPoints& HealthPoints::operator+=(const HealthPoints& hp){

 if(this->m_healthPoints + hp.m_healthPoints >= this->m_MAXHP)
   {
    this->m_healthPoints = this->m_MAXHP;
   }
   else 
    this->m_healthPoints += hp.m_healthPoints;
   return *this;
}

HealthPoints& HealthPoints::operator-=(const HealthPoints& hp){

 if(this->m_healthPoints - hp.m_healthPoints <= 0)
   {
    this->m_healthPoints = 0;
   }
   else 
   this->m_healthPoints -=  hp.m_healthPoints;
   return *this;
}

bool operator==(const HealthPoints& hp1,const HealthPoints& hp2){

 return (hp1.m_healthPoints == hp2.m_healthPoints);
}

bool operator!=(const HealthPoints& hp1,const HealthPoints& hp2){

 return !(hp1 == hp2);   
}

bool operator>=(const HealthPoints& hp1,const HealthPoints& hp2){

 return !(hp1.m_healthPoints < hp2.m_healthPoints);
}

bool operator>(const HealthPoints& hp1,const HealthPoints& hp2){

 return (hp1.m_healthPoints > hp2.m_healthPoints);
}

bool operator<=(const HealthPoints& hp1,const HealthPoints& hp2){

 return !(hp1.m_healthPoints > hp2.m_healthPoints);
}

bool operator<(const HealthPoints& hp1,const HealthPoints& hp2){

 return (hp1.m_healthPoints < hp2.m_healthPoints);  
}
 
 std::ostream&  operator<<(std::ostream& os, const HealthPoints& hp){
  return os<<hp.m_healthPoints<<"("<<hp.m_MAXHP<<")";
 }