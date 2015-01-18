#ifndef ANALYTICALFINITESTRAINRHEOLOGYMATRIXDECOMPOSER_HPP
#define	ANALYTICALFINITESTRAINRHEOLOGYMATRIXDECOMPOSER_HPP

#include "libgcm/solvers/matrixDecomposers/RheologyMatrixDecomposer.hpp"
#include "libgcm/solvers/matrixDecomposers/AnalyticalRheologyMatrixDecomposer.hpp"
#include "libgcm/solvers/matrixDecomposers/NumericalRheologyMatrixDecomposer.hpp"


namespace gcm
{
    class AnalyticalFiniteStrainRheologyMatrixDecomposer: public RheologyMatrixDecomposer
    {
        public:
            AnalyticalFiniteStrainRheologyMatrixDecomposer();
            ~AnalyticalFiniteStrainRheologyMatrixDecomposer();
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
};

#endif	/* ANALYTICALFINITESTRAINRHEOLOGYMATRIXDECOMPOSER_HPP */

