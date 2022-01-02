#include "transformowalne.h"
#define DIG_2_RAD (G_PI / 180.0)
#define RAD_2_DIG (180.0 / G_PI)

Transformowalne::Transformowalne()
{
    //float sine = sin(0.5 * 0.0 * DIG_2_RAD);
    m_quat[0] = 0;
    m_quat[1] = 0;
    m_quat[2] = 0;
    m_quat[3] = 1.0;
	m_quatDiff[0] = 0.0;
    m_quatDiff[1] = 0.0;
    m_quatDiff[2] = 0.0;
    m_quatDiff[3] = 1.0;
    for(int i = 0; i < 4 ; i++)for(int j = 0; j < 4 ; j++)m_macierzObrotu[i][j] = 0.0;
	m_macierzObrotu[0][0] = 1.0;
	m_macierzObrotu[1][1] = 1.0;
	m_macierzObrotu[2][2] = 1.0;
	m_macierzObrotu[3][3] = 1.0;
    m_przesuniecie[0] = 0;
    m_przesuniecie[1] = 0;
    m_przesuniecie[2] = 0;
    
    przeznaczonyDoTransformacji = false;
}

Transformowalne::~Transformowalne()
{

}

const float* Transformowalne::QuatDiff()
{
    return m_quatDiff;
}
void Transformowalne::QuatDiff(float* q)
{
    memcpy(m_quatDiff,q,4*sizeof(float));
}

const float* Transformowalne::Quat()
{
    return m_quat;
}

void Transformowalne::Quat(float* q)
{
    memcpy(m_quat,q,4*sizeof(float));
}
/*
pf4 Transformowalne::ppMacierzObrotu()
{
    return m_macierzObrotu;
}
*/
void Transformowalne::MacierzObrotu(float* m)
{
    memcpy(m_macierzObrotu,m,16*sizeof(float));
    constexpr float macierzJednostkowa[] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
    jestObrot = false;
    for(short i = 0; i < 4 ; i++)for(short j = 0; j < 4 ; j++)jestObrot += macierzJednostkowa[i * 4 + j] != m_macierzObrotu[i][j];
    przeznaczonyDoTransformacji = jestObrot || jestPrzesuniecie;
}
const float* Transformowalne::MacierzObrotu()
{	
	return m_macierzObrotu[0];
}
const float* Transformowalne::Przesuniecie()
{
	return m_przesuniecie;
}
void Transformowalne::UstawPrzesuniecie(float* poz)
{
	for(short i = 0; i < 3; i++) m_przesuniecie[i] = poz[i];
    jestPrzesuniecie = false;
    for(short i = 0; i < 3 ; i++)jestPrzesuniecie += m_przesuniecie[i];
    przeznaczonyDoTransformacji = jestObrot || jestPrzesuniecie;
}
void Transformowalne::DodajPrzesuniecie(float* przes)
{
	jestPrzesuniecie = false;
    for(short i = 0; i < 3; i++) m_przesuniecie[i] += przes[i];
    for(short i = 0; i < 3 ; i++)jestPrzesuniecie += m_przesuniecie[i];
    przeznaczonyDoTransformacji = jestObrot || jestPrzesuniecie;
}
