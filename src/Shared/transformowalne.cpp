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
    m_pozycja[0] = 0;
    m_pozycja[1] = 0;
    m_pozycja[2] = 0;
}

Transformowalne::~Transformowalne()
{

}

float* Transformowalne::QuatDiff()
{
    return m_quatDiff;
}
void Transformowalne::QuatDiff(float* q)
{
    memcpy(m_quatDiff,q,4*sizeof(float));
}

float* Transformowalne::Quat()
{
    return m_quat;
}

void Transformowalne::Quat(float* q)
{
    memcpy(m_quat,q,4*sizeof(float));
}

pf4 Transformowalne::ppMacierzObrotu()
{
    return m_macierzObrotu;
/*    float macierz[4][4];
    float* adr1 = macierz[0];
    float** adr2 = &adr1;
    return adr2;*/
}

void Transformowalne::MacierzObrotu(float* m)
{
    memcpy(m_macierzObrotu,m,16*sizeof(float));
}
float* Transformowalne::MacierzObrotu()
{	
	return m_macierzObrotu[0];
}
float* Transformowalne::Pozycja()
{
	return m_pozycja;
}
void Transformowalne::UstawPozycje(float* poz)
{
	for(short i = 0; i < 3; i++) m_pozycja[i] = poz[i];
}
