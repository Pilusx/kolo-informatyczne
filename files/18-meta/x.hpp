// Na podstawie https://www.boost.org/doc/libs/1_70_0/libs/mpl/doc/tutorial/implementing.html
#include <iostream>
#include <typeinfo>
#include <boost/format.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal.hpp>
#include<boost/mpl/placeholders.hpp>

using boost::format;
namespace mpl = boost::mpl;
using namespace mpl::placeholders;

typedef mpl::vector_c<int,1,0,0,0,0,0,0> mass;
typedef mpl::vector_c<int,0,1,0,0,0,0,0> length; // or position 
typedef mpl::vector_c<int,0,0,1,0,0,0,0> mtime;
typedef mpl::vector_c<int,0,0,0,1,0,0,0> charge;
typedef mpl::vector_c<int,0,0,0,0,1,0,0> temperature;
typedef mpl::vector_c<int,0,0,0,0,0,1,0> intensity;
typedef mpl::vector_c<int,0,0,0,0,0,0,1> angle;
typedef mpl::vector_c<int,0,1,-1,0,0,0,0> velocity;     // l/t
typedef mpl::vector_c<int,0,1,-2,0,0,0,0> acceleration; // l/(t2)
typedef mpl::vector_c<int,1,1,-1,0,0,0,0> momentum;     // ml/t
typedef mpl::vector_c<int,1,1,-2,0,0,0,0> force;        // ml/(t2)

template <class T, class Dimensions>
struct quantity
{
    explicit quantity(T x)
       : m_value(x)
    {}
    
    template <class OtherDimensions>
    quantity(quantity<T,OtherDimensions> const& rhs)
    : m_value(rhs.value())
    {
        BOOST_STATIC_ASSERT((
        mpl::equal<Dimensions,OtherDimensions>::type::value
        ));
    }

    T value() const { return m_value; }
 private:
    T m_value;
};

template <class T, class D>
quantity<T,D>
operator+(quantity<T,D> x, quantity<T,D> y)
{
  return quantity<T,D>(x.value() + y.value());
}

template <class T, class D>
quantity<T,D>
operator-(quantity<T,D> x, quantity<T,D> y)
{
  return quantity<T,D>(x.value() - y.value());
}

template <class D1, class D2>
struct divide_dimensions
  : mpl::transform<D1,D2,mpl::minus<_1,_2> > // forwarding again
{};

template <class T, class D1, class D2>
quantity<T, typename divide_dimensions<D1,D2>::type>
operator/(quantity<T,D1> x, quantity<T,D2> y)
{
   return quantity<T, typename divide_dimensions<D1,D2>::type>(
      x.value() / y.value());
}

template<typename T>
void print(T t) {
    std::cout << typeid(T).name() << (format(" %1%") % t) << std::endl;
}

int main()
{
    print(13);
    quantity<float,length> len1( 1.0f );
    quantity<float,length> len2( 2.0f );
    len1 + len2;
    quantity<float, mass> m(5.0f);
    quantity<float, acceleration> a(13.0f);
    quantity<float, force> f(3);
    m = f/a;
    std::cout << "Hello, Wandbox!" << std::endl;
}
