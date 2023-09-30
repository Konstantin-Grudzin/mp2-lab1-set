// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s): BitField(s.BitField)
{
    MaxPower = s.GetMaxPower();
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
    MaxPower = bf.GetLength();
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
    if (Elem<0 && Elem>MaxPower)
        throw "Out of Range";
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem<0 && Elem>MaxPower)
        throw "Out of Range";
    return BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem<0 && Elem>MaxPower)
        throw "Out of Range";
    return BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    ~BitField;
    MaxPower = s.GetMaxPower();
    BitField = TBitField(MaxPower);
    BitField = BitField | s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (MaxPower != s.GetMaxPower())
        return 0;
    int minlen = min(MaxPower, s.GetMaxPower());
    for (int i = 0; i < minlen; ++i)
    {
        if (BitField.GetBit(i) != s.BitField.GetBit(i))
            return 0;
    }
    return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return !(*this==s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    MaxPower = max(MaxPower, s.GetMaxPower());
    TBitField A(MaxPower);
    A = BitField | s.BitField;
    BitField = A;
    return *this;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem<0 && Elem>MaxPower)
        throw "Out of Range";
    BitField.SetBit(Elem);
    return *this;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem<0 && Elem>MaxPower)
        throw "Out of Range";
    BitField.ClrBit(Elem);
    return *this;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    MaxPower = max(MaxPower, s.GetMaxPower());
    TBitField A(MaxPower);
    A = BitField & s.BitField;
    BitField = A;
    return *this;
}

TSet TSet::operator~(void) // дополнение
{
    BitField = ~BitField;
    return *this;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    int x = s.MaxPower;
    for (int i = 0; i <= x; ++i)
    {
        cout << s.IsMember(i) << " ";
    }
    return ostr;
}
