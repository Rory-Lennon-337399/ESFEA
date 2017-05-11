
#pragma once

class SJVec2s
{
public:

   SJVec2s();
   SJVec2s(const short v[2]);
   SJVec2s(short x, short y);
   
   long						dot(const SJVec2s &v) const;
   const short*			get_value() const;
   void						get_value(short &x, short &y) const;
   void						negate();
   SJVec2s&					set_value(const short v[2]);
   SJVec2s&					set_value(short x, short y);
   short&					operator [](int i);
   const short&			operator [](int i) const;
   SJVec2s&					operator *=(int d);
   SJVec2s&					operator *=(double d);
   SJVec2s&					operator /=(int d);
   SJVec2s&					operator /=(double d);
   SJVec2s&					operator +=(const SJVec2s &u);
   SJVec2s&					operator -=(const SJVec2s &u);
   SJVec2s					operator -() const;
   
	short						get_x();
	short						get_y();

protected:

   short vector[2];
};
