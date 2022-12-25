#ifndef EX3_HealthPoints_H
#define EX3_HealthPoints_H
#include <new>
#include <iostream>
const int START_HP = 100; 

class HealthPoints{
    public:
    
    ~HealthPoints() = default;
    HealthPoints& operator=(const HealthPoints& ) = default;
    HealthPoints(const HealthPoints& ) = default; 
    HealthPoints(int healthPoints = START_HP);

    // :אופרטורים אריתמטיים
    HealthPoints& operator+(const HealthPoints& hp);
    HealthPoints& operator-(const HealthPoints& hp);
    HealthPoints& operator+=(const HealthPoints& hp);
    HealthPoints& operator-=(const HealthPoints& hp);
    
     // :אופרטורים בוליאניים
    friend bool operator==(const HealthPoints& hp1,const HealthPoints& hp2);
    friend bool operator!=(const HealthPoints& hp1,const HealthPoints& hp2);
    friend bool operator>=(const HealthPoints& hp1,const HealthPoints& hp2);
    friend bool operator>(const HealthPoints& hp1,const HealthPoints& hp2);
    friend bool operator<=(const HealthPoints& hp1,const HealthPoints& hp2);
    friend bool operator<(const HealthPoints& hp1,const HealthPoints& hp2);
  
    class InvalidArgument{};  
    // :אופרטור הדפסה
    friend std::ostream&  operator<<(std::ostream&, const HealthPoints& hp);
    // if(healthPoints<=0)
    // {
    //     cout<<HealthPoints::InvalidArgumet&
    // }
    // 
    private:
      int m_healthPoints ;
      const int m_MAXHP;
};

   std::ostream&  operator<<(std::ostream&, const HealthPoints& hp);
 // :אופרטורים בוליאניים
    bool operator==(const HealthPoints& hp1,const HealthPoints& hp2);
    bool operator!=(const HealthPoints& hp1,const HealthPoints& hp2);
    bool operator>=(const HealthPoints& hp1,const HealthPoints& hp2);
    bool operator>(const HealthPoints& hp1,const HealthPoints& hp2);
    bool operator<=(const HealthPoints& hp1,const HealthPoints& hp2);
    bool operator<(const HealthPoints& hp1,const HealthPoints& hp2);

#endif // EX3_HealthPoints_H
