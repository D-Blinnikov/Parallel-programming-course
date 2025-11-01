// номер 8

// 1) _mm (SSE, 128 бит)
// 2) _pd (работа с double)
// 3) _and



// This program uses _mm_and_pd (bitwise AND for packed doubles) to apply
// a binary mask. It shows how SIMD intrinsics can be used 
// for vectorized logical operations on floating-point data.

// Two double values are stored in a 128-bit SSE register.
// The mask is created so that only the the first double 
// is preserved, while the upper 64 bits are zeroed out. 
// The _mm_and_pd instruction performs a bitwise AND
// between the vector and the mask, effectively clearing the upper double.

// The result demonstrates how bit-level manipulation can be done
// on multiple floating-point numbers simultaneously 
// within a single CPU instruction.


#include <iostream>
#include <immintrin.h>
using namespace std;

const double double1 = -2.0;
const double double2 = - 10.0;



int main() {
    // Initialize a 128-bit vector with two double values
    __m128d a = _mm_set_pd(double1, double2);

    // Create a mask that keeps only the lower double and clears the upper one
    __m128d mask = _mm_castsi128_pd(_mm_set_epi64x(0, -1)); 

    // Perform bitwise AND to keep only the lower double value
    __m128d res = _mm_and_pd(a, mask);

    // Allocate an aligned array to store the resulting two doubles
    alignas(16) double out[2];
    _mm_store_pd(out, res);

    cout << "After _mm_and_pd: " << out[0] << ", " << out[1] << endl;

    return 0;
}


