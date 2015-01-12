#ifndef RheologyMatrixDecomposer_HPP
#define RheologyMatrixDecomposer_HPP 

#include "libgcm/rheologyModels/GcmMatrix.hpp"

#include <memory>

namespace gcm
{
    /**
     * Interface to implement for rheology matrix decomposer. Decomposer is supposed to be used
     * for matrix decomposition, i.e. to fill matricex \f$U\f$, \f$\Lambda\f$ and \f$U^{-1}\f$.
     */
    class RheologyMatrixDecomposer
    {
    public:
        /**
         * Computes decomposition for matrix in X direction.
         *
         * @param a Matrix to decompose.
         * @param u Matrix to store \f$U\f$
         * @param l Matrix to store \f$\Lambda\f$
         * @param u1 Matrix to store \f$U^{-1}\f$
         */
        virtual void decomposeX(const GcmMatrix& a, GcmMatrix& u, GcmMatrix& l, GcmMatrix& u1) const = 0;
        /**
         * Computes decomposition for matrix in Y direction.
         *
         * @param a Matrix to decompose.
         * @param u Matrix to store \f$U\f$
         * @param l Matrix to store \f$\Lambda\f$
         * @param u1 Matrix to store \f$U^{-1}\f$
         */
        virtual void decomposeY(const GcmMatrix& a, GcmMatrix& u, GcmMatrix& l, GcmMatrix& u1) const = 0;
        /**
         * Computes decomposition for matrix in Z direction.
         *
         * @param a Matrix to decompose.
         * @param u Matrix to store \f$U\f$
         * @param l Matrix to store \f$\Lambda\f$
         * @param u1 Matrix to store \f$U^{-1}\f$
         */
        virtual void decomposeZ(const GcmMatrix& a, GcmMatrix& u, GcmMatrix& l, GcmMatrix& u1) const = 0;
    };

    typedef std::shared_ptr<RheologyMatrixDecomposer> DecomposerPtr;
    
    template<typename T, typename...Args>
    std::shared_ptr<T> makeDecomposerPtr(Args...args)
    {
        return std::make_shared<T>(args...);
    }
};

#endif /* RheologyMatrixDecomposer_HPP */