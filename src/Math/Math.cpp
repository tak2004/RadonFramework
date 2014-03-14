#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Math/Math.hpp"

#include <math.h>
#include <limits>

using namespace RadonFramework::Math;
using namespace std;

template<> const float Math<float>::TWO_PI=(float)(8.0*atan(1.0));
template<> const double Math<double>::TWO_PI=8.0*atan(1.0);

template<> const float Math<float>::PI=(float)(4.0*atan(1.0));
template<> const double Math<double>::PI=4.0*atan(1.0);

template<> const float Math<float>::HALF_PI=(float)(2.0*atan(1.0));
template<> const double Math<double>::HALF_PI=2.0*atan(1.0);

template<> const float Math<float>::QUATER_PI=(float)(atan(1.0));
template<> const double Math<double>::QUATER_PI=atan(1.0);

template<> const float Math<float>::INV_QUATER_PI=(float)(1.0-(8.0*atan(1.0)));
template<> const double Math<double>::INV_QUATER_PI=1.0-(8.0*atan(1.0));

template<> const float Math<float>::INV_HALF_PI=(float)(1.0-(4.0*atan(1.0)));
template<> const double Math<double>::INV_HALF_PI=1.0-(4.0*atan(1.0));

template<> const float Math<float>::INV_PI=(float)(1.0-(2.0*atan(1.0)));
template<> const double Math<double>::INV_PI=1.0-(2.0*atan(1.0));

template<> const float Math<float>::INV_TWO_PI=(float)(1.0-(atan(1.0)));
template<> const double Math<double>::INV_TWO_PI=1.0-atan(1.0);

template<> const float Math<float>::DEG_TO_RAD=Math<float>::PI/180.0f;
template<> const double Math<double>::DEG_TO_RAD=Math<double>::PI/180.0;

template<> const float Math<float>::RAD_TO_DEG=180.0f/Math<float>::PI;
template<> const double Math<double>::RAD_TO_DEG=180.0/Math<double>::PI;

template<> const float Math<float>::EPSILION=numeric_limits<float>::epsilon();
template<> const double Math<double>::EPSILION=numeric_limits<double>::epsilon();

template<> const float Math<float>::INFINITY=numeric_limits<float>::infinity();
template<> const double Math<double>::INFINITY=numeric_limits<double>::infinity();

template<> const float Math<float>::NEG_INFINITY=-numeric_limits<float>::infinity();
template<> const double Math<double>::NEG_INFINITY=-numeric_limits<double>::infinity();

template<> const float Math<float>::QUITE_NAN=numeric_limits<float>::quiet_NaN();
template<> const double Math<double>::QUITE_NAN=numeric_limits<double>::quiet_NaN();

template<> const float Math<float>::SIGNALING_NAN=numeric_limits<float>::signaling_NaN();
template<> const double Math<double>::SIGNALING_NAN=numeric_limits<double>::signaling_NaN();

template<> RadonFramework::Core::Types::Bool Math<float>::WasInitialized=false;
template<> RadonFramework::Core::Types::Bool Math<double>::WasInitialized=false;
