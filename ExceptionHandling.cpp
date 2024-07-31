#pragma once
#include <iostream>
using namespace std;

class ExceptionHandling:public exception {
   const char * what () const throw () {
      return "Error: USER INPUT FAULT";
   }
};