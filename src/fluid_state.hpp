#pragma once 
#include <math.h>
#include "property.hpp"
#include "cfdVector.hpp"

template<typename T>
T E(const cfdVector<T> &V);

template<typename T>
T H(const cfdVector<T> &V);

template<typename T>
cfdVector<T> convU_V(const cfdVector<T> &U);

template<typename T>
cfdVector<T> convV_U(const cfdVector<T> &V);

template<typename T>
T speed_sound(const T&P, const T &rho);


template<typename T>
T E(const cfdVector<T> &V){
    T e = (T)0;
    auto rho = V[0];
    auto u = V[1];
    auto v = V[2];
    auto P = V[3];
    e = P/((Gamma - 1)*rho) + 0.5*(pow(u, 2) + pow(v, 2));
    return e;
}

template <typename T>
inline T H(const cfdVector<T> &V)
{
    T res = (T)0.0;
    auto rho = V[0]; auto P = V[3];
    return E(V) + P/rho;
}

template <typename T>
inline cfdVector<T> convU_V(const cfdVector<T> &U)
{
    auto V = cfdVector<T>(U.d());
    auto rho = U[0];
    auto rho_u = U[1];
    auto rho_v = U[2];
    auto rho_e = U[3];

    V[0] = rho;
    V[1] = rho_u /rho;
    V[2] = rho_v / rho;
    V[3] = (Gamma - 1)*(rho_e - 0.5*rho*(pow(V[1], 2) + pow(V[2], 2)));

    return V;
}

template <typename T>
inline cfdVector<T> convV_U(const cfdVector<T> &V)
{
    auto U = cfdVector<T>(V.d());
    
    auto rho = V[0];
    auto u = V[1];
    auto v = V[2];
    auto P = V[3];

    U[0] = rho;
    U[1] = rho*u;
    U[2] = rho*v;
    U[3] = rho*E(V);
    return U;
}

template <typename T>
inline T speed_sound(const T &P, const T &rho)
{
    return sqrt((Gamma*P)/rho);
}
