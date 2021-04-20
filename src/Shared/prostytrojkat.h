#ifndef ProstyTrojkat_H
#define ProstyTrojkat_H
#include "donarysowania.h"

using namespace std;


class ProstyTrojkat : public DoNarysowania
{
  public:
    ProstyTrojkat();
    virtual ~ProstyTrojkat();
	
protected:

private:
   unsigned short m_indeksyVertexow[3];
    float m_wspolrzedneVrtx[9];
};
//using spProstyTrojkat = shared_ptr<ProstyTrojkat>;
//using upProstyTrojkat = unique_ptr<ProstyTrojkat>;
#endif // ProstyTrojkat_H
