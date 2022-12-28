#ifndef EX3_HealthPoints_H
#define EX3_HealthPoints_H
#include <new>
#include <iostream>

const int START_HP = 100;

class HealthPoints
{
public:
  ~HealthPoints() = default;
  HealthPoints(const HealthPoints&) = default;
  HealthPoints(int healthPoints = START_HP);
  HealthPoints& operator=(const HealthPoints&) = default;

  HealthPoints operator+(const int num);
  HealthPoints operator-(const int num);
  HealthPoints& operator+=(const HealthPoints& hp);
  HealthPoints& operator+=(const int num);
  HealthPoints& operator-=(const HealthPoints& hp);
  HealthPoints& operator-=(const int num);
  friend HealthPoints operator+(const int num, HealthPoints& hp);

  //boolean operators
  friend bool operator==(const HealthPoints& hp1, const HealthPoints& hp2);
  friend bool operator!=(const HealthPoints& hp1, const HealthPoints& hp2);
  friend bool operator>=(const HealthPoints& hp1, const HealthPoints& hp2);
  friend bool operator>(const HealthPoints& hp1, const HealthPoints& hp2);
  friend bool operator<=(const HealthPoints& hp1, const HealthPoints& hp2);
  friend bool operator<(const HealthPoints& hp1, const HealthPoints& hp2);

  class InvalidArgument;
  friend std::ostream& operator<<(std::ostream&, const HealthPoints& hp);
  
private:
  int m_healthPoints;
  int m_MAXHP;
};

class HealthPoints::InvalidArgument
{
public:
  InvalidArgument() = default;
  ~InvalidArgument() = default;
  InvalidArgument(const InvalidArgument&) = default;
  InvalidArgument& operator=(const InvalidArgument&) = default;
    
  const char* what()
  {
      return "Failed: Invalid Argument on the Iterator";
  }
};

HealthPoints operator+(const int num, HealthPoints& hp);
std::ostream& operator<<(std::ostream& , const HealthPoints& hp);

//boolean operators
bool operator==(const HealthPoints& hp1, const HealthPoints& hp2);
bool operator!=(const HealthPoints& hp1, const HealthPoints& hp2);
bool operator>=(const HealthPoints& hp1, const HealthPoints& hp2);
bool operator>(const HealthPoints& hp1, const HealthPoints& hp2);
bool operator<=(const HealthPoints& hp1, const HealthPoints& hp2);
bool operator<(const HealthPoints& hp1, const HealthPoints& hp2);

#endif // EX3_HealthPoints_H
