// -*- C++ -*-
/*

Copyright 2005 Manuel Baptista

This file is part of cat++

cat++ is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

cat++ is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/
//test_field.C

#include <iomanip>
#include <cat/cat.h>

using namespace cat;
using namespace std;

void test_et();
void test_copy();
void test_tvector();
void test_array();
void test_array_tvector();
void test_cross();


int main()
{
	test_et();
	//test_copy();
  //test_tvector();
  //test_array();
  //test_array_tvector();
  test_cross();
  return 0;
}

void test_et()
{
	int n=5000000;
	cat::Array<double,1> a(n);
	cat::Array<double,1> b(n);
	cat::Array<double,1> c(n);
	cat::Array<double,1> d(n);
	a=1;
	b=2;
	c=3;
	int t0=clock();
	d=a+b*(c*3.);
	cout << (clock()-t0)/1000. << endl;
};


void test_tvector()
{
  cout << "Testing tvector ..." << endl;
  Tvector<double,1> a(1);
  Tvector<double,3> d(1,2,3);
  Tvector<complex<double>,3> b(1,2,3),c(b);
  cout << a << endl;
  cout << b << endl;
  cout << c << endl;
  cout << dot_product(b,d) << endl;
  cout << norm_sq(d) << endl;
  cout << endl;
}


void test_array()
{
  cout << "Testing array ..." << endl;
  Array<double,3> a(2,2,2);
  a=5;
  cout << a << endl;
  
  cout << endl;
  Array<double,3> & b(a);
  cout << b << endl;
  cout << endl;

  b=1;
  cout << a << endl;
  cout << endl;
  cout << b << endl;
  cout << endl;
  

  Array<double,3> c(a);
  b=2;
  cout << a << endl;
  cout << endl;
  cout << b << endl;
  cout << endl;
  cout << c << endl;
  cout << endl;

 
  //cout << a.num_references() << endl;

  for (int i=0;i<1000000;++i)
    c+=a;

  cout << c << endl;
  cout << endl;


}


void test_array_tvector()
{

  cout << "Testing Array<tvector> ..." << endl;

#if 0
  Array<Tvector<double,3>,3> tt(2,2,2);

  tt=Tvector<double,3>(5,6,7);

  cout << tt << endl;
  cout << endl;
  
  
  Array<Tvector<complex<double>,3>,3> ttt(tt.shape());

  ttt=Tvector<complex<double>,3>(complex<double>(5,1));

  cout << norm_sq(ttt) << endl;
#endif
    
#if 0

  cout << "create from extract" << endl;

  Array<double,3> stt(tt[1]);
  
  cout << stt << endl;
  
  stt=1;

  cout << tt << endl;

  tt[1]=2;
  
  cout << stt << endl;

  cout << endl;
   
#endif



//testing copy constructor
 
 
 
 //Array<Tvector<double,3>,3> ooo(Tvector<int,3>(2,2,2),Tvector<double,3>(1,2,3));
 
 


//testing copy constructor
#if 0
  Array<Tvector<double,3>,3> ooo(2,2,2);
 ooo=Tvector<double,3>(1.1,2.2,3.3);
 
   cout << ooo << endl;
    Array<Tvector<double,3>,3> ccc(ooo);
    cout << ccc << endl;
    ccc=Tvector<double,3>(4,5,6);
    cout << ccc << endl;
    cout << ooo << endl;
#endif  
#if 0
//testing copy constructor on extracted value
    //Array<double,3> oooo(ooo.shape());
    //oooo=ooo[1];
    Array<double,3> ooo_comp_copy(ooo[1]);
    cout << setprecision(20) << scientific << ooo_comp_copy <<endl;
    cout << ooo <<endl;
    ooo_comp_copy=3;
    cout << ooo_comp_copy <<endl;
    cout << ooo <<endl;
#endif
	
//testing operators

#if 0
  ttt=ttt+tt;

  cout << ttt << endl;
  
  
  
  cout << "cross r c tv " << cross_product(Tvector<double,3>(1,2,3),Tvector<complex<double>,3>(1,-2,3)) << endl;
  
  
  Array<Tvector<double,3>,3> vr(3,3,3);
  vr=Tvector<double,3>(1,2,3);
  Array<Tvector<complex<double>,3>,3> vc(3,3,3);
  vc=Tvector<complex<double>,3>(complex<double>(1,1),complex<double>(-2,-2),complex<double>(3,3));
  
  cout << "cross r c a " << cross_product(vr,vc) << endl;
#endif 
  
  //testing reshape;
  #if 0
  ttt.reshape(Tvector<int,3>(1,1,1));
  
  ttt=1;
  
  cout << ttt << endl;
  
  ttt.reshape(Tvector<int,3>(3,3,2));
  
  ttt=2;
  
  cout << ttt << endl;
  #endif
  
}



#if 1

void test_cross()
{
	int n1=64;
	int n2=n1;
	int n3=n2;

	Array<Tvector<double,3>,3> a(n1,n2,n3),b(n1,n2,n3),cross(n1,n2,n3),cross_e(n1,n2,n3);
	for (int i=0;i<n1;++i)
		for (int j=0;j<n2;++j)
			for (int k=0;k<n3;++k)
				{	
					a(i,j,k)=Tvector<int,3>(i+j,i+k,j+k);
					b(i,j,k)=Tvector<int,3>(i-j,k-j,k-i);
					cross_e(i,j,k)=Tvector<int,3>((i+k)*(k-i)-(j+k)*(k-j),
										(j+k)*(i-j)-(i+j)*(k-i),
										(i+j)*(k-j)-(i+k)*(i-j));
				}

	cross=cross_product(a,b);

	for (int i=0;i<n1;++i)
                for (int j=0;j<n2;++j)
                        for (int k=0;k<n3;++k)
                                if (norm_sq(cross(i,j,k)-cross_e(i,j,k))!=0)
					{
						cout << i << " " << j << " " << k << endl;
						cout << cross(i,j,k) << " " << cross_e(i,j,k) << endl; 
						cout << "Failed." << endl;
						exit(0);
					}

	cout << "Success!" << endl;

	cross=cross_product(a,b)-cross_product(a,b);
}

#endif



void test_copy()
{
  cat::Array<double,2> a(9,9);
  cat::Array<double,2> b(5,5);
  
  for (int i=0;i<9;++i)
    for (int j=0;j<9;++j)
      a(i,j)=i+j;

  b=a;

    cout << a << "\n\n\n" << b << endl;

 //  for (int i=0;i<5;++i)
//     for (int j=0;j<5;++j)
//       cout << a(i,j) << " " << b(i,j) << endl;

}
