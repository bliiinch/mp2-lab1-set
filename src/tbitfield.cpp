// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    BitLen = len;
    TELEM s = sizeof(TELEM) * 8;
    MemLen = (len + s - 1) / s;
    pMem=new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }

}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    if (pMem != nullptr)
        delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n<0 || n>BitLen) {
        throw "ERROR";
    }

    return n/ (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n<0 || n>BitLen) {
        throw "ERROR";
    }
    return 1<<n;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n<0 || n>BitLen) {
        throw "ERROR";
    }

    int index = GetMemIndex(n);
    int number_bit = n - (n / (sizeof(TELEM) * 8) * (sizeof(TELEM) * 8));
    pMem[index] |= GetMemMask(number_bit);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n<0 || n>BitLen) {
        throw "ERROR";
    }

    int index = GetMemIndex(n);
    int number_bit = n - (n / (sizeof(TELEM) * 8) * (sizeof(TELEM) * 8));
    pMem[index] &= GetMemMask(number_bit);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n<0 || n>BitLen) {
        throw "ERROR";
    }
    int index = GetMemIndex(n);
    int number_bit = n - (n / (sizeof(TELEM) * 8) * (sizeof(TELEM) * 8));
    return pMem[index] & GetMemMask(number_bit);

}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this != &bf)
    {
        if (pMem != nullptr)
            delete[] pMem;

        BitLen = bf.BitLen;
        MemLen = bf.MemLen;              
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++) {
            pMem[i] = bf.pMem[i];
        }
            
    }

    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (this == &bf) return 1;

    if (BitLen != bf.BitLen || MemLen != bf.MemLen)
    {
        return 0;
    }

    for (int i = 0; i < MemLen; i++)
    {
        if (pMem[i] != bf.pMem[i])
        {
            return 0;
        }
    }
 
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (this == &bf) return 0;

    if (BitLen != bf.BitLen || MemLen != bf.MemLen)
    {
        return 1;
    }

    for (int i = 0; i < MemLen; i++)
    {
        if (pMem[i] != bf.pMem[i])
        {
            return 1;
        }
    }
  
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    return FAKE_BITFIELD;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    return FAKE_BITFIELD;
}

TBitField TBitField::operator~(void) // отрицание
{
    return FAKE_BITFIELD;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    return ostr;
}
