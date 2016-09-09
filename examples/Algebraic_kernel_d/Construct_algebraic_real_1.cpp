// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.6-branch/Algebraic_kernel_d/examples/Algebraic_kernel_d/Construct_algebraic_real_1.cpp $
// $Id: Construct_algebraic_real_1.cpp 53386 2009-12-11 11:22:11Z penarand $

#include <CGAL/Algebraic_kernel_d_1_RS_Gmpz.h>
#include <vector>

typedef CGAL::Algebraic_kernel_d_1_RS_Gmpz              AK;
typedef AK::Polynomial_1                                Polynomial_1;
typedef AK::Algebraic_real_1                            Algebraic_real_1;
typedef AK::Coefficient                                 Coefficient;
typedef AK::Bound                                       Bound;
typedef AK::Multiplicity_type                           Multiplicity_type;

int main(){
  AK ak; // an object of Algebraic_kernel_d_1_RS_Gmpz
  AK::Construct_algebraic_real_1 construct_algreal_1 = ak.construct_algebraic_real_1_object();

  std::cout << "Construct from int         : " << construct_algreal_1(int(2)) << "\n";
  std::cout << "Construct from Coefficient : " << construct_algreal_1(Coefficient(2)) << "\n";
  std::cout << "Construct from Bound       : " << construct_algreal_1(Bound(2)) << "\n\n";

  Polynomial_1 x = CGAL::shift(AK::Polynomial_1(1),1); // the monomial x
  std::cout << "Construct by index              : "
            << construct_algreal_1(x*x-2,1) << "\n"
            << to_double(construct_algreal_1(x*x-2,1)) << "\n";
  std::cout << "Construct by isolating interval : "
            << construct_algreal_1(x*x-2,Bound(0),Bound(2)) << "\n"
            << to_double(construct_algreal_1(x*x-2,Bound(0),Bound(2))) << "\n\n";

  return 0;
}