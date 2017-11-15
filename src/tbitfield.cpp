// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

#define BITS_IN_ONE_MEM (sizeof(TELEM) * 8)

TBitField::TBitField(int len)
{  
  if (len < 0)
    throw "negative length";
  BitLen=len;
  
  MemLen= (len +  BITS_IN_ONE_MEM - 1) / BITS_IN_ONE_MEM;

  pMem=new TELEM[MemLen];
	for (int i=0;i<MemLen;i++)
		pMem[i]=0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen=bf.BitLen;
	MemLen=bf.MemLen;
	pMem=new TELEM[MemLen];
	for (int i=0;i<MemLen;i++)
		pMem[i]=bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	int res=n/BITS_IN_ONE_MEM;
	return res;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM res;
	res=1<<(n-GetMemIndex(n)*BITS_IN_ONE_MEM);
	return res;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0)
		throw "negative index";
	if (n > BitLen)
		throw "too large index";
	pMem[GetMemIndex(n)]=pMem[GetMemIndex(n)]|GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0)
		throw "negative index";
	if (n > BitLen)
		throw "too large index";
	pMem[GetMemIndex(n)]=pMem[GetMemIndex(n)]&(~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0)
		throw "negative index";
	if (n > BitLen)
		throw "too large index";
	
	TELEM res = pMem[GetMemIndex(n)] & GetMemMask(n);
	if (res!=0) return 1;
	else return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
 	BitLen=bf.BitLen;
	MemLen=bf.MemLen;
	for (int i=0;i<MemLen;i++)
		pMem[i]=bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (BitLen!=bf.BitLen) 
		return 0;
  int res=1;
  for (int i=0;i<MemLen;i++)
		if (pMem[i]!=bf.pMem[i]) res=0;
	return res;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len=0,mlen=0;
	if (BitLen<bf.BitLen) len=bf.BitLen;
		else len=BitLen;
	if (MemLen>bf.MemLen) mlen=bf.MemLen;
		else mlen=MemLen;
	TBitField res(len);
	for (int i=0; i<mlen; i++)
		res.pMem[i]=pMem[i]|bf.pMem[i];
	if (BitLen>bf.BitLen) 
	{
		for (int i=mlen; i<res.MemLen; i++)
			res.pMem[i]=pMem[i];
	}
		else
		{
			for (int i=mlen; i<res.MemLen; i++)
				res.pMem[i]=bf.pMem[i];
		}
	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len=0;
	if (BitLen>bf.BitLen) len=bf.BitLen;
		else len=BitLen;
	TBitField res(len);
	for(int i=0;i<res.MemLen;i++)
		res.pMem[i]=pMem[i]&bf.pMem[i];
	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(BitLen);
	for(int i=0;i<res.BitLen;i++)
		res.SetBit(i);
	for(int i=0;i<MemLen;i++)
		pMem[i]=~pMem[i];
	*this=*this&res;
	return *this;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
     for (int i = 0; i < bf.BitLen; i++)
      istr >> bf.pMem[i];
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  for (int i = 0; i < bf.BitLen; i++)
	cout << "{" << bf.pMem[i] << "}\n";
  return ostr;
}
