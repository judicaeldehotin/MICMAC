%module mmv2
%{
  //includes to be able to compile
  #define SWIG_FILE_WITH_INIT
  #include <stdexcept>
  using std::runtime_error;
  #include "MMVII_all.h"
  #include "api/api_mmv2.h"
  #include <sstream>
  using namespace MMVII;
%}

//----------------------------------------------------------------------
#define ElSTDNS  std::
#define ElTmplSpecNull template <>
%include <std_string.i>
%include <std_vector.i>
%include <std_map.i>
%include <std_list.i>
%include <cpointer.i>
%include stl.i



//----------------------------------------------------------------------
//rename overloaded methods to avoid shadowing

//True is a reserved name in python3
%rename(_True) FBool::True;
%rename(_MayBe) FBool::MayBe;
%rename(_False) FBool::False;

//----------------------------------------------------------------------
//be able to use python exceptions
%include exception.i       
%exception {
  try {
    $action
  } catch(runtime_error & e) {
    SWIG_exception(SWIG_RuntimeError, e.what());
  } catch(...) {
    SWIG_exception(SWIG_RuntimeError, "Unknown exception");
  }
}

//----------------------------------------------------------------------
//things to ignore in next includes to be able to compile



//----------------------------------------------------------------------
//templates (has to be before %include "api/api_mmv2.h")
//used to make them usable as python lists
//first, expose templates
%include "MMVII_Ptxd.h"
%include "MMVII_Images.h"

//then, name templates implementations
%template(cIm2Du8) MMVII::cIm2D<tU_INT1>;

namespace std {
    %template(IntVector)    vector<int>;
    %template(DoubleVector) vector<double>;
    %template(FloatVector)  vector<float>;
    %template(StringVector) vector<string>;
    
}
 

//----------------------------------------------------------------------
//classes to export

%include "api/api_mmv2.h"


//----------------------------------------------------------------------

//check python version
%pythoncode %{
print("MicMac Python3 API")
mmv2_init();
%}


