#pragma once
#include <vector>
#include <memory>
#include <cassert>
#include <iostream>

template <typename T>
class cfdVector
{
private:
    int dim;
    std::unique_ptr<std::vector<T>> vecPtr;

public:
    cfdVector(int dim); // 初始化

    cfdVector(const cfdVector &other) : dim(other.dim), vecPtr(new std::vector<double>(*other.vecPtr)) {} // 自定义拷贝构造函数
    T &operator[](int i);                                                                                 // 取值
    const T &operator[](int i) const;                                                                     //
    void setValue(std::vector<T> &&data);                                                                 // 赋值
    int d()const { return this->dim; } ;                                                                        // 取得维度

    cfdVector<T> &operator=(const cfdVector<T> &other); // 复制

    template <typename T1>
    friend std::ostream &operator<<(std::ostream &os, const cfdVector<T1> &vec); // 打印

    template <typename T1>
    friend T1 dot(cfdVector<T1> &v1, cfdVector<T1> &v2); // 向量点乘

    template<typename T1>
    friend cfdVector<T1> cross(const cfdVector<T1>&v1, const cfdVector<T1> &v2);    // 向量叉乘

    template <typename T1, typename T2>
    friend cfdVector<T1> operator*(const cfdVector<T1> &v, const T2 &s); // 标量乘以向量

    template <typename T1, typename T2>
    friend cfdVector<T1> operator*(const T2 &s, const cfdVector<T1> &v); // 标量乘以向量

    template <typename T1>
    friend cfdVector<T1> operator+(cfdVector<T1> &v1, cfdVector<T1> &v2); // 向量相加

    template <typename T1>
    friend cfdVector<T1> operator-(cfdVector<T1> &v1, cfdVector<T1> &v2); // 向量相减
};

template <typename T>
cfdVector<T>::cfdVector(int dim)
{
    this->dim = dim;
    this->vecPtr = std::make_unique<std::vector<T>>(dim);
}

template <typename T>
T &cfdVector<T>::operator[](int i)
{
    return (*vecPtr)[i];
}

template <typename T>
const T &cfdVector<T>::operator[](int i) const
{
    return (*vecPtr)[i];
}

template <typename T>
void cfdVector<T>::setValue(std::vector<T> &&data)
{
    assert(data.size() == this->dim);
    vecPtr = std::make_unique<std::vector<T>>(data);
}

template <typename T>
cfdVector<T> &cfdVector<T>::operator=(const cfdVector<T> &other)
{
    if (this != &other)
    { // 自我赋值检查
        dim = other.dim;
        vecPtr.reset(new std::vector<double>(*other.vecPtr));
    }
    return *this;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const cfdVector<T> &vec)
{
    for (int i = 0; i < vec.dim - 1; i++)
    {
        os << (*vec.vecPtr)[i] << ", ";
    }
    os << (*vec.vecPtr)[vec.dim - 1];
    return os;
}

template <typename T1>
inline T1 dot(cfdVector<T1> &v1, cfdVector<T1> &v2)
{
    assert(v1.d() == v2.d());
    T1 res = (T1)0;
    for (int i = 0; i < v1.d(); i++)
    {
        res += v1[i] * v2[i];
    }
    return res;
}

template <typename T1>
inline cfdVector<T1> cross(const cfdVector<T1> &v1, const cfdVector<T1> &v2)
{
    assert((v1.dim == v2.dim) &&(v1.dim == 3));
    auto res = cfdVector<T1>(v1.dim);
    res[0] = v1[1]*v2[2] - v1[2]*v2[1];
    res[1] = -(v1[0]*v2[2]-v1[2]*v2[0]);
    res[2] = v1[0]*v2[1] - v1[1]*v2[0];
    return res;
}

template <typename T1, typename T2>
inline cfdVector<T1> operator*(const cfdVector<T1> &v, const T2 &s)
{
    auto res = v;
    for (int i = 0; i < res.dim; i++)
    {
        res[i] *= s;
    }
    return res;
}

template <typename T1, typename T2>
inline cfdVector<T1> operator*(const T2 &s, const cfdVector<T1> &v)
{
    auto res = v;
    for (int i = 0; i < res.dim; i++)
    {
        res[i] *= s;
    }
    return res;
}

template <typename T1>
inline cfdVector<T1> operator+(cfdVector<T1> &v1, cfdVector<T1> &v2)
{
    assert(v1.dim == v2.dim);
    auto res = cfdVector<T1>(v1.dim);
    for(int i =0; i < v1.dim; i++){
        res[i] = v1[i] + v2[i];
    }
    return res;
}

template <typename T1>
inline cfdVector<T1> operator-(cfdVector<T1> &v1, cfdVector<T1> &v2)
{
    assert(v1.dim == v2.dim);
    auto res = cfdVector<T1>(v1.dim);
    for(int i =0; i < v1.dim; i++){
        res[i] = v1[i] - v2[i];
    }
    return res;
}
