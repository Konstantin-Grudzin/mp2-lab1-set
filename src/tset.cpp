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
    if (Elem<0 && Elem>=MaxPower)
        throw "Out of Range";
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem<0 && Elem>=MaxPower)
        throw "Out of Range";
    return BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem<0 && Elem>=MaxPower)
        throw "Out of Range";
    return BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    MaxPower = s.GetMaxPower();
    BitField = TBitField(MaxPower);
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (MaxPower != s.GetMaxPower())
        return 0;
    return BitField==s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return !(*this==s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet A(max(MaxPower, s.GetMaxPower()));
    A.BitField = BitField | s.BitField;
    return A;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem<0 && Elem>MaxPower)
        throw "Out of Range";
    TSet A(*this);
    A.BitField.SetBit(Elem);
    return A;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem<0 && Elem>MaxPower)
        throw "Out of Range";
    TSet A(*this);
    A.BitField.ClrBit(Elem);
    return A;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet A(max(MaxPower, s.GetMaxPower()));
    A.BitField = BitField & s.BitField;
    return A;
}

TSet TSet::operator~(void) // дополнение
{
    //из реализации в битовых полях предполагается, 
    //что задействуются только действительные элементы
    TSet A(MaxPower);
    A.BitField = ~BitField;
    return A;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    const int x = s.MaxPower;
    for (int i = 0; i < x; ++i)
    {
        int val; istr >> val;
        s.InsElem(val);
    }
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    const int x = s.MaxPower;
    for (int i = 0; i < x; ++i)
    {
        if(s.IsMember(i))
            ostr << i << " ";
    }
    return ostr;
}
