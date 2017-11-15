// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower=mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.MaxPower)
{
	MaxPower=s.MaxPower;
	BitField=s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower=bf.GetLength();
	BitField=bf;
}

TSet::operator TBitField()
{
  return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
   int res=0;
   res=BitField.GetBit(Elem);
	return res;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower=s.MaxPower;
	BitField=s.BitField; 
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	int res=1;
	if (BitField!=s.BitField) res=0;
	return res;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	int res=0;
	if (BitField!=s.BitField) res=1;
	return res;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet set(BitField|s.BitField);
	return set;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
  	InsElem(Elem);
	return *this;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	DelElem(Elem);
	return TSet(0);
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet set(BitField&s.BitField);
	return set;
}

TSet TSet::operator~(void) // дополнение
{
	BitField=~BitField;
	return *this;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	return ostr;
}
