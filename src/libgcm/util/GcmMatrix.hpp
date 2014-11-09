#ifndef _GCM_GcmMatrix_H
#define _GCM_GcmMatrix_H  1

#include <iostream>
#include <math.h>
#include <string.h>
#include <assert.h>

#include "libgcm/Logging.hpp"

#define GCM_MATRIX_SIZE 9

namespace gcm {

    class GcmMatrix {
    public:
        GcmMatrix();
        ~GcmMatrix();
        
        // Basic operators
        
        // Assign matrix
        GcmMatrix& operator=(const GcmMatrix &A);
        // Check for matrix equality
        bool operator==(const GcmMatrix &A) const;
        bool operator!=(const GcmMatrix &A) const;
        // Get elements - read-write and read-only options
        gcm::real& operator()(uint i, uint j);
        gcm::real get(uint i, uint j) const;
        // Matrix operations
        GcmMatrix operator+(const GcmMatrix &A) const;
        GcmMatrix operator-(const GcmMatrix &A) const;
        GcmMatrix operator*(const GcmMatrix &A) const;
        GcmMatrix operator/(const GcmMatrix &A) const;
        // Multiply and divide matrix by constant
        GcmMatrix operator*(const gcm::real &a) const;
        GcmMatrix operator/(const gcm::real &a) const;
        
        // Divide two matrixes element by element (e.g. c[i][j] = a[i][j] / b[i][j])
        GcmMatrix operator%(const GcmMatrix &A) const;
        // Get inverse matrix
        GcmMatrix inv() const;

        // TODO: do we really need these functions?
        // They are meant to reduce the number of code lines around matrixes.
        // Recheck if we really use them now.
        
        // Set all elements to zero
        void clear();
        // Create unit matrix
        void createE();
        // Set matrix column to certain values
        void setColumn(gcm::real *clmn, int num);

    protected:
        // Real matrix data lives here
        gcm::real p[GCM_MATRIX_SIZE][GCM_MATRIX_SIZE];
        
    private:
        USE_LOGGER;
    };
}

namespace std {

    inline std::ostream& operator<<(std::ostream &os, const gcm::GcmMatrix &matrix) {
        for (int r = 0; r < GCM_MATRIX_SIZE; r++) {
            for (int c = 0; c < GCM_MATRIX_SIZE; c++)
                os << matrix.p[r][c] << " ";
            os << std::endl;
        }
        return os;
    };
}

#endif