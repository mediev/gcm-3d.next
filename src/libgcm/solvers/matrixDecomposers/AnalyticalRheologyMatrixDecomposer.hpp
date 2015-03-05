#ifndef ANALYTICAL_RHEOLOGY_MATRIX_DECOMPOSER_HPP
#define ANALYTICAL_RHEOLOGY_MATRIX_DECOMPOSER_HPP

#include "libgcm/solvers/matrixDecomposers/RheologyMatrixDecomposer.hpp"
#include "libgcm/util/Math.hpp"

#include "libgcm/util/Exception.hpp"
#include <assert.h>

namespace gcm
{
    class AnalyticalRheologyMatrixDecomposer : public RheologyMatrixDecomposer
    {
		private:
			void findNonZeroSolution(double **M, double *x) const;
			void findNonZeroSolution(double **M, double *x, double *y) const;
			void findEigenVec(double *eigenVec,
						double l, const GcmMatrix &A, int stage) const;
			void findEigenVec(double *eigenVec1, double *eigenVec2,
						double l, const GcmMatrix &A, int stage) const;
			void findRoots(const GcmMatrix &A, int stage, 
						double& r1, double& r2, double& r3, bool& isMultiple) const;
        public:
            AnalyticalRheologyMatrixDecomposer();
            ~AnalyticalRheologyMatrixDecomposer();
            /**
             * Computes decomposition for matrix in X direction.
             *
             * @param a Matrix to decompose.
             * @param u Matrix to store \f$U\f$
             * @param l Matrix to store \f$\Lambda\f$
             * @param u1 Matrix to store \f$U^{-1}\f$
             */
            void decomposeX(const GcmMatrix& a, GcmMatrix& u, GcmMatrix& l, GcmMatrix& u1) const;
            /**
             * Computes decomposition for matrix in Y direction.
             *
             * @param a Matrix to decompose.
             * @param u Matrix to store \f$U\f$
             * @param l Matrix to store \f$\Lambda\f$
             * @param u1 Matrix to store \f$U^{-1}\f$
             */
            void decomposeY(const GcmMatrix& a, GcmMatrix& u, GcmMatrix& l, GcmMatrix& u1) const;
            /**
             * Computes decomposition for matrix in Z direction.
             *
             * @param a Matrix to decompose.
             * @param u Matrix to store \f$U\f$
             * @param l Matrix to store \f$\Lambda\f$
             * @param u1 Matrix to store \f$U^{-1}\f$
             */
            void decomposeZ(const GcmMatrix& a, GcmMatrix& u, GcmMatrix& l, GcmMatrix& u1) const;
    };
}

#endif /* ANALYTICAL_RHEOLOGY_MATRIX_DECOMPOSER_HPP */
