/**
 * @file core/cereal/array_wrapper.hpp
 * @author Omar Shrit
 *
 * Implementation of an array wrapper.
 *
 * This implementation will allows to serilize array easily using cereal.
 *
 * mlpack is free software; you may redistribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */
#ifndef MLPACK_CORE_CEREAL_ARRAY_WRAPPER_HPP
#define MLPACK_CORE_CEREAL_ARRAY_WRAPPER_HPP

#include <cereal/archives/binary.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>

namespace cereal {

template<class T>
class ArrayWrapper
{
/* This file add make_array functionality to cereal
 * This functionality exist only in boost::serialization.
 * Most part of this code are copied from ArrayWrapper in boost::serialization
 */
public:

  ArrayWrapper(T* t, std::size_t s) :
      arrayAddress(t),
      arraySize(s)
  {}

  /* default implementation
  * Cereal does not require to split member, it can do that internally
  * If this is the case we can not implement optimized version, since
  * the only possible one is optimized.
  * Some verification needed...
  * default implementation
  */
  template<class Archive>
  void serialize(Archive& ar)
  {
   // default implemention does the loop
    size_t c = count();
    T* t = address();
    while(0 < c--)
          ar & cereal::make_nvp("item", *t++);
  }

  T* address() const
  {
    return arrayAddress;
  }

  size_t count() const
  {
    return arraySize;
  }

private:
  ArrayWrapper& operator=(ArrayWrapper rhs);
  // note: I would like to make the copy constructor private but this breaks
  // make_array.  So I make make_array a friend
  template<class Tx, class S>
  friend const cereal::ArrayWrapper<Tx> make_array(Tx* t, S s);

  T* arrayAddress;
  const size_t arraySize;
};

template<class T, class S>
inline
ArrayWrapper< T > make_array(T* t, S s)
{
  ArrayWrapper< T > a(t, s);
  return a;
}

} // end namespace cereal

#endif //CEREAL_ARRAY_WRAPPER_HPP
